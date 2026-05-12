// Lee la entrada línea por línea y escribe cada línea en la salida solo si ya la has leído antes. 
// (El resultado final es que eliminas la primera aparición de cada línea).
// Ten especial cuidado para que un archivo con muchas líneas duplicadas no consuma más memoria de la necesaria para la cantidad de líneas únicas.

#include <iostream>
#include <unordered_set>
#include <fstream>


using namespace std;

int main(){

    ifstream archi("lineas_text.txt");
    unordered_set<string> visto;
    string linea;

    if (!archi)
    {
        cout<<"error";
    }
    

    while (getline(archi, linea))
    {

        if (visto.count(linea))
        {
            cout<<"visto: "<<linea<<endl;//imprimimos si ya lo vimos
        }
        visto.insert(linea);//almacenamsosi no lo vinos(el set no guarda duplicados)
        
        
    }
    


    return 0;
}