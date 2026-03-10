#ifndef CLIENTE_H
#define CLIENTE_H

#include "Persona.h"
#include <string>

using namespace std;

class Cliente : public Persona {

private:
    int codigoCliente;

public:
    Cliente(string nombre, int edad, string dni, int codigoCliente);

    void mostrarCliente();

};

#endif