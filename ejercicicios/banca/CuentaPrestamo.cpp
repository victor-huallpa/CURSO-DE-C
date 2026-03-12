#include <iostream>
#include "CuentaPrestamo.h"

using namespace std;

CuentaPrestamo::CuentaPrestamo(int numeroCuenta, double saldo, double deuda)
: Cuenta(numeroCuenta, saldo)
{
    this->deuda = deuda;
}

void CuentaPrestamo::pagarPrestamo(double monto){
    if (deuda >= monto)
    {
        deuda -= monto;
        cout<<"deuda: : "<<deuda<<endl;

    }else if (deuda == 0)
    {
        cout<<"Usted no tiene deuda"<<endl;
    }else{
        int restante = monto - deuda;
        monto -= restante;
        deuda -= monto;
        cout<<"Cambio: "<<restante<<endl;
        cout<<"deuda: : "<<deuda<<endl;
    }
    
}