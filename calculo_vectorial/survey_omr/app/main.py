"""
Módulo: main.py
Responsabilidad:
    Interfaz web principal del sistema OMR usando Streamlit.
    Proporciona una interfaz moderna estilo dashboard para:
    - Cargar formularios escaneados
    - Visualizar el procesamiento
    - Mostrar resultados de detección
    - Exportar resultados

    Esta es la entrada principal de la aplicación.

Entradas:
    - Archivos cargados por el usuario (imágenes o PDFs)
Salidas:
    - Visualización interactiva de resultados
    - Archivos exportados (JSON, CSV)
Dependencias:
    - streamlit
    - Todos los módulos del sistema OMR
"""

import streamlit as st
import numpy as np
import cv2
import sys
import os
from pathlib import Path
from datetime import datetime

# Configurar el path del proyecto
ROOT_DIR = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT_DIR))

# Importar módulos del sistema
from app.config import (
    APP_TITLE, APP_DESCRIPTION, MAX_FILE_SIZE_MB,
    PREVIEW_MAX_WIDTH, VALID_EXTENSIONS, OUTPUTS_DIR,
    LABEL_MARKED, LABEL_EMPTY, LABEL_AMBIGUOUS
)
from modules.input_handler import load_image, load_pdf, validate_uploaded_file
from modules.preprocessing import preprocess_full
from modules.geometry import correct_geometry
from modules.segmentation import detect_boxes, crop_regions, extract_answer_regions, group_by_question
from modules.mark_classifier import classify_mark, classify_multiple
from modules.postprocessing import validate_answers, detect_conflicts, fix_minor_errors
from modules.exporter import export_json_string, export_csv_string, export_json, export_csv, save_to_database
from utils.image_utils import bgr_to_rgb, draw_boxes, draw_classification_results, resize_image
from utils.validation_utils import validate_processing_input


# =============================================================================
# CONFIGURACIÓN DE LA PÁGINA
# =============================================================================

st.set_page_config(
    page_title="Sistema OMR - Reconocimiento de Encuestas",
    page_icon="📋",
    layout="wide",
    initial_sidebar_state="expanded"
)


# =============================================================================
# ESTILOS CSS PERSONALIZADOS
# =============================================================================

def apply_custom_styles():
    """
    Aplica estilos CSS personalizados para lograr un diseño
    moderno, minimalista y profesional tipo dashboard.
    """
    st.markdown("""
    <style>
        /* Tema general */
        .stApp {
            background: linear-gradient(135deg, #0f0c29 0%, #1a1a3e 50%, #24243e 100%);
        }

        /* Sidebar */
        section[data-testid="stSidebar"] {
            background: linear-gradient(180deg, #1e1e3f 0%, #2d2d5e 100%);
            border-right: 1px solid rgba(255,255,255,0.1);
        }

        section[data-testid="stSidebar"] .stMarkdown {
            color: #e0e0ff;
        }

        /* Cards / contenedores */
        div[data-testid="stExpander"] {
            background: rgba(255,255,255,0.05);
            border: 1px solid rgba(255,255,255,0.1);
            border-radius: 12px;
        }

        /* Título principal */
        .main-title {
            font-size: 2.5rem;
            font-weight: 800;
            background: linear-gradient(90deg, #667eea 0%, #764ba2 100%);
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            margin-bottom: 0;
            text-align: center;
        }

        .subtitle {
            font-size: 1.1rem;
            color: #9999cc;
            text-align: center;
            margin-bottom: 2rem;
        }

        /* Métricas */
        div[data-testid="stMetric"] {
            background: rgba(255,255,255,0.05);
            border: 1px solid rgba(255,255,255,0.1);
            border-radius: 12px;
            padding: 1rem;
        }

        div[data-testid="stMetric"] label {
            color: #9999cc !important;
        }

        div[data-testid="stMetric"] div[data-testid="stMetricValue"] {
            color: #e0e0ff !important;
        }

        /* Botones */
        .stButton > button {
            background: linear-gradient(90deg, #667eea 0%, #764ba2 100%);
            color: white;
            border: none;
            border-radius: 8px;
            padding: 0.6rem 2rem;
            font-weight: 600;
            transition: all 0.3s ease;
        }

        .stButton > button:hover {
            transform: translateY(-2px);
            box-shadow: 0 6px 20px rgba(102, 126, 234, 0.4);
        }

        /* Uploader */
        div[data-testid="stFileUploader"] {
            background: rgba(255,255,255,0.03);
            border: 2px dashed rgba(102, 126, 234, 0.4);
            border-radius: 12px;
            padding: 1rem;
        }

        /* Tablas */
        .stDataFrame {
            border-radius: 12px;
            overflow: hidden;
        }

        /* Tabs */
        .stTabs [data-baseweb="tab-list"] {
            gap: 8px;
        }

        .stTabs [data-baseweb="tab"] {
            background: rgba(255,255,255,0.05);
            border-radius: 8px;
            color: #9999cc;
            padding: 0.5rem 1rem;
        }

        .stTabs [aria-selected="true"] {
            background: linear-gradient(90deg, #667eea 0%, #764ba2 100%);
            color: white;
        }

        /* Status cards */
        .status-card {
            background: rgba(255,255,255,0.05);
            border: 1px solid rgba(255,255,255,0.1);
            border-radius: 12px;
            padding: 1.2rem;
            margin: 0.5rem 0;
        }

        .status-success {
            border-left: 4px solid #00d4aa;
        }

        .status-warning {
            border-left: 4px solid #ffc107;
        }

        .status-error {
            border-left: 4px solid #ff4757;
        }

        /* Alertas */
        .stAlert {
            border-radius: 12px;
        }

        /* Divisor */
        hr {
            border-color: rgba(255,255,255,0.1);
        }

        /* Download buttons */
        .stDownloadButton > button {
            background: rgba(255,255,255,0.1);
            border: 1px solid rgba(255,255,255,0.2);
            color: #e0e0ff;
        }

        .stDownloadButton > button:hover {
            background: rgba(255,255,255,0.15);
        }
    </style>
    """, unsafe_allow_html=True)


