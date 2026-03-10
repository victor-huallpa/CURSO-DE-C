#include <iostream>
#include <chrono>
#include <thread>

const int ANCHO = 80;
const int ALTO = 40;
const float PI = 3.14159265f;

// --- LÓGICA MATEMÁTICA MANUAL (Taylor) ---
float mi_sin(float x) {
    while (x > PI) x -= 2 * PI;
    while (x < -PI) x += 2 * PI;
    float x2 = x * x;
    return x * (1 - x2/6.0f * (1 - x2/20.0f * (1 - x2/42.0f)));
}

float mi_cos(float x) {
    return mi_sin(x + (PI / 2.0f));
}

// --- LIMPIEZA TOTAL DEL LIENZO ---
void limpiarLienzo(char lienzo[ALTO][ANCHO]) {
    // Llenamos toda la matriz de espacios ' '
    for (int i = 0; i < ALTO; i++)
        for (int j = 0; j < ANCHO; j++)
            lienzo[i][j] = ' ';
}

// --- RENDERIZADO ---
void renderizar(char lienzo[ALTO][ANCHO]) {
    std::cout << "\033[H"; 
    for (int i = 0; i < ALTO; i++) {
        for (int j = 0; j < ANCHO; j++) std::cout << lienzo[i][j];
        std::cout << '\n';
    }
}

// --- DIBUJO DE LA ROSA POLAR ---
void generarFigura(char lienzo[ALTO][ANCHO], float t) {
    float k = 4.0f; 
    float radioFijo = 15.0f; // Tamaño fijo

    for (float angulo = 0; angulo < 2 * PI; angulo += 0.01f) {
        // La rotación viene dada por 't'
        float r = radioFijo * mi_cos(k * angulo + t);
        float x = r * mi_cos(angulo);
        float y = r * mi_sin(angulo);

        // Mapeo al centro y corrección de aspecto (x * 2.0f)
        int screenX = (int)(ANCHO / 2 + (x * 2.0f));
        int screenY = (int)(ALTO / 2 - y);

        if (screenX >= 0 && screenX < ANCHO && screenY >= 0 && screenY < ALTO) {
            // Dibujamos el punto sin preocuparnos por ejes o números
            lienzo[screenY][screenX] = '*'; 
        }
    }
}

int main() {
    char lienzo[ALTO][ANCHO];
    float t = 0;
    // Ocultar cursor y limpiar pantalla una vez
    std::cout << "\033[?25l\033[2J";

    while (1) {
        // Limpiamos todo con espacios
        limpiarLienzo(lienzo); 
        generarFigura(lienzo, t);
        renderizar(lienzo);

        t += 0.05f; 
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    return 0;
}