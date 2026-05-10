#include <iostream>
using namespace std;

int main() {

    int entregaron = 80;
    int noEntregaron = 60;
    int parcial = 20;

    // Total de estudiantes
    int total = entregaron + noEntregaron - parcial;

    cout << "Total de estudiantes del curso: ";
    cout << total << endl;

    return 0;
}