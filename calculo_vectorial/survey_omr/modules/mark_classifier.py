"""
Módulo: mark_classifier.py
Responsabilidad:
    Clasificar las casillas detectadas en los formularios OMR.
    Determinar si cada casilla está:
    - Vacía (no marcada)
    - Marcada (seleccionada)
    - Ambigua (marca parcial o dudosa)

    Soporta dos métodos de clasificación:
    1. Método clásico: conteo de píxeles negros con umbrales
    2. Método IA: clasificación con modelo CNN (Fase 2)

Entradas:
    - Imagen recortada de una casilla individual
Salidas:
    - Etiqueta de clasificación y confianza
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
    MARK_THRESHOLD_FILLED,
    MARK_THRESHOLD_EMPTY,
    LABEL_EMPTY,
    LABEL_MARKED,
    LABEL_AMBIGUOUS,
    MODELS_DIR
)


def classify_mark(image: np.ndarray, method: str = "threshold") -> dict:
    """
    Clasifica una casilla como vacía, marcada o ambigua.

    Función principal que delega al método apropiado según
    el parámetro 'method'.

    Parámetros:
        image (np.ndarray): Imagen recortada de la casilla
        method (str): Método de clasificación:
            - 'threshold': método clásico por conteo de píxeles
            - 'model': método IA con CNN (requiere modelo entrenado)

    Retorna:
        dict: Resultado de clasificación con:
            - 'label' (str): Etiqueta ('vacia', 'marcada', 'ambigua')
            - 'confidence' (float): Nivel de confianza [0.0, 1.0]
            - 'fill_ratio' (float): Porcentaje de píxeles oscuros
            - 'method' (str): Método utilizado
    """
    if method == "threshold":
        return classify_by_threshold(image)
    elif method == "model":
        return classify_by_model(image)
    else:
        raise ValueError(
            f"Método de clasificación no soportado: '{method}'. "
            "Use 'threshold' o 'model'"
        )


def classify_by_threshold(image: np.ndarray) -> dict:
    """
    Clasifica una casilla por conteo de píxeles negros (método clásico).

    Este método funciona bien para formularios limpios con marcas
    claras. Calcula el porcentaje de píxeles oscuros en la casilla
    y compara con umbrales predefinidos.

    Lógica de clasificación:
    - Si fill_ratio > MARK_THRESHOLD_FILLED → marcada
    - Si fill_ratio < MARK_THRESHOLD_EMPTY → vacía
    - Si está entre ambos umbrales → ambigua

    La confianza se calcula como la distancia del fill_ratio
    al umbral más cercano, normalizada.

    Parámetros:
        image (np.ndarray): Imagen recortada de la casilla

    Retorna:
        dict: Resultado de clasificación con label, confidence,
            fill_ratio y method
    """
    # Convertir a escala de grises si es necesario
    if len(image.shape) > 2:
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    else:
        gray = image.copy()

    # Binarizar la imagen de la casilla
    # Usar Otsu para umbral automático
    _, binary = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

    # Contar píxeles negros (en la imagen invertida, los píxeles blancos son marcas)
    total_pixels = binary.shape[0] * binary.shape[1]

    if total_pixels == 0:
        return {
            "label": LABEL_EMPTY,
            "confidence": 0.0,
            "fill_ratio": 0.0,
            "method": "threshold"
        }

    # Contar píxeles blancos en la imagen invertida (= píxeles oscuros originales)
    white_pixels = cv2.countNonZero(binary)
    fill_ratio = white_pixels / total_pixels

    # Clasificar según umbrales
    if fill_ratio >= MARK_THRESHOLD_FILLED:
        label = LABEL_MARKED
        # Confianza: qué tan lejos está del umbral, escalada
        confidence = min(1.0, (fill_ratio - MARK_THRESHOLD_FILLED) /
                        (1.0 - MARK_THRESHOLD_FILLED) * 0.5 + 0.5)

    elif fill_ratio <= MARK_THRESHOLD_EMPTY:
        label = LABEL_EMPTY
        # Confianza: qué tan lejos está del umbral
        confidence = min(1.0, (MARK_THRESHOLD_EMPTY - fill_ratio) /
                        MARK_THRESHOLD_EMPTY * 0.5 + 0.5)

    else:
        label = LABEL_AMBIGUOUS
        # Confianza: distancia al centro del rango ambiguo
        mid = (MARK_THRESHOLD_FILLED + MARK_THRESHOLD_EMPTY) / 2
        range_size = MARK_THRESHOLD_FILLED - MARK_THRESHOLD_EMPTY
        if range_size > 0:
            confidence = 1.0 - abs(fill_ratio - mid) / (range_size / 2)
        else:
            confidence = 0.5

    return {
        "label": label,
        "confidence": round(confidence, 4),
        "fill_ratio": round(fill_ratio, 4),
        "method": "threshold"
    }


def classify_by_model(image: np.ndarray) -> dict:
    """
    Clasifica una casilla usando un modelo de red neuronal CNN.

    Este método proporciona mayor precisión que el método de umbral,
    especialmente para marcas ambiguas, parciales o ruidosas.

    Requiere un modelo entrenado (.pt) en el directorio models/.

    NOTA: Este método está preparado para la Fase 2 del proyecto.
    Actualmente verifica si existe un modelo entrenado y, de no existir,
    hace fallback al método de umbral.

    Parámetros:
        image (np.ndarray): Imagen recortada de la casilla

    Retorna:
        dict: Resultado de clasificación con label, confidence,
            fill_ratio y method
    """
    model_path = MODELS_DIR / "mark_model.pt"

    # Verificar si existe un modelo entrenado
    if not model_path.exists():
        # Fallback al método de umbral si no hay modelo
        result = classify_by_threshold(image)
        result["method"] = "threshold_fallback"
        result["note"] = "Modelo IA no disponible, usando método de umbral"
        return result

    try:
        import torch
        import torchvision.transforms as transforms

        # Preparar la imagen para el modelo
        # Redimensionar a 28x28 (estándar para clasificación simple)
        if len(image.shape) > 2:
            gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        else:
            gray = image.copy()

        resized = cv2.resize(gray, (28, 28))

        # Normalizar y convertir a tensor
        transform = transforms.Compose([
            transforms.ToTensor(),
            transforms.Normalize((0.5,), (0.5,))
        ])

        from PIL import Image as PILImage
        pil_image = PILImage.fromarray(resized)
        tensor = transform(pil_image).unsqueeze(0)

        # Cargar modelo
        model = torch.load(model_path, map_location=torch.device('cpu'))
        model.eval()

        # Realizar predicción
        with torch.no_grad():
            output = model(tensor)
            probabilities = torch.softmax(output, dim=1)
            predicted_class = torch.argmax(probabilities, dim=1).item()
            confidence = probabilities[0][predicted_class].item()

        # Mapear clase a etiqueta
        class_labels = {0: LABEL_EMPTY, 1: LABEL_MARKED, 2: LABEL_AMBIGUOUS}
        label = class_labels.get(predicted_class, LABEL_AMBIGUOUS)

        # Calcular fill_ratio como referencia
        _, binary = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)
        total = binary.shape[0] * binary.shape[1]
        fill_ratio = cv2.countNonZero(binary) / total if total > 0 else 0.0

        return {
            "label": label,
            "confidence": round(confidence, 4),
            "fill_ratio": round(fill_ratio, 4),
            "method": "model"
        }

    except Exception as e:
        # Si hay error con el modelo, fallback a umbral
        result = classify_by_threshold(image)
        result["method"] = "threshold_fallback"
        result["note"] = f"Error al usar modelo IA: {str(e)}"
        return result


def classify_multiple(regions: list, method: str = "threshold") -> list:
    """
    Clasifica múltiples casillas de una sola vez.

    Parámetros:
        regions (list[dict]): Lista de regiones de segmentation.py
            Cada región debe tener la clave 'image' con la sub-imagen.
        method (str): Método de clasificación ('threshold' o 'model')

    Retorna:
        list[dict]: Lista de resultados de clasificación.
            Cada resultado incluye los campos de classify_mark más:
            - 'index': índice de la región
            - 'box': coordenadas de la casilla original
    """
    results = []

    for region in regions:
        # Clasificar la imagen de la casilla
        classification = classify_mark(region["image"], method=method)

        # Agregar metadata de la región
        classification["index"] = region.get("index", -1)
        classification["box"] = region.get("box", {})
        classification["question"] = region.get("question")
        classification["option"] = region.get("option")

        results.append(classification)

    return results
