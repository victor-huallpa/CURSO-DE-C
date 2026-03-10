#include <iostream>
#include "CuentaAhorro.h"

using namespace std;

CuentaAhorro::CuentaAhorro(int numeroCuenta, double saldo, double interes)
: Cuenta(numeroCuenta, saldo){
    this->interes = interes;
}

void CuentaAhorro::aplicarInteres(){
    saldo += saldo * interes;
}