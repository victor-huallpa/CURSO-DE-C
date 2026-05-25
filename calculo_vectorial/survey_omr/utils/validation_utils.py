"""
Módulo: validation_utils.py
Responsabilidad:
    Funciones auxiliares de validación para archivos, imágenes
    y datos de entrada al sistema OMR.

Entradas:
    - Archivos, imágenes, datos de configuración
Salidas:
    - Resultados de validación (booleanos y mensajes)
Dependencias:
    - os (librería estándar)
    - cv2 (opencv-python)
    - numpy
    - app.config
"""

import os
import numpy as np
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from app.config import (
    VALID_EXTENSIONS,
    MAX_FILE_SIZE_MB
)


def validate_file_size(file_path: str = None, file_bytes: bytes = None,
                       max_size_mb: float = None) -> dict:
    """
    Valida el tamaño de un archivo.

    Parámetros:
        file_path (str, opcional): Ruta al archivo
        file_bytes (bytes, opcional): Contenido del archivo en bytes
        max_size_mb (float, opcional): Tamaño máximo en MB

    Retorna:
        dict: {'valid': bool, 'size_mb': float, 'error': str or None}
    """
    if max_size_mb is None:
        max_size_mb = MAX_FILE_SIZE_MB

    size_bytes = 0

    if file_path is not None:
        if os.path.exists(file_path):
            size_bytes = os.path.getsize(file_path)
        else:
            return {"valid": False, "size_mb": 0, "error": "Archivo no encontrado"}

    elif file_bytes is not None:
        size_bytes = len(file_bytes)

    size_mb = size_bytes / (1024 * 1024)

    if size_mb > max_size_mb:
        return {
            "valid": False,
            "size_mb": round(size_mb, 2),
            "error": f"Archivo demasiado grande: {size_mb:.1f}MB (máx: {max_size_mb}MB)"
        }

    return {
        "valid": True,
        "size_mb": round(size_mb, 2),
        "error": None
    }


def validate_image_dimensions(image: np.ndarray,
                               min_width: int = 100,
                               min_height: int = 100,
                               max_width: int = 10000,
                               max_height: int = 10000) -> dict:
    """
    Valida las dimensiones de una imagen.

    Parámetros:
        image (np.ndarray): Imagen a validar
        min_width (int): Ancho mínimo aceptable
        min_height (int): Alto mínimo aceptable
        max_width (int): Ancho máximo aceptable
        max_height (int): Alto máximo aceptable

    Retorna:
        dict: {'valid': bool, 'width': int, 'height': int, 'error': str or None}
    """
    if image is None:
        return {"valid": False, "width": 0, "height": 0, "error": "Imagen es None"}

    h, w = image.shape[:2]

    if w < min_width or h < min_height:
        return {
            "valid": False,
            "width": w,
            "height": h,
            "error": (
                f"Imagen demasiado pequeña: {w}x{h} "
                f"(mínimo: {min_width}x{min_height})"
            )
        }

    if w > max_width or h > max_height:
        return {
            "valid": False,
            "width": w,
            "height": h,
            "error": (
                f"Imagen demasiado grande: {w}x{h} "
                f"(máximo: {max_width}x{max_height})"
            )
        }

    return {
        "valid": True,
        "width": w,
        "height": h,
        "error": None
    }


def validate_image_quality(image: np.ndarray) -> dict:
    """
    Evalúa la calidad de una imagen para procesamiento OMR.

    Analiza:
    - Contraste (desviación estándar de píxeles)
    - Brillo (media de píxeles)
    - Nitidez (varianza del Laplaciano)

    Parámetros:
        image (np.ndarray): Imagen a evaluar

    Retorna:
        dict: Métricas de calidad con recomendaciones
    """
    import cv2

    # Convertir a escala de grises
    if len(image.shape) > 2:
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    else:
        gray = image.copy()

    # Calcular métricas
    brightness = float(np.mean(gray))
    contrast = float(np.std(gray))

    # Nitidez: varianza del Laplaciano
    laplacian = cv2.Laplacian(gray, cv2.CV_64F)
    sharpness = float(np.var(laplacian))

    # Evaluar calidad
    warnings = []
    quality_score = 1.0

    # Evaluación de brillo
    if brightness < 50:
        warnings.append("Imagen muy oscura. Considere mejorar la iluminación del escaneo.")
        quality_score -= 0.3
    elif brightness > 230:
        warnings.append("Imagen muy brillante/sobreexpuesta.")
        quality_score -= 0.2

    # Evaluación de contraste
    if contrast < 30:
        warnings.append("Contraste bajo. Las marcas podrían no detectarse bien.")
        quality_score -= 0.3
    elif contrast < 50:
        warnings.append("Contraste moderado. Se recomienda mejorar.")
        quality_score -= 0.1

    # Evaluación de nitidez
    if sharpness < 100:
        warnings.append("Imagen borrosa. Considere un escaneo de mayor calidad.")
        quality_score -= 0.3
    elif sharpness < 500:
        warnings.append("Nitidez moderada.")
        quality_score -= 0.1

    quality_score = max(0.0, min(1.0, quality_score))

    return {
        "brightness": round(brightness, 2),
        "contrast": round(contrast, 2),
        "sharpness": round(sharpness, 2),
        "quality_score": round(quality_score, 2),
        "warnings": warnings,
        "acceptable": quality_score >= 0.5
    }


def validate_processing_input(image: np.ndarray) -> dict:
    """
    Validación completa de una imagen antes del procesamiento OMR.

    Combina validación de dimensiones y calidad.

    Parámetros:
        image (np.ndarray): Imagen a validar

    Retorna:
        dict: Resultado completo de validación
    """
    results = {
        "valid": True,
        "dimensions": None,
        "quality": None,
        "errors": [],
        "warnings": []
    }

    # Validar dimensiones
    dim_result = validate_image_dimensions(image)
    results["dimensions"] = dim_result
    if not dim_result["valid"]:
        results["valid"] = False
        results["errors"].append(dim_result["error"])

    # Validar calidad
    quality_result = validate_image_quality(image)
    results["quality"] = quality_result
    results["warnings"].extend(quality_result["warnings"])

    if not quality_result["acceptable"]:
        results["warnings"].append(
            "La calidad de la imagen es baja. "
            "Los resultados podrían ser imprecisos."
        )

    return results
