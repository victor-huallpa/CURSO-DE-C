// Ejercicio 6: Combinaciones de equipos de trabajo
// Autor: M.Sc. Juan Carlos Pinto L.
// Fecha: 10-06-2026
// Problema: Formar equipos de k programadores de un grupo de n ingresados por teclado.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cout << "Ingrese la cantidad total de programadores disponibles (n): ";
    cin >> n;
    cout << "Ingrese la cantidad de integrantes por equipo (k): ";
    cin >> k;

    vector<int> programadores(n);
    cout << "Ingrese los " << n << " numeros identificadores de los programadores:\n";
    for(int i = 0; i < n; i++) {
        cout << "Programador " << i + 1 << ": ";
        cin >> programadores[i];
    }

    vector<bool> seleccion(programadores.size());
    fill(seleccion.begin(), seleccion.begin()+k, true);
    int contador = 0;
    
    cout << "Equipos posibles de " << k << " programadores: \n";
    do {
        for(int i=0; i<programadores.size();i++)
        if(seleccion[i]) cout << programadores[i] << " ";
        cout << endl;
        contador++;
    } while(prev_permutation(seleccion.begin(), seleccion.end()));
    cout << "Total de equipos posibles: " << contador << endl;
}