// Lee la entrada completa línea por línea. Luego, imprime todas las líneas ordenadas por longitud, 
// comenzando por las más cortas. Si dos líneas tienen la misma longitud, resuelve su 
// orden utilizando el método habitual de ordenación. Las líneas duplicadas se imprimirán solo una vez.

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

int main(){
    
    unordered_set<string> vista;
    vector<string> lista;
    string linea;
    ifstream archi("lineas_text.txt");

    if (!archi)
    {
        /* code */
        cout<<"error";
    }

    while (getline(archi, linea))
    {
        /* code */
        if (linea == "")
        {
            continue;
        }
        vista.insert(linea);
    }

    for (auto x : vista)
    {
        // cout<<x<<endl;
        lista.push_back(x);
    }

    sort(lista.begin(), lista.end(), [](const string& a, const string& b){
        if (a.size() != b.size()) return a.size() < b.size();

        return a<b;
        
    });

    for (auto x : lista)
    {
        cout<<x<<endl;
    }
    
    
    
    

    return 0;
}