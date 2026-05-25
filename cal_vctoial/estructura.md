# Arquitectura General del Sistema OMR de Formularios con QR Estructural

## Descripción General

El sistema tiene como objetivo crear, gestionar y procesar formularios físicos (encuestas o fichas de preguntas cerradas) que serán llenados manualmente por usuarios y posteriormente escaneados para extraer automáticamente sus respuestas.

A diferencia de un sistema OMR tradicional, este sistema utilizará un **QR estructural**, el cual almacenará información necesaria para reconstruir el formulario al momento del procesamiento.

El QR contendrá:

- ID del formulario
- Versión de plantilla
- Coordenadas de preguntas
- Coordenadas de opciones
- Tipo de pregunta
- Información de estructura

Esto permitirá que el formulario sea parcialmente autocontenible al momento del escaneo.

---

# Flujo General del Sistema

```text
1. Crear formulario
2. Registrar preguntas
3. Generar estructura
4. Codificar estructura en QR
5. Generar PDF imprimible
6. Imprimir formulario
7. Usuario llena manualmente
8. Escanear documento
9. Leer QR
10. Reconstruir estructura
11. Procesar respuestas
12. Validar resultados
13. Guardar datos
14. Generar reportes
```

---

# Arquitectura Modular del Sistema

El sistema estará compuesto por **6 módulos principales**.

```text
Sistema OMR de Formularios
│
├── Módulo 1: Generador de Formularios
├── Módulo 2: Registro de Estructura y QR
├── Módulo 3: Procesamiento de Imagen
├── Módulo 4: Reconocimiento de Marcas (OMR)
├── Módulo 5: Validación de Respuestas
└── Módulo 6: Reportes y Exportación
```

---

# MÓDULO 1: Generador de Formularios

## Objetivo

Permite crear formularios o encuestas que serán impresos y llenados manualmente.

## Funciones principales

- Crear formulario
- Registrar preguntas
- Registrar opciones
- Diseñar estructura visual
- Posicionar casillas
- Preparar datos para QR
- Generar PDF imprimible

## Subprocesos internos

```text
Crear encuesta
Agregar preguntas
Definir tipo de pregunta
Definir opciones
Diseñar layout
Calcular posiciones
Preparar datos estructurales
Generar PDF
```

## Tipos de preguntas soportadas

- Opción única
- Sí / No
- Escala cerrada
- Selección múltiple
- Preguntas cerradas con casillas

## Componentes de código

```text
SurveyController
SurveyModel
QuestionManager
LayoutGenerator
TemplateDesigner
PDFGenerator
```

---

# MÓDULO 2: Registro de Estructura y QR

## Objetivo

Registrar la estructura exacta del formulario y generar un QR que contenga información estructural para su posterior procesamiento.

## Información que guarda el QR

- form_id
- version
- tipo de pregunta
- coordenadas
- opciones
- cantidad de respuestas
- metadata estructural

## Ejemplo de estructura QR

```json
{
  "form_id": "1001",
  "version": "1.0",
  "questions": [
    {
      "id": 1,
      "type": "single_choice",
      "options": [
        {"label": "A", "x": 120, "y": 200},
        {"label": "B", "x": 220, "y": 200}
      ]
    }
  ]
}
```

## Funciones principales

- Registrar estructura
- Serializar datos
- Codificar coordenadas
- Codificar tipo de pregunta
- Generar QR
- Guardar respaldo en BD

## Subprocesos internos

```text
Capturar estructura
Serializar datos
Codificar información
Generar QR
Guardar estructura
Versionar plantilla
```

## Componentes de código

```text
QRStructureEncoder
QRDataBuilder
CoordinateSerializer
QuestionTypeSerializer
QRGenerator
TemplateStructureService
VersionControl
```

---

# MÓDULO 3: Procesamiento de Imagen

## Objetivo

Preparar el formulario escaneado para análisis.

## Funciones principales

- Cargar imagen
- Leer QR
- Decodificar QR
- Corregir rotación
- Corregir perspectiva
- Eliminar ruido
- Escalar imagen
- Reconstruir estructura desde QR

## Subprocesos internos

```text
Leer imagen
Detectar QR
Decodificar QR
Extraer coordenadas
Corregir inclinación
Quitar ruido
Normalizar tamaño
Preparar regiones de análisis
```