# =============================================================================
# FUNCIONES DE LA INTERFAZ
# =============================================================================

def render_header():
    """Renderiza el encabezado principal de la aplicación."""
    st.markdown('<h1 class="main-title">📋 Sistema OMR</h1>', unsafe_allow_html=True)
    st.markdown(
        '<p class="subtitle">Reconocimiento Automático de Encuestas y Formularios Estructurados</p>',
        unsafe_allow_html=True
    )


def render_sidebar():
    """
    Renderiza la barra lateral con configuración y ayuda.

    Retorna:
        dict: Configuración seleccionada por el usuario
    """
    with st.sidebar:
        st.markdown("## ⚙️ Configuración")
        st.markdown("---")

        # Método de clasificación
        classification_method = st.selectbox(
            "🔬 Método de clasificación",
            options=["threshold", "model"],
            index=0,
            help="'threshold': Método clásico por píxeles. 'model': CNN (requiere modelo entrenado)"
        )

        # Método de binarización
        threshold_method = st.selectbox(
            "📊 Binarización",
            options=["otsu", "adaptive", "simple"],
            index=0,
            help="Método de binarización para preprocesamiento"
        )

        # Método de ruido
        noise_method = st.selectbox(
            "🔇 Reducción de ruido",
            options=["gaussian", "median"],
            index=0,
            help="Método de filtrado de ruido"
        )

        # Estrategia de segmentación
        segmentation_strategy = st.selectbox(
            "📐 Segmentación",
            options=["auto", "fixed"],
            index=0,
            help="'auto': Detección automática. 'fixed': Coordenadas predefinidas"
        )

        st.markdown("---")

        # Opciones de exportación
        st.markdown("### 📤 Exportación")
        save_db = st.checkbox("💾 Guardar en base de datos", value=False)

        st.markdown("---")

        # Información del sistema
        st.markdown("### ℹ️ Información")
        st.markdown(f"""
        <div class="status-card">
            <strong>Versión:</strong> 1.0.0<br>
            <strong>Fase:</strong> 1 (Clásico)<br>
            <strong>Formatos:</strong> JPG, PNG, PDF<br>
            <strong>Máx. archivo:</strong> {MAX_FILE_SIZE_MB}MB
        </div>
        """, unsafe_allow_html=True)

        st.markdown("---")
        st.markdown(
            "🧠 *Desarrollado como proyecto de ingeniería de software*"
        )

    return {
        "classification_method": classification_method,
        "threshold_method": threshold_method,
        "noise_method": noise_method,
        "segmentation_strategy": segmentation_strategy,
        "save_db": save_db
    }


