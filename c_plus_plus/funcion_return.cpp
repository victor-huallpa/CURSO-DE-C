#include <iostream>

using std::cout;
using std::cin;

double areaCuadrada(double alto, double ancho);
void volumen(double longitud);
int main(){
    double resultado = areaCuadrada(50.3 ,12.5);
    cout<<resultado<<std::endl;
    volumen(15.5);

    return 0;//si no lo escribimos se entiende por defecto.
}

double areaCuadrada(double alto, double ancho){
    return alto*ancho;
}

void volumen(double longitud){
    cout<<"el volumen de " << longitud << " es: " << longitud*longitud*longitud << std::endl;
}

