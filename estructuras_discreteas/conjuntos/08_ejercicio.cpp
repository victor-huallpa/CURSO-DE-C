#include <iostream>
using namespace std;

int main() {

    int validos = 600;
    int duplicados = 200;
    int ambos = 150;

    // Registros validos y unicos
    int validosUnicos = validos - ambos;

    cout << "Registros validos y unicos: ";
    cout << validosUnicos << endl;

    return 0;
}