def render_upload_zone():
    """
    Renderiza la zona de carga de archivos.

    Retorna:
        UploadedFile or None: Archivo cargado por el usuario
    """
    st.markdown("### 📁 Cargar Formulario")

    uploaded_file = st.file_uploader(
        "Arrastra o selecciona un archivo escaneado",
        type=["jpg", "jpeg", "png", "pdf"],
        help=f"Formatos aceptados: JPG, JPEG, PNG, PDF. Máximo: {MAX_FILE_SIZE_MB}MB",
        key="file_uploader"
    )

    return uploaded_file


def process_image(image: np.ndarray, config: dict) -> dict:
    """
    Ejecuta el pipeline completo de procesamiento OMR.

    Parámetros:
        image (np.ndarray): Imagen del formulario (BGR)
        config (dict): Configuración de procesamiento

    Retorna:
        dict: Resultados completos del procesamiento
    """
    results = {
        "steps": {},
        "boxes": [],
        "regions": [],
        "classifications": [],
        "grouped": {},
        "validated": {},
        "conflicts": [],
        "final": {},
        "success": False
    }

    try:
        # === PASO 1: Validación de entrada ===
        with st.spinner("🔍 Validando imagen..."):
            validation = validate_processing_input(image)
            results["steps"]["validation"] = validation

            if not validation["valid"]:
                st.error("❌ La imagen no pasó la validación")
                for err in validation["errors"]:
                    st.error(err)
                return results

            # Mostrar advertencias de calidad
            for warn in validation.get("warnings", []):
                st.warning(f"⚠️ {warn}")

        # === PASO 2: Preprocesamiento ===
        with st.spinner("🔧 Preprocesando imagen..."):
            preprocess_results = preprocess_full(
                image,
                noise_method=config["noise_method"],
                threshold_method=config["threshold_method"]
            )
            results["steps"]["preprocessing"] = {
                k: v.shape for k, v in preprocess_results.items()
            }

        # === PASO 3: Corrección geométrica ===
        with st.spinner("📐 Corrigiendo geometría..."):
            geometry_results = correct_geometry(image)
            corrected_image = geometry_results["final"]
            results["steps"]["geometry"] = {
                "document_detected": geometry_results["document_points"] is not None
            }

        # === PASO 4: Preprocesar la imagen corregida ===
        with st.spinner("🔧 Preprocesando imagen corregida..."):
            corrected_preprocess = preprocess_full(
                corrected_image,
                noise_method=config["noise_method"],
                threshold_method=config["threshold_method"]
            )
            binary = corrected_preprocess["binary"]

        # === PASO 5: Segmentación ===
        with st.spinner("✂️ Detectando casillas..."):
            boxes = detect_boxes(binary)
            results["boxes"] = boxes

            regions = crop_regions(corrected_image, boxes)
            results["regions"] = regions

            st.info(f"📊 Se detectaron **{len(boxes)}** casillas")

        # === PASO 6: Clasificación ===
        with st.spinner("🏷️ Clasificando marcas..."):
            # Clasificar cada región usando la imagen binaria
            binary_regions = crop_regions(binary, boxes)
            classifications = classify_multiple(
                binary_regions,
                method=config["classification_method"]
            )
            results["classifications"] = classifications

        # === PASO 7: Agrupar por pregunta ===
        with st.spinner("📋 Agrupando respuestas..."):
            # Agregar clasificación a las regiones
            for i, cls in enumerate(classifications):
                if i < len(regions):
                    regions[i].update(cls)

            grouped = group_by_question(regions)
            results["grouped"] = grouped

        # === PASO 8: Postprocesamiento ===
        with st.spinner("✅ Validando respuestas..."):
            # Preparar datos para validación
            grouped_cls = {}
            for q_id, q_regions in grouped.items():
                grouped_cls[q_id] = q_regions

            validated = validate_answers(grouped_cls)
            validated = fix_minor_errors(validated)
            conflicts = detect_conflicts(validated)

            results["validated"] = validated
            results["conflicts"] = conflicts
            results["final"] = validated
            results["success"] = True

        # Guardar imágenes procesadas para visualización
        results["images"] = {
            "original": image,
            "preprocessed": preprocess_results,
            "corrected": corrected_image,
            "binary": binary
        }

    except Exception as e:
        st.error(f"❌ Error en el procesamiento: {str(e)}")
        results["error"] = str(e)

    return results


