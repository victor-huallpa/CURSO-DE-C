#include <iostream>
using namespace std;

int main() {

    int lectura = 150;
    int escritura = 120;
    int ejecucion = 100;

    int lecEsc = 60;
    int escEje = 50;
    int lecEje = 40;

    int tresPermisos = 30;

    // Formula de inclusion y exclusion
    int total = lectura + escritura + ejecucion
              - lecEsc - escEje - lecEje
              + tresPermisos;

    cout << "Usuarios con al menos un permiso: ";
    cout << total << endl;

    return 0;
}