## Componentes de código

```text
ImageProcessor
QRReader
QRDecoder
RotationCorrector
PerspectiveFixer
NoiseCleaner
PreprocessingService
StructureLoader
CoordinateMapper
```

---

# MÓDULO 4: Reconocimiento de Marcas (OMR)

## Objetivo

Detectar automáticamente qué casillas fueron marcadas por el usuario.

## Funciones principales

- Ubicar casillas según QR
- Extraer regiones de respuesta
- Analizar densidad de tinta
- Detectar marcas
- Clasificar respuesta

## Subprocesos internos

```text
Localizar campo
Recortar región
Analizar píxeles
Detectar tinta
Clasificar casilla
Guardar resultado preliminar
```

## Casos detectables

- Casilla marcada
- Casilla vacía
- Doble marcado
- Marcado dudoso

## Componentes de código

```text
OMRService
MarkDetector
AnswerRecognizer
FieldScanner
PixelAnalyzer
RegionExtractor
ResponseClassifier
```

---

# MÓDULO 5: Validación de Respuestas

## Objetivo

Verificar que las respuestas detectadas cumplan las reglas definidas por el formulario.

## Reglas posibles

- Una sola respuesta permitida
- Múltiples respuestas permitidas
- Pregunta obligatoria
- Respuesta vacía
- Respuesta inválida
- Error de marcado

## Funciones principales

- Validar respuesta
- Aplicar reglas según tipo de pregunta
- Detectar inconsistencias
- Generar observaciones

## Subprocesos internos

```text
Leer respuesta
Aplicar reglas
Detectar errores
Clasificar estado
Generar observación
Guardar validación
```

## Componentes de código

```text
ValidationService
RuleEngine
ResponseChecker
ErrorClassifier
QuestionValidator
ObservationGenerator
```

---

# MÓDULO 6: Reportes y Exportación

## Objetivo

Guardar, mostrar y exportar resultados obtenidos del procesamiento.

## Funciones principales

- Guardar respuestas
- Mostrar resultados
- Generar estadísticas
- Exportar Excel
- Exportar PDF
- Historial de formularios

## Subprocesos internos

```text
Guardar datos
Consultar respuestas
Generar resumen
Crear estadísticas
Exportar resultados
Mostrar historial
```

## Componentes de código

```text
ReportService
ExportManager
StatisticsEngine
HistoryManager
DashboardService
DataExporter
```

---

# Arquitectura Técnica General

```text
Aplicación Completa
│
├── Frontend
│   ├── Crear formularios
│   ├── Diseñar preguntas
│   ├── Subir escaneos
│   ├── Ver resultados
│   └── Reportes
│
├── Backend
│   ├── Controladores
│   ├── Servicios
│   ├── Validaciones
│   ├── API
│   └── Lógica de negocio
│
├── Base de Datos
│   ├── Formularios
│   ├── Preguntas
│   ├── Opciones
│   ├── Coordenadas
│   ├── Estructuras QR
│   ├── Respuestas
│   └── Logs
│
├── Motor OMR
│   ├── Lectura QR
│   ├── Procesamiento de imagen
│   ├── Reconocimiento de marcas
│   └── Validación
│
└── Motor de Reportes
```

---

# Desarrollo Interno

Cada módulo tendrá:

- Controladores
- Modelos
- Servicios
- Algoritmos
- Interfaces
- Validaciones
- Acceso a BD

---

# Resumen Final

## El sistema es:

**1 sola aplicación**

Dividida en:

- 6 módulos grandes
- múltiples submódulos
- clases
- algoritmos
- lógica de negocio
- procesamiento de imagen
- reconocimiento OMR

---

# Estimación técnica

```text
6 módulos grandes
20 a 40 submódulos
100+ funciones
Base de datos
Frontend
Backend
Motor OMR
QR estructural
Generador de reportes
```

---

# Tipo de sistema

Este proyecto corresponde a:

**OMR System (Optical Mark Recognition System)**

Con una arquitectura mejorada basada en:

**QR estructural + detección de marcas manuales**

Aplicable para:

- Encuestas físicas
- Formularios administrativos
- Hojas de respuestas
- Procesamiento de fichas
- Evaluaciones de selección cerrada