def render_results(results: dict, config: dict):
    """
    Renderiza los resultados del procesamiento OMR.

    Parámetros:
        results (dict): Resultados del procesamiento
        config (dict): Configuración usada
    """
    if not results.get("success", False):
        return

    validated = results.get("validated", {})
    summary = validated.get("summary", {})
    answers = validated.get("answers", {})
    warnings = validated.get("warnings", [])
    errors = validated.get("errors", [])
    corrections = validated.get("corrections", [])
    conflicts = results.get("conflicts", [])

    # === MÉTRICAS RESUMEN ===
    st.markdown("### 📊 Resumen de Resultados")

    col1, col2, col3, col4 = st.columns(4)

    with col1:
        st.metric(
            "📝 Preguntas",
            summary.get("total_questions", 0)
        )
    with col2:
        st.metric(
            "✅ Válidas",
            summary.get("valid", 0),
            delta=None
        )
    with col3:
        st.metric(
            "⚠️ Ambiguas",
            summary.get("ambiguous", 0),
            delta=None
        )
    with col4:
        st.metric(
            "❌ Errores",
            summary.get("total_errors", 0),
            delta=None
        )

    st.markdown("---")

    # === TABS PRINCIPALES ===
    tab1, tab2, tab3, tab4 = st.tabs([
        "📋 Respuestas", "🖼️ Visualización", "⚠️ Advertencias", "📤 Exportar"
    ])

    # --- Tab 1: Respuestas ---
    with tab1:
        st.markdown("#### Respuestas Detectadas")

        if len(answers) > 0:
            import pandas as pd

            rows = []
            for q_id, answer in answers.items():
                detail = validated.get("details", {}).get(q_id, {})
                status = detail.get("status", "unknown")

                # Formatear respuesta
                if isinstance(answer, dict):
                    resp_str = str(answer.get("suggested", answer.get("selected", "?")))
                    if answer.get("conflict"):
                        resp_str += " ⚠️"
                    elif answer.get("ambiguous"):
                        resp_str += " ❓"
                elif answer is None:
                    resp_str = "— (sin respuesta)"
                else:
                    resp_str = str(answer)

                # Icono de estado
                status_icons = {
                    "valid": "✅",
                    "valid_with_warning": "⚠️",
                    "empty": "⬜",
                    "multiple": "❌",
                    "ambiguous": "❓"
                }
                status_icon = status_icons.get(status, "❔")

                rows.append({
                    "Pregunta": f"Pregunta {q_id}",
                    "Respuesta": resp_str,
                    "Estado": f"{status_icon} {status}",
                })

            df = pd.DataFrame(rows)
            st.dataframe(df, use_container_width=True, hide_index=True)
        else:
            st.info("No se detectaron respuestas")

    # --- Tab 2: Visualización ---
    with tab2:
        st.markdown("#### Pipeline de Procesamiento")

        images = results.get("images", {})

        if images:
            # Imagen original vs procesada
            vis_col1, vis_col2 = st.columns(2)

            with vis_col1:
                st.markdown("**📷 Original**")
                if "original" in images:
                    st.image(
                        bgr_to_rgb(resize_image(images["original"], PREVIEW_MAX_WIDTH)),
                        use_column_width=True
                    )

            with vis_col2:
                st.markdown("**🔧 Procesada (Binaria)**")
                if "binary" in images:
                    st.image(
                        resize_image(images["binary"], PREVIEW_MAX_WIDTH),
                        use_column_width=True
                    )

            # Imagen con casillas detectadas
            if len(results.get("boxes", [])) > 0 and "corrected" in images:
                st.markdown("#### 🎯 Casillas Detectadas")

                annotated = draw_classification_results(
                    images["corrected"],
                    results["boxes"],
                    results["classifications"]
                )
                st.image(
                    bgr_to_rgb(resize_image(annotated, PREVIEW_MAX_WIDTH)),
                    use_column_width=True
                )

                # Leyenda
                st.markdown("""
                <div style="display: flex; gap: 2rem; justify-content: center; margin: 1rem 0;">
                    <span>🟢 Marcada</span>
                    <span>🔴 Vacía</span>
                    <span>🟡 Ambigua</span>
                </div>
                """, unsafe_allow_html=True)

            # Etapas de preprocesamiento
            with st.expander("🔍 Ver etapas de preprocesamiento"):
                preprocess = images.get("preprocessed", {})
                if preprocess:
                    pp_cols = st.columns(4)
                    step_names = [
                        ("original", "Original"),
                        ("grayscale", "Escala de grises"),
                        ("contrast", "Contraste"),
                        ("binary", "Binaria")
                    ]
                    for i, (key, label) in enumerate(step_names):
                        with pp_cols[i]:
                            st.markdown(f"**{label}**")
                            if key in preprocess:
                                img = preprocess[key]
                                img_display = bgr_to_rgb(img) if len(img.shape) > 2 else img
                                st.image(resize_image(img_display, 200))

    # --- Tab 3: Advertencias ---
    with tab3:
        st.markdown("#### Advertencias y Errores")

        if len(errors) > 0:
            st.markdown("##### ❌ Errores")
            for err in errors:
                st.markdown(f"""
                <div class="status-card status-error">
                    <strong>{err.get('type', 'error')}</strong><br>
                    {err.get('message', '')}
                </div>
                """, unsafe_allow_html=True)

        if len(warnings) > 0:
            st.markdown("##### ⚠️ Advertencias")
            for warn in warnings:
                st.markdown(f"""
                <div class="status-card status-warning">
                    <strong>{warn.get('type', 'warning')}</strong><br>
                    {warn.get('message', '')}
                </div>
                """, unsafe_allow_html=True)

        if len(corrections) > 0:
            st.markdown("##### 🔧 Correcciones Automáticas")
            for cor in corrections:
                st.markdown(f"""
                <div class="status-card status-success">
                    <strong>{cor.get('type', '')}</strong><br>
                    {cor.get('message', '')}
                </div>
                """, unsafe_allow_html=True)

        if len(conflicts) > 0:
            st.markdown("##### 🔍 Conflictos Detectados")
            for conf in conflicts:
                severity_color = {
                    "high": "status-error",
                    "medium": "status-warning",
                    "low": "status-success"
                }
                css_class = severity_color.get(conf.get("severity", "low"), "")
                st.markdown(f"""
                <div class="status-card {css_class}">
                    <strong>[{conf.get('severity', '').upper()}]</strong> {conf.get('message', '')}
                </div>
                """, unsafe_allow_html=True)

        if len(errors) == 0 and len(warnings) == 0 and len(conflicts) == 0:
            st.success("✅ No se detectaron problemas")

    # --- Tab 4: Exportar ---
    with tab4:
        st.markdown("#### Exportar Resultados")

        exp_col1, exp_col2, exp_col3 = st.columns(3)

        with exp_col1:
            # Exportar JSON
            json_str = export_json_string(validated)
            st.download_button(
                label="📄 Descargar JSON",
                data=json_str,
                file_name=f"resultados_omr_{datetime.now().strftime('%Y%m%d_%H%M%S')}.json",
                mime="application/json",
                use_container_width=True
            )

        with exp_col2:
            # Exportar CSV
            csv_str = export_csv_string(validated)
            st.download_button(
                label="📊 Descargar CSV",
                data=csv_str,
                file_name=f"resultados_omr_{datetime.now().strftime('%Y%m%d_%H%M%S')}.csv",
                mime="text/csv",
                use_container_width=True
            )

        with exp_col3:
            # Guardar en BD
            if st.button("💾 Guardar en BD", use_container_width=True):
                try:
                    rows = save_to_database(validated)
                    st.success(f"✅ {rows} registros guardados en la base de datos")
                except Exception as e:
                    st.error(f"❌ Error al guardar: {str(e)}")

        # Vista previa del JSON
        with st.expander("👁️ Vista previa JSON"):
            st.json(validated.get("answers", {}))


