#include <iostream>

using std::cout;
using std::cin;

//declaramos funciones;

double areaCuadrada(double alto, double ancho);
void volumen(double longitud);

//funcion  principal
int main(){//al ser int teine que retornar un entero
    std::string nombre; 
    double resultado = areaCuadrada(50.3 ,12.5);
    cout<<resultado<<std::endl;
    volumen(15.5);

    return 0;//si no lo escribimos se entiende por defecto.
}

// fuciones ya declradas
double areaCuadrada(double alto, double ancho){//retornara un tipo de dato flotante
    return alto*ancho;
}

void volumen(double longitud){//no retorna nada 
    cout<<"el volumen de " << longitud << " es: " << longitud*longitud*longitud << std::endl;
}

