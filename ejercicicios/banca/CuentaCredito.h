#ifndef CUENTACREDITO_H
#define CUENTACREDITO_H

#include "Cuenta.h"

class CuentaCredito : public Cuenta {

private:
    double limiteCredito;
    double deuda;

public:
    CuentaCredito(int numeroCuenta, double saldo, double limiteCredito);

    void usarCredito(double monto);

};

#endif