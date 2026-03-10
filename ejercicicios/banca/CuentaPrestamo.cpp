#include <iostream>
#include "CuentaPrestamo.h"

using namespace std;

CuentaPrestamo::CuentaPrestamo(int numeroCuenta, double saldo, double deuda){
    this->deuda = deuda;
}

void CuentaPrestamo::pagarPrestamo(double monto){
    deuda -= monto;

    if(deuda < 0){
        deuda = 0;
    }
}