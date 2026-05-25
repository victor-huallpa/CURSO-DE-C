# MÓDULO 1 – Generador de Formularios
## Configuración y Desarrollo Base (Entorno ya configurado)

---

# Objetivo del módulo

Permite crear formularios o encuestas desde una interfaz web para luego:

- definir preguntas
- definir opciones
- diseñar estructura
- calcular posiciones exactas
- preparar metadata para QR
- generar PDF imprimible usando LaTeX

---

# Estado actual del entorno

El entorno virtual y dependencias YA están configuradas.

Dependencias instaladas:

- Flask
- Flask-SQLAlchemy
- Flask-Migrate
- Flask-WTF
- SQLAlchemy
- OpenCV
- NumPy
- pyzbar
- qrcode
- Pillow
- reportlab
- pandas
- openpyxl
- python-dotenv
- Jinja2

No es necesario volver a instalar dependencias.

Solo recordar trabajar siempre con:

```bash
source venv/bin/activate
```

---

# Objetivo técnico del módulo

Este módulo será responsable de:

1. Crear formularios
2. Crear preguntas
3. Crear opciones
4. Definir tipo de pregunta
5. Calcular layout
6. Generar coordenadas OMR
7. Preparar datos QR
8. Generar archivo LaTeX
9. Compilar PDF final

---

# Tecnologías del módulo

## Backend

- Python 3.12+
- Flask
- SQLAlchemy
- Flask-Migrate
- Flask-WTF

---

## Frontend

- HTML
- CSS
- JavaScript
- Jinja2

---

## PDF

- LaTeX
- pdflatex

---

## QR

- qrcode
- pyzbar

---

## OMR Layout

- NumPy
- OpenCV

---

# Estructura del proyecto

```text
omr_system/
│
├── app/
│   ├── __init__.py
│   ├── config.py
│   │
│   ├── models/
│   │   ├── survey.py
│   │   ├── question.py
│   │   └── option.py
│   │
│   ├── controllers/
│   │   ├── survey_controller.py
│   │   └── question_controller.py
│   │
│   ├── services/
│   │   ├── qr_service.py
│   │   ├── latex_service.py
│   │   ├── pdf_service.py
│   │   └── layout_service.py
│   │
│   ├── templates/
│   │   ├── base.html
│   │   ├── create_form.html
│   │   └── preview.html
│   │
│   ├── static/
│   │   ├── css/
│   │   ├── js/
│   │   └── images/
│   │
│   └── routes/
│       └── web.py
│
├── latex/
│   ├── templates/
│   │   └── survey_template.tex
│   │
│   └── output/
│
├── generated_qr/
├── migrations/
├── instance/
│
├── requirements.txt
├── run.py
└── .env
```

---

# Variables de entorno

Archivo:

```text
.env
```

Contenido:

```env
FLASK_APP=run.py
FLASK_ENV=development
SECRET_KEY=tu_clave_secreta
DATABASE_URL=sqlite:///database.db
```

---

# Base de datos del módulo

---

## Tabla surveys

Representa un formulario general.

Campos:

- id
- title
- description
- page_size
- margins
- qr_position
- columns
- created_at

---

## Tabla questions

Representa cada pregunta.

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

---

## Tabla options

Representa opciones marcables.

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

# Tipos de preguntas soportadas

---

## single_choice

Una sola respuesta.

Ejemplo:

```text
( ) A
( ) B
( ) C
```

---

## yes_no

Ejemplo:

```text
( ) SI
( ) NO
```

---

## scale

Ejemplo:

```text
1 2 3 4 5
```

---

## multiple_choice

Ejemplo:

```text
[ ] A
[ ] B
[ ] C
```

---

## closed_box

Casillas personalizadas.

---

# Arquitectura interna del módulo

---

## Submódulo 1.1 – Modelos BD

Archivos:

```text
app/models/
    survey.py
    question.py
    option.py
```

Responsable de:

