#include <iostream>
#include <string>
using namespace std;

//clase padre
class Persona
{
    protected:
        //atributos
       string nombre;     
    private:
        //atributos
        int edad;
    public:
        //metodos
        void setDatos(string n, int e){
            nombre = n;
            edad = e;
        }

        int getEdad(){
            return edad;
        }

        virtual void trabajar (){
            cout<<"La persona esta trabajando";
        }

};

//clase hija

