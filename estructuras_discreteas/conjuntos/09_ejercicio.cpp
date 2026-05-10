#include <iostream>
using namespace std;

int main() {

    int movil = 70;
    int pc = 90;
    int ambos = 40;

    // Total de usuarios
    int total = movil + pc - ambos;

    cout << "Total de usuarios en la reunion: ";
    cout << total << endl;

    return 0;
}