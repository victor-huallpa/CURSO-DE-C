# Sistema de Reconocimiento de Encuestas Estructuradas

## 1. Descripción General

Este proyecto tiene como objetivo desarrollar un sistema capaz de **interpretar encuestas o cuestionarios estructurados llenados manualmente**, detectando las opciones seleccionadas por una persona dentro de formularios de respuesta cerrada.

A diferencia de un OCR manuscrito tradicional, este sistema no busca interpretar texto libre escrito por el usuario, sino **identificar marcas, selecciones y respuestas cerradas dentro de campos predefinidos**.

---

## 2. Tipo de documento objetivo

# Cuestionarios o Encuestas Estructuradas

Son formularios donde:

- Las preguntas están definidas previamente
- El usuario no redacta respuestas libres
- El usuario selecciona opciones cerradas
- La estructura del formulario es fija
- Las posiciones de las respuestas son conocidas

---

## 3. Tipos de preguntas soportadas

---

### 3.1 Preguntas dicotómicas

Permiten únicamente dos respuestas posibles.

Ejemplo:

```text
¿Ha visitado nuestra tienda este mes?

( ) Sí
( ) No
```

Respuesta esperada:

```json
{
  "respuesta": "Sí"
}
```

---

### 3.2 Preguntas de opción múltiple

Permiten seleccionar una o varias opciones.

Ejemplo:

```text
¿Cuál es su medio de transporte principal?

( ) Auto
( ) Bicicleta
( ) Bus
( ) Moto
```

Respuesta esperada:

```json
{
  "respuesta": "Bus"
}
```

---

### 3.3 Escala de Likert

Miden percepción o nivel de acuerdo.

Ejemplo:

```text
El servicio fue rápido:

( ) Muy en desacuerdo
( ) En desacuerdo
( ) Neutral
( ) De acuerdo
( ) Muy de acuerdo
```

Respuesta esperada:

```json
{
  "respuesta": "De acuerdo"
}
```

---

### 3.4 Preguntas de ranking o clasificación

El usuario asigna números de prioridad.

Ejemplo:

```text
Ordene del 1 al 3:

Chocolate [ ]
Vainilla  [ ]
Fresa     [ ]
```

Respuesta esperada:

```json
{
  "Chocolate": 2,
  "Vainilla": 1,
  "Fresa": 3
}
```

---

## 4. Redefinición del problema técnico

Este sistema NO es un OCR completo de escritura libre.

El problema principal es:

# Reconocimiento de marcas en formularios estructurados (OMR)

El sistema debe detectar:

- Casillas vacías
- Casillas marcadas
- Casillas ambiguas
- Marcas parciales
- Selecciones múltiples
- Campos numéricos pequeños (solo en ranking)

---

## 5. Objetivo General

Desarrollar un sistema capaz de:

- Procesar formularios estructurados
- Detectar respuestas marcadas
- Interpretar respuestas cerradas
- Generar una salida digital estructurada

---

## 6. Objetivos Específicos

### 6.1 Procesamiento de imagen

- Corregir inclinación
- Eliminar ruido
- Mejorar contraste
- Corregir perspectiva

---

### 6.2 Segmentación

- Detectar preguntas
- Detectar casillas
- Extraer regiones de respuesta

---

### 6.3 Reconocimiento de marcas

- Determinar si una opción está marcada
- Detectar múltiples selecciones
- Detectar marcas incompletas

---

### 6.4 Reconocimiento numérico (ranking)

- Leer números pequeños manuscritos
- Asociar ranking con opción correspondiente

---

### 6.5 Generación de salida

- Convertir respuestas a formato estructurado

---

## 7. Arquitectura general del sistema

```text
Formulario escaneado
        ↓
Preprocesamiento
        ↓
Corrección geométrica
        ↓
Segmentación de regiones
        ↓
Detección de marcas
        ↓
OCR numérico (si aplica)
        ↓
Postprocesamiento
        ↓
Salida estructurada
```

---

## 8. División tecnológica

El sistema será desarrollado completamente en **Python**, utilizando bibliotecas especializadas para visión por computadora, procesamiento de imágenes y aprendizaje automático.

| Componente | Lenguaje |
|---|---|
| Procesamiento de imagen | Python |
| Corrección geométrica | Python |
| Segmentación de regiones | Python |
| Preparación de dataset | Python |
| Entrenamiento del modelo | Python |
| Inferencia del modelo | Python |
| Postprocesamiento | Python |

---

## 9. Justificación técnica

### 9.1 Uso de Python como lenguaje unificado

Se usará Python para:

