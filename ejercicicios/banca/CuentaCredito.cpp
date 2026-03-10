#include <iostream>
#include "CuentaCredito.h"

using namespace std;

CuentaCredito::CuentaCredito(int numeroCuenta, double saldo, double limiteCredito)
: Cuenta(numeroCuenta, saldo)
{
    this->limiteCredito = limiteCredito;
    deuda = 0;
}

void CuentaCredito::usarCredito(double monto){

    if(deuda + monto <= limiteCredito){
        deuda += monto;
    }else{
        cout << "Limite de credito excedido" << endl;
    }

}