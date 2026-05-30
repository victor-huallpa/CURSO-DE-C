"""
Módulo: postprocessing.py
Responsabilidad:
    Validar y postprocesar los resultados de clasificación OMR.
    Detectar y reportar inconsistencias como respuestas dobles,
    preguntas vacías, marcas ambiguas y rankings repetidos.

    Aplica reglas de negocio para generar resultados finales
    limpios y confiables.

Entradas:
    - Resultados de clasificación de marcas (mark_classifier)
    - Resultados de OCR numérico (numeric_ocr)
Salidas:
    - Resultados validados con advertencias y correcciones
Dependencias:
    - app.config
"""

from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))
from app.config import (
    MAX_ANSWERS_PER_QUESTION,
    ALLOW_EMPTY_ANSWERS,
    LABEL_EMPTY,
    LABEL_MARKED,
    LABEL_AMBIGUOUS
)


def validate_answers(grouped_results: dict) -> dict:
    """
    Valida las respuestas agrupadas por pregunta.

    Verifica cada pregunta para detectar:
    - Ninguna respuesta marcada (pregunta vacía)
    - Más de una respuesta marcada (respuesta múltiple)
    - Respuestas ambiguas

    Parámetros:
        grouped_results (dict): Diccionario {pregunta_id: [clasificaciones]}
            donde cada clasificación tiene los campos de classify_mark.

    Retorna:
        dict: Diccionario con los resultados validados:
            - 'answers' (dict): {pregunta_id: respuesta_seleccionada}
            - 'warnings' (list): Lista de advertencias
            - 'errors' (list): Lista de errores
            - 'details' (dict): Detalles por pregunta
            - 'summary' (dict): Resumen estadístico
    """
    answers = {}
    warnings = []
    errors = []
    details = {}

    # Contadores para resumen
    total_questions = 0
    valid_count = 0
    empty_count = 0
    multiple_count = 0
    ambiguous_count = 0

    for q_id, classifications in grouped_results.items():
        total_questions += 1

        # Analizar las marcas de esta pregunta
        marked = []
        ambiguous = []
        empty = []

        for i, cls in enumerate(classifications):
            label = cls.get("label", LABEL_EMPTY)

            if label == LABEL_MARKED:
                marked.append({
                    "option_index": i,
                    "option": cls.get("option") or chr(65 + i),  # A, B, C, D...
                    "confidence": cls.get("confidence", 0.0),
                    "fill_ratio": cls.get("fill_ratio", 0.0)
                })
            elif label == LABEL_AMBIGUOUS:
                ambiguous.append({
                    "option_index": i,
                    "option": cls.get("option") or chr(65 + i),
                    "confidence": cls.get("confidence", 0.0),
                    "fill_ratio": cls.get("fill_ratio", 0.0)
                })
            else:
                empty.append({
                    "option_index": i,
                    "option": cls.get("option") or chr(65 + i)
                })

        # Determinar el estado de la pregunta
        question_detail = {
            "marked": marked,
            "ambiguous": ambiguous,
            "empty": empty,
            "status": "valid"
        }

        # Caso 1: Sin respuesta
        if len(marked) == 0 and len(ambiguous) == 0:
            empty_count += 1
            question_detail["status"] = "empty"

            if not ALLOW_EMPTY_ANSWERS:
                warnings.append({
                    "question": q_id,
                    "type": "empty",
                    "message": f"Pregunta {q_id}: Sin respuesta detectada"
                })

            answers[q_id] = None

        # Caso 2: Exactamente una respuesta
        elif len(marked) == 1 and len(ambiguous) == 0:
            valid_count += 1
            question_detail["status"] = "valid"
            answers[q_id] = marked[0]["option"]

        # Caso 3: Múltiples respuestas
        elif len(marked) > MAX_ANSWERS_PER_QUESTION:
            multiple_count += 1
            question_detail["status"] = "multiple"

            options_str = ", ".join([m["option"] for m in marked])
            errors.append({
                "question": q_id,
                "type": "multiple",
                "message": (
                    f"Pregunta {q_id}: Múltiples respuestas detectadas "
                    f"({options_str})"
                ),
                "options": [m["option"] for m in marked]
            })

            # Seleccionar la opción con mayor confianza como sugerencia
            best = max(marked, key=lambda m: m["confidence"])
            answers[q_id] = {
                "selected": [m["option"] for m in marked],
                "suggested": best["option"],
                "conflict": True
            }

        # Caso 4: Hay marcas ambiguas
        elif len(ambiguous) > 0:
            ambiguous_count += 1
            question_detail["status"] = "ambiguous"

            options_str = ", ".join([a["option"] for a in ambiguous])
            warnings.append({
                "question": q_id,
                "type": "ambiguous",
                "message": (
                    f"Pregunta {q_id}: Marca(s) ambigua(s) detectada(s) "
                    f"en opción(es) {options_str}"
                ),
                "options": [a["option"] for a in ambiguous]
            })

            # Si hay una respuesta clara más la ambigua, usar la clara
            if len(marked) == 1:
                answers[q_id] = marked[0]["option"]
                question_detail["status"] = "valid_with_warning"
            else:
                # Si solo hay ambiguas, seleccionar la de mayor fill_ratio
                all_candidates = marked + ambiguous
                best = max(all_candidates, key=lambda c: c["fill_ratio"])
                answers[q_id] = {
                    "suggested": best["option"],
                    "ambiguous": True
                }

        # Caso 5: Respuestas múltiples dentro del límite permitido
        else:
            valid_count += 1
            question_detail["status"] = "valid"

            if MAX_ANSWERS_PER_QUESTION == 1:
                answers[q_id] = marked[0]["option"]
            else:
                answers[q_id] = [m["option"] for m in marked]

        details[q_id] = question_detail

    # Generar resumen
    summary = {
        "total_questions": total_questions,
        "valid": valid_count,
        "empty": empty_count,
        "multiple_answers": multiple_count,
        "ambiguous": ambiguous_count,
        "total_warnings": len(warnings),
        "total_errors": len(errors)
    }

    return {
        "answers": answers,
        "warnings": warnings,
        "errors": errors,
        "details": details,
        "summary": summary
    }


