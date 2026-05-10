#include <iostream>
using namespace std;

int main() {

    int nube = 400;
    int local = 350;
    int ambos = 200;

    // Solo nube
    int soloNube = nube - ambos;

    // Solo local
    int soloLocal = local - ambos;

    cout << "Archivos solo en la nube: ";
    cout << soloNube << endl;

    cout << "Archivos solo en local: ";
    cout << soloLocal << endl;

    return 0;
}