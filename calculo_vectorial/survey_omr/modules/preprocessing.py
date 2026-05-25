"""
Módulo: preprocessing.py
Responsabilidad:
    Realizar el preprocesamiento de imágenes para mejorar la calidad
    antes de la detección de marcas. Incluye conversión a escala de grises,
    reducción de ruido, binarización y mejora de contraste.

Entradas:
    - Imagen en formato NumPy (BGR, OpenCV)
Salidas:
    - Imagen preprocesada (generalmente binaria o en escala de grises)
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
    NOISE_KERNEL_SIZE,
    MEDIAN_BLUR_KERNEL,
    CLAHE_CLIP_LIMIT,
    CLAHE_TILE_GRID_SIZE,
    ADAPTIVE_BLOCK_SIZE,
    ADAPTIVE_C
)


def to_grayscale(image: np.ndarray) -> np.ndarray:
    """
    Convierte una imagen a escala de grises.

    Si la imagen ya está en escala de grises (1 canal), se retorna sin cambios.
    Si la imagen tiene 3 canales (BGR), se convierte usando cv2.cvtColor.
    Si tiene 4 canales (BGRA), se convierte descartando el canal alfa.

    Parámetros:
        image (np.ndarray): Imagen de entrada (BGR, BGRA o escala de grises)

    Retorna:
        np.ndarray: Imagen en escala de grises (1 canal)
    """
    # Si ya es escala de grises, retornar sin cambios
    if len(image.shape) == 2:
        return image.copy()

    # Si tiene 3 canales (BGR), convertir
    if image.shape[2] == 3:
        return cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Si tiene 4 canales (BGRA), convertir
    if image.shape[2] == 4:
        return cv2.cvtColor(image, cv2.COLOR_BGRA2GRAY)

    raise ValueError(f"Número de canales no soportado: {image.shape[2]}")


def remove_noise(image: np.ndarray, method: str = "gaussian") -> np.ndarray:
    """
    Reduce el ruido de una imagen usando filtrado espacial.

    Se ofrecen dos métodos:
        - 'gaussian': GaussianBlur, bueno para ruido general
        - 'median': medianBlur, excelente para ruido salt-and-pepper

    Parámetros:
        image (np.ndarray): Imagen de entrada (escala de grises recomendada)
        method (str): Método de filtrado ('gaussian' o 'median')

    Retorna:
        np.ndarray: Imagen con ruido reducido
    """
    if method == "gaussian":
        # GaussianBlur suaviza la imagen con un kernel gaussiano
        # El kernel (5,5) es un buen balance entre suavizado y preservación de bordes
        return cv2.GaussianBlur(image, NOISE_KERNEL_SIZE, 0)

    elif method == "median":
        # medianBlur es especialmente efectivo contra ruido salt-and-pepper
        # que es común en imágenes escaneadas
        return cv2.medianBlur(image, MEDIAN_BLUR_KERNEL)

    else:
        raise ValueError(
            f"Método de filtrado no soportado: '{method}'. "
            "Use 'gaussian' o 'median'"
        )


def threshold_image(image: np.ndarray, method: str = "otsu") -> np.ndarray:
    """
    Binariza una imagen usando umbrales.

    La binarización convierte la imagen a blanco y negro puro,
    lo cual es esencial para la detección de contornos y marcas.

    Métodos disponibles:
        - 'otsu': Umbral automático de Otsu (ideal para documentos escaneados)
        - 'adaptive': Umbral adaptativo (mejor para iluminación desigual)
        - 'simple': Umbral fijo en 127

    Parámetros:
        image (np.ndarray): Imagen en escala de grises
        method (str): Método de binarización

    Retorna:
        np.ndarray: Imagen binarizada (valores 0 o 255)
    """
    # Asegurar que la imagen esté en escala de grises
    if len(image.shape) > 2:
        image = to_grayscale(image)

    if method == "otsu":
        # Umbral de Otsu: calcula automáticamente el mejor umbral
        # Minimiza la varianza intra-clase del histograma
        _, binary = cv2.threshold(
            image, 0, 255,
            cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU
        )
        return binary

    elif method == "adaptive":
        # Umbral adaptativo: calcula umbrales locales
        # Mejor cuando la iluminación no es uniforme
        return cv2.adaptiveThreshold(
            image, 255,
            cv2.ADAPTIVE_THRESH_GAUSSIAN_C,
            cv2.THRESH_BINARY_INV,
            ADAPTIVE_BLOCK_SIZE,
            ADAPTIVE_C
        )

    elif method == "simple":
        # Umbral fijo simple: rápido pero menos robusto
        _, binary = cv2.threshold(
            image, 127, 255,
            cv2.THRESH_BINARY_INV
        )
        return binary

    else:
        raise ValueError(
            f"Método de binarización no soportado: '{method}'. "
            "Use 'otsu', 'adaptive' o 'simple'"
        )


def enhance_contrast(image: np.ndarray) -> np.ndarray:
    """
    Mejora el contraste de una imagen usando CLAHE.

    CLAHE (Contrast Limited Adaptive Histogram Equalization) mejora
    el contraste local de la imagen, lo cual ayuda a distinguir
    marcas en formularios con impresión deficiente o escaneados
    de baja calidad.

    Parámetros:
        image (np.ndarray): Imagen en escala de grises

    Retorna:
        np.ndarray: Imagen con contraste mejorado
    """
    # Asegurar escala de grises
    if len(image.shape) > 2:
        image = to_grayscale(image)

    # Crear objeto CLAHE con los parámetros de configuración
    # clipLimit controla el límite de amplificación del contraste
    # tileGridSize define el tamaño de la región para ecualización local
    clahe = cv2.createCLAHE(
        clipLimit=CLAHE_CLIP_LIMIT,
        tileGridSize=CLAHE_TILE_GRID_SIZE
    )

    # Aplicar CLAHE a la imagen
    return clahe.apply(image)


def preprocess_full(image: np.ndarray,
                    noise_method: str = "gaussian",
                    threshold_method: str = "otsu") -> dict:
    """
    Pipeline completo de preprocesamiento.

    Ejecuta todos los pasos de preprocesamiento en secuencia:
    1. Conversión a escala de grises
    2. Mejora de contraste (CLAHE)
    3. Reducción de ruido
    4. Binarización

    Retorna todas las versiones intermedias para depuración y visualización.

    Parámetros:
        image (np.ndarray): Imagen original en BGR
        noise_method (str): Método de reducción de ruido ('gaussian' o 'median')
        threshold_method (str): Método de binarización ('otsu', 'adaptive', 'simple')

    Retorna:
        dict: Diccionario con las imágenes en cada etapa:
            - 'original': imagen original
            - 'grayscale': escala de grises
            - 'contrast': contraste mejorado
            - 'denoised': ruido reducido
            - 'binary': imagen binarizada (resultado final)
    """
    results = {"original": image.copy()}

    # Paso 1: Conversión a escala de grises
    gray = to_grayscale(image)
    results["grayscale"] = gray

    # Paso 2: Mejora de contraste
    # Se aplica antes del ruido para maximizar la separación tonal
    contrast = enhance_contrast(gray)
    results["contrast"] = contrast

    # Paso 3: Reducción de ruido
    # Se aplica después del contraste para no suavizar detalles importantes
    denoised = remove_noise(contrast, method=noise_method)
    results["denoised"] = denoised

    # Paso 4: Binarización
    # Paso final que produce la imagen blanco/negro para detección
    binary = threshold_image(denoised, method=threshold_method)
    results["binary"] = binary

    return results
