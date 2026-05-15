#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int main(){
    vector<string> lista;
    string linea;

    ifstream archi("lineas_text.txt");

    if (!archi)
    {
        cout<<"Error";
    }

    while (getline(archi, linea))
    {
        lista.push_back(linea);
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