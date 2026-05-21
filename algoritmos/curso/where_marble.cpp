#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, Q;
    int caso = 1;

    while (cin >> N >> Q) {

        if (N == 0 && Q == 0)
            break;

        vector<int> marbles(N);

        for (int i = 0; i < N; i++) {
            cin >> marbles[i];
        }

        // Ordenar las canicas
        sort(marbles.begin(), marbles.end());

        cout << "CASE# " << caso++ << ":" << endl;

        for (int i = 0; i < Q; i++) {

            int x;
            cin >> x;

            // Buscar primera aparición
            auto it = lower_bound(marbles.begin(), marbles.end(), x);

            // Verificar si existe
            if (it != marbles.end() && *it == x) {

                int pos = (it - marbles.begin()) + 1;

                cout << x << " found at " << pos << endl;

            } else {

                cout << x << " not found" << endl;
            }
        }
    }

    return 0;
}