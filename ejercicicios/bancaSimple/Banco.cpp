#include <iostream>
#include "Banco.h"
#include "Cuenta.h"

Banco::Banco(){
    cuenta[0].setDatos(123, 56.0);
    cuenta[1].setDatos(321, 21.0);
    cuenta[2].setDatos(213, 10.0);
}

void Banco::mostrarCuentas(){
    for (int i = 0; i < 3; i++)
    {
        cuenta[i].mostrar();
    }
}