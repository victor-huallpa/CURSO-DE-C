#include <iostream>
using namespace std;

class Palindromo
{
public:
    // Verifica si una cadena es palíndromo
    bool esPalindromo(const string &s){
        int i = 0, j = s.size() - 1;
        while (i < j) {
            if (s[i] != s[j])
                return false;
            i++;
            j--;
        }
        return true;
    }
};

int main() {
    Palindromo p;
    const int TAM = 5;
    string palabras[TAM];

    cout << "Ingrese " << TAM << " palabras:\n";

    for (int i = 0; i < TAM; i++) {
        cout << "Palabra " << i + 1 << ": ";
        cin >> palabras[i];
    }

    cout << "\nRESULTADOS:\n";
    for (int i = 0; i < TAM; i++) {
        if (p.esPalindromo(palabras[i])) {
            cout << palabras[i] << " -> Es palindromo\n";
        } else {
            cout << palabras[i] << " -> No es palindromo\n";
        }
    }

    return 0;
}
