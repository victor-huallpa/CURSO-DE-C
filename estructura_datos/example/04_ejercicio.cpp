// Lee la entrada línea por línea y escribe cada línea en la salida si no es una duplicación de alguna línea anterior. 
// Ten especial cuidado para que un archivo con muchas líneas duplicadas no consuma más memoria de la necesaria para la cantidad de líneas únicas.

#include <iostream>
#include <unordered_set>//busqueda rapida (hashing)
#include <fstream>
#include <vector>

using namespace std;

int main(){

    unordered_set<string> visto;
    string linea;
    ifstream archi("lineas_text.txt");
    vector<string> duplicados;

    if (!archi)
    {
        cout<<"error";
    }
    
    while (getline(archi, linea))
    {
        if (!visto.count(linea))//verificamos si no esiste el elemento
        {
            visto.insert(linea);//insertamos el elemento aun no existente
            cout<<linea<<endl;
        }else{
            duplicados.push_back(linea);//almacemaos si ya existe en un vector
        }
        
    }

    for (int i = 0; i < (int)duplicados.size() ; i++)
    {
        cout<<duplicados[i]<<endl;
    }
    
    



    return 0;
}