#include <iostream>

using namespace std;

// Función iterativa para calcular la potencia a^b
long long calcularPotenciaIterativa(int a, int b) {
    long long resultado = 1; // Almacena el resultado, inicia en 1 para el caso b = 0

    // El ciclo se repite 'b' veces, multiplicando el resultado por la base 'a'
    for (int i = 0; i < b; i++) {
        resultado = resultado * a;
    }

    return resultado;
}

int main() {
    // Optimización de la consola para lectura rápida de datos
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casos;
    if (!(cin >> casos)) return 0; // Lee la cantidad total de casos

    // Ciclo para procesar individualmente cada caso
    for (int c = 0; c < casos; c++) {
        int a, b;
        cin >> a >> b; // Lee la base 'a' y el exponente 'b'

        // Llama a la función e imprime el resultado
        cout << calcularPotenciaIterativa(a, b) << "\n";
    }

    return 0;
}