- Lectura de imagen
- Conversión a escala de grises
- Binarización
- Filtrado
- Detección de contornos
- Segmentación de casillas
- Entrenamiento de modelos
- Inferencia
- Postprocesamiento

### Razones técnicas

Python permite:

- Desarrollo rápido y modular
- Amplio ecosistema de visión por computadora
- Integración sencilla con OpenCV
- Ecosistema robusto para Machine Learning
- Soporte para GPU en entrenamiento
- Facilidad de mantenimiento
- Integración completa sin necesidad de múltiples lenguajes

---

## 10. Estructura modular

---

### Módulo 1: Preprocesamiento (Python)

Responsabilidades:

- Escala de grises
- Corrección de iluminación
- Eliminación de ruido
- Corrección de inclinación
- Corrección de perspectiva

#### Entrada

```text
Imagen original
```

#### Salida

```text
Formulario limpio
```

---

### Módulo 2: Segmentación (Python)

Responsabilidades:

- Detectar regiones de preguntas
- Encontrar casillas
- Extraer imágenes pequeñas de respuesta

#### Entrada

```text
Formulario procesado
```

#### Salida

```text
casilla_1.png
casilla_2.png
casilla_3.png
...
```

---

### Módulo 3: Clasificador de marcas (Python)

Responsabilidades:

Clasificar cada casilla como:

- Vacía
- Marcada
- Ambigua

#### Entrada

```text
Imagen pequeña de casilla
```

#### Salida

```text
Marcada / Vacía / Ambigua
```

---

### Módulo 4: OCR numérico (Python)

Solo usado en ranking.

Responsabilidades:

- Detectar números pequeños escritos a mano

#### Entrada

```text
Imagen pequeña con número
```

#### Salida

```text
1 / 2 / 3 / 4 ...
```

---

### Módulo 5: Postprocesamiento (Python)

Responsabilidades:

- Detectar errores
- Validar consistencia
- Corregir salidas ambiguas

Ejemplos:

- Dos respuestas marcadas en una pregunta única
- Ranking duplicado
- Casillas parcialmente marcadas

---

## 11. Diseño del modelo

El sistema usará modelos pequeños de clasificación.

---

### Modelo 1: Clasificador de casillas

Entrada:

```text
Imagen de casilla
```

Salida:

```text
Vacía
Marcada
Ambigua
```

---

### Modelo 2: OCR numérico pequeño

Entrada:

```text
Imagen con número manuscrito
```

Salida:

```text
Número reconocido
```

---

## 12. Datos de entrenamiento

---

### 12.1 Formularios reales

Características:

- Marcas reales
- Errores reales
- Ruido real

Problema:

- Requieren etiquetado

---

### 12.2 Formularios sintéticos

Se generarán automáticamente:

- Casillas vacías
- Casillas marcadas
- Diferentes tipos de marcas
- Rotación
- Ruido
- Sombreado
- Iluminación variable

Ventaja:

Permiten entrenar rápidamente.

---

## 13. Estrategia de entrenamiento

Se trabajará en dos fases.

---

### Etapa 1

Entrenamiento inicial con:

```text
Datos sintéticos
```

---

### Etapa 2

Ajuste fino con:

```text
Datos reales
```

---

## 14. Pipeline de entrenamiento

```text
Dataset
   ↓
Preprocesamiento
   ↓
Generación de batches
   ↓
Entrenamiento
   ↓
Validación
   ↓
Optimización
   ↓
Exportación del modelo
```

---

## 15. Tipos de marcas esperadas

El sistema deberá reconocer:

```text
X
✓
●
/////
Sombreado parcial
Relleno completo
```

También deberá detectar:

- Marcas débiles
- Casillas parcialmente llenas
- Doble marcado

---

## 16. Posibles desafíos técnicos

### Calidad de imagen

- Fotos inclinadas
- Baja luz
- Sombras

---

### Errores humanos

- Marcas fuera de casilla
- Doble respuesta
- Borrados

---

### Marcas ambiguas

- X muy tenue
- Sombreado parcial
- Marcas incompletas

---

## 17. Resultado esperado

El sistema deberá devolver respuestas estructuradas.

Ejemplo:

```json
{
  "pregunta_1": "Sí",
  "pregunta_2": "Bus",
  "pregunta_3": "De acuerdo",
  "pregunta_4": {
    "Chocolate": 2,
    "Vainilla": 1,
    "Fresa": 3
  }
}
```

---

## 18. Primera fase de desarrollo

En esta etapa se definirá:

- Diseño físico del formulario
- Tipo de casillas
- Estrategia de segmentación
- Dataset
- Diseño del clasificador
- Integración entre módulos en Python