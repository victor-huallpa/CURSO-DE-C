#include <iostream>
//lamando a  la cabecera
#include "Persona.h"

using namespace std;

Persona::Persona(float e, float p, string d, string n){
    this->estatura = e;
    this->peso = p;
    this->dni = d;
    this->nombre = n;
}


void Persona::trabajar(){
    cout<<nombre<<" esta trabajndo\n";
}

void Persona::comer(){
    cout<<nombre<<" esta comiendol.\n";
}
void Persona::getDatos(){
    cout<<nombre<<endl;
    cout<<estatura<<endl;
    cout<<peso<<endl;
    cout<<dni<<endl;
}