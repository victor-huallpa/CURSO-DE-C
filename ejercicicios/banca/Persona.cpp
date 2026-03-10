#include <iostream>
#include "Persona.h"

using namespace std;

Persona::Persona(string nombre, int edad, string dni){
    this->nombre = nombre;
    this->edad = edad;
    this->dni = dni;
}

void Persona::mostrarDatos(){
    cout<< "nombre: " << nombre << endl;
    cout<< "edad: " << edad << endl;
    cout<< "dni: " << dni << endl;
}