#include <iostream>
#include "Cliente.h"

using namespace std;

//template de funcion(no esta defifdo que retornara hasta que se use).
template <typename T>
T pedirDato(string texto){
    T valor;
    cout << "Ingrese " << texto << ": ";
    cin >> valor;
    return valor;
}

int main(){
    //pedir datos
    string nombre = pedirDato<string>("nombre");
    int edad = pedirDato<int>("edad");
    string dni = pedirDato<string>("dni");
    int codigo = pedirDato<int>("codigo");


    Cliente c1(nombre, edad, dni, codigo);

    c1.mostrarCliente();

    return 0;
}

