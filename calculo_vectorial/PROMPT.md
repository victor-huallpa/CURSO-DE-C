# PROMPT MAESTRO PARA CONSTRUCCIÓN DEL SISTEMA OMR DE ENCUESTAS ESTRUCTURADAS

## Objetivo del prompt

Construir un sistema web completo para el **reconocimiento automático de encuestas o formularios estructurados (OMR)** usando únicamente **Python**, siguiendo arquitectura modular, código limpio, documentación interna, comentarios detallados y buenas prácticas de ingeniería de software.

El sistema debe ser desarrollado como un proyecto real, funcional, mantenible y escalable.

---

# Descripción general del sistema

Construir un aplicativo web capaz de:

- Recibir formularios escaneados (imagen o PDF)
- Procesarlos automáticamente
- Detectar preguntas
- Detectar casillas marcadas
- Detectar casillas vacías
- Detectar marcas ambiguas
- Detectar respuestas múltiples
- Leer números pequeños manuscritos (solo ranking)
- Validar respuestas
- Generar resultados estructurados
- Exportar resultados

---

# Restricciones tecnológicas

## Lenguaje obligatorio

Usar únicamente:

```text
Python
```

NO usar:

```text
C++
Java
Node.js
PHP
```

---

## Framework recomendado

Frontend web:

```text
Streamlit
```

Backend:

```text
Python modular
```

---

## Librerías permitidas

```text
opencv-python
numpy
pandas
pillow
pdf2image
streamlit
torch
torchvision
scikit-learn
matplotlib
easyocr
sqlite3
json
```

---

# Requerimiento de arquitectura

El sistema debe construirse con esta estructura:

```text
survey_omr/
│
├── app/
│   ├── main.py
│   ├── config.py
│
├── modules/
│   ├── input_handler.py
│   ├── preprocessing.py
│   ├── geometry.py
│   ├── segmentation.py
│   ├── mark_classifier.py
│   ├── numeric_ocr.py
│   ├── postprocessing.py
│   ├── exporter.py
│
├── models/
│   ├── mark_model.pt
│   ├── numeric_model.pt
│
├── datasets/
│   ├── synthetic/
│   ├── real/
│
├── training/
│   ├── train_marks.py
│   ├── train_numbers.py
│
├── utils/
│   ├── image_utils.py
│   ├── validation_utils.py
│
├── outputs/
│
├── requirements.txt
└── README.md
```

---

# Instrucciones obligatorias de desarrollo

---

## 1. Código limpio y profesional

El código debe:

- Ser modular
- Tener separación de responsabilidades
- Usar funciones pequeñas
- Tener clases si son necesarias
- Evitar duplicación de lógica
- Tener nombres claros

---

## 2. Comentarios obligatorios

TODO el código debe estar comentado.

Se debe comentar:

- Qué hace cada archivo
- Qué hace cada función
- Parámetros
- Retorno
- Lógica compleja
- Decisiones técnicas

Formato esperado:

```python
def preprocess_image(image):
    """
    Realiza preprocesamiento de imagen.

    Parámetros:
        image: imagen original

    Retorna:
        imagen procesada
    """
```

---

## 3. Documentación interna

Cada archivo debe tener:

```python
"""
Nombre del módulo
Responsabilidad
Entradas
Salidas
Dependencias
"""
```

---

## 4. Código completo

NO generar:

- TODOs
- pseudocódigo
- "implementar aquí"
- funciones vacías
- placeholders

Todo debe quedar funcional.

---

# Módulos obligatorios a construir

---

# Módulo 1: input_handler.py

Responsabilidades:

- Cargar imágenes
- Cargar PDF
- Convertir PDF a imagen
- Validar formatos

Debe soportar:

```text
jpg
jpeg
png
pdf
```

Funciones esperadas:

- load_image()
- load_pdf()
- validate_file()

---

# Módulo 2: preprocessing.py

Responsabilidades:

- Escala de grises
- Reducción de ruido
- Binarización
- Contraste

Funciones:

- to_grayscale()
- remove_noise()
- threshold_image()
- enhance_contrast()

