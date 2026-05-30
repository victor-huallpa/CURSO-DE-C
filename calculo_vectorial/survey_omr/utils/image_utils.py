"""
Módulo: image_utils.py
Responsabilidad:
    Funciones auxiliares para manipulación y visualización de imágenes.
    Incluye redimensionado, dibujo de contornos y anotaciones,
    conversiones de formato y generación de imágenes de depuración.

Entradas:
    - Imágenes NumPy (BGR, OpenCV)
Salidas:
    - Imágenes modificadas o convertidas
Dependencias:
    - cv2 (opencv-python)
    - numpy
"""

import cv2
import numpy as np


def resize_image(image: np.ndarray, max_width: int = 800,
                 max_height: int = None) -> np.ndarray:
    """
    Redimensiona una imagen manteniendo la relación de aspecto.

    Calcula el factor de escala para que la imagen quepa dentro
    de las dimensiones máximas especificadas sin distorsión.

    Parámetros:
        image (np.ndarray): Imagen original
        max_width (int): Ancho máximo en píxeles
        max_height (int, opcional): Alto máximo. Si es None, se calcula proporcionalmente.

    Retorna:
        np.ndarray: Imagen redimensionada
    """
    h, w = image.shape[:2]

    # Calcular factor de escala por ancho
    scale = max_width / w

    # Si también hay restricción de alto, usar el factor más restrictivo
    if max_height is not None:
        scale_h = max_height / h
        scale = min(scale, scale_h)

    # Solo redimensionar si la imagen es más grande
    if scale >= 1.0:
        return image.copy()

    new_w = int(w * scale)
    new_h = int(h * scale)

    resized = cv2.resize(image, (new_w, new_h), interpolation=cv2.INTER_AREA)
    return resized


def draw_boxes(image: np.ndarray, boxes: list,
               color: tuple = (0, 255, 0),
               thickness: int = 2,
               labels: list = None) -> np.ndarray:
    """
    Dibuja rectángulos alrededor de las casillas detectadas.

    Útil para visualización y depuración de la detección de casillas.

    Parámetros:
        image (np.ndarray): Imagen base (BGR)
        boxes (list[dict]): Lista de casillas con claves x, y, w, h
        color (tuple): Color BGR de los rectángulos
        thickness (int): Grosor de la línea
        labels (list[str], opcional): Etiquetas para cada casilla

    Retorna:
        np.ndarray: Imagen con rectángulos dibujados
    """
    annotated = image.copy()

    # Asegurar que la imagen sea BGR para dibujar en color
    if len(annotated.shape) == 2:
        annotated = cv2.cvtColor(annotated, cv2.COLOR_GRAY2BGR)

    for i, box in enumerate(boxes):
        x, y, w, h = box["x"], box["y"], box["w"], box["h"]

        # Dibujar rectángulo
        cv2.rectangle(annotated, (x, y), (x + w, y + h), color, thickness)

        # Agregar etiqueta si está disponible
        if labels and i < len(labels):
            label = labels[i]
            # Fondo para el texto
            text_size = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.4, 1)[0]
            cv2.rectangle(
                annotated,
                (x, y - text_size[1] - 4),
                (x + text_size[0], y),
                color, -1
            )
            # Texto
            cv2.putText(
                annotated, label,
                (x, y - 2),
                cv2.FONT_HERSHEY_SIMPLEX, 0.4,
                (255, 255, 255), 1
            )

    return annotated


