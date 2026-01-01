#include <iostream>
#include <chrono>
#include <thread>

const int ANCHO = 80;
const int ALTO  = 40;
const float PI = 3.14159265f;

// --- Taylor ---
float mi_sin(float x) {
    while (x > PI)  x -= 2*PI;
    while (x < -PI) x += 2*PI;
    float x2 = x*x;
    return x * (1 - x2/6 * (1 - x2/20));
}

float mi_cos(float x) {
    return mi_sin(x + PI/2);
}

// --- Lienzo ---
void limpiar(char L[ALTO][ANCHO]) {
    for(int i=0;i<ALTO;i++)
        for(int j=0;j<ANCHO;j++)
            L[i][j] = ' ';
}

void renderizar(char L[ALTO][ANCHO]) {
    std::cout << "\033[H";
    for(int i=0;i<ALTO;i++) {
        for(int j=0;j<ANCHO;j++)
            std::cout << L[i][j];
        std::cout << '\n';
    }
}

// --- ESTRELLA 6 PUNTAS CORRECTA ---
void estrella6(char L[ALTO][ANCHO], float t) {
    float R = 15.0f * t;
    float r = R * 0.577350f;   // radio interno correcto

    float vx[12], vy[12];

    // 🔴 ROTACIÓN CORRECTA → DOS PUNTAS ABAJO
    float rot = PI/6;

    for(int i=0;i<12;i++) {
        float ang = rot + i * PI/6;
        float rad = (i % 2 == 0) ? R : r;
        vx[i] = rad * mi_cos(ang);
        vy[i] = rad * mi_sin(ang);
    }

    // Scanline fill
    for(int sy=0; sy<ALTO; sy++) {
        float y = ALTO/2 - sy;
        float interX[24];
        int n = 0;

        for(int i=0;i<12;i++) {
            int j = (i+1)%12;
            float y1 = vy[i], y2 = vy[j];
            if((y1<=y && y2>y)||(y2<=y && y1>y)) {
                interX[n++] = vx[i] + (y-y1)*(vx[j]-vx[i])/(y2-y1);
            }
        }

        for(int i=0;i<n-1;i++)
            for(int j=i+1;j<n;j++)
                if(interX[j]<interX[i])
                    std::swap(interX[i],interX[j]);

        for(int i=0;i<n;i+=2) {
            int x1 = ANCHO/2 + interX[i]*2;
            int x2 = ANCHO/2 + interX[i+1]*2;
            if(x1>x2) std::swap(x1,x2);
            for(int x=x1;x<=x2;x++)
                if(x>=0 && x<ANCHO)
                    L[sy][x]='*';
        }
    }
}

int main() {
    char lienzo[ALTO][ANCHO];
    float t = 0;

    std::cout << "\033[2J\033[?25l";

    while(true) {
        limpiar(lienzo);
        estrella6(lienzo,t);
        renderizar(lienzo);

        if(t<1) t+=0.03f;
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}
