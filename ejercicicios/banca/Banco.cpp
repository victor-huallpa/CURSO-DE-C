#include <iostream>
#include "Banco.h"

using namespace std;

void Banco::agregarCliente(Cliente cliente){

    clientes.push_back(cliente);

}

void Banco::mostrarClientes(){

    for(int i = 0; i < clientes.size(); i++){

        clientes[i].mostrarCliente();
        cout << "------------------" << endl;

    }

}