---

# Módulo 3: geometry.py

Responsabilidades:

- Detectar formulario
- Detectar bordes
- Detectar esquinas
- Corregir perspectiva
- Corregir inclinación

Funciones:

- detect_edges()
- detect_document()
- correct_perspective()
- correct_rotation()

---

# Módulo 4: segmentation.py

Responsabilidades:

- Detectar preguntas
- Detectar casillas
- Recortar regiones

Debe soportar dos estrategias:

## Estrategia 1

Coordenadas fijas

## Estrategia 2

Detección automática

Funciones:

- detect_boxes()
- crop_regions()
- extract_answer_regions()

---

# Módulo 5: mark_classifier.py

Responsabilidades:

Clasificar casillas:

- Vacía
- Marcada
- Ambigua

Primera versión:

Método clásico:

- conteo de píxeles negros

Segunda versión:

Modelo IA

Funciones:

- classify_mark()
- classify_by_threshold()
- classify_by_model()

---

# Módulo 6: numeric_ocr.py

Responsabilidades:

Leer números pequeños manuscritos

Funciones:

- detect_number()
- recognize_number()

Usar:

- EasyOCR o modelo propio

---

# Módulo 7: postprocessing.py

Responsabilidades:

Validar:

- doble respuesta
- respuesta vacía
- ambigüedad
- ranking repetido

Funciones:

- validate_answers()
- detect_conflicts()
- fix_minor_errors()

---

# Módulo 8: exporter.py

Responsabilidades:

Exportar:

- JSON
- CSV
- SQLite

Funciones:

- export_json()
- export_csv()
- save_to_database()

---

# Módulo 9: main.py (interfaz web)

Construir una interfaz web estilo moderno.

Debe incluir:

---

## Pantalla principal

Elementos:

- título
- descripción
- botón subir archivo
- vista previa

---

## Zona de procesamiento

Botón:

```text
Procesar formulario
```

Mostrar:

- imagen procesada
- casillas detectadas
- resultados

---

## Zona de salida

Mostrar:

- respuestas
- advertencias
- ambigüedades

Botones:

- descargar JSON
- descargar CSV

---

# Requerimientos visuales de la interfaz web

La web debe verse moderna.

Usar estilo tipo dashboard.

Debe incluir:

- layout limpio
- sidebar opcional
- cards
- botones grandes
- preview de imágenes
- tablas limpias
- feedback visual

Diseño:

```text
moderno
minimalista
profesional
responsive
```

---

# Flujo funcional obligatorio

```text
Usuario sube formulario
        ↓
Validación de archivo
        ↓
Preprocesamiento
        ↓
Corrección geométrica
        ↓
Segmentación
        ↓
Detección de marcas
        ↓
OCR ranking (si aplica)
        ↓
Postprocesamiento
        ↓
Salida estructurada
        ↓
Exportación
```

---

# Estrategia de implementación

---

## Fase 1

NO usar IA.

Implementar:

- detección de casillas
- conteo de píxeles negros
- umbrales

Objetivo:

prototipo funcional rápido

---

## Fase 2

Agregar IA para:

- marcas ambiguas
- clasificación compleja

---

## Fase 3

Agregar OCR numérico

---

## Fase 4

Optimización e interfaz final

---

# Requerimientos de calidad

El sistema debe cumplir:

- código ejecutable
- sin errores sintácticos
- modular
- documentado
- comentado
- mantenible
- escalable

---

# Requerimiento final para la IA generadora

Genera el proyecto completo archivo por archivo.

Para cada archivo:

1. Indica ruta
2. Explica función
3. Genera código completo
4. Comenta el código
5. Documenta funciones
6. No omitas lógica
7. No uses pseudocódigo

---

# Formato esperado de salida

La IA debe responder así:

```text
Archivo: modules/preprocessing.py
Descripción:
[código completo]
```

Luego continuar con el siguiente archivo.

---

# Regla final obligatoria

NO resumir.

NO generar ejemplos incompletos.

Construir el sistema real completo.
```