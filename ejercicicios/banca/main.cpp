#include <iostream>
#include "Cuenta.h"

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
    // string nombre = pedirDato<string>("nombre");
    // int edad = pedirDato<int>("edad");
    // string dni = pedirDato<string>("dni");
    // int codigo = pedirDato<int>("codigo");


    // Cliente c1(nombre, edad, dni, codigo);

    // c1.mostrarCliente();

    Cuenta c1(1001, 500);

    c1.depositar(200);
    c1.retirar(100);

    c1.mostrarCenta();
    

    return 0;
}