- estructura de BD
- relaciones
- validaciones

---

## Submódulo 1.2 – CRUD Web

Archivos:

```text
controllers/
routes/
templates/
```

Responsable de:

- crear formulario
- editar
- eliminar
- cargar datos

---

## Submódulo 1.3 – Layout Generator

Archivo:

```text
services/layout_service.py
```

Responsable de:

- calcular coordenadas
- tamaño de burbujas
- columnas
- spacing
- posición OMR exacta

---

## Submódulo 1.4 – QR Builder

Archivo:

```text
services/qr_service.py
```

Responsable de:

- generar QR
- generar hash
- guardar referencia de layout

---

## Submódulo 1.5 – LaTeX Builder

Archivo:

```text
services/latex_service.py
```

Responsable de:

- construir `.tex`

---

## Submódulo 1.6 – PDF Compiler

Archivo:

```text
services/pdf_service.py
```

Responsable de:

- compilar TEX
- generar PDF final

---

# Diseño correcto del QR

IMPORTANTE:

El QR NO debe guardar todo el examen completo.

Debe guardar referencia ligera:

```json
{
  "survey_id": 12,
  "version": "A",
  "layout_hash": "abc123",
  "question_map_ref": "db"
}
```

---

# ¿Por qué así?

Porque la base de datos guardará:

- coordenadas
- tipos de preguntas
- opciones
- layout

Y el QR solo permitirá:

- identificar examen
- validar versión
- buscar estructura

---

# Flujo interno del módulo

```text
Usuario entra a interfaz web
↓
Crea formulario
↓
Agrega preguntas
↓
Define opciones
↓
Selecciona tipo de pregunta
↓
Sistema calcula layout
↓
Sistema genera coordenadas exactas
↓
Sistema guarda estructura en BD
↓
Sistema genera QR
↓
Sistema construye LaTeX
↓
Python compila PDF
↓
PDF final generado
```

---

# Flujo futuro del OMR (módulos posteriores)

Cuando una hoja sea escaneada:

```text
Sistema lee QR
↓
Obtiene survey_id
↓
Busca estructura en BD
↓
Obtiene coordenadas
↓
Detecta burbujas
↓
Evalúa marcas
↓
Guarda respuestas
```

---

# Inicialización Flask

Archivo:

```text
run.py
```

Contenido:

```python
from app import create_app

app = create_app()

if __name__ == "__main__":
    app.run(debug=True)
```

---

# Orden correcto de desarrollo

NO empezar por todo a la vez.

Orden recomendado:

---

## Paso 1

Crear:

- Survey model
- Question model
- Option model

---

## Paso 2

Crear:

```text
app/__init__.py
```

---

## Paso 3

Crear:

```text
config.py
```

---

## Paso 4

Migraciones:

```bash
flask db init
flask db migrate -m "initial tables"
flask db upgrade
```

---

## Paso 5

CRUD de formularios

---

## Paso 6

Layout service

---

## Paso 7

QR service

---

## Paso 8

LaTeX service

---

## Paso 9

PDF compiler

---

# Comandos útiles

Activar entorno:

```bash
source venv/bin/activate
```

---

Guardar dependencias:

```bash
pip freeze > requirements.txt
```

---

Ejecutar servidor:

```bash
flask run
```

o

```bash
python run.py
```

---

# Estado esperado al finalizar módulo 1

Debe quedar funcionando:

✔ Creación de formularios  
✔ Creación de preguntas  
✔ Creación de opciones  
✔ Tipos de preguntas  
✔ Layout calculado  
✔ Coordenadas OMR generadas  
✔ QR generado  
✔ LaTeX generado  
✔ PDF final generado  
✔ Base de datos funcionando

---

# NOTA IMPORTANTE

Python calculará todo el layout.

LaTeX NO decidirá posiciones.

LaTeX solo dibujará usando coordenadas que Python ya calculó.

Esto evita errores de detección OMR.