"""
Script: train_numbers.py
Responsabilidad:
    Entrenar un modelo para reconocimiento de números manuscritos.
    Se usa para leer valores de ranking en formularios OMR.

    Este script está preparado para la Fase 3 del proyecto.
    Usa datos del dataset MNIST como base y puede complementarse
    con datos propios.

Entradas:
    - Dataset MNIST o imágenes propias de números
Salidas:
    - Modelo entrenado (models/numeric_model.pt)
Dependencias:
    - torch
    - torchvision
    - numpy
"""

import os
import sys
from pathlib import Path

ROOT_DIR = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT_DIR))

from app.config import MODELS_DIR, DATASETS_DIR


def build_number_model():
    """
    Construye la arquitectura CNN para reconocimiento de dígitos.

    Arquitectura similar a LeNet-5, optimizada para dígitos manuscritos.

    Retorna:
        torch.nn.Module: Modelo CNN sin entrenar
    """
    import torch.nn as nn

    class NumberRecognizerCNN(nn.Module):
        """
        Red neuronal para reconocimiento de dígitos manuscritos (0-9).

        Arquitectura tipo LeNet:
        - Conv2D(1, 32) → ReLU → MaxPool
        - Conv2D(32, 64) → ReLU → MaxPool
        - Flatten → Linear(1600, 256) → ReLU → Dropout
        - Linear(256, 10) → Softmax

        Entrada: imagen 28x28 en escala de grises
        Salida: 10 clases (dígitos 0-9)
        """
        def __init__(self):
            super(NumberRecognizerCNN, self).__init__()

            self.features = nn.Sequential(
                nn.Conv2d(1, 32, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.MaxPool2d(2, 2),

                nn.Conv2d(32, 64, kernel_size=3, padding=1),
                nn.ReLU(),
                nn.MaxPool2d(2, 2),
            )

            self.classifier = nn.Sequential(
                nn.Flatten(),
                nn.Linear(64 * 7 * 7, 256),
                nn.ReLU(),
                nn.Dropout(0.5),
                nn.Linear(256, 10)
            )

        def forward(self, x):
            x = self.features(x)
            x = self.classifier(x)
            return x

    return NumberRecognizerCNN()


def train_number_model(epochs: int = 15, batch_size: int = 64,
                       lr: float = 0.001, use_mnist: bool = True):
    """
    Entrena el modelo de reconocimiento de números.

    Puede usar el dataset MNIST (descarga automática) o
    un dataset personalizado.

    Parámetros:
        epochs (int): Número de épocas
        batch_size (int): Tamaño del batch
        lr (float): Learning rate
        use_mnist (bool): Si usar MNIST como dataset base

    Retorna:
        dict: Historial de entrenamiento
    """
    import torch
    import torch.nn as nn
    import torch.optim as optim
    from torch.utils.data import DataLoader
    import torchvision
    import torchvision.transforms as transforms

    # Transformaciones
    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.5,), (0.5,))
    ])

    # Cargar dataset
    data_dir = str(DATASETS_DIR / "mnist")
    os.makedirs(data_dir, exist_ok=True)

    if use_mnist:
        train_dataset = torchvision.datasets.MNIST(
            root=data_dir, train=True, download=True, transform=transform
        )
        test_dataset = torchvision.datasets.MNIST(
            root=data_dir, train=False, download=True, transform=transform
        )
    else:
        print("Dataset personalizado no implementado. Usando MNIST.")
        train_dataset = torchvision.datasets.MNIST(
            root=data_dir, train=True, download=True, transform=transform
        )
        test_dataset = torchvision.datasets.MNIST(
            root=data_dir, train=False, download=True, transform=transform
        )

    train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
    test_loader = DataLoader(test_dataset, batch_size=batch_size)

    # Crear modelo
    model = build_number_model()
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.Adam(model.parameters(), lr=lr)

    # Entrenamiento
    history = {"train_loss": [], "test_loss": [], "test_accuracy": []}

    for epoch in range(epochs):
        # Entrenamiento
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

        # Evaluación
        model.eval()
        test_loss = 0.0
        correct = 0
        total = 0

        with torch.no_grad():
            for images, labels in test_loader:
                outputs = model(images)
                loss = criterion(outputs, labels)
                test_loss += loss.item()

                _, predicted = torch.max(outputs, 1)
                total += labels.size(0)
                correct += (predicted == labels).sum().item()

        test_loss /= len(test_loader)
        test_accuracy = correct / total

        history["train_loss"].append(train_loss)
        history["test_loss"].append(test_loss)
        history["test_accuracy"].append(test_accuracy)

        print(f"Época {epoch+1}/{epochs} - "
              f"Loss: {train_loss:.4f} - "
              f"Test Loss: {test_loss:.4f} - "
              f"Test Acc: {test_accuracy:.4f}")

    # Guardar modelo
    model_path = MODELS_DIR / "numeric_model.pt"
    MODELS_DIR.mkdir(parents=True, exist_ok=True)
    torch.save(model, str(model_path))
    print(f"Modelo guardado en {model_path}")

    return history


if __name__ == "__main__":
    print("=" * 60)
    print("  Entrenamiento del Reconocedor de Números OMR")
    print("=" * 60)

    print("\nIniciando entrenamiento con MNIST...")
    history = train_number_model(
        epochs=15,
        batch_size=64,
        lr=0.001
    )

    print("\nEntrenamiento completado.")
    print(f"Precisión final de test: {history['test_accuracy'][-1]:.4f}")
