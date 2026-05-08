#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;

    while (N--) {
        int L;
        cin >> L;

        vector<int> train(L);
        for (int i = 0; i < L; i++) {
            cin >> train[i];
        }

        int swaps = 0;

        // Bubble Sort contando intercambios
        for (int i = 0; i < L - 1; i++) {
            for (int j = 0; j < L - i - 1; j++) {
                if (train[j] > train[j + 1]) {
                    swap(train[j], train[j + 1]);
                    swaps++;
                }
            }
        }

        cout << "Optimal train swapping takes " << swaps << " swaps." << endl;
    }

    return 0;
}