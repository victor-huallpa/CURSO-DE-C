"""
Script: train_marks.py
Responsabilidad:
    Entrenar un modelo CNN para clasificación de marcas OMR.
    El modelo aprende a distinguir entre casillas vacías, marcadas y ambiguas.

    Este script está preparado para la Fase 2 del proyecto.
    Incluye la arquitectura del modelo, el generador de datos sintéticos
    y el pipeline de entrenamiento.

Entradas:
    - Directorio de imágenes de entrenamiento (datasets/)
Salidas:
    - Modelo entrenado (models/mark_model.pt)
Dependencias:
    - torch
    - torchvision
    - numpy
    - cv2
    - sklearn
"""

import os
import sys
import numpy as np
import cv2
from pathlib import Path

# Agregar directorio raíz al path
ROOT_DIR = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT_DIR))

from app.config import MODELS_DIR, DATASETS_DIR


def generate_synthetic_marks(output_dir: str, num_per_class: int = 500):
    """
    Genera imágenes sintéticas de marcas para entrenamiento.

    Crea tres tipos de imágenes:
    - Vacías: casillas sin marcas
    - Marcadas: casillas con marcas claras (X, relleno)
    - Ambiguas: casillas con marcas parciales

    Parámetros:
        output_dir (str): Directorio donde guardar las imágenes
        num_per_class (int): Número de imágenes por clase
    """
    classes = ["empty", "marked", "ambiguous"]
    size = 28  # Tamaño de cada imagen

    for cls in classes:
        cls_dir = os.path.join(output_dir, cls)
        os.makedirs(cls_dir, exist_ok=True)

        for i in range(num_per_class):
            img = np.ones((size, size), dtype=np.uint8) * 255  # Fondo blanco

            if cls == "empty":
                # Casilla vacía: solo ruido leve
                noise = np.random.randint(0, 20, (size, size), dtype=np.uint8)
                img = cv2.subtract(img, noise)

            elif cls == "marked":
                # Casilla marcada: X o relleno
                mark_type = np.random.choice(["x", "fill", "check"])
                if mark_type == "x":
                    # Dibujar X
                    thickness = np.random.randint(2, 5)
                    cv2.line(img, (3, 3), (size-3, size-3), 0, thickness)
                    cv2.line(img, (size-3, 3), (3, size-3), 0, thickness)
                elif mark_type == "fill":
                    # Relleno parcial o total
                    fill_level = np.random.uniform(0.4, 0.9)
                    mask = np.random.random((size, size)) < fill_level
                    img[mask] = np.random.randint(0, 80, mask.sum())
                else:
                    # Check mark
                    pts = np.array([[3, size//2], [size//3, size-5], [size-3, 3]])
                    cv2.polylines(img, [pts], False, 0, np.random.randint(2, 4))

                # Agregar ruido
                noise = np.random.randint(0, 15, (size, size), dtype=np.uint8)
                img = cv2.subtract(img, noise)

            elif cls == "ambiguous":
                # Marca parcial, borrosa o leve
                mark_type = np.random.choice(["light", "partial", "smudge"])
                if mark_type == "light":
                    fill_level = np.random.uniform(0.1, 0.3)
                    mask = np.random.random((size, size)) < fill_level
                    img[mask] = np.random.randint(100, 200, mask.sum())
                elif mark_type == "partial":
                    # Solo una parte marcada
                    x1 = np.random.randint(2, size//2)
                    y1 = np.random.randint(2, size//2)
                    x2 = np.random.randint(size//2, size-2)
                    y2 = np.random.randint(size//2, size-2)
                    cv2.rectangle(img, (x1, y1), (x2, y2), 
                                np.random.randint(50, 150), -1)
                else:
                    # Mancha
                    center = (np.random.randint(8, 20), np.random.randint(8, 20))
                    radius = np.random.randint(3, 8)
                    cv2.circle(img, center, radius, np.random.randint(80, 180), -1)
                    img = cv2.GaussianBlur(img, (5, 5), 0)

            # Guardar imagen
            filepath = os.path.join(cls_dir, f"{cls}_{i:04d}.png")
            cv2.imwrite(filepath, img)

    print(f"Generadas {num_per_class * len(classes)} imágenes sintéticas en {output_dir}")


def build_mark_model():
    """
    Construye la arquitectura CNN para clasificación de marcas.

    Arquitectura: CNN simple con 3 capas convolucionales
    y 2 capas fully-connected.

    Retorna:
        torch.nn.Module: Modelo CNN sin entrenar
    """
    import torch
    import torch.nn as nn

    class MarkClassifierCNN(nn.Module):
        """
        Red neuronal convolucional para clasificación de marcas OMR.

        Arquitectura:
        - Conv2D(1, 32) → ReLU → MaxPool
        - Conv2D(32, 64) → ReLU → MaxPool
        - Conv2D(64, 64) → ReLU
        - Flatten → Linear(576, 128) → ReLU → Dropout
        - Linear(128, 3) → Softmax

        Entrada: imagen 28x28 en escala de grises (1 canal)
        Salida: 3 clases (vacía, marcada, ambigua)
        """
        def __init__(self):
            super(MarkClassifierCNN, self).__init__()

            self.features = nn.Sequential(
                nn.Conv2d(1, 32, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.MaxPool2d(2, 2),

                nn.Conv2d(32, 64, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.MaxPool2d(2, 2),

                nn.Conv2d(64, 64, kernel_size=3, padding=1),
                nn.ReLU(),
            )

            self.classifier = nn.Sequential(
                nn.Flatten(),
                nn.Linear(64 * 7 * 7, 128),
                nn.ReLU(),
                nn.Dropout(0.5),
                nn.Linear(128, 3)
            )

        def forward(self, x):
            x = self.features(x)
            x = self.classifier(x)
            return x

    return MarkClassifierCNN()


def train_mark_model(data_dir: str = None, epochs: int = 20,
                     batch_size: int = 32, lr: float = 0.001):
    """
    Entrena el modelo de clasificación de marcas.

    Parámetros:
        data_dir (str): Directorio con imágenes de entrenamiento
        epochs (int): Número de épocas de entrenamiento
        batch_size (int): Tamaño del batch
        lr (float): Learning rate

    Retorna:
        dict: Historial de entrenamiento (loss, accuracy por época)
    """
    import torch
    import torch.nn as nn
    import torch.optim as optim
    from torch.utils.data import DataLoader, Dataset
    import torchvision.transforms as transforms

    if data_dir is None:
        data_dir = str(DATASETS_DIR / "synthetic" / "marks")

    # Dataset personalizado
    class MarkDataset(Dataset):
        def __init__(self, root_dir, transform=None):
            self.root_dir = root_dir
            self.transform = transform
            self.samples = []
            self.class_map = {"empty": 0, "marked": 1, "ambiguous": 2}

            for cls_name, cls_id in self.class_map.items():
                cls_dir = os.path.join(root_dir, cls_name)
                if os.path.exists(cls_dir):
                    for fname in os.listdir(cls_dir):
                        if fname.endswith((".png", ".jpg")):
                            self.samples.append((
                                os.path.join(cls_dir, fname), cls_id
                            ))

        def __len__(self):
            return len(self.samples)

        def __getitem__(self, idx):
            img_path, label = self.samples[idx]
            img = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)
            img = cv2.resize(img, (28, 28))

            if self.transform:
                from PIL import Image as PILImage
                img = PILImage.fromarray(img)
                img = self.transform(img)
            else:
                img = torch.FloatTensor(img).unsqueeze(0) / 255.0

            return img, label

    # Transformaciones
    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.5,), (0.5,))
    ])

    # Crear dataset y dataloader
    dataset = MarkDataset(data_dir, transform=transform)

    if len(dataset) == 0:
        print(f"No se encontraron imágenes en {data_dir}")
        print("Generando datos sintéticos...")
        generate_synthetic_marks(data_dir)
        dataset = MarkDataset(data_dir, transform=transform)

    # Dividir en train/val (80/20)
    train_size = int(0.8 * len(dataset))
    val_size = len(dataset) - train_size
    train_dataset, val_dataset = torch.utils.data.random_split(
        dataset, [train_size, val_size]
    )

    train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
    val_loader = DataLoader(val_dataset, batch_size=batch_size)

    # Crear modelo
    model = build_mark_model()
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.Adam(model.parameters(), lr=lr)

    # Entrenamiento
    history = {"train_loss": [], "val_loss": [], "val_accuracy": []}

    for epoch in range(epochs):
        # Fase de entrenamiento
        model.train()
        train_loss = 0.0

        for images, labels in train_loader:
            optimizer.zero_grad()
            outputs = model(images)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()
            train_loss += loss.item()

        train_loss /= len(train_loader)

        # Fase de validación
        model.eval()
        val_loss = 0.0
        correct = 0
        total = 0

        with torch.no_grad():
            for images, labels in val_loader:
                outputs = model(images)
                loss = criterion(outputs, labels)
                val_loss += loss.item()

                _, predicted = torch.max(outputs, 1)
                total += labels.size(0)
                correct += (predicted == labels).sum().item()

        val_loss /= len(val_loader) if len(val_loader) > 0 else 1
        val_accuracy = correct / total if total > 0 else 0

        history["train_loss"].append(train_loss)
        history["val_loss"].append(val_loss)
        history["val_accuracy"].append(val_accuracy)

        print(f"Época {epoch+1}/{epochs} - "
              f"Loss: {train_loss:.4f} - "
              f"Val Loss: {val_loss:.4f} - "
              f"Val Acc: {val_accuracy:.4f}")

    # Guardar modelo
    model_path = MODELS_DIR / "mark_model.pt"
    MODELS_DIR.mkdir(parents=True, exist_ok=True)
    torch.save(model, str(model_path))
    print(f"Modelo guardado en {model_path}")

    return history


if __name__ == "__main__":
    print("=" * 60)
    print("  Entrenamiento del Clasificador de Marcas OMR")
    print("=" * 60)

    # Generar datos sintéticos si no existen
    synthetic_dir = str(DATASETS_DIR / "synthetic" / "marks")
    if not os.path.exists(synthetic_dir):
        print("\nGenerando datos sintéticos de entrenamiento...")
        generate_synthetic_marks(synthetic_dir, num_per_class=1000)

    # Entrenar modelo
    print("\nIniciando entrenamiento...")
    history = train_mark_model(
        data_dir=synthetic_dir,
        epochs=20,
        batch_size=32,
        lr=0.001
    )

    print("\nEntrenamiento completado.")
    print(f"Precisión final de validación: {history['val_accuracy'][-1]:.4f}")
