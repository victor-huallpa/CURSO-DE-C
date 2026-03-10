#ifndef PERSONA_H
#define PERSONA_H

#include <string>

using namespace std;

class Persona
{
private:
   string nombre;
   int edad;
   string dni;
public:
    Persona(string nombre, int edad, string dni);

    void mostrarDatos();
};



#endif

