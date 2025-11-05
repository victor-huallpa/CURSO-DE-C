#include <iostream>
#include <vector>
using namespace std;

// Clase encargada de clasificar una sola nota
class ClasificadorNotas {
public:
    // Método que devuelve la categoría según la nota
    char clasificar(int nota) const {
        if (nota > 18) return 'A';
        else if (nota >= 15) return 'B';
        else if (nota >= 12) return 'C';
        else if (nota >= 10) return 'D';
        else return 'F';
    }

    // Método auxiliar: determina si la nota es aprobatoria
    bool esAprobado(int nota) const {
        return nota >= 11; // para ajustar el rango
    }
};

// Clase que gestiona el ingreso y reporte de múltiples notas
class SistemaNotas {
private:
    vector<int> notas;          // almacena todas las notas
    ClasificadorNotas clasif;   // objeto clasificador

public:
    void solicitarNotas() {
        int cantidad;

        cout << "-----------------------------------\n";
        cout << "-- RECIBE NOTA / DEVUELVE CATEGORIA --\n";
        cout << "-----------------------------------\n\n";

        cout << "Ingrese la cantidad de notas que desea agregar: ";
        cin >> cantidad;

        for (int i = 0; i < cantidad; ++i) {
            int nota;
            cout << "\nIngrese nota (" << i + 1 << " de " << cantidad << ", rango 0-20): ";
            cin >> nota;

            if (nota < 0 || nota > 20) {
                cout << "Nota fuera del rango. Intente nuevamente.\n";
                --i; // repetir iteración
            } else {
                notas.push_back(nota);
            }
        }
    }

    void mostrarResultados() const {
        cout << "\n\n========== RESULTADOS ==========\n";
        for (size_t i = 0; i < notas.size(); ++i) {
            int nota = notas[i];
            char categoria = clasif.clasificar(nota);
            bool aprobado = clasif.esAprobado(nota);

            cout << "Nota #" << (i + 1) << ": " << nota
                 << " → Categoría: " << categoria
                 << " → " << (aprobado ? "APROBADO " : "DESAPROBADO ")
                 << endl;
        }
        cout << "================================\n";
    }
};

int main() {
    SistemaNotas sistema;
    sistema.solicitarNotas();
    sistema.mostrarResultados();
    return 0;
}
