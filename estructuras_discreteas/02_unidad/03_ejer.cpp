/*
 * Ejercicio 1: Permutaciones de n elementos
 * Autor: M.Sc. Juan Carlos Pinto L.
 * Fecha: 10-06-2026
 * Problema: Calcular todas las permutaciones de 5 usuarios distintos.
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<string> usuarios = {"U1", "U2", "U3", "U4", "U5"};

    // Ordenamos para usar next_permutation
    sort(usuarios.begin(), usuarios.end());

    cout << "Permutaciones de 5 usuarios\n";
    int contador = 0;
    do {
        for(string u : usuarios) cout << u << " ";
        cout << endl;
        contador++;
    } while(next_permutation(usuarios.begin(), usuarios.end()));

    cout << "Total de permutaciones: " << contador << endl;
}