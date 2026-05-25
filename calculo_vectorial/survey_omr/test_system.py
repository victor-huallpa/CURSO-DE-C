import cv2
import numpy as np
import os
import sys
from pathlib import Path

# Agregar el directorio raíz al path
ROOT_DIR = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT_DIR))

from app.config import OUTPUTS_DIR
from modules.preprocessing import preprocess_full
from modules.geometry import correct_geometry
from modules.segmentation import detect_boxes, crop_regions, group_by_question
from modules.mark_classifier import classify_multiple
from modules.postprocessing import validate_answers
from utils.image_utils import draw_classification_results

def create_synthetic_survey():
    """Crea una imagen de encuesta sintética para pruebas."""
    # Crear imagen blanca de 800x1000
    img = np.ones((1000, 800, 3), dtype=np.uint8) * 255
    
    # Dibujar un borde exterior (para simular el documento)
    cv2.rectangle(img, (20, 20), (780, 980), (0, 0, 0), 2)
    
    # Título
    cv2.putText(img, "ENCUESTA DE PRUEBA", (250, 80), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 0), 2)
    
    # Preguntas y casillas
    y_offset = 150
    box_size = 30
    
    # Pregunta 1: Opción B marcada
    cv2.putText(img, "1. Pregunta uno:", (50, y_offset + 20), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 1)
    for i, opt in enumerate(["A", "B", "C", "D"]):
        x = 250 + i * 80
        cv2.rectangle(img, (x, y_offset), (x + box_size, y_offset + box_size), (0, 0, 0), 2)
        cv2.putText(img, opt, (x + 8, y_offset - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1)
        if opt == "B":
            # Marcar la opción B con una X
            cv2.line(img, (x, y_offset), (x + box_size, y_offset + box_size), (0, 0, 0), 3)
            cv2.line(img, (x + box_size, y_offset), (x, y_offset + box_size), (0, 0, 0), 3)
            
    y_offset += 100
    
    # Pregunta 2: Opción C marcada (relleno)
    cv2.putText(img, "2. Pregunta dos:", (50, y_offset + 20), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 1)
    for i, opt in enumerate(["A", "B", "C", "D"]):
        x = 250 + i * 80
        cv2.rectangle(img, (x, y_offset), (x + box_size, y_offset + box_size), (0, 0, 0), 2)
        cv2.putText(img, opt, (x + 8, y_offset - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1)
        if opt == "C":
            # Marcar la opción C rellenándola
            cv2.rectangle(img, (x + 5, y_offset + 5), (x + box_size - 5, y_offset + box_size - 5), (0, 0, 0), -1)

    y_offset += 100
    
    # Pregunta 3: Vacía
    cv2.putText(img, "3. Pregunta tres:", (50, y_offset + 20), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0), 1)
    for i, opt in enumerate(["A", "B", "C", "D"]):
        x = 250 + i * 80
        cv2.rectangle(img, (x, y_offset), (x + box_size, y_offset + box_size), (0, 0, 0), 2)
        cv2.putText(img, opt, (x + 8, y_offset - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1)

    # Guardar la imagen
    os.makedirs(OUTPUTS_DIR, exist_ok=True)
    test_path = os.path.join(OUTPUTS_DIR, "test_survey.jpg")
    cv2.imwrite(test_path, img)
    return test_path, img

def run_test():
    print("1. Generando encuesta sintética...")
    test_path, image = create_synthetic_survey()
    print(f"   Imagen guardada en: {test_path}")
    
    print("\n2. Ejecutando preprocesamiento...")
    prep_results = preprocess_full(image, noise_method="gaussian", threshold_method="otsu")
    binary = prep_results["binary"]
    
    print("\n3. Detectando casillas...")
    boxes = detect_boxes(binary)
    print(f"   Casillas detectadas: {len(boxes)}")
    
    print("\n4. Recortando y clasificando regiones...")
    regions = crop_regions(image, boxes)
    binary_regions = crop_regions(binary, boxes)
    
    classifications = classify_multiple(binary_regions, method="threshold")
    for i, cls in enumerate(classifications):
        regions[i].update(cls)
        
    print("\n5. Agrupando por pregunta y validando...")
    grouped = group_by_question(regions)
    
    # Preparar para validación
    grouped_cls = {}
    for q_id, q_regions in grouped.items():
        grouped_cls[q_id] = q_regions
        
    validated = validate_answers(grouped_cls)
    
    print("\n=== RESULTADOS FINALES ===")
    for q_id, answer in validated["answers"].items():
        print(f"Pregunta {q_id}: {answer}")
        
    print("\n=== RESUMEN ===")
    print(validated["summary"])
    
    # Dibujar resultados
    annotated = draw_classification_results(image, boxes, classifications)
    annotated_path = os.path.join(OUTPUTS_DIR, "test_survey_annotated.jpg")
    cv2.imwrite(annotated_path, annotated)
    print(f"\nImagen con resultados guardada en: {annotated_path}")

if __name__ == "__main__":
    run_test()
