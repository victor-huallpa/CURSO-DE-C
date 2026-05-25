# Creación del Aplicativo

## 1. Metodología de desarrollo

Para este proyecto conviene trabajar de forma **modular e incremental**, desarrollando primero los componentes básicos y luego integrándolos.

Se seguirá la metodología:

# Desarrollo incremental por módulos

Cada módulo se desarrolla, prueba y valida por separado antes de integrarlo al sistema completo.

Etapas:

```text
Análisis del problema
        ↓
Diseño del formulario
        ↓
Construcción de dataset
        ↓
Desarrollo de módulos
        ↓
Entrenamiento de modelos
        ↓
Integración del sistema
        ↓
Validación
        ↓
Despliegue del aplicativo
```

---

## 2. Requerimientos del aplicativo

### 2.1 Requerimientos funcionales

El sistema deberá permitir:

- Cargar una imagen o PDF escaneado
- Detectar automáticamente el formulario
- Corregir inclinación y perspectiva
- Detectar preguntas
- Detectar casillas
- Determinar opciones marcadas
- Detectar respuestas ambiguas
- Leer números manuscritos pequeños (ranking)
- Validar inconsistencias
- Generar salida estructurada
- Exportar resultados (JSON, CSV o base de datos)

---

### 2.2 Requerimientos no funcionales

El sistema deberá:

- Procesar imágenes en tiempo razonable
- Tener alta precisión
- Ser modular
- Ser mantenible
- Permitir reentrenamiento
- Ser escalable para nuevos formularios
- Tener interfaz amigable

---

## 3. Arquitectura del aplicativo

El aplicativo puede dividirse en dos grandes bloques:

```text
Frontend (Interfaz)
        ↓
Backend (Procesamiento OMR)
```

---

### 3.1 Frontend

Interfaz para el usuario.

Funciones:

- Subir formulario
- Ver imagen procesada
- Ver respuestas detectadas
- Descargar resultados
- Revisar respuestas ambiguas

Tecnologías posibles:

- Streamlit (rápido)
- Flask + HTML/CSS/JS
- Django

Para prototipo:

**Streamlit** (más rápido)

---

### 3.2 Backend

Encargado del procesamiento.

Módulos internos:

```text
Carga de imagen
    ↓
Preprocesamiento
    ↓
Segmentación
    ↓
Clasificación
    ↓
OCR
    ↓
Postprocesamiento
    ↓
Generación de salida
```

---

## 4. Módulos que se deben desarrollar

---

### Módulo 1: Gestión de entrada

Responsabilidades:

- Cargar imagen
- Cargar PDF
- Convertir PDF a imagen
- Validar formato

Bibliotecas:

```text
opencv-python
Pillow
pdf2image
```

---

### Módulo 2: Preprocesamiento

Responsabilidades:

- Escala de grises
- Reducción de ruido
- Binarización
- Mejora de contraste

Bibliotecas:

```text
OpenCV
NumPy
```

---

### Módulo 3: Corrección geométrica

Responsabilidades:

- Detectar bordes del formulario
- Detectar esquinas
- Corregir perspectiva
- Corregir rotación

Bibliotecas:

```text
OpenCV
```

---

### Módulo 4: Segmentación de regiones

Responsabilidades:

- Detectar preguntas
- Detectar casillas
- Recortar regiones

Estrategias:

- Coordenadas fijas (si el formulario es estándar)
- Detección automática (si cambia)

Bibliotecas:

```text
OpenCV
NumPy
```

---

### Módulo 5: Clasificador de marcas

Responsabilidades:

Determinar:

- Vacía
- Marcada
- Ambigua

Bibliotecas:

```text
TensorFlow o PyTorch
```

Modelo:

```text
CNN pequeña
```

---

### Módulo 6: OCR numérico

Solo para ranking.

Responsabilidades:

- Detectar número
- Reconocerlo

Bibliotecas:

```text
TensorFlow / PyTorch
EasyOCR / modelo propio
```

---

### Módulo 7: Postprocesamiento

Responsabilidades:

Validar:

- Pregunta con doble marca
- Pregunta vacía
- Ranking repetido
- Ambigüedad

Generar reglas de negocio.

Bibliotecas:

```text
Python puro
```

---

### Módulo 8: Generador de salida

Responsabilidades:

Convertir resultados a:

- JSON
- CSV
- Base de datos

Bibliotecas:

```text
json
pandas
sqlite3
```

---

### Módulo 9: Interfaz de usuario

Responsabilidades:

Permitir:

- Subir archivo
- Procesar
- Mostrar resultados
- Descargar

Bibliotecas:

```text
Streamlit
```

---

## 5. Estructura del proyecto

Una estructura profesional sería:

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

## 6. Requerimientos técnicos

### Software

- Python 3.11+
- pip
- virtualenv

---

### Librerías

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
```

---

### Hardware recomendado

Para desarrollo:

```text
CPU: i5 o superior
RAM: 8GB mínimo
```

Para entrenamiento:

```text
GPU opcional
RAM: 16GB recomendado
```

---

## 7. Metodología de implementación recomendada

### Fase 1 (más rápida)

No usar IA todavía.

Usar:

- Coordenadas fijas
- Umbral de píxeles negros

Objetivo:

Tener prototipo funcional rápido.

---

### Fase 2

Agregar clasificador IA para:

- Marcas ambiguas
- Casillas difíciles

---

### Fase 3

Agregar OCR ranking.

---

### Fase 4

Interfaz final.

---

## 8. Resultado final del aplicativo

El usuario:

```text
Sube formulario
      ↓
El sistema procesa
      ↓
Muestra respuestas
      ↓
Exporta resultados
```

Salida:

```json
{
  "pregunta_1": "Sí",
  "pregunta_2": "Bus",
  "pregunta_3": "De acuerdo"
}
```

---

## 9. Recomendación técnica

Se recomienda **no entrenar modelos de IA desde el inicio**.

Primero desarrollar un sistema OMR clásico usando OpenCV:

- Detección de casillas
- Conteo de píxeles
- Validación básica

Posteriormente agregar IA donde el método clásico falle:

- Marcas ambiguas
- Casillas con ruido
- OCR numérico manuscrito

Esta estrategia reduce tiempo de desarrollo, complejidad y riesgo técnico.