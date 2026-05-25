"""
Módulo: geometry.py
Responsabilidad:
    Realizar correcciones geométricas en las imágenes de formularios.
    Incluye detección de bordes, detección del documento,
    corrección de perspectiva y corrección de rotación/inclinación.

Entradas:
    - Imagen preprocesada (escala de grises o binaria)
Salidas:
    - Imagen geométricamente corregida
Dependencias:
    - cv2 (opencv-python)
    - numpy
    - app.config
"""

import cv2
import numpy as np
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from app.config import (
    CANNY_THRESHOLD_LOW,
    CANNY_THRESHOLD_HIGH,
    POLYGON_APPROX_FACTOR,
    MIN_DOCUMENT_AREA_RATIO,
    MAX_ROTATION_ANGLE
)


def detect_edges(image: np.ndarray) -> np.ndarray:
    """
    Detecta bordes en una imagen usando el algoritmo de Canny.

    Canny es un detector de bordes multi-etapa que produce
    bordes delgados y bien definidos, ideal para detectar
    los límites del formulario.

    Parámetros:
        image (np.ndarray): Imagen en escala de grises

    Retorna:
        np.ndarray: Imagen binaria de bordes detectados
    """
    # Asegurar escala de grises
    if len(image.shape) > 2:
        image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Aplicar desenfoque gaussiano previo para reducir ruido
    # Esto previene la detección de bordes falsos por ruido
    blurred = cv2.GaussianBlur(image, (5, 5), 0)

    # Aplicar detector de bordes Canny
    # threshold_low: bordes débiles por debajo se descartan
    # threshold_high: bordes fuertes por encima se aceptan siempre
    # Bordes entre ambos umbrales se aceptan si están conectados a bordes fuertes
    edges = cv2.Canny(
        blurred,
        CANNY_THRESHOLD_LOW,
        CANNY_THRESHOLD_HIGH
    )

    return edges


def detect_document(image: np.ndarray) -> np.ndarray:
    """
    Detecta los bordes del documento/formulario en la imagen.

    Busca el contorno rectangular más grande en la imagen,
    que se asume es el formulario. Retorna las 4 esquinas
    del documento ordenadas.

    Parámetros:
        image (np.ndarray): Imagen original (BGR o escala de grises)

    Retorna:
        np.ndarray or None: Array de 4 puntos [top-left, top-right,
            bottom-right, bottom-left] si se detecta el documento,
            None en caso contrario.
    """
    # Convertir a escala de grises si es necesario
    if len(image.shape) > 2:
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    else:
        gray = image.copy()

    # Detectar bordes
    edges = detect_edges(gray)

    # Dilatar bordes para cerrar gaps
    # Esto ayuda a conectar bordes fragmentados del documento
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))
    edges = cv2.dilate(edges, kernel, iterations=2)

    # Encontrar contornos en la imagen de bordes
    contours, _ = cv2.findContours(
        edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE
    )

    if len(contours) == 0:
        return None

    # Calcular el área total de la imagen para filtrado
    total_area = image.shape[0] * image.shape[1]
    min_area = total_area * MIN_DOCUMENT_AREA_RATIO

    # Filtrar contornos por área y buscar el más grande con 4 lados
    candidates = []

    for contour in contours:
        area = cv2.contourArea(contour)

        # Descartar contornos muy pequeños
        if area < min_area:
            continue

        # Aproximar el contorno a un polígono
        perimeter = cv2.arcLength(contour, True)
        approx = cv2.approxPolyDP(
            contour, POLYGON_APPROX_FACTOR * perimeter, True
        )

        # Buscar polígonos de 4 lados (rectángulos/cuadriláteros)
        if len(approx) == 4:
            candidates.append((area, approx))

    if len(candidates) == 0:
        return None

    # Seleccionar el candidato más grande
    candidates.sort(key=lambda x: x[0], reverse=True)
    best_contour = candidates[0][1]

    # Ordenar los puntos: top-left, top-right, bottom-right, bottom-left
    points = _order_points(best_contour.reshape(4, 2))

    return points


def _order_points(pts: np.ndarray) -> np.ndarray:
    """
    Ordena 4 puntos en el orden: top-left, top-right, bottom-right, bottom-left.

    La técnica usa la suma y diferencia de coordenadas:
    - Top-left tiene la menor suma (x+y)
    - Bottom-right tiene la mayor suma (x+y)
    - Top-right tiene la menor diferencia (y-x)
    - Bottom-left tiene la mayor diferencia (y-x)

    Parámetros:
        pts (np.ndarray): Array de 4 puntos (x, y)

    Retorna:
        np.ndarray: Puntos ordenados [tl, tr, br, bl]
    """
    rect = np.zeros((4, 2), dtype=np.float32)

    # Calcular suma y diferencia
    s = pts.sum(axis=1)
    diff = np.diff(pts, axis=1)

    rect[0] = pts[np.argmin(s)]      # Top-left: menor suma
    rect[2] = pts[np.argmax(s)]      # Bottom-right: mayor suma
    rect[1] = pts[np.argmin(diff)]   # Top-right: menor diferencia
    rect[3] = pts[np.argmax(diff)]   # Bottom-left: mayor diferencia

    return rect


