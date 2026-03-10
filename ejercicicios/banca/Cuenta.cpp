#include <iostream>
#include "Cuenta.h"

using namespace std;

Cuenta::Cuenta(int numeroCuenta, double saldo){
    this->numeroCuenta = numeroCuenta;
    this->saldo = saldo;
}
//depositar dinero
void Cuenta::depositar(double monto){
    saldo += monto;
}
//retirar dinero
void Cuenta::retirar(double monto){
    if(monto <= saldo){
        saldo -= monto;
    }else{
        cout<< "Saldo insuficient" << endl;
    }
}

// mostar datos de cuenta
void Cuenta::mostrarCenta(){
    cout << "Numeor de cuenta: " << numeroCuenta << endl;
    cout << "Saldo: "<< saldo<<endl;
}