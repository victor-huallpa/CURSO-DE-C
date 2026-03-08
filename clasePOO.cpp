#include <iostream>
#include <string>

using namespace std;

//clase padre
class Vehiculo
{
private:
    int anio;

public:
    string color;
    string modelo;
    string marca;

    void setAnio(int a){
        anio = a;
    }

    int getAnio(){
        return anio;
    }

    virtual void acelerar(){
        cout<<"aceleracion normal"<<endl;
    }
};

//clase hija
class Moto : public Vehiculo
{
public:
    int numLlantas = 2;
    int numPersona = 2;

    void equilibrio(){
        cout<<"estas conduciendo"<<endl;
    }

    void acelerar(){
        cout<<"aceleracion doble"<<endl;
    }
};

int main() {
    Vehiculo* vehiculo;

    Vehiculo camion;

    Moto m1;

    vehiculo = &m1;
    vehiculo->acelerar();


    camion.setAnio(2002);
    camion.color = "morado";
    camion.modelo = "f125";
    camion.marca = "Toyota";

    cout<<camion.modelo<<endl;
    cout<<camion.color<<endl;
    cout<<camion.getAnio()<<endl;

    camion.acelerar();

    return 0;
}