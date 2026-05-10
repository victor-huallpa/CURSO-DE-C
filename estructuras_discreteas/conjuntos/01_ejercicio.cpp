#include <iostream>
using namespace std;

int main() {

    // Cantidad de estudiantes
    int moodle = 200;
    int classroom = 180;
    int ambos = 90;
    int total = 300;

    // Formula de conjuntos:
    // A U B = A + B - (A ∩ B)
    int usanPlataformas = moodle + classroom - ambos;

    // Estudiantes que no usan ninguna plataforma
    int ninguno = total - usanPlataformas;

    cout << "Estudiantes que no usan ninguna plataforma: ";
    cout << ninguno << endl;

    return 0;
}