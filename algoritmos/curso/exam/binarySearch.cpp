#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Optimiza la velocidad de lectura y escritura en la consola
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casos;
    // Lee la cantidad total de casos de prueba que se van a evaluar
    if (!(cin >> casos)) return 0; 

    // Bucle para procesar cada caso de manera independiente
    for (int c = 0; c < casos; c++) {
        int tam;
        cin >> tam; // 1. Lee el tamaño del arreglo para el caso actual

        // Crea un arreglo dinámico (vector) del tamaño exacto solicitado
        vector<int> y(tam);
        for (int i = 0; i < tam; i++) {
            cin >> y[i]; // 2. Llena el arreglo con los elementos ordenados
        }

        int search;
        cin >> search; // 3. Lee el valor X que queremos buscar

        // --- INICIO DE LA BÚSQUEDA BINARIA ---
        int ini = 0;          // Límite izquierdo de nuestra zona de búsqueda (piso)
        int fin = tam - 1;    // Límite derecho de nuestra zona de búsqueda (techo)
        int mit;              // Variable para almacenar el índice central
        bool encontrado = false; // Bandera para saber si hallamos el valor X

        // El ciclo continúa mientras la zona de búsqueda sea válida (no se crucen)
        while (ini <= fin) {
            // Calcula el punto medio exacto de la zona actual
            mit = (ini + fin) / 2;

            // Caso de éxito: Si el valor del centro es igual al buscado
            if (y[mit] == search) {
                cout << mit << "\n"; // Imprime el índice (posición base 0)
                encontrado = true;   // Marcamos que sí existía
                break;               // Rompe el ciclo inmediatamente
            }
            
            // Si el valor buscado es mayor, descartamos la mitad izquierda
            if (search > y[mit]) {
                ini = mit + 1; // Movemos el piso justo después del centro
            } 
            // Si el valor buscado es menor, descartamos la mitad derecha
            else {
                fin = mit - 1; // Movemos el techo justo antes del centro
            }
        }

        // Si el ciclo terminó y la bandera sigue en falso, el número no existe
        if (!encontrado) {
            cout << "not found\n"; // Imprime el texto exacto exigido
        }
    }

    return 0;
}