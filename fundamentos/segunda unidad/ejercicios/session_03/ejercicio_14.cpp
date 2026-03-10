#include <iostream>
using namespace std;

class BusquedaElemento
{
private:
    static const int TAM = 15; // tamaño mínimo
    int arr[TAM];

public:

    // Pide 15 números enteros
    void ingresarDatos() {
        cout << "Ingrese " << TAM << " números enteros:\n";
        for (int i = 0; i < TAM; i++) {
            cout << "Número " << i + 1 << ": ";
            cin >> arr[i];
        }
    }

    // Busca un número x; retorna índice o -1 si no existe
    int buscar(int x) {
        for (int i = 0; i < TAM; i++) {
            if (arr[i] == x) {
                return i;
            }
        }
        return -1;
    }

    // Busca un vecino cercano: valores entre (x - 3) y (x + 3)
    int vecinoCercano(int x) {
        int minRango = x - 3;
        int maxRango = x + 3;

        for (int i = 0; i < TAM; i++) {
            if (arr[i] >= minRango && arr[i] <= maxRango) {
                return arr[i];  // retorna el número cercano encontrado
            }
        }
        return -1; // si no hay vecino cercano
    }
};

int main() {
    BusquedaElemento be;
    be.ingresarDatos();

    int buscarNum;
    cout << "\nIngrese el número a buscar: ";
    cin >> buscarNum;

    int indice = be.buscar(buscarNum);

    if (indice != -1) {
        cout << "El número " << buscarNum << " se encuentra en el índice: " << indice << endl;
    } 
    else {
        cout << "No se encontró el número.\n";

        int vecino = be.vecinoCercano(buscarNum);

        if (vecino != -1) {
            cout << "Pero encontré un número cercano (±3): " << vecino << endl;
        } else {
            cout << "No hay ningún número cercano dentro del rango permitido.\n";
        }
    }

    return 0;
}
