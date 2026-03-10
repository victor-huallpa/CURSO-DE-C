#ifndef CUENTAPRESTAMO_H
#define CUENTAPRESTAMO_H

#include "Cuenta.h"

class CuentaPrestamo
{
private:
    // atributos
    double deuda;
public:
//metodos
CuentaPrestamo(int numeroCuenta, double saldo, double deuda);

void pagarPrestamo(double monto);

};



#endif