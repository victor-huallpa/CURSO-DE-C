#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;

int main(){
    vector<string> lista;
    string linea;
    ifstream archi("lineas_text.txt");

    std::random_device rd;
    std::mt19937 gen(rd());

    if(!archi) return 0;

    while (getline(archi, linea))
    {
        lista.push_back(linea);
    }


    shuffle(lista.begin(), lista.end(), gen);

    for (auto value: lista)
    {
        cout<<value<<endl;
    }
    

    return 0;
}