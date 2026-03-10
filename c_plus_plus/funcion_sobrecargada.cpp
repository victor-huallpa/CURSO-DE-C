#include <iostream>


using std::cout;
using std::cin;
using std::endl;

//declarando funciones sobrecargadas, se basa en la forma que se representan los paramaetros de cada una de estas fucnciones y mintras tengan el mismo nombre es osi no importa lo que reotrne.

void hornearPizzza();
void hornearPizzza(std::string ingrediente);
void hornearPizzza(std::string ingrediente, std::string ingrediente1);
std::string hornearPizzza(std::string ingredientes,  std::string ingrediente1,  std::string ingrediente3);

int main (){

    std::string mensaje ;
    hornearPizzza();
    hornearPizzza("peperoni");
    hornearPizzza("peperoni", "hotdog");
    mensaje = hornearPizzza("pi;a","hotdog","peperoni");
    cout<<mensaje;
    return 0;

}

void hornearPizzza(){
    cout<<"Hornear Pizza comun\n";
}

void hornearPizzza(std::string ingrediente){
    cout<<"Hornear Pizza de "<<ingrediente<<endl;
}

void hornearPizzza(std::string ingrediente, std::string ingrediente1){
    cout<<"Hornear Pizza de "<<ingrediente<<" y "<<ingrediente1<<endl;
}

std::string hornearPizzza(std::string ingredientes,  std::string ingrediente1,  std::string ingrediente3){
    return "Hornear pizz de "+ingredientes+", "+ingrediente1+" y "+ingrediente3;
}
