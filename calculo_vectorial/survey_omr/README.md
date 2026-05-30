# Sistema OMR de Encuestas Estructuradas

Sistema web completo para el reconocimiento automático de encuestas o formularios estructurados (OMR - Optical Mark Recognition) desarrollado en Python y Streamlit.

## Características

- 📁 **Soporte multiformato**: Carga de imágenes (JPG, PNG) y documentos PDF.
- 🔧 **Preprocesamiento robusto**: Reducción de ruido, binarización adaptativa y mejora de contraste (CLAHE).
- 📐 **Corrección geométrica**: Detección automática del documento, corrección de perspectiva e inclinación.
- ✂️ **Segmentación flexible**: Detección automática de casillas o uso de coordenadas fijas.
- 🏷️ **Clasificación precisa**: Método clásico por umbrales (Fase 1) preparado para integración con modelos CNN (Fase 2).
- 🔢 **OCR Numérico**: Reconocimiento de números manuscritos para campos de ranking usando EasyOCR.
- ✅ **Validación de reglas**: Detección de respuestas múltiples, vacías, ambiguas y conflictos.
- 📤 **Exportación**: Salida estructurada en JSON, CSV y base de datos SQLite.
- 🖥️ **Interfaz moderna**: Dashboard interactivo construido con Streamlit.

## Arquitectura del Sistema

El proyecto sigue una arquitectura modular con separación clara de responsabilidades:

```text
survey_omr/
├── app/                    # Interfaz web y configuración
│   ├── main.py             # Aplicación Streamlit principal
│   └── config.py           # Parámetros y umbrales centralizados
├── modules/                # Lógica core de procesamiento OMR
│   ├── input_handler.py    # Carga y validación de archivos
│   ├── preprocessing.py    # Mejora de imagen y binarización
│   ├── geometry.py         # Corrección de perspectiva y rotación
│   ├── segmentation.py     # Detección y recorte de casillas
│   ├── mark_classifier.py  # Clasificación (vacía/marcada/ambigua)
│   ├── numeric_ocr.py      # Reconocimiento de números manuscritos
│   ├── postprocessing.py   # Validación y reglas de negocio
│   └── exporter.py         # Exportación a JSON, CSV, SQLite
├── utils/                  # Funciones auxiliares
│   ├── image_utils.py      # Manipulación y dibujo en imágenes
│   └── validation_utils.py # Validación de calidad y dimensiones
├── training/               # Scripts de entrenamiento (Fase 2/3)
│   ├── train_marks.py      # Entrenamiento de CNN para marcas
│   └── train_numbers.py    # Entrenamiento de CNN para números
├── models/                 # Modelos IA entrenados (.pt)
├── datasets/               # Datos de entrenamiento
└── outputs/                # Resultados exportados y base de datos
```

## Requisitos Previos

- Python 3.11 o superior
- Para soporte PDF: `poppler-utils` instalado en el sistema operativo
  - Ubuntu/Debian: `sudo apt-get install poppler-utils`
  - macOS: `brew install poppler`
  - Windows: Descargar binarios de poppler y agregar al PATH

## Instalación

1. Clonar el repositorio o descargar el código.
2. Crear un entorno virtual (recomendado):
   ```bash
   python -m venv venv
   source venv/bin/activate  # En Windows: venv\Scripts\activate
   ```
3. Instalar las dependencias:
   ```bash
   pip install -r requirements.txt
   ```

## Uso

Para iniciar la interfaz web del sistema:

```bash
cd survey_omr
streamlit run app/main.py
```

La aplicación se abrirá automáticamente en tu navegador web predeterminado (usualmente en `http://localhost:8501`).

## Fases de Desarrollo

Este proyecto está estructurado para un desarrollo incremental:

- **Fase 1 (Actual)**: Prototipo funcional usando métodos clásicos de visión por computadora (OpenCV) sin IA. Clasificación por conteo de píxeles y umbrales.
- **Fase 2**: Integración de modelos de Deep Learning (PyTorch) para clasificación de marcas ambiguas o ruidosas. (Scripts de entrenamiento incluidos en `training/`).
- **Fase 3**: Integración completa de OCR numérico para campos de ranking.

## Flujo de Procesamiento Interno

1. **Entrada**: `input_handler` carga la imagen o convierte el PDF.
2. **Preprocesamiento**: `preprocessing` convierte a escala de grises, reduce ruido y binariza.
3. **Geometría**: `geometry` endereza la imagen y corrige la perspectiva si es necesario.
4. **Segmentación**: `segmentation` encuentra las casillas de respuesta y las recorta.
5. **Clasificación**: `mark_classifier` evalúa cada casilla (vacía, marcada, ambigua).
6. **Postprocesamiento**: `postprocessing` agrupa por pregunta, aplica reglas (ej. no permitir doble marca) y detecta conflictos.
7. **Salida**: La interfaz web muestra los resultados y `exporter` permite guardarlos.
