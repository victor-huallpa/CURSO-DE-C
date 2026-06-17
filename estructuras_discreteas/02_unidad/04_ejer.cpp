// Ejercicio 4: Relación entre combinaciones y permutaciones
// Autor: M.Sc. Juan Carlos Pinto L.
// Fecha: 10-06-2026
// Problema: Seleccionar k registros de n ingresados por teclado y luego permutarlos.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cout << "Ingrese la cantidad total de registros (n): ";
    cin >> n;
    cout << "Ingrese el tamano del subconjunto (k): ";
    cin >> k;

    vector<int> registros(n);
    cout << "Ingrese los " << n << " numeros identificadores de los registros:\n";
    for(int i = 0; i < n; i++) {
        cout << "Registro " << i + 1 << ": ";
        cin >> registros[i];
    }

    int contador = 0;
    vector<bool> seleccion(registros.size());
    fill(seleccion.begin(), seleccion.begin()+k, true);
    
    cout << "Combinaciones y sus permutaciones: \n";
    do {
        vector<int> comb;
        for(int i=0;i<registros.size();i++)
        if(seleccion[i]) comb.push_back(registros[i]);
        sort(comb.begin(), comb.end());
        do {
            for(int x: comb) cout << x << " ";
            cout << endl;
            contador++;
        } while(next_permutation(comb.begin(), comb.end()));
    } while(prev_permutation(seleccion.begin(), seleccion.end()));
    cout << "Total de permutaciones generadas: " << contador << endl;
}