"""
Módulo: input_handler.py
Responsabilidad:
    Gestionar la entrada de archivos al sistema OMR.
    Cargar imágenes (JPG, JPEG, PNG), cargar documentos PDF,
    convertir páginas PDF a imágenes y validar formatos de archivo.

Entradas:
    - Ruta de archivo o bytes de archivo cargado por el usuario
Salidas:
    - Lista de imágenes (numpy arrays) listas para procesamiento
Dependencias:
    - cv2 (opencv-python)
    - numpy
    - PIL (pillow)
    - pdf2image
    - app.config
"""

import os
import io
import numpy as np
import cv2
from PIL import Image
from pathlib import Path

# Importación condicional de pdf2image (requiere poppler instalado)
try:
    from pdf2image import convert_from_path, convert_from_bytes
    PDF_SUPPORT = True
except ImportError:
    PDF_SUPPORT = False

# Importar configuración del sistema
import sys
sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from app.config import (
    VALID_IMAGE_EXTENSIONS,
    VALID_PDF_EXTENSIONS,
    VALID_EXTENSIONS,
    PDF_DPI
)


def validate_file(file_path: str) -> dict:
    """
    Valida que un archivo sea apto para procesamiento OMR.

    Verifica:
        - Que el archivo exista
        - Que la extensión sea válida
        - Que el archivo no esté vacío

    Parámetros:
        file_path (str): Ruta completa al archivo a validar

    Retorna:
        dict: Diccionario con las claves:
            - 'valid' (bool): True si el archivo es válido
            - 'file_type' (str): 'image' o 'pdf'
            - 'extension' (str): Extensión del archivo
            - 'error' (str or None): Mensaje de error si no es válido
    """
    result = {
        "valid": False,
        "file_type": None,
        "extension": None,
        "error": None
    }

    # Verificar existencia del archivo
    if not os.path.exists(file_path):
        result["error"] = f"El archivo no existe: {file_path}"
        return result

    # Verificar que no sea un directorio
    if os.path.isdir(file_path):
        result["error"] = f"La ruta apunta a un directorio, no a un archivo: {file_path}"
        return result

    # Obtener y verificar extensión
    extension = Path(file_path).suffix.lower()
    result["extension"] = extension

    if extension not in VALID_EXTENSIONS:
        result["error"] = (
            f"Extensión no soportada: '{extension}'. "
            f"Extensiones válidas: {', '.join(sorted(VALID_EXTENSIONS))}"
        )
        return result

    # Verificar que el archivo no esté vacío
    file_size = os.path.getsize(file_path)
    if file_size == 0:
        result["error"] = "El archivo está vacío (0 bytes)"
        return result

    # Determinar tipo de archivo
    if extension in VALID_IMAGE_EXTENSIONS:
        result["file_type"] = "image"
    elif extension in VALID_PDF_EXTENSIONS:
        result["file_type"] = "pdf"
        # Verificar que pdf2image esté disponible
        if not PDF_SUPPORT:
            result["error"] = (
                "La librería pdf2image no está instalada. "
                "Instálala con: pip install pdf2image"
            )
            return result

    result["valid"] = True
    return result


def validate_uploaded_file(uploaded_file) -> dict:
    """
    Valida un archivo cargado a través de Streamlit (UploadedFile).

    Parámetros:
        uploaded_file: Objeto UploadedFile de Streamlit

    Retorna:
        dict: Diccionario de validación con las mismas claves que validate_file()
    """
    result = {
        "valid": False,
        "file_type": None,
        "extension": None,
        "error": None
    }

    if uploaded_file is None:
        result["error"] = "No se proporcionó ningún archivo"
        return result

    # Obtener nombre y extensión del archivo
    filename = uploaded_file.name
    extension = Path(filename).suffix.lower()
    result["extension"] = extension

    # Verificar extensión
    if extension not in VALID_EXTENSIONS:
        result["error"] = (
            f"Extensión no soportada: '{extension}'. "
            f"Extensiones válidas: {', '.join(sorted(VALID_EXTENSIONS))}"
        )
        return result

    # Verificar tamaño
    uploaded_file.seek(0, 2)  # Ir al final del archivo
    file_size = uploaded_file.tell()
    uploaded_file.seek(0)  # Volver al inicio

    if file_size == 0:
        result["error"] = "El archivo está vacío (0 bytes)"
        return result

    # Determinar tipo
    if extension in VALID_IMAGE_EXTENSIONS:
        result["file_type"] = "image"
    elif extension in VALID_PDF_EXTENSIONS:
        result["file_type"] = "pdf"
        if not PDF_SUPPORT:
            result["error"] = (
                "La librería pdf2image no está instalada. "
                "Instálala con: pip install pdf2image"
            )
            return result

    result["valid"] = True
    return result


