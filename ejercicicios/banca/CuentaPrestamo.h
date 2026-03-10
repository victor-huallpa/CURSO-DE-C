#ifndef CUENTAPRESTAMO_H
#define CUENTAPRESTAMO_H

#include "Cuenta.h"

class CuentaPrestamo : public Cuenta {

private:
    double deuda;

public:
    CuentaPrestamo(int numeroCuenta, double saldo, double deuda);

    void pagarPrestamo(double monto);

};

#endif