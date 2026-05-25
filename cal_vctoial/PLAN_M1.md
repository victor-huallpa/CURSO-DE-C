# MÓDULO 1 – PLAN DE DESARROLLO
## Generador de Formularios OMR (Guía de implementación)

---

# Estado actual

Entorno listo:

✔ Python 3.12  
✔ venv funcionando  
✔ Flask instalado  
✔ SQLAlchemy instalado  
✔ OpenCV instalado  
✔ NumPy instalado  
✔ pyzbar instalado  
✔ qrcode instalado  
✔ reportlab instalado  
✔ pandas instalado  
✔ LaTeX listo  
✔ estructura de carpetas creada  

---

# Objetivo del módulo 1

Construir el sistema que permita:

- crear formularios
- crear preguntas
- crear opciones
- definir tipo de pregunta
- calcular layout
- generar coordenadas
- generar QR
- generar LaTeX
- generar PDF imprimible

---

# Estrategia de desarrollo

NO se hará todo junto.

El módulo se divide en partes pequeñas.

Esto permite:

- detectar errores rápido
- probar por partes
- evitar rehacer código
- construir base sólida

---

# PARTE 1 – Núcleo Flask + Configuración

## Objetivo

Levantar el servidor correctamente.

---

## Archivos

```text
app/config.py
app/__init__.py
run.py
```

---

## Qué debe hacer

### config.py

Debe cargar:

- SECRET_KEY
- DATABASE_URL
- DEBUG
- rutas base

---

### __init__.py

Debe inicializar:

- Flask
- SQLAlchemy
- Flask-Migrate
- dotenv

Registrar:

- rutas
- modelos

---

### run.py

Debe arrancar:

```text
create_app()
```

---

## Resultado esperado

Al ejecutar:

```bash
python run.py
```

Debe iniciar servidor Flask.

---

# PARTE 2 – Modelos Base de Datos

## Objetivo

Crear estructura de BD real.

---

## Archivos

```text
app/models/
    survey.py
    question.py
    option.py
    __init__.py
```

---

## Modelos

---

### Survey

Representa formulario.

Campos:

- id
- title
- description
- page_size
- margins
- qr_position
- columns
- created_at

Relación:

- 1 survey → muchas questions

---

### Question

Representa pregunta.

Campos:

- id
- survey_id
- question_number
- text
- question_type
- required
- max_answers
- layout_direction
- position

Relación:

- 1 question → muchas options

---

### Option

Representa casilla marcable.

Campos:

- id
- question_id
- option_text
- x
- y
- width
- height
- bubble_shape
- is_correct (opcional)

---

## Resultado esperado

Ejecutar:

```bash
flask db migrate -m "initial models"
flask db upgrade
```

Debe crear BD correctamente.

---

# PARTE 3 – CRUD Formularios

## Objetivo

Crear formularios desde web.

---

## Archivos

```text
controllers/survey_controller.py
routes/web.py
templates/
```

---

## Funciones

- crear formulario
- listar formularios
- editar
- eliminar
- ver detalle

---

## Resultado esperado

Desde navegador:

```text
/form/create
```

Debe permitir crear formulario.

---

# PARTE 4 – CRUD Preguntas y Opciones

## Objetivo

Agregar preguntas al formulario.

---

## Funciones

Crear:

- preguntas
- opciones
- tipo de pregunta
- validaciones

---

## Tipos soportados

- single_choice
- yes_no
- scale
- multiple_choice
- closed_box

---

## Resultado esperado

Formulario ya podrá construirse completo.

---

# PARTE 5 – Layout Engine

## Objetivo

Calcular coordenadas OMR.

---

## Archivo

```text
services/layout_service.py
```

---

## Debe calcular

- x
- y
- width
- height
- spacing
- columnas
- posición QR

---

## Resultado esperado

Cada opción tendrá coordenadas exactas.

---

# PARTE 6 – QR Generator

## Objetivo

Generar QR ligero.

---

## Archivo

```text
services/qr_service.py
```

---

## QR contendrá

Ejemplo:

```json
{
  "survey_id": 12,
  "version": "A",
  "layout_hash": "abc123",
  "question_map_ref": "db"
}
```

---

## Resultado esperado

Generar imagen QR automáticamente.

---

# PARTE 7 – LaTeX Builder

## Objetivo

Convertir estructura → TEX.

---

## Archivo

```text
services/latex_service.py
```

---

## Debe dibujar

- preguntas
- opciones
- casillas
- QR
- layout

---

## IMPORTANTE

Python calcula posiciones.

LaTeX solo dibuja.

---

# PARTE 8 – PDF Compiler

## Objetivo

Compilar TEX → PDF.

---

## Archivo

```text
services/pdf_service.py
```

---

## Debe ejecutar

```bash
pdflatex
```

---

## Resultado esperado

PDF final generado.

---

# Flujo completo del módulo

```text
Crear formulario
↓
Agregar preguntas
↓
Agregar opciones
↓
Definir tipo
↓
Calcular layout
↓
Guardar coordenadas
↓
Generar QR
↓
Generar TEX
↓
Compilar PDF
↓
PDF listo
```

---

# Orden REAL de trabajo

---

## Primero

PARTE 1

- config.py
- __init__.py
- run.py

---

## Segundo

PARTE 2

- survey.py
- question.py
- option.py

---

## Tercero

Migraciones

---

## Cuarto

CRUD formulario

---

## Quinto

CRUD preguntas

---

## Sexto

Layout

---

## Séptimo

QR

---

## Octavo

LaTeX

---

## Noveno

PDF

---

# Regla de desarrollo

NO avanzar a la siguiente parte hasta probar la anterior.

---

# Próximo paso

EMPEZAR CON:

## PARTE 1 + PARTE 2

Archivos a programar:

```text
app/config.py
app/__init__.py
run.py

app/models/survey.py
app/models/question.py
app/models/option.py
app/models/__init__.py
```

---

# Estado esperado después de PARTE 1 + PARTE 2

Debe funcionar:

✔ Flask levanta  
✔ Base de datos inicializa  
✔ Migraciones funcionan  
✔ Tablas se crean  
✔ Modelos listos  
✔ Proyecto base estable