# =============================================================================
# FLUJO PRINCIPAL
# =============================================================================

def main():
    """
    Función principal de la aplicación Streamlit.

    Orquesta el flujo completo:
    1. Configuración del sidebar
    2. Carga del archivo
    3. Validación
    4. Procesamiento
    5. Visualización de resultados
    6. Exportación
    """
    # Aplicar estilos
    apply_custom_styles()

    # Header
    render_header()

    # Sidebar con configuración
    config = render_sidebar()

    # Zona principal
    st.markdown("---")

    # Zona de carga
    uploaded_file = render_upload_zone()

    if uploaded_file is not None:
        # Validar archivo
        validation = validate_uploaded_file(uploaded_file)

        if not validation["valid"]:
            st.error(f"❌ {validation['error']}")
            return

        st.success(f"✅ Archivo cargado: **{uploaded_file.name}** ({validation['file_type']})")

        # Cargar la imagen
        try:
            if validation["file_type"] == "image":
                image = load_image(uploaded_file)
                images = [image]
            else:
                images = load_pdf(uploaded_file)
                st.info(f"📄 PDF con **{len(images)}** páginas detectadas")
        except Exception as e:
            st.error(f"❌ Error al cargar archivo: {str(e)}")
            return

        # Si es PDF con múltiples páginas, permitir seleccionar
        if len(images) > 1:
            page_num = st.slider(
                "Seleccionar página",
                1, len(images), 1,
                key="page_selector"
            )
            current_image = images[page_num - 1]
        else:
            current_image = images[0]

        # Vista previa
        col_preview, col_info = st.columns([2, 1])

        with col_preview:
            st.markdown("#### 📷 Vista Previa")
            preview = resize_image(current_image, PREVIEW_MAX_WIDTH)
            st.image(bgr_to_rgb(preview), use_column_width=True)

        with col_info:
            st.markdown("#### 📐 Información")
            h, w = current_image.shape[:2]
            st.metric("Dimensiones", f"{w} × {h}")
            st.metric("Canales", current_image.shape[2] if len(current_image.shape) > 2 else 1)
            size_kb = current_image.nbytes / 1024
            st.metric("Tamaño", f"{size_kb:.0f} KB")

        st.markdown("---")

        # Botón de procesamiento
        col_btn = st.columns([1, 2, 1])
        with col_btn[1]:
            process_clicked = st.button(
                "🚀 Procesar Formulario",
                use_container_width=True,
                type="primary"
            )

        if process_clicked:
            st.markdown("---")
            st.markdown("### ⏳ Procesando...")

            # Ejecutar pipeline
            results = process_image(current_image, config)

            if results["success"]:
                st.balloons()
                st.markdown("---")
                render_results(results, config)

                # Guardar en BD si está configurado
                if config["save_db"]:
                    try:
                        rows = save_to_database(results["validated"])
                        st.sidebar.success(f"💾 {rows} registros guardados")
                    except Exception as e:
                        st.sidebar.error(f"Error BD: {str(e)}")

    else:
        # Estado inicial: mostrar instrucciones
        st.markdown("""
        <div style="text-align: center; padding: 3rem; color: #9999cc;">
            <p style="font-size: 4rem; margin-bottom: 1rem;">📋</p>
            <h3>Bienvenido al Sistema OMR</h3>
            <p style="max-width: 500px; margin: 1rem auto;">
                Cargue una imagen o documento PDF de un formulario escaneado
                para comenzar el procesamiento automático.
            </p>
            <p style="font-size: 0.9rem; opacity: 0.7;">
                Formatos soportados: JPG, JPEG, PNG, PDF
            </p>
        </div>
        """, unsafe_allow_html=True)

        # Flujo visual del sistema
        with st.expander("📖 ¿Cómo funciona?"):
            st.markdown("""
            **Flujo de procesamiento:**

            1. 📁 **Carga** → Suba su formulario escaneado
            2. 🔍 **Validación** → Verificación de formato y calidad
            3. 🔧 **Preprocesamiento** → Escala de grises, ruido, binarización
            4. 📐 **Corrección** → Perspectiva y rotación
            5. ✂️ **Segmentación** → Detección de casillas
            6. 🏷️ **Clasificación** → Marcada / Vacía / Ambigua
            7. ✅ **Validación** → Reglas de negocio
            8. 📤 **Exportación** → JSON, CSV o base de datos
            """)


# Punto de entrada
if __name__ == "__main__":
    main()
