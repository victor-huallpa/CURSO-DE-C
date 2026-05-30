"""
Módulo de configuración central del sistema OMR.

Responsabilidad:
    Centralizar todas las constantes, umbrales, rutas y parámetros
    de configuración del sistema para facilitar el mantenimiento
    y la calibración.

Dependencias:
    - os (librería estándar)
    - pathlib (librería estándar)
"""

import os
from pathlib import Path


# =============================================================================
# RUTAS DEL PROYECTO
# =============================================================================

# Directorio raíz del proyecto (un nivel arriba de app/)
PROJECT_ROOT = Path(__file__).resolve().parent.parent

# Directorio donde se guardan los modelos entrenados
MODELS_DIR = PROJECT_ROOT / "models"

# Directorio donde se guardan los datasets
DATASETS_DIR = PROJECT_ROOT / "datasets"

# Directorio de salida para resultados exportados
OUTPUTS_DIR = PROJECT_ROOT / "outputs"

# Crear directorios de salida si no existen
OUTPUTS_DIR.mkdir(parents=True, exist_ok=True)


# =============================================================================
# FORMATOS DE ARCHIVO ACEPTADOS
# =============================================================================

# Extensiones de imagen válidas
VALID_IMAGE_EXTENSIONS = {".jpg", ".jpeg", ".png", ".bmp", ".tiff"}

# Extensiones de PDF válidas
VALID_PDF_EXTENSIONS = {".pdf"}

# Todas las extensiones válidas
VALID_EXTENSIONS = VALID_IMAGE_EXTENSIONS | VALID_PDF_EXTENSIONS


# =============================================================================
# PARÁMETROS DE PREPROCESAMIENTO
# =============================================================================

# Resolución DPI para conversión de PDF a imagen
PDF_DPI = 300

# Tamaño del kernel para reducción de ruido (GaussianBlur)
NOISE_KERNEL_SIZE = (5, 5)

# Tamaño del kernel para reducción de ruido (medianBlur)
MEDIAN_BLUR_KERNEL = 5

# Clip limit para CLAHE (mejora de contraste)
CLAHE_CLIP_LIMIT = 2.0

# Tamaño del grid para CLAHE
CLAHE_TILE_GRID_SIZE = (8, 8)

# Tamaño de bloque para binarización adaptativa
ADAPTIVE_BLOCK_SIZE = 11

# Constante C para binarización adaptativa
ADAPTIVE_C = 2


# =============================================================================
# PARÁMETROS DE DETECCIÓN GEOMÉTRICA
# =============================================================================

# Umbrales para detección de bordes Canny
CANNY_THRESHOLD_LOW = 50
CANNY_THRESHOLD_HIGH = 150

# Factor de aproximación de polígono (porcentaje del perímetro)
POLYGON_APPROX_FACTOR = 0.02

# Área mínima de contorno para considerar como documento (porcentaje del área total)
MIN_DOCUMENT_AREA_RATIO = 0.1

# Ángulo máximo de rotación a corregir (grados)
MAX_ROTATION_ANGLE = 45


# =============================================================================
# PARÁMETROS DE SEGMENTACIÓN
# =============================================================================

# Área mínima de una casilla en píxeles
MIN_BOX_AREA = 100

# Área máxima de una casilla en píxeles
MAX_BOX_AREA = 10000

# Relación de aspecto mínima para considerar un contorno como casilla
MIN_ASPECT_RATIO = 0.5

# Relación de aspecto máxima para considerar un contorno como casilla
MAX_ASPECT_RATIO = 2.0

# Margen interior para recorte de casillas (píxeles)
BOX_INNER_MARGIN = 3


# =============================================================================
# PARÁMETROS DE CLASIFICACIÓN DE MARCAS
# =============================================================================

# Umbral de porcentaje de píxeles negros para considerar una casilla como marcada
# Si el porcentaje de píxeles negros es mayor a este valor, se considera marcada
MARK_THRESHOLD_FILLED = 0.35

# Umbral inferior: por debajo de este valor se considera vacía
MARK_THRESHOLD_EMPTY = 0.10

# Entre MARK_THRESHOLD_EMPTY y MARK_THRESHOLD_FILLED se considera ambigua

# Etiquetas de clasificación
LABEL_EMPTY = "vacia"
LABEL_MARKED = "marcada"
LABEL_AMBIGUOUS = "ambigua"


# =============================================================================
# PARÁMETROS DE OCR NUMÉRICO
# =============================================================================

# Idiomas soportados por EasyOCR
OCR_LANGUAGES = ["es", "en"]

# Confianza mínima para aceptar un resultado de OCR
OCR_MIN_CONFIDENCE = 0.5

# Rango de números válidos para ranking
RANKING_MIN = 1
RANKING_MAX = 10


# =============================================================================
# PARÁMETROS DE POSTPROCESAMIENTO
# =============================================================================

# Máximo de respuestas permitidas por pregunta (1 = opción única)
MAX_ANSWERS_PER_QUESTION = 1

# Permitir preguntas sin respuesta
ALLOW_EMPTY_ANSWERS = False


# =============================================================================
# PARÁMETROS DE LA INTERFAZ WEB
# =============================================================================

# Título de la aplicación
APP_TITLE = "📋 Sistema OMR - Reconocimiento de Encuestas"

# Descripción de la aplicación
APP_DESCRIPTION = """
Sistema de reconocimiento óptico de marcas (OMR) para procesamiento
automático de encuestas y formularios estructurados.
"""

# Tamaño máximo de archivo en MB
MAX_FILE_SIZE_MB = 20

# Ancho máximo de imagen para vista previa (píxeles)
PREVIEW_MAX_WIDTH = 700


# =============================================================================
# CONFIGURACIÓN DE BASE DE DATOS
# =============================================================================

# Nombre del archivo SQLite
DATABASE_FILE = OUTPUTS_DIR / "survey_results.db"

# Nombre de la tabla principal
DATABASE_TABLE = "respuestas"