def correct_perspective(image: np.ndarray,
                        points: np.ndarray = None) -> np.ndarray:
    """
    Corrige la perspectiva de la imagen del documento.

    Transforma el documento desde una vista en perspectiva
    a una vista frontal (bird's eye view) usando una
    transformación de perspectiva.

    Parámetros:
        image (np.ndarray): Imagen original (BGR)
        points (np.ndarray, opcional): 4 esquinas del documento.
            Si no se proporcionan, se detectan automáticamente.

    Retorna:
        np.ndarray: Imagen con perspectiva corregida.
            Si no se detectan esquinas, retorna la imagen original.
    """
    # Si no se proporcionan puntos, detectarlos automáticamente
    if points is None:
        points = detect_document(image)

    if points is None:
        # No se pudo detectar el documento, retornar original
        return image.copy()

    # Calcular dimensiones del documento destino
    # Usando la distancia entre esquinas
    tl, tr, br, bl = points

    # Ancho = máximo entre la distancia top y bottom
    width_top = np.sqrt(((tr[0] - tl[0]) ** 2) + ((tr[1] - tl[1]) ** 2))
    width_bottom = np.sqrt(((br[0] - bl[0]) ** 2) + ((br[1] - bl[1]) ** 2))
    max_width = int(max(width_top, width_bottom))

    # Alto = máximo entre la distancia izquierda y derecha
    height_left = np.sqrt(((bl[0] - tl[0]) ** 2) + ((bl[1] - tl[1]) ** 2))
    height_right = np.sqrt(((br[0] - tr[0]) ** 2) + ((br[1] - tr[1]) ** 2))
    max_height = int(max(height_left, height_right))

    # Definir puntos destino (vista frontal)
    dst = np.array([
        [0, 0],
        [max_width - 1, 0],
        [max_width - 1, max_height - 1],
        [0, max_height - 1]
    ], dtype=np.float32)

    # Calcular y aplicar la transformación de perspectiva
    matrix = cv2.getPerspectiveTransform(points.astype(np.float32), dst)
    warped = cv2.warpPerspective(image, matrix, (max_width, max_height))

    return warped


def correct_rotation(image: np.ndarray) -> np.ndarray:
    """
    Corrige la inclinación/rotación de la imagen.

    Detecta el ángulo de inclinación del documento usando
    líneas detectadas con la transformada de Hough y rota
    la imagen para enderezarla.

    Parámetros:
        image (np.ndarray): Imagen (BGR o escala de grises)

    Retorna:
        np.ndarray: Imagen con rotación corregida
    """
    # Convertir a escala de grises si es necesario
    if len(image.shape) > 2:
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    else:
        gray = image.copy()

    # Binarizar la imagen
    _, binary = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

    # Encontrar todos los puntos blancos (texto/marcas)
    coords = np.column_stack(np.where(binary > 0))

    if len(coords) < 10:
        # No hay suficientes puntos para determinar la inclinación
        return image.copy()

    # Usar minAreaRect para encontrar el ángulo del rectángulo mínimo
    # que contiene todos los puntos de contenido
    rect = cv2.minAreaRect(coords)
    angle = rect[2]

    # Normalizar el ángulo
    # minAreaRect retorna ángulos entre -90 y 0
    if angle < -45:
        angle = -(90 + angle)
    else:
        angle = -angle

    # Verificar que el ángulo no sea excesivo
    if abs(angle) > MAX_ROTATION_ANGLE:
        return image.copy()

    # Si la inclinación es mínima (< 0.5 grados), no corregir
    if abs(angle) < 0.5:
        return image.copy()

    # Calcular la matriz de rotación
    (h, w) = image.shape[:2]
    center = (w // 2, h // 2)
    rotation_matrix = cv2.getRotationMatrix2D(center, angle, 1.0)

    # Calcular el nuevo tamaño para que no se recorte la imagen
    cos = np.abs(rotation_matrix[0, 0])
    sin = np.abs(rotation_matrix[0, 1])
    new_w = int((h * sin) + (w * cos))
    new_h = int((h * cos) + (w * sin))

    # Ajustar la traslación en la matriz de rotación
    rotation_matrix[0, 2] += (new_w / 2) - center[0]
    rotation_matrix[1, 2] += (new_h / 2) - center[1]

    # Aplicar la rotación
    # Usar borde blanco para las áreas nuevas (fondo del formulario)
    rotated = cv2.warpAffine(
        image, rotation_matrix, (new_w, new_h),
        flags=cv2.INTER_CUBIC,
        borderMode=cv2.BORDER_CONSTANT,
        borderValue=(255, 255, 255) if len(image.shape) > 2 else 255
    )

    return rotated


def correct_geometry(image: np.ndarray) -> dict:
    """
    Pipeline completo de corrección geométrica.

    Ejecuta en secuencia:
    1. Corrección de rotación/inclinación
    2. Detección del documento
    3. Corrección de perspectiva

    Parámetros:
        image (np.ndarray): Imagen original (BGR)

    Retorna:
        dict: Diccionario con:
            - 'original': imagen original
            - 'rotation_corrected': imagen con rotación corregida
            - 'document_points': esquinas del documento detectado (o None)
            - 'perspective_corrected': imagen con perspectiva corregida
            - 'final': imagen final corregida
    """
    results = {"original": image.copy()}

    # Paso 1: Corregir rotación
    rotated = correct_rotation(image)
    results["rotation_corrected"] = rotated

    # Paso 2: Detectar el documento
    doc_points = detect_document(rotated)
    results["document_points"] = doc_points

    # Paso 3: Corregir perspectiva (si se detectó el documento)
    if doc_points is not None:
        warped = correct_perspective(rotated, doc_points)
        results["perspective_corrected"] = warped
        results["final"] = warped
    else:
        results["perspective_corrected"] = rotated
        results["final"] = rotated

    return results
