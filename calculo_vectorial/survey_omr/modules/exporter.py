"""
Módulo: exporter.py
Responsabilidad:
    Exportar los resultados del procesamiento OMR a diferentes formatos.
    Soporta exportación a JSON, CSV y SQLite.

Entradas:
    - Resultados validados del postprocesamiento
Salidas:
    - Archivos JSON, CSV o registros en base de datos SQLite
Dependencias:
    - json (librería estándar)
    - csv (librería estándar)
    - sqlite3 (librería estándar)
    - pandas
    - app.config
"""

import json
import csv
import sqlite3
import os
from datetime import datetime
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from app.config import (
    OUTPUTS_DIR,
    DATABASE_FILE,
    DATABASE_TABLE
)

# Intentar importar pandas (opcional para CSV mejorado)
try:
    import pandas as pd
    PANDAS_AVAILABLE = True
except ImportError:
    PANDAS_AVAILABLE = False


def export_json(results: dict, filename: str = None,
                output_dir: str = None) -> str:
    """
    Exporta los resultados a un archivo JSON.

    Genera un archivo JSON estructurado con las respuestas,
    advertencias, errores y metadata del procesamiento.

    Parámetros:
        results (dict): Resultados validados del postprocesamiento.
            Debe contener al menos 'answers'.
        filename (str, opcional): Nombre del archivo de salida.
            Si no se proporciona, se genera automáticamente con timestamp.
        output_dir (str, opcional): Directorio de salida.
            Si no se proporciona, usa OUTPUTS_DIR de config.

    Retorna:
        str: Ruta completa del archivo JSON generado
    """
    # Configurar directorio de salida
    if output_dir is None:
        output_dir = str(OUTPUTS_DIR)

    os.makedirs(output_dir, exist_ok=True)

    # Generar nombre de archivo si no se proporciona
    if filename is None:
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        filename = f"resultados_omr_{timestamp}.json"

    # Asegurar extensión .json
    if not filename.endswith(".json"):
        filename += ".json"

    filepath = os.path.join(output_dir, filename)

    # Preparar datos para exportación
    export_data = _prepare_export_data(results)

    # Escribir archivo JSON con formato legible
    with open(filepath, "w", encoding="utf-8") as f:
        json.dump(export_data, f, ensure_ascii=False, indent=2)

    return filepath


def export_json_string(results: dict) -> str:
    """
    Exporta los resultados como cadena JSON (sin escribir archivo).

    Útil para descargas directas desde la interfaz web.

    Parámetros:
        results (dict): Resultados validados

    Retorna:
        str: Cadena JSON formateada
    """
    export_data = _prepare_export_data(results)
    return json.dumps(export_data, ensure_ascii=False, indent=2)


def export_csv(results: dict, filename: str = None,
               output_dir: str = None) -> str:
    """
    Exporta los resultados a un archivo CSV.

    Genera un archivo CSV con una fila por pregunta,
    incluyendo la respuesta seleccionada y el estado.

    Parámetros:
        results (dict): Resultados validados del postprocesamiento.
        filename (str, opcional): Nombre del archivo de salida.
        output_dir (str, opcional): Directorio de salida.

    Retorna:
        str: Ruta completa del archivo CSV generado
    """
    # Configurar directorio de salida
    if output_dir is None:
        output_dir = str(OUTPUTS_DIR)

    os.makedirs(output_dir, exist_ok=True)

    # Generar nombre de archivo
    if filename is None:
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        filename = f"resultados_omr_{timestamp}.csv"

    if not filename.endswith(".csv"):
        filename += ".csv"

    filepath = os.path.join(output_dir, filename)

    # Preparar datos tabulares
    rows = _prepare_csv_rows(results)

    if PANDAS_AVAILABLE and len(rows) > 0:
        # Usar pandas para CSV más robusto
        df = pd.DataFrame(rows)
        df.to_csv(filepath, index=False, encoding="utf-8-sig")
    else:
        # Fallback a csv estándar
        if len(rows) > 0:
            fieldnames = rows[0].keys()
            with open(filepath, "w", newline="", encoding="utf-8-sig") as f:
                writer = csv.DictWriter(f, fieldnames=fieldnames)
                writer.writeheader()
                writer.writerows(rows)
        else:
            # Archivo vacío con headers
            with open(filepath, "w", newline="", encoding="utf-8-sig") as f:
                writer = csv.writer(f)
                writer.writerow(["pregunta", "respuesta", "estado", "confianza"])

    return filepath


def export_csv_string(results: dict) -> str:
    """
    Exporta los resultados como cadena CSV (sin escribir archivo).

    Parámetros:
        results (dict): Resultados validados

    Retorna:
        str: Cadena CSV formateada
    """
    import io

    rows = _prepare_csv_rows(results)

    if PANDAS_AVAILABLE and len(rows) > 0:
        df = pd.DataFrame(rows)
        return df.to_csv(index=False)
    else:
        output = io.StringIO()
        if len(rows) > 0:
            writer = csv.DictWriter(output, fieldnames=rows[0].keys())
            writer.writeheader()
            writer.writerows(rows)
        return output.getvalue()


