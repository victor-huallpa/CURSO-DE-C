#include <iostream>

#include "Banco.h"
#include "Cliente.h"
#include "CuentaAhorro.h"
#include "CuentaPrestamo.h"
#include "CuentaCredito.h"

using namespace std;

//template de funcion(no esta defifdo que retornara hasta que se use).
template <typename T>
T pedirDato(string texto){
    T valor;
    cout << "Ingrese " << texto << ": ";
    cin >> valor;
    return valor;
}

int main(){
    
    //pedir datos
    // string nombre = pedirDato<string>("nombre");
    // int edad = pedirDato<int>("edad");
    // string dni = pedirDato<string>("dni");
    // int codigo = pedirDato<int>("codigo");


    // Cliente c1(nombre, edad, dni, codigo);

    // c1.mostrarCliente();

    Banco banco;
    // Crear clientes
    Cliente c1("Carlos", 25, "12345678", 1);
    Cliente c2("Ana", 30, "87654321", 2);

    // Agregar clientes al banco
    banco.agregarCliente(c1);
    banco.agregarCliente(c2);

    cout << "CLIENTES DEL BANCO\n";
    cout << "------------------\n";

    banco.mostrarClientes();

    cout << "\nPRUEBA DE CUENTAS\n";
    cout << "------------------\n";

    // Crear cuentas
    CuentaAhorro ahorro(1001, 500, 0.05);
    CuentaPrestamo prestamo(2001, 0, 1000);
    CuentaCredito credito(3001, 0, 2000);

    // Operaciones
    ahorro.depositar(200);
    ahorro.aplicarInteres();
    ahorro.mostrarCenta();

    cout << endl;

    prestamo.pagarPrestamo(300);
    prestamo.mostrarCenta();

    cout << endl;

    credito.usarCredito(500);
    credito.mostrarCenta();

    

    return 0;
}

