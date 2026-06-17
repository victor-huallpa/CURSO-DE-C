// Ejercicio 2 Permutaciones de a elementos tomados en k
// Autor N.Sc. Juan Carlos Pinto L.
// Fecha: 10-06-2026
// problema calcular todas las permutaciones de procesos ingresados por teclado tomados de k en k
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cout << "Ingrese la cantidad total de procesos (n): ";
    cin >> n;
    cout << "Ingrese el tamano de los grupos (k): ";
    cin >> k;

    vector<int> procesos(n);
    cout << "Ingrese los " << n << " números identificadores de los procesos:\n";
    for(int i = 0; i < n; i++) {
        cout << "Proceso " << i + 1 << ": ";
        cin >> procesos[i];
    }

    int contador = 0;
    cout << "Permutaciones de " << n << " procesos tomados de " << k << " en " << k << ": \n";
    
    // Generasos todas las combinaciones de tamaño k
    vector<bool> seleccion(procesos.size());
    fill(seleccion.begin(), seleccion.begin()+k, true);
    do {
        vector<int> comb;
        for(int i=0; i<procesos.size(); i++)
        if(seleccion[i]) comb.push_back(procesos[i]);
        // Generamos todas las permutaciones de esa combinación
        sort(comb.begin(), comb.end());
        do {
            for(int x : comb) cout << x << " ";
            cout << endl;
            contador++;
        } while(next_permutation(comb.begin(), comb.end()));
    } while(prev_permutation(seleccion.begin(), seleccion.end()));

    cout << "Total de permutaciones: " << contador << endl;
}