#include <iostream>

using namespace std;

// Función recursiva para calcular la potencia a^b
long long calcularPotencia(int a, int b) {
    // Caso base: Todo número elevado a la 0 es 1
    if (b == 0) {
        return 1;
    }
    // Caso recursivo: a^b = a * a^(b-1)
    return a * calcularPotencia(a, b - 1);
}

int main() {
    // Optimización de entrada/salida para la consola
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casos;
    if (!(cin >> casos)) return 0; // Lee la cantidad de casos

    // Procesa cada caso de prueba
    for (int c = 0; c < casos; c++) {
        int a, b;
        cin >> a >> b; // Lee la base 'a' y el exponente 'b'

        // Llama a la función recursiva e imprime el resultado
        cout << calcularPotencia(a, b) << "\n";
    }

    return 0;
}