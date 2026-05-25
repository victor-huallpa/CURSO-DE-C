# Marco Matemático del Sistema de Reconocimiento de Encuestas Estructuradas (OMR)

## 1. Introducción

El desarrollo de un sistema de reconocimiento automático de encuestas estructuradas (OMR, *Optical Mark Recognition*) requiere una base matemática enfocada en el análisis y procesamiento de imágenes digitales, la detección de patrones y la clasificación de respuestas.

El sistema propuesto tiene como objetivo:

* Detectar formularios estructurados.
* Corregir deformaciones geométricas.
* Localizar preguntas y casillas.
* Identificar marcas realizadas por el usuario.
* Aplicar OCR en campos requeridos.
* Clasificar automáticamente respuestas.

Para ello, el sistema integra conceptos de:

* Álgebra lineal
* Geometría analítica y proyectiva
* Procesamiento digital de imágenes
* Morfología matemática
* Probabilidad y estadística
* Cálculo diferencial y vectorial
* Optimización matemática
* Machine Learning
* Reconocimiento de patrones

---

## 2. Álgebra Lineal

### 2.1 Vectores

Aplicaciones:

* Representación de características (*features*)
* Coordenadas espaciales
* Vectores de entrada en modelos de clasificación

### 2.2 Matrices

Las imágenes digitales se modelan como matrices bidimensionales de intensidad.

Aplicaciones:

* Representación de imágenes
* Convoluciones
* Filtros
* Transformaciones geométricas

### 2.3 Transformaciones Lineales

Aplicaciones:

* Rotación
* Escalamiento
* Traslación
* Corrección geométrica

### 2.4 Normas y Distancias

Norma Euclidiana:

[
||x||_2 = \sqrt{x_1^2+x_2^2+\cdots+x_n^2}
]

Aplicaciones:

* Comparación de patrones
* Similitud entre vectores
* Clasificación

---

## 3. Geometría Analítica y Proyectiva

### 3.1 Sistema de Coordenadas Cartesianas

Aplicaciones:

* Detección de casillas
* Localización de preguntas
* Bounding boxes

### 3.2 Distancia Euclidiana

[
d(p,q)=\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}
]

### 3.3 Transformaciones Afines

Aplicaciones:

* Rotación
* Traslación
* Escalado
* Alineación de formularios

### 3.4 Homografías

[
x' = Hx
]

Aplicaciones:

* Corrección de perspectiva
* Normalización del formulario

---

## 4. Procesamiento Digital de Imágenes

### 4.1 Imagen Digital

[
f(x,y)
]

### 4.2 Muestreo y Cuantización

Aplicaciones:

* Escaneo
* Digitalización de formularios

### 4.3 Histogramas

Aplicaciones:

* Mejora de contraste
* Análisis de iluminación

### 4.4 Convolución

[
(f*g)(x,y)=\sum_m \sum_n f(m,n)g(x-m,y-n)
]

Aplicaciones:

* Filtrado
* Detección de bordes
* Suavizado

### 4.5 Filtros Espaciales

Aplicaciones:

* Reducción de ruido
* Realce de imagen

---

## 5. Thresholding (Umbralización)

### 5.1 Umbral Binario

[
g(x,y)=
\begin{cases}
1 & \text{si } f(x,y) > T \
0 & \text{si no}
\end{cases}
]

Aplicaciones:

* Convertir imagen a binaria
* Separar fondo y marca

### 5.2 Método de Otsu

[
T^* = \arg\max \sigma_b^2(T)
]

Aplicaciones:

* Binarización automática

---

## 6. Morfología Matemática

### 6.1 Dilatación

Aplicaciones:

* Unir trazos
* Conectar marcas

### 6.2 Erosión

Aplicaciones:

* Eliminar ruido

### 6.3 Apertura

Aplicaciones:

* Eliminar partículas pequeñas

### 6.4 Cierre

Aplicaciones:

* Cerrar huecos

---

## 7. Análisis de Regiones y Contornos

### 7.1 Connected Components

Aplicaciones:

* Detectar blobs
* Separar casillas

### 7.2 Bounding Boxes

Aplicaciones:

* Localizar preguntas
* OCR

### 7.3 Momentos de Imagen

[
M_{pq} = \sum_x \sum_y x^p y^q f(x,y)
]

Aplicaciones:

* Centroides
* Orientación
* Área

### 7.4 Fill Ratio

[
fill_ratio =
\frac{\text{pixeles negros}}{\text{área total}}
]

Aplicaciones:

