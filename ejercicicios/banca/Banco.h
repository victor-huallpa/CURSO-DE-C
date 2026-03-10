#ifndef BANCO_H
#define BANCO_H

#include <vector>
#include "Cliente.h"

using namespace std;

class Banco {

private:
    vector<Cliente> clientes;

public:

    void agregarCliente(Cliente cliente);

    void mostrarClientes();

};

#endif