def save_to_database(results: dict, db_path: str = None,
                     table_name: str = None) -> int:
    """
    Guarda los resultados en una base de datos SQLite.

    Crea la tabla si no existe y agrega los resultados como
    registros individuales.

    Parámetros:
        results (dict): Resultados validados del postprocesamiento.
        db_path (str, opcional): Ruta a la base de datos SQLite.
            Si no se proporciona, usa DATABASE_FILE de config.
        table_name (str, opcional): Nombre de la tabla.
            Si no se proporciona, usa DATABASE_TABLE de config.

    Retorna:
        int: Número de registros insertados
    """
    if db_path is None:
        db_path = str(DATABASE_FILE)

    if table_name is None:
        table_name = DATABASE_TABLE

    # Asegurar que el directorio existe
    os.makedirs(os.path.dirname(db_path) if os.path.dirname(db_path) else ".", exist_ok=True)

    # Conectar a la base de datos
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()

    # Crear tabla si no existe
    cursor.execute(f"""
        CREATE TABLE IF NOT EXISTS {table_name} (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            fecha_procesamiento TEXT NOT NULL,
            pregunta TEXT NOT NULL,
            respuesta TEXT,
            estado TEXT NOT NULL,
            confianza REAL,
            fill_ratio REAL,
            advertencias TEXT,
            formulario_id TEXT
        )
    """)

    # Preparar registros
    timestamp = datetime.now().isoformat()
    formulario_id = datetime.now().strftime("%Y%m%d%H%M%S")

    answers = results.get("answers", {})
    details = results.get("details", {})
    rows_inserted = 0

    for q_id, answer in answers.items():
        detail = details.get(q_id, {})
        status = detail.get("status", "unknown")

        # Formatear la respuesta
        if isinstance(answer, dict):
            respuesta = json.dumps(answer, ensure_ascii=False)
        elif answer is None:
            respuesta = ""
        else:
            respuesta = str(answer)

        # Obtener confianza y fill_ratio de las opciones marcadas
        marked = detail.get("marked", [])
        confidence = marked[0]["confidence"] if marked else 0.0
        fill_ratio = marked[0]["fill_ratio"] if marked else 0.0

        # Recopilar advertencias para esta pregunta
        question_warnings = [
            w["message"] for w in results.get("warnings", [])
            if w.get("question") == q_id
        ]
        warnings_str = "; ".join(question_warnings) if question_warnings else ""

        cursor.execute(f"""
            INSERT INTO {table_name}
            (fecha_procesamiento, pregunta, respuesta, estado,
             confianza, fill_ratio, advertencias, formulario_id)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?)
        """, (
            timestamp, str(q_id), respuesta, status,
            confidence, fill_ratio, warnings_str, formulario_id
        ))

        rows_inserted += 1

    # Confirmar cambios y cerrar conexión
    conn.commit()
    conn.close()

    return rows_inserted


def _prepare_export_data(results: dict) -> dict:
    """
    Prepara los datos para exportación en formato estructurado.

    Limpia y formatea los resultados para que sean serializables
    a JSON y legibles.

    Parámetros:
        results (dict): Resultados crudos del postprocesamiento

    Retorna:
        dict: Datos preparados para exportación
    """
    export = {
        "metadata": {
            "fecha_procesamiento": datetime.now().isoformat(),
            "sistema": "Survey OMR System",
            "version": "1.0.0"
        },
        "resumen": results.get("summary", {}),
        "respuestas": {},
        "advertencias": results.get("warnings", []),
        "errores": results.get("errors", []),
        "correcciones": results.get("corrections", [])
    }

    # Formatear respuestas
    for q_id, answer in results.get("answers", {}).items():
        export["respuestas"][str(q_id)] = answer

    return export


def _prepare_csv_rows(results: dict) -> list:
    """
    Prepara filas para exportación CSV.

    Convierte los resultados a formato tabular plano.

    Parámetros:
        results (dict): Resultados del postprocesamiento

    Retorna:
        list[dict]: Lista de diccionarios representando filas CSV
    """
    rows = []
    answers = results.get("answers", {})
    details = results.get("details", {})

    for q_id, answer in answers.items():
        detail = details.get(q_id, {})

        # Formatear respuesta
        if isinstance(answer, dict):
            respuesta = str(answer.get("selected", answer.get("suggested", "")))
        elif answer is None:
            respuesta = "(sin respuesta)"
        else:
            respuesta = str(answer)

        # Obtener estado
        status = detail.get("status", "unknown")

        # Obtener confianza
        marked = detail.get("marked", [])
        confidence = marked[0]["confidence"] if marked else 0.0

        rows.append({
            "pregunta": str(q_id),
            "respuesta": respuesta,
            "estado": status,
            "confianza": round(confidence, 4),
            "marcadas": len(detail.get("marked", [])),
            "ambiguas": len(detail.get("ambiguous", [])),
            "vacias": len(detail.get("empty", []))
        })

    return rows