* Determinar si una casilla está marcada o vacía

---

## 8. Probabilidad y Estadística

### 8.1 Esperanza Matemática

[
E(X)
]

### 8.2 Varianza

[
Var(X)=E[(X-\mu)^2]
]

### 8.3 Probabilidad Condicional

[
P(A|B)=\frac{P(A\cap B)}{P(B)}
]

Aplicaciones:

* Clasificación probabilística

---

## 9. Cálculo Diferencial

### 9.1 Derivadas

Aplicaciones:

* Detección de bordes
* Optimización

### 9.2 Derivadas Parciales

Aplicaciones:

* Procesamiento de imágenes
* Redes neuronales

### 9.3 Regla de la Cadena

Aplicaciones:

* Backpropagation

---

## 10. Cálculo Vectorial

### 10.1 Gradiente

[
\nabla f(x,y)
]

Aplicaciones:

* Sobel
* Canny
* Detección de bordes

### 10.2 Laplaciano

[
\nabla^2 f
]

Aplicaciones:

* Detección de contornos
* Sharpening

### 10.3 Jacobiano

Aplicaciones:

* Homografías
* Warp perspective

### 10.4 Hessiano (Opcional)

Aplicaciones:

* Detectores avanzados

---

## 11. Optimización Matemática

### 11.1 Función de Costo

Mide el error del modelo.

### 11.2 Descenso por Gradiente

[
\theta := \theta - \alpha \nabla J(\theta)
]

### 11.3 Regularización

Aplicaciones:

* Evitar overfitting

---

## 12. Machine Learning

### 12.1 Clasificación Supervisada

Aplicaciones:

* Casilla marcada / no marcada

### 12.2 Funciones de Activación

* ReLU
* Sigmoid
* Softmax

### 12.3 Entropía Cruzada

Función de pérdida para clasificación.

### 12.4 Backpropagation

Entrenamiento de redes neuronales.

---

## 13. Métricas de Evaluación

### 13.1 Accuracy

[
Accuracy=\frac{TP+TN}{TP+TN+FP+FN}
]

### 13.2 Precision

[
Precision=\frac{TP}{TP+FP}
]

### 13.3 Recall

[
Recall=\frac{TP}{TP+FN}
]

### 13.4 F1 Score

[
F1=2\cdot\frac{Precision\cdot Recall}{Precision+Recall}
]

### 13.5 Matriz de Confusión

Permite evaluar errores de clasificación.

---

## 14. OCR y Reconocimiento de Patrones

### 14.1 Segmentación de Regiones

Aplicaciones:

* Detección de texto
* Regiones de interés

### 14.2 Normalización Geométrica

Aplicaciones:

* OCR manuscrito

### 14.3 Extracción de Características

Aplicaciones:

* Reconocimiento numérico

---

## 15. Conclusión

El sistema OMR de encuestas estructuradas requiere principalmente:

* Álgebra lineal
* Geometría analítica y proyectiva
* Procesamiento digital de imágenes
* Morfología matemática
* Estadística
* Cálculo diferencial y vectorial
* Optimización
* Machine Learning (si aplica)

Estas áreas permiten detectar, analizar, corregir y clasificar información visual proveniente de formularios estructurados.

---

## 16. Referencias Bibliográficas

1. Gonzalez, R. C., & Woods, R. E. (2018). *Digital Image Processing* (4th ed.). Pearson.
2. Szeliski, R. (2022). *Computer Vision: Algorithms and Applications* (2nd ed.). Springer.
3. Hartley, R., & Zisserman, A. (2004). *Multiple View Geometry in Computer Vision* (2nd ed.). Cambridge University Press.
4. Goodfellow, I., Bengio, Y., & Courville, A. (2016). *Deep Learning*. MIT Press.
5. Bishop, C. M. (2006). *Pattern Recognition and Machine Learning*. Springer.
6. Strang, G. (2016). *Introduction to Linear Algebra* (5th ed.). Wellesley-Cambridge Press.
7. Marsden, J. E., & Tromba, A. (2011). *Vector Calculus* (6th ed.). W. H. Freeman.
8. Duda, R. O., Hart, P. E., & Stork, D. G. (2001). *Pattern Classification* (2nd ed.). Wiley.
9. Serra, J. (1982). *Image Analysis and Mathematical Morphology*. Academic Press.
10. Smith, R. (2007). “An Overview of the Tesseract OCR Engine.” *Proceedings of the Ninth International Conference on Document Analysis and Recognition (ICDAR 2007)*, IEEE.
