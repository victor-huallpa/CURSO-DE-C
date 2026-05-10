#include <iostream>
using namespace std;

int main() {

    int correo = 120;
    int vpn = 100;
    int ambos = 70;
    int total = 200;

    // Empleados que tienen al menos un servicio
    int unionConjuntos = correo + vpn - ambos;

    // Empleados que no tienen ninguno
    int ninguno = total - unionConjuntos;

    cout << "Empleados sin correo ni VPN: ";
    cout << ninguno << endl;

    return 0;
}