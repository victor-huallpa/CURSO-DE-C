#include <iostream>
#include "Cuenta.h"

using namespace std;

void Cuenta::mostrar(){
    cout<<"Cuenta: "<<numero<<"\nSaldo: "<<saldo<<endl;
}

void Cuenta::setDatos(int n, double s){
    numero = n;
    saldo = s;
}