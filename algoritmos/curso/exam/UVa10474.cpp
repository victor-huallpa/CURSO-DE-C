#include <iostream>
#include <vector>
#include <algorithm> // Necesario para usar sort()

using namespace std;

int main() {
    // Optimización de E/S para evitar Time Limit Exceeded (TLE)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    int caso = 1;

    // Se lee de manera continua hasta que N y Q sean 0 0
    while (cin >> n >> q && (n != 0 || q != 0)) {
        
        // Imprime la cabecera del caso actual
        cout << "CASE# " << caso << ":\n";
        caso++;

        vector<int> canicas(n);
        for (int i = 0; i < n; i++) {
            cin >> canicas[i]; // Lee los valores de las canicas
        }

        // REQUISITO: Ordenar el arreglo ascendentemente
        sort(canicas.begin(), canicas.end());

        // Procesar cada una de las Q consultas
        for (int i = 0; i < q; i++) {
            int x;
            cin >> x; // Valor a buscar

            // --- BÚSQUEDA BINARIA MODIFICADA (Lower Bound) ---
            int ini = 0;
            int fin = n - 1;
            int resultado_idx = -1; // Almacenará el primer índice donde aparezca X

            while (ini <= fin) {
                int mit = (ini + fin) / 2;

                if (canicas[mit] == x) {
                    resultado_idx = mit; // Guardamos el índice actual donde se encontró
                    fin = mit - 1;       // Seguimos buscando a la izquierda por si hay repetidos anteriores
                } 
                else if (x > canicas[mit]) {
                    ini = mit + 1;
                } 
                else {
                    fin = mit - 1;
                }
            }

            // --- SALIDA CON FORMATO UVa ---
            if (resultado_idx != -1) {
                // UVa trabaja con índices base 1 (la primera posición es 1, no 0)
                cout << x << " found at " << (resultado_idx + 1) << "\n";
            } else {
                cout << x << " not found\n";
            }
        }
    }

    return 0;
}