def load_image(source) -> np.ndarray:
    """
    Carga una imagen desde una ruta de archivo o desde bytes en memoria.

    La imagen se retorna como un array NumPy en formato BGR (estándar OpenCV).

    Parámetros:
        source: Puede ser:
            - str o Path: ruta al archivo de imagen
            - bytes: contenido binario de la imagen
            - UploadedFile de Streamlit: archivo cargado por el usuario

    Retorna:
        np.ndarray: Imagen cargada en formato BGR (OpenCV)

    Raises:
        ValueError: Si la fuente no es válida o la imagen no puede cargarse
    """
    image = None

    if isinstance(source, (str, Path)):
        # Cargar desde ruta de archivo
        file_path = str(source)
        if not os.path.exists(file_path):
            raise ValueError(f"El archivo no existe: {file_path}")

        # Leer imagen con OpenCV
        image = cv2.imread(file_path)
        if image is None:
            raise ValueError(f"No se pudo leer la imagen: {file_path}")

    elif isinstance(source, bytes):
        # Cargar desde bytes en memoria
        nparr = np.frombuffer(source, np.uint8)
        image = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
        if image is None:
            raise ValueError("No se pudo decodificar la imagen desde bytes")

    elif hasattr(source, 'read'):
        # Cargar desde objeto tipo archivo (UploadedFile de Streamlit)
        file_bytes = source.read()
        source.seek(0)  # Resetear posición para posibles lecturas futuras
        nparr = np.frombuffer(file_bytes, np.uint8)
        image = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
        if image is None:
            raise ValueError("No se pudo decodificar la imagen desde el archivo cargado")

    else:
        raise ValueError(
            f"Tipo de fuente no soportado: {type(source)}. "
            "Se esperaba str, Path, bytes o UploadedFile"
        )

    return image


def load_pdf(source, dpi: int = None) -> list:
    """
    Carga un documento PDF y lo convierte en una lista de imágenes.

    Cada página del PDF se convierte en una imagen NumPy (BGR).

    Parámetros:
        source: Puede ser:
            - str o Path: ruta al archivo PDF
            - bytes: contenido binario del PDF
            - UploadedFile de Streamlit: archivo PDF cargado
        dpi (int, opcional): Resolución de conversión. Por defecto usa PDF_DPI de config.

    Retorna:
        list[np.ndarray]: Lista de imágenes (una por página) en formato BGR

    Raises:
        ImportError: Si pdf2image no está instalado
        ValueError: Si el PDF no puede procesarse
    """
    if not PDF_SUPPORT:
        raise ImportError(
            "La librería pdf2image no está instalada. "
            "Instálala con: pip install pdf2image. "
            "También necesitas instalar poppler-utils."
        )

    # Usar DPI de configuración si no se especifica
    if dpi is None:
        dpi = PDF_DPI

    images_pil = []

    if isinstance(source, (str, Path)):
        # Convertir desde ruta de archivo
        file_path = str(source)
        if not os.path.exists(file_path):
            raise ValueError(f"El archivo PDF no existe: {file_path}")

        images_pil = convert_from_path(file_path, dpi=dpi)

    elif isinstance(source, bytes):
        # Convertir desde bytes en memoria
        images_pil = convert_from_bytes(source, dpi=dpi)

    elif hasattr(source, 'read'):
        # Convertir desde UploadedFile de Streamlit
        file_bytes = source.read()
        source.seek(0)  # Resetear posición
        images_pil = convert_from_bytes(file_bytes, dpi=dpi)

    else:
        raise ValueError(
            f"Tipo de fuente no soportado para PDF: {type(source)}"
        )

    if len(images_pil) == 0:
        raise ValueError("El PDF no contiene páginas procesables")

    # Convertir imágenes PIL a arrays NumPy BGR (formato OpenCV)
    images_cv = []
    for i, img_pil in enumerate(images_pil):
        # Convertir PIL Image (RGB) a NumPy array y luego a BGR
        img_array = np.array(img_pil)
        img_bgr = cv2.cvtColor(img_array, cv2.COLOR_RGB2BGR)
        images_cv.append(img_bgr)

    return images_cv


def load_file(source) -> list:
    """
    Función unificada de carga que detecta el tipo de archivo
    y lo procesa automáticamente.

    Parámetros:
        source: Puede ser:
            - str o Path: ruta al archivo
            - UploadedFile de Streamlit: archivo cargado

    Retorna:
        list[np.ndarray]: Lista de imágenes en formato BGR.
            Para imágenes retorna una lista con un solo elemento.
            Para PDFs retorna una imagen por página.

    Raises:
        ValueError: Si el archivo no es válido
    """
    # Determinar la extensión del archivo
    if isinstance(source, (str, Path)):
        extension = Path(str(source)).suffix.lower()
    elif hasattr(source, 'name'):
        extension = Path(source.name).suffix.lower()
    else:
        raise ValueError("No se puede determinar el tipo de archivo")

    # Cargar según el tipo
    if extension in VALID_IMAGE_EXTENSIONS:
        # Es una imagen: retornar como lista de un elemento
        image = load_image(source)
        return [image]

    elif extension in VALID_PDF_EXTENSIONS:
        # Es un PDF: retornar lista de imágenes (una por página)
        images = load_pdf(source)
        return images

    else:
        raise ValueError(
            f"Extensión no soportada: '{extension}'. "
            f"Use: {', '.join(sorted(VALID_EXTENSIONS))}"
        )
