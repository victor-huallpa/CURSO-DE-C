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
        // seters
        void setDatos(string n, int e){
            nombre = n;
            edad = e;
        }
        //geters
        int getEdad(){
            return edad;
        }

        virtual void trabajar (){
            cout<<"La persona esta trabajando";
        }

};

//clase hija
int main(){
    int ed;
    Persona p1;
    p1.setDatos("victor", 25);
    ed = p1.getEdad();
    cout<<p1.getEdad();;
    return 0;
}