def draw_classification_results(image: np.ndarray,
                                 boxes: list,
                                 classifications: list) -> np.ndarray:
    """
    Dibuja casillas coloreadas según su clasificación.

    Colores:
    - Verde: marcada
    - Rojo: vacía
    - Amarillo: ambigua

    Parámetros:
        image (np.ndarray): Imagen base (BGR)
        boxes (list[dict]): Casillas detectadas
        classifications (list[dict]): Resultados de clasificación

    Retorna:
        np.ndarray: Imagen anotada con colores de clasificación
    """
    # Mapeo de etiquetas a colores (BGR)
    color_map = {
        "marcada": (0, 200, 0),     # Verde
        "vacia": (0, 0, 200),       # Rojo
        "ambigua": (0, 200, 200)    # Amarillo
    }

    annotated = image.copy()
    if len(annotated.shape) == 2:
        annotated = cv2.cvtColor(annotated, cv2.COLOR_GRAY2BGR)

    for i, (box, cls) in enumerate(zip(boxes, classifications)):
        label = cls.get("label", "unknown")
        color = color_map.get(label, (200, 200, 200))
        confidence = cls.get("confidence", 0.0)

        x, y, w, h = box["x"], box["y"], box["w"], box["h"]

        # Dibujar rectángulo con color de clasificación
        cv2.rectangle(annotated, (x, y), (x + w, y + h), color, 2)

        # Overlay semitransparente para marcadas
        if label == "marcada":
            overlay = annotated.copy()
            cv2.rectangle(overlay, (x, y), (x + w, y + h), color, -1)
            cv2.addWeighted(overlay, 0.3, annotated, 0.7, 0, annotated)

        # Etiqueta con confianza
        text = f"{label[:3]} {confidence:.0%}"
        cv2.putText(
            annotated, text,
            (x, y - 4),
            cv2.FONT_HERSHEY_SIMPLEX, 0.35,
            color, 1
        )

    return annotated


def bgr_to_rgb(image: np.ndarray) -> np.ndarray:
    """
    Convierte imagen de BGR (OpenCV) a RGB (PIL/matplotlib/Streamlit).

    Parámetros:
        image (np.ndarray): Imagen en formato BGR

    Retorna:
        np.ndarray: Imagen en formato RGB
    """
    if len(image.shape) == 2:
        return image  # Escala de grises, no necesita conversión
    return cv2.cvtColor(image, cv2.COLOR_BGR2RGB)


def rgb_to_bgr(image: np.ndarray) -> np.ndarray:
    """
    Convierte imagen de RGB a BGR (OpenCV).

    Parámetros:
        image (np.ndarray): Imagen en formato RGB

    Retorna:
        np.ndarray: Imagen en formato BGR
    """
    if len(image.shape) == 2:
        return image
    return cv2.cvtColor(image, cv2.COLOR_RGB2BGR)


def create_comparison_image(images: list, labels: list = None,
                            max_width: int = 300) -> np.ndarray:
    """
    Crea una imagen de comparación colocando múltiples imágenes lado a lado.

    Útil para mostrar el pipeline de procesamiento (original → procesada).

    Parámetros:
        images (list[np.ndarray]): Lista de imágenes a comparar
        labels (list[str], opcional): Etiquetas para cada imagen
        max_width (int): Ancho máximo por imagen individual

    Retorna:
        np.ndarray: Imagen compuesta con todas las imágenes lado a lado
    """
    if len(images) == 0:
        return np.zeros((100, 100, 3), dtype=np.uint8)

    # Redimensionar todas las imágenes al mismo alto
    resized = []
    for img in images:
        r = resize_image(img, max_width=max_width)
        # Convertir a BGR si es escala de grises
        if len(r.shape) == 2:
            r = cv2.cvtColor(r, cv2.COLOR_GRAY2BGR)
        resized.append(r)

    # Encontrar la altura máxima
    max_h = max(img.shape[0] for img in resized)

    # Agregar padding para igualar alturas y agregar etiquetas
    padded = []
    for i, img in enumerate(resized):
        h, w = img.shape[:2]

        # Agregar espacio para etiqueta (30 píxeles arriba)
        label_h = 30 if labels else 0
        canvas = np.ones((max_h + label_h, w, 3), dtype=np.uint8) * 240

        # Colocar imagen
        canvas[label_h:label_h + h, :w] = img

        # Agregar etiqueta
        if labels and i < len(labels):
            cv2.putText(
                canvas, labels[i],
                (5, 20),
                cv2.FONT_HERSHEY_SIMPLEX, 0.5,
                (0, 0, 0), 1
            )

        padded.append(canvas)

    # Concatenar horizontalmente con separadores
    separator = np.ones((padded[0].shape[0], 2, 3), dtype=np.uint8) * 180

    parts = []
    for i, img in enumerate(padded):
        parts.append(img)
        if i < len(padded) - 1:
            parts.append(separator)

    return np.hstack(parts)
