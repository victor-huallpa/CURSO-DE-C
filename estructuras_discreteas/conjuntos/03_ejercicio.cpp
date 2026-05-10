#include <iostream>
using namespace std;

int main() {

    int totalUsuarios = 500;
    int autenticados = 320;
    int enProceso = 100;

    // Usuarios no autenticados
    int noAutenticados = totalUsuarios - autenticados - enProceso;

    cout << "Usuarios no autenticados: ";
    cout << noAutenticados << endl;

    return 0;
}