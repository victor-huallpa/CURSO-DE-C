#include <iostream>
using namespace std;

class CadenaInversa
{
public:
    // Invierte la cadena
    string invertir(const string &cadena){
        string r = "";
        for (int i = cadena.size() - 1; i >= 0; i--)
            r += cadena[i];
        return r;
    }

    // Retorna la cadena cortada en dos segmentos
    // Segmento 1: desde 0 hasta mitad-1
    // Segmento 2: desde mitad hasta el final
    string cortarEnDos(const string &cadena){
        int mitad = cadena.size() / 2;

        string parte1 = cadena.substr(0, mitad);
        string parte2 = cadena.substr(mitad);

        return parte1 + " | " + parte2; // separador para visualizar
    }
};

int main(){
    CadenaInversa ci;
    string texto;

    cout << "Ingrese una cadena: ";
    getline(cin, texto);

    // Mostrar la cadena invertida
    cout << "Cadena invertida: " << ci.invertir(texto) << endl;

    // Mostrar la cadena cortada
    cout << "Cadena cortada en dos partes: " << ci.cortarEnDos(texto) << endl;

    return 0;
}
