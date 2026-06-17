/*
 * Ejercicio 1: Permutaciones de n elementos
 * Autor: M.Sc. Juan Carlos Pinto L.
 * Fecha: 10-06-2026
 * Problema: Calcular todas las permutaciones de 5 usuarios distintos ingresados por el usuario.
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<string> usuarios(5);

    // El usuario ingresa los datos por teclado
    cout << "Ingrese el nombre de 5 usuarios distintos:\n";
    for(int i = 0; i < 5; i++) {
        cout << "Usuario " << i + 1 << ": ";
        cin >> usuarios[i];
    }

    // Ordenamos para usar next_permutation
    sort(usuarios.begin(), usuarios.end());

    cout << "\nPermutaciones de 5 usuarios\n";
    int contador = 0;
    do {
        for(string u : usuarios) cout << u << " ";
        cout << endl;
        contador++;
    } while(next_permutation(usuarios.begin(), usuarios.end()));

    cout << "Total de permutaciones: " << contador << endl;
}