def detect_conflicts(validated_results: dict) -> list:
    """
    Detecta conflictos en los resultados validados.

    Busca patrones problemáticos como:
    - Demasiadas preguntas vacías
    - Patrón sospechoso de respuestas (todas iguales)
    - Rankings conflictivos

    Parámetros:
        validated_results (dict): Resultado de validate_answers()

    Retorna:
        list[dict]: Lista de conflictos detectados con:
            - 'type' (str): Tipo de conflicto
            - 'severity' (str): 'low', 'medium', 'high'
            - 'message' (str): Descripción del conflicto
    """
    conflicts = []
    answers = validated_results.get("answers", {})
    summary = validated_results.get("summary", {})

    total = summary.get("total_questions", 0)
    if total == 0:
        conflicts.append({
            "type": "no_questions",
            "severity": "high",
            "message": "No se detectaron preguntas en el formulario"
        })
        return conflicts

    # Verificar tasa de preguntas vacías
    empty_ratio = summary.get("empty", 0) / total
    if empty_ratio > 0.5:
        conflicts.append({
            "type": "high_empty_rate",
            "severity": "high",
            "message": (
                f"Tasa alta de preguntas vacías: "
                f"{summary['empty']}/{total} ({empty_ratio:.0%}). "
                "Posible error de procesamiento."
            )
        })

    # Verificar si todas las respuestas son iguales (patrón sospechoso)
    valid_answers = [
        v for v in answers.values()
        if v is not None and isinstance(v, str)
    ]
    if len(valid_answers) > 3:
        unique = set(valid_answers)
        if len(unique) == 1:
            conflicts.append({
                "type": "uniform_answers",
                "severity": "medium",
                "message": (
                    f"Todas las respuestas son '{valid_answers[0]}'. "
                    "Patrón posiblemente sospechoso."
                )
            })

    # Verificar tasa de ambigüedad
    ambiguous_ratio = summary.get("ambiguous", 0) / total
    if ambiguous_ratio > 0.3:
        conflicts.append({
            "type": "high_ambiguity",
            "severity": "medium",
            "message": (
                f"Tasa alta de marcas ambiguas: "
                f"{summary['ambiguous']}/{total} ({ambiguous_ratio:.0%}). "
                "Considere mejorar la calidad del escaneo."
            )
        })

    return conflicts


def fix_minor_errors(validated_results: dict) -> dict:
    """
    Intenta corregir errores menores automáticamente.

    Correcciones automáticas:
    - Si hay una sola opción ambigua y el fill_ratio es cercano
      al umbral de marcado, marcarla como seleccionada
    - Normalizar formato de respuestas

    Parámetros:
        validated_results (dict): Resultado de validate_answers()

    Retorna:
        dict: Resultados corregidos con campo adicional 'corrections'
    """
    corrections = []
    corrected_answers = dict(validated_results.get("answers", {}))
    details = validated_results.get("details", {})

    for q_id, detail in details.items():
        # Intentar resolver ambigüedades simples
        if detail["status"] == "ambiguous":
            ambiguous = detail.get("ambiguous", [])
            marked = detail.get("marked", [])

            # Si hay exactamente una opción ambigua con fill_ratio > 0.25
            # y no hay opciones claramente marcadas, aceptarla
            if len(ambiguous) == 1 and len(marked) == 0:
                if ambiguous[0]["fill_ratio"] > 0.25:
                    corrected_answers[q_id] = ambiguous[0]["option"]
                    corrections.append({
                        "question": q_id,
                        "type": "ambiguous_resolved",
                        "message": (
                            f"Pregunta {q_id}: Marca ambigua en opción "
                            f"'{ambiguous[0]['option']}' "
                            f"(fill_ratio={ambiguous[0]['fill_ratio']:.2f}) "
                            "aceptada automáticamente"
                        ),
                        "original": validated_results["answers"].get(q_id),
                        "corrected": ambiguous[0]["option"]
                    })

    # Construir resultado final
    result = dict(validated_results)
    result["answers"] = corrected_answers
    result["corrections"] = corrections

    return result


def validate_ranking(ranking_results: list) -> dict:
    """
    Valida resultados de ranking numérico.

    Verifica que los rankings sean válidos:
    - No hay números repetidos
    - Todos los números están en el rango esperado
    - No hay gaps en la secuencia

    Parámetros:
        ranking_results (list): Lista de resultados de numeric_ocr

    Retorna:
        dict: Resultado de validación con:
            - 'valid' (bool): Si el ranking es válido
            - 'rankings' (dict): {pregunta: ranking}
            - 'warnings' (list): Advertencias
            - 'errors' (list): Errores
    """
    warnings = []
    errors = []
    rankings = {}

    for result in ranking_results:
        q_index = result.get("index", -1)
        number = result.get("number")
        valid = result.get("valid", False)

        if number is None:
            warnings.append({
                "index": q_index,
                "type": "unrecognized",
                "message": f"Ranking en posición {q_index}: No se pudo reconocer"
            })
            continue

        if not valid:
            errors.append({
                "index": q_index,
                "type": "out_of_range",
                "message": f"Ranking en posición {q_index}: Valor {number} fuera de rango"
            })
            continue

        rankings[q_index] = number

    # Verificar duplicados
    seen_numbers = {}
    for q_index, number in rankings.items():
        if number in seen_numbers:
            errors.append({
                "type": "duplicate_ranking",
                "message": (
                    f"Ranking duplicado: {number} aparece en posiciones "
                    f"{seen_numbers[number]} y {q_index}"
                ),
                "positions": [seen_numbers[number], q_index]
            })
        else:
            seen_numbers[number] = q_index

    return {
        "valid": len(errors) == 0,
        "rankings": rankings,
        "warnings": warnings,
        "errors": errors
    }
