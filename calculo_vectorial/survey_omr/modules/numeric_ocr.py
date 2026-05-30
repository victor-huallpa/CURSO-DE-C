"""
Módulo: numeric_ocr.py
Responsabilidad:
    Leer y reconocer números manuscritos pequeños en formularios.
    Se usa específicamente para campos de ranking donde el usuario
    escribe un número a mano (1-10).

    Usa EasyOCR como motor principal con fallback a método clásico.

Entradas:
    - Imagen recortada de la región numérica
Salidas:
    - Número reconocido y nivel de confianza
Dependencias:
    - easyocr
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
    OCR_LANGUAGES,
    OCR_MIN_CONFIDENCE,
    RANKING_MIN,
    RANKING_MAX,
    MODELS_DIR
)

# Variable global para cachear el reader de EasyOCR
# Inicializar es costoso, así que se hace una sola vez
_ocr_reader = None


def _get_ocr_reader():
    """
    Obtiene o inicializa el lector de EasyOCR.

    Se implementa como singleton para evitar múltiples
    inicializaciones del modelo (que son costosas en tiempo y memoria).

    Retorna:
        easyocr.Reader: Instancia del lector de EasyOCR

    Raises:
        ImportError: Si EasyOCR no está instalado
    """
    global _ocr_reader

    if _ocr_reader is None:
        try:
            import easyocr
            # Inicializar con soporte GPU si está disponible
            _ocr_reader = easyocr.Reader(
                OCR_LANGUAGES,
                gpu=False  # Usar CPU por defecto (más compatible)
            )
        except ImportError:
            raise ImportError(
                "EasyOCR no está instalado. "
                "Instálalo con: pip install easyocr"
            )

    return _ocr_reader


def detect_number(image: np.ndarray) -> bool:
    """
    Detecta si una región de imagen contiene un número manuscrito.

    Analiza la densidad de píxeles y las características
    de la región para determinar si hay contenido numérico.

    Parámetros:
        image (np.ndarray): Imagen recortada de la región

    Retorna:
        bool: True si se detecta posible contenido numérico
    """
    # Convertir a escala de grises
    if len(image.shape) > 2:
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    else:
        gray = image.copy()

    # Binarizar
    _, binary = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

    # Calcular la proporción de píxeles de contenido
    total_pixels = binary.shape[0] * binary.shape[1]
    if total_pixels == 0:
        return False

    content_pixels = cv2.countNonZero(binary)
    content_ratio = content_pixels / total_pixels

    # Un número manuscrito típicamente ocupa entre 5% y 70% del área
    if content_ratio < 0.05 or content_ratio > 0.70:
        return False

    # Buscar contornos significativos
    contours, _ = cv2.findContours(
        binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE
    )

    # Debe haber al menos un contorno significativo
    significant_contours = [
        c for c in contours
        if cv2.contourArea(c) > total_pixels * 0.02
    ]

    return len(significant_contours) > 0


def recognize_number(image: np.ndarray) -> dict:
    """
    Reconoce un número manuscrito en una imagen.

    Intenta reconocer el número usando EasyOCR. Si falla
    o no está disponible, usa un método básico de conteo.

    Parámetros:
        image (np.ndarray): Imagen recortada de la región numérica

    Retorna:
        dict: Resultado con:
            - 'number' (int or None): Número reconocido
            - 'confidence' (float): Confianza del reconocimiento [0.0, 1.0]
            - 'raw_text' (str): Texto crudo reconocido por OCR
            - 'method' (str): Método utilizado
            - 'valid' (bool): Si el número está en el rango válido
    """
    result = {
        "number": None,
        "confidence": 0.0,
        "raw_text": "",
        "method": "none",
        "valid": False
    }

    # Verificar que hay contenido
    if not detect_number(image):
        return result

    # Intentar con EasyOCR
    try:
        ocr_result = _recognize_with_easyocr(image)
        if ocr_result["number"] is not None:
            return ocr_result
    except (ImportError, Exception):
        pass

    # Fallback: método básico
    basic_result = _recognize_basic(image)
    return basic_result


def _recognize_with_easyocr(image: np.ndarray) -> dict:
    """
    Reconoce número usando EasyOCR.

    EasyOCR es un motor de OCR basado en deep learning que
    funciona bien con texto manuscrito y impreso.

    Parámetros:
        image (np.ndarray): Imagen de la región numérica

    Retorna:
        dict: Resultado de reconocimiento
    """
    result = {
        "number": None,
        "confidence": 0.0,
        "raw_text": "",
        "method": "easyocr",
        "valid": False
    }

    # Preprocesar la imagen para mejorar el reconocimiento
    if len(image.shape) > 2:
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    else:
        gray = image.copy()

    # Mejorar contraste para números manuscritos
    clahe = cv2.createCLAHE(clipLimit=3.0, tileGridSize=(4, 4))
    enhanced = clahe.apply(gray)

    # Redimensionar para mejor reconocimiento (EasyOCR funciona mejor con imágenes más grandes)
    scale = max(1, 100 // max(enhanced.shape))
    if scale > 1:
        enhanced = cv2.resize(
            enhanced, None,
            fx=scale, fy=scale,
            interpolation=cv2.INTER_CUBIC
        )

    # Ejecutar OCR
    reader = _get_ocr_reader()
    ocr_results = reader.readtext(
        enhanced,
        allowlist='0123456789',  # Solo permitir dígitos
        detail=1
    )

    if len(ocr_results) == 0:
        return result

    # Tomar el resultado con mayor confianza
    best_result = max(ocr_results, key=lambda x: x[2])
    raw_text = best_result[1].strip()
    confidence = best_result[2]

    result["raw_text"] = raw_text
    result["confidence"] = round(confidence, 4)

    # Intentar convertir a número
    try:
        number = int(raw_text)
        result["number"] = number

        # Validar rango
        if RANKING_MIN <= number <= RANKING_MAX:
            result["valid"] = True
        else:
            result["valid"] = False

    except ValueError:
        # El texto reconocido no es un número válido
        result["number"] = None

    return result


def _recognize_basic(image: np.ndarray) -> dict:
    """
    Método básico de reconocimiento de números por conteo de componentes.

    Método heurístico simple que intenta identificar dígitos
    basándose en el número de componentes conectados y su disposición.

    Este método es menos preciso que OCR pero funciona sin dependencias externas.

    Parámetros:
        image (np.ndarray): Imagen de la región numérica

    Retorna:
        dict: Resultado de reconocimiento
    """
    result = {
        "number": None,
        "confidence": 0.0,
        "raw_text": "",
        "method": "basic",
        "valid": False
    }

    # Convertir a escala de grises
    if len(image.shape) > 2:
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    else:
        gray = image.copy()

    # Binarizar
    _, binary = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

    # Contar componentes conectados
    num_labels, labels, stats, centroids = cv2.connectedComponentsWithStats(
        binary, connectivity=8
    )

    # Filtrar componentes pequeños (ruido)
    total_area = binary.shape[0] * binary.shape[1]
    significant_components = []

    for i in range(1, num_labels):  # Saltar fondo (label 0)
        area = stats[i, cv2.CC_STAT_AREA]
        if area > total_area * 0.05:  # Al menos 5% del área
            significant_components.append({
                "area": area,
                "centroid": centroids[i],
                "bbox": stats[i]
            })

    # Heurística simple basada en número de componentes
    # 1 componente = podría ser varios dígitos
    if len(significant_components) == 0:
        return result

    # Usar el fill_ratio para intentar identificar el dígito
    total_pixels = binary.shape[0] * binary.shape[1]
    fill_ratio = cv2.countNonZero(binary) / total_pixels if total_pixels > 0 else 0

    # Heurística: estimar número basado en densidad y forma
    # Esto es MUY básico y solo sirve como fallback
    result["confidence"] = 0.3  # Baja confianza por ser heurístico
    result["raw_text"] = f"~{len(significant_components)} comp"

    return result


def recognize_ranking(regions: list) -> list:
    """
    Reconoce números de ranking en múltiples regiones.

    Procesa una lista de regiones numéricas y retorna
    los rankings reconocidos.

    Parámetros:
        regions (list[dict]): Lista de regiones con campo 'image'

    Retorna:
        list[dict]: Lista de resultados de reconocimiento,
            cada uno con los campos de recognize_number más
            metadata de la región original.
    """
    results = []

    for region in regions:
        recognition = recognize_number(region["image"])

        # Agregar metadata de la región
        recognition["index"] = region.get("index", -1)
        recognition["box"] = region.get("box", {})

        results.append(recognition)

    return results
