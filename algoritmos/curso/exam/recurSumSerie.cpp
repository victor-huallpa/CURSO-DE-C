#include <iostream>

using namespace std;

// Función recursiva que calcula la sumatoria de la serie hasta n
long long sumarSerie(int n) {
    // Caso base: Si n es 0, no hay elementos que sumar, devolvemos 0
    if (n == 0) {
        // Detiene la recursión y empieza a retornar los valores hacia atrás
        return 0; 
    }
    
    // Caso recursivo: Término actual (n^2 + 1) + la suma acumulada de los n-1 anteriores
    return (n * n + 1) + sumarSerie(n - 1);
}

int main() {
    // Optimización de flujos de consola para la lectura veloz de datos
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casos;
    if (!(cin >> casos)) return 0; // Lee la cantidad de casos a procesar

    // Procesa de manera individual cada caso de prueba
    for (int c = 0; c < casos; c++) {
        int n;
        cin >> n; // Lee el valor de n para la serie actual

        // Llama a la función recursiva e imprime el resultado final
        cout << sumarSerie(n) << "\n";
    }

    return 0;
}
