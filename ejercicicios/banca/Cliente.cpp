#include <iostream>
#include "Cliente.h"

using namespace std;

Cliente::Cliente(string nombre, int edad, string dni, int codigoCliente)
: Persona(nombre, edad, dni)
{
    this->codigoCliente = codigoCliente;
}

void Cliente::mostrarCliente() {

    mostrarDatos();

    cout << "Codigo Cliente: " << codigoCliente << endl;
}