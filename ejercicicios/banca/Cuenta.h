#ifndef CUENTA_H
#define CUENTA_H

#include <string>

using namespace std;

class Cuenta
{
protected:
    //atributos
    int numeroCuenta;
    double saldo;
public:
    //metodos
    Cuenta(int numeroCuenta, double saldo);

    void depositar(double monto);
    void retirar(double monto);

    void mostrarCenta();

};



#endif