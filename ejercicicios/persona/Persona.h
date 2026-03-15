#ifndef PERSONA_H
#define PERSONA_H
#include <string>

class Persona
{
private:
    /* atributos */
    float estatura;
    float peso;
    std::string dni;
    std::string nombre;
public:
    //metodos
    Persona(float e, float p, std::string d, std::string n);
    void trabajar();
    void comer();
    void getDatos();
    //codigo
    
   // ~Persona();
};


#endif

