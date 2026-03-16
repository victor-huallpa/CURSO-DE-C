#include <iostream>
#include "Banco.h"
// #include "Cuenta.h"

using namespace std;


Banco::Banco(){
    cuenta = 123;
}

void Banco::mostrarCuentas(){
    for (int i = 0; i < 3; i++)
    {
        cout<<cuenta<<endl;
    }
}