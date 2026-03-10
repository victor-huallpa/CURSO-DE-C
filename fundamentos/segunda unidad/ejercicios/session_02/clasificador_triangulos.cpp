#include <iostream>
#include <limits>
using namespace std;

class Triangulo {
public:
    // Verifica si los lados forman un triángulo válido
    bool esValido(double a, double b, double c) const {
        return (a > 0 && b > 0 && c > 0) && (a + b > c && a + c > b && b + c > a);
    }

    // Determina el tipo de triángulo según los lados
    string tipoTriangulo(double a, double b, double c) const {
        if (a == b && b == c)
            return "Equilatero";
        else if (a == b || a == c || b == c)
            return "Isosceles";
        else
            return "Escaleno";
    }
};

class GestorTriangulo {
private:
    Triangulo t;
    double a, b, c;

    // Método privado para pedir un lado y validar entrada
    double solicitarLado(const string& nombreLado) {
        double valor;
        while (true) {
            cout << "Ingrese " << nombreLado << ": ";
            cin >> valor;

            // Verifica si la entrada es válida
            if (cin.fail()) {
                cin.clear(); // limpia el estado de error
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descarta la entrada incorrecta
                cout << "Entrada invalida. Ingrese un numero valido.\n";
                continue;
            }

            // Verifica que el número sea positivo
            if (valor <= 0) {
                cout << "El valor debe ser mayor que cero.\n";
                continue;
            }

            return valor; // valor correcto
        }
    }

public:
    // Pide los lados y muestra el resultado
    void ejecutar() {
        cout << "-----------------------------------\n";
        cout << "  VERIFICADOR Y CLASIFICADOR DE TRIANGULOS\n";
        cout << "-----------------------------------\n\n";

        a = solicitarLado("el primer lado");
        b = solicitarLado("el segundo lado");
        c = solicitarLado("el tercer lado");

        cout << "\n-----------------------------------\n";

        if (t.esValido(a, b, c)) {
            cout << "El triangulo es valido.\n";
            cout << "Tipo de triangulo: " << t.tipoTriangulo(a, b, c) << endl;
        } else {
            cout << "Los lados ingresados no forman un triangulo valido.\n";
        }

        cout << "-----------------------------------\n";
    }
};

int main() {
    GestorTriangulo gestor;
    gestor.ejecutar();
    return 0;
}
