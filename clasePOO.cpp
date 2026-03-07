#include <iostream>
#include <string>
#include <cstring>
using namespace std;



class car
{
private:
    /* data */
public:
// atributos
    string color;
    int anio = 2022;
    char modelo[10];
    char marca;
//metodos
    int acelarar(){
        cout<<"acelerando";
        return 0;
    }
};

int main() {
    //objeto instacado
    car camion;
    car camion2;
    //asignarle valores a los atributos

    cout<<camion.anio<<endl;

    camion.anio = 2002;
    camion.color = "morado";
    strcpy(camion.modelo, "f125");
    camion.marca = 'T';

    cout<<camion.anio<<endl;
    cout<<camion.modelo<<endl;
    cout<<camion.color<<endl;
    cout<<camion2.anio<<endl;

    //metodos
    camion2.acelarar();
    camion.acelarar();

    return 0;
}



