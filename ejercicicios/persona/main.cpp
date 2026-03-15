#include <iostream>
#include "Persona.h"

using namespace std;

int main(){
    Persona p1(1.70, 56.7, "12345678-g", "Pedrito");
    p1.comer();
    p1.trabajar();
    p1.getDatos();
}