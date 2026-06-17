// Ejercicio 5: Permutaciones de contraseñas
// Autor: M.Sc. Juan Carlos Pinto L.
// Fecha: 10-06-2026
// Problema: Generar todas las contraseñas de k caracteres a partir de n símbolos ingresados por teclado.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cout << "Ingrese la cantidad total de simbolos disponibles (n): ";
    cin >> n;
    cout << "Ingrese la longitud de la contrasena (k): ";
    cin >> k;

    vector<char> simbolos(n);
    cout << "Ingrese los " << n << " caracteres o simbolos permitidos:\n";
    for(int i = 0; i < n; i++) {
        cout << "Simbolo " << i + 1 << ": ";
        cin >> simbolos[i];
    }

    int contador = 0;
    vector<bool> seleccion(simbolos.size());
    fill(seleccion.begin(), seleccion.begin()+k, true);
    
    cout << "Posibles contraseñas de " << k << " caracteres: \n";
    
    // Nota: El bucle do-while externo se reestructuró para abarcar correctamente 
    // la recolección de subconjuntos de forma dinámica en cada iteración de prev_permutation
    do {
        vector<char> comb;
        for(int i=0; i<simbolos.size(); i++)
            if(seleccion[i]) comb.push_back(simbolos[i]);
            
        sort(comb.begin(), comb.end());
        do {
            for(char c: comb) cout << c;
            cout << endl;
            contador++;
        } while(next_permutation(comb.begin(), comb.end()));
        
    } while(prev_permutation(seleccion.begin(), seleccion.end()));
    
    cout << "Total de contraseñas posibles: " << contador << endl;
}