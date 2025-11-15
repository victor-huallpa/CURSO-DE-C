#include <iostream>
using namespace std;

class VectorNumero
{
private:
    static const int TAM = 7;     // constante: buen uso de POO
    int vector[TAM];

public:

    // método para sumar los elementos del vector
    int suma() const {
        int total = 0;
        for (int i = 0; i < TAM; i++)
            total += vector[i];
        return total;
    }

    // método para pedir datos al usuario
    void getDatos() {
        cout << "Ingrese datos:" << endl;
        for (int i = 0; i < TAM; i++)
        {
            cout << "Dato " << i+1 << ": ";
            cin >> vector[i];
        }
    }
};

int main() {
    VectorNumero vn;
    vn.getDatos();
    cout << "La suma de elementos del vector es: " << vn.suma() << endl;
    return 0;
}
