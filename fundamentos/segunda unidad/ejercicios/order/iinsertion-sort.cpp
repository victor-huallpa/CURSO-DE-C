#include <iostream>

using namespace std;
// ISNERTION SORT

int main() {
    // ARREGO A ORDENAR
    int number[] = {6, 10, 10, 3, 7, 9, 1}; 
    int n = sizeof(number) / sizeof(number[0]); // Tamaño dinámico

    // Empezamos en 1: el primer elemento de la "derecha"
    for (int i = 1; i < n; i++) {
        int llave = number[i]; 
        int retro = i - 1;    
        /* Lógica: Mientras el elemento de la izquierda sea mayor que nuestra llave,
           lo movemos una posición a la derecha para abrir espacio.
        */
        while (retro >= 0 && number[retro] > llave) {
            number[retro + 1] = number[retro]; // Desplazamiento
            retro--; // Seguimos comparando hacia atrás
        }

        // Insertamos la llave en la posicion correcto
        number[retro + 1] = llave;
    }

    // Imprimir resultado
    cout << "Arreglo ordenado:" << endl;
    for (int i = 0; i < n; i++) {
        cout << number[i] << " ";
    }
    
    cout << endl;

    return 0;
}