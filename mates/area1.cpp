#include <iostream>
#include <cmath>
#include <vector>

const int WIDTH = 40;   // ancho de la "pantalla"
const int HEIGHT = 20;  // alto de la "pantalla"

int main() {
    std::vector<std::vector<char>> screen(HEIGHT, std::vector<char>(WIDTH, ' '));

    double r_out = 9.0; // radio exterior
    double r_in = r_out * sin(M_PI/10)/sin(3*M_PI/10); // radio interior para proporción correcta

    double cx = WIDTH/2.0;
    double cy = HEIGHT/2.0;

    // Dibujar puntos de la estrella
    for(int i = 0; i < 5; i++) {
        // Punta exterior
        double theta_ext = i * 2*M_PI/5 - M_PI/2;
        int x_ext = round(cx + r_out * cos(theta_ext));
        int y_ext = round(cy + r_out * sin(theta_ext));
        screen[y_ext][x_ext] = '*';

        // Punta interior
        double theta_in = theta_ext + M_PI/5;
        int x_in = round(cx + r_in * cos(theta_in));
        int y_in = round(cy + r_in * sin(theta_in));
        screen[y_in][x_in] = '*';
    }

    // Imprimir pantalla
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            std::cout << screen[y][x];
        }
        std::cout << "\n";
    }

    return 0;
}
