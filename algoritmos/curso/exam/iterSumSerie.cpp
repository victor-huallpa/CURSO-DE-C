#include <iostream>

using namespace std;

// Función iterativa para calcular la sumatoria de la serie hasta n
long long sumarSerieIterativa(int n) {
    long long suma = 0; // Acumulador donde guardaremos el total de la serie

    // Un ciclo que va calculando uno a uno los términos desde 1 hasta n
    for (int i = 1; i <= n; i++) {
        // Calculamos el término i^2 + 1 y lo agregamos a la suma total
        suma = suma + (i * i + 1);
    }

    return suma; // Retornamos el total calculado
}

int main() {
    // Optimización de la consola para agilizar la lectura de datos
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casos;
    if (!(cin >> casos)) return 0; // Lee la cantidad de casos (ej. 3)

    // Bucle para procesar cada caso de prueba por separado
    for (int c = 0; c < casos; c++) {
        int n;
        cin >> n; // Lee el límite superior 'n' de la serie

        // Llama a la función iterativa e imprime el resultado
        cout << sumarSerieIterativa(n) << "\n";
    }

    return 0;
}