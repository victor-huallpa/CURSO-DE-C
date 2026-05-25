"""
Módulo: segmentation.py
Responsabilidad:
    Segmentar la imagen del formulario en regiones individuales.
    Detectar casillas de respuesta, preguntas y recortar
    las regiones de interés para su posterior clasificación.

    Soporta dos estrategias:
    1. Coordenadas fijas (formularios con diseño conocido)
    2. Detección automática (formularios desconocidos)

Entradas:
    - Imagen preprocesada (binaria o escala de grises)
Salidas:
    - Lista de regiones (casillas) recortadas con sus coordenadas
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
    MIN_BOX_AREA,
    MAX_BOX_AREA,
    MIN_ASPECT_RATIO,
    MAX_ASPECT_RATIO,
    BOX_INNER_MARGIN
)


def detect_boxes(binary_image: np.ndarray,
                 min_area: int = None,
                 max_area: int = None) -> list:
    """
    Detecta casillas rectangulares en una imagen binarizada.

    Usa detección de contornos y filtrado por forma/tamaño
    para encontrar casillas de respuesta en formularios.

    Criterios de filtrado:
    - Área dentro del rango [min_area, max_area]
    - Relación de aspecto cercana a 1:1 (cuadrado) o rectangular
    - Contorno con al menos 4 vértices

    Parámetros:
        binary_image (np.ndarray): Imagen binarizada (blanco y negro)
        min_area (int, opcional): Área mínima de casilla. Default: MIN_BOX_AREA
        max_area (int, opcional): Área máxima de casilla. Default: MAX_BOX_AREA

    Retorna:
        list[dict]: Lista de casillas detectadas, cada una con:
            - 'x': coordenada X del bounding box
            - 'y': coordenada Y del bounding box
            - 'w': ancho del bounding box
            - 'h': alto del bounding box
            - 'area': área del contorno
            - 'contour': contorno original
            - 'center': tupla (cx, cy) del centro
    """
    if min_area is None:
        min_area = MIN_BOX_AREA
    if max_area is None:
        max_area = MAX_BOX_AREA

    # Asegurar que la imagen sea binaria
    if len(binary_image.shape) > 2:
        binary_image = cv2.cvtColor(binary_image, cv2.COLOR_BGR2GRAY)

    # Encontrar todos los contornos
    contours, hierarchy = cv2.findContours(
        binary_image.copy(),
        cv2.RETR_TREE,       # Usar TREE para detectar jerarquía (casillas dentro de áreas)
        cv2.CHAIN_APPROX_SIMPLE
    )

    boxes = []

    for i, contour in enumerate(contours):
        # Calcular área del contorno
        area = cv2.contourArea(contour)

        # Filtrar por área
        if area < min_area or area > max_area:
            continue

        # Obtener bounding box
        x, y, w, h = cv2.boundingRect(contour)

        # Calcular relación de aspecto
        if h == 0:
            continue
        aspect_ratio = float(w) / float(h)

        # Filtrar por relación de aspecto
        if aspect_ratio < MIN_ASPECT_RATIO or aspect_ratio > MAX_ASPECT_RATIO:
            continue

        # Aproximar contorno para verificar que sea rectangular
        perimeter = cv2.arcLength(contour, True)
        approx = cv2.approxPolyDP(contour, 0.04 * perimeter, True)

        # Aceptar polígonos con 4 o más vértices (rectángulos y cuadrados)
        if len(approx) >= 4:
            # Calcular centro
            cx = x + w // 2
            cy = y + h // 2

            boxes.append({
                "x": x,
                "y": y,
                "w": w,
                "h": h,
                "area": area,
                "contour": contour,
                "center": (cx, cy),
                "vertices": len(approx)
            })

    # Ordenar casillas de arriba a abajo, izquierda a derecha
    # Primero por Y (filas), luego por X (columnas)
    boxes = _sort_boxes(boxes)

    return boxes


def _sort_boxes(boxes: list, row_threshold: int = 20) -> list:
    """
    Ordena casillas en orden de lectura: de arriba a abajo, izquierda a derecha.

    Agrupa casillas en filas usando un umbral de tolerancia vertical,
    luego ordena dentro de cada fila por posición horizontal.

    Parámetros:
        boxes (list): Lista de diccionarios de casillas
        row_threshold (int): Tolerancia vertical para agrupación en filas (píxeles)

    Retorna:
        list: Casillas ordenadas en orden de lectura
    """
    if len(boxes) == 0:
        return boxes

    # Ordenar primero por Y
    boxes_sorted = sorted(boxes, key=lambda b: b["y"])

    # Agrupar en filas
    rows = []
    current_row = [boxes_sorted[0]]
    current_y = boxes_sorted[0]["y"]

    for box in boxes_sorted[1:]:
        if abs(box["y"] - current_y) <= row_threshold:
            # Misma fila
            current_row.append(box)
        else:
            # Nueva fila
            rows.append(current_row)
            current_row = [box]
            current_y = box["y"]

    rows.append(current_row)

    # Ordenar dentro de cada fila por X y concatenar
    result = []
    for row in rows:
        row_sorted = sorted(row, key=lambda b: b["x"])
        result.extend(row_sorted)

    return result


def crop_regions(image: np.ndarray, boxes: list,
                 margin: int = None) -> list:
    """
    Recorta regiones de la imagen según las casillas detectadas.

    Extrae cada casilla como una sub-imagen individual para
    su posterior clasificación.

    Parámetros:
        image (np.ndarray): Imagen de la cual recortar
        boxes (list): Lista de casillas detectadas (de detect_boxes)
        margin (int, opcional): Margen interior para recorte. Default: BOX_INNER_MARGIN

    Retorna:
        list[dict]: Lista de regiones recortadas, cada una con:
            - 'image': sub-imagen recortada (np.ndarray)
            - 'box': diccionario de la casilla original
            - 'index': índice de la casilla
    """
    if margin is None:
        margin = BOX_INNER_MARGIN

    regions = []

    for i, box in enumerate(boxes):
        x, y, w, h = box["x"], box["y"], box["w"], box["h"]

        # Aplicar margen interior para excluir los bordes de la casilla
        x1 = max(0, x + margin)
        y1 = max(0, y + margin)
        x2 = min(image.shape[1], x + w - margin)
        y2 = min(image.shape[0], y + h - margin)

        # Verificar que la región sea válida
        if x2 <= x1 or y2 <= y1:
            continue

        # Recortar la región
        crop = image[y1:y2, x1:x2].copy()

        regions.append({
            "image": crop,
            "box": box,
            "index": i
        })

    return regions


def extract_answer_regions(image: np.ndarray,
                           binary_image: np.ndarray = None,
                           strategy: str = "auto") -> list:
    """
    Extrae regiones de respuesta del formulario.

    Función principal de segmentación que combina detección de casillas
    y recorte de regiones.

    Estrategias:
        - 'auto': Detección automática de casillas
        - 'fixed': Usa coordenadas predefinidas (para formularios estándar)

    Parámetros:
        image (np.ndarray): Imagen original (BGR o escala de grises)
        binary_image (np.ndarray, opcional): Imagen binarizada para detección.
            Si no se proporciona, se genera automáticamente.
        strategy (str): Estrategia de segmentación ('auto' o 'fixed')

    Retorna:
        list[dict]: Lista de regiones de respuesta con imagen recortada,
            coordenadas y metadata
    """
    # Si no se proporciona imagen binaria, generarla
    if binary_image is None:
        if len(image.shape) > 2:
            gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        else:
            gray = image.copy()
        _, binary_image = cv2.threshold(
            gray, 0, 255,
            cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU
        )

    if strategy == "auto":
        # Estrategia automática: detectar casillas con OpenCV
        boxes = detect_boxes(binary_image)
        regions = crop_regions(image, boxes)
        return regions

    elif strategy == "fixed":
        # Estrategia de coordenadas fijas
        # Las coordenadas se definen según el diseño del formulario
        regions = _extract_fixed_regions(image)
        return regions

    else:
        raise ValueError(
            f"Estrategia no soportada: '{strategy}'. "
            "Use 'auto' o 'fixed'"
        )


def _extract_fixed_regions(image: np.ndarray) -> list:
    """
    Extrae regiones usando coordenadas fijas predefinidas.

    Este método se usa cuando el formulario tiene un diseño conocido
    y las casillas están en posiciones fijas. Las coordenadas deben
    ajustarse según el diseño específico del formulario.

    Los valores aquí son un ejemplo para un formulario tipo encuesta
    con casillas de 30x30 píxeles distribuidas en filas.

    Parámetros:
        image (np.ndarray): Imagen del formulario

    Retorna:
        list[dict]: Regiones extraídas con coordenadas fijas
    """
    # Ejemplo de coordenadas fijas para un formulario estándar
    # Estas deben ajustarse según el formulario real
    # Formato: (x, y, w, h, pregunta_id, opcion_id)
    fixed_coords = [
        # Ejemplo: pregunta 1, opciones A-D
        {"x": 100, "y": 200, "w": 30, "h": 30, "question": 1, "option": "A"},
        {"x": 150, "y": 200, "w": 30, "h": 30, "question": 1, "option": "B"},
        {"x": 200, "y": 200, "w": 30, "h": 30, "question": 1, "option": "C"},
        {"x": 250, "y": 200, "w": 30, "h": 30, "question": 1, "option": "D"},
        # Ejemplo: pregunta 2, opciones A-D
        {"x": 100, "y": 260, "w": 30, "h": 30, "question": 2, "option": "A"},
        {"x": 150, "y": 260, "w": 30, "h": 30, "question": 2, "option": "B"},
        {"x": 200, "y": 260, "w": 30, "h": 30, "question": 2, "option": "C"},
        {"x": 250, "y": 260, "w": 30, "h": 30, "question": 2, "option": "D"},
    ]

    regions = []

    for i, coord in enumerate(fixed_coords):
        x, y, w, h = coord["x"], coord["y"], coord["w"], coord["h"]

        # Verificar que las coordenadas están dentro de la imagen
        if (y + h > image.shape[0]) or (x + w > image.shape[1]):
            continue

        # Recortar la región
        crop = image[y:y+h, x:x+w].copy()

        regions.append({
            "image": crop,
            "box": {
                "x": x, "y": y, "w": w, "h": h,
                "area": w * h,
                "center": (x + w // 2, y + h // 2)
            },
            "index": i,
            "question": coord.get("question"),
            "option": coord.get("option")
        })

    return regions


def group_by_question(regions: list, row_threshold: int = 30) -> dict:
    """
    Agrupa regiones segmentadas por pregunta.

    Usa la posición vertical (Y) para determinar qué casillas
    pertenecen a la misma pregunta (misma fila).

    Parámetros:
        regions (list): Lista de regiones segmentadas
        row_threshold (int): Tolerancia vertical para agrupación

    Retorna:
        dict: Diccionario {pregunta_id: [regiones]} donde cada
            pregunta contiene sus casillas/opciones
    """
    if len(regions) == 0:
        return {}

    # Si las regiones tienen campo 'question', usar ese
    if "question" in regions[0]:
        groups = {}
        for region in regions:
            q_id = region["question"]
            if q_id not in groups:
                groups[q_id] = []
            groups[q_id].append(region)
        return groups

    # Si no, agrupar por posición Y
    sorted_regions = sorted(regions, key=lambda r: r["box"]["y"])

    groups = {}
    question_id = 1
    current_y = sorted_regions[0]["box"]["y"]
    groups[question_id] = [sorted_regions[0]]

    for region in sorted_regions[1:]:
        if abs(region["box"]["y"] - current_y) <= row_threshold:
            # Misma fila = misma pregunta
            groups[question_id].append(region)
        else:
            # Nueva fila = nueva pregunta
            question_id += 1
            groups[question_id] = [region]
            current_y = region["box"]["y"]

    # Ordenar opciones dentro de cada pregunta por X
    for q_id in groups:
        groups[q_id] = sorted(
            groups[q_id],
            key=lambda r: r["box"]["x"]
        )

    return groups
