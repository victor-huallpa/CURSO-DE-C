#include <iostream>
using namespace std;

class PromedioNotas
{
private:
    static const int TAM = 6;   // cantidad de notas
    float notas[TAM];           // notas almacenadas

public:
    // Pide las notas con validación
    void pedirNotas() {
        cout << "Ingrese " << TAM << " notas (entre 11 y 20):\n";

        for (int i = 0; i < TAM; i++) {
            do {
                cout << "Nota " << i + 1 << ": ";
                cin >> notas[i];

                // Validar el rango
                if (notas[i] < 11 || notas[i] > 20) {
                    cout << "Nota inválida. Debe ser entre 11 y 20.\n";
                }

            } while (notas[i] < 11 || notas[i] > 20);
        }
    }

    // Calcula el promedio de las notas
    float promedio() {
        float suma = 0;
        for (int i = 0; i < TAM; i++)
            suma += notas[i];

        return suma / TAM;
    }
};

int main() {
    PromedioNotas pn;      // objeto
    pn.pedirNotas();       // pedir notas mediante método
    cout << "El promedio es: " << pn.promedio() << endl;
    return 0;
}
