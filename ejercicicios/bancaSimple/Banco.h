#ifndef BANCO_H
#define BANCO_H
#include "Cuenta.h"

class Banco
{
private:
    Cuenta cuenta[3];
public:
    Banco();

    void mostrarCuentas();
};





#endif