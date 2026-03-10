#ifndef CUENTAAHORRO_H
#define CUENTAAHORRO_H

#include "Cuenta.h"

class CuentaAhorro : public Cuenta
{
private:
    double interes;
public:
    CuentaAhorro(int numeroCuenta, double saldo, double interes);

    void aplicarInteres();
};



#endif