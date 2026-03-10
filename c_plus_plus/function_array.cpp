#include <iostream>

using namespace std;

double getTotal(double precios[], int tam);

int main (){
    double precios[] = {23.5, 46.5, 12.0, 14.60, 15.43};
    int tam = sizeof(precios) / sizeof(precios[0]);
    double total = getTotal(precios, tam);
    cout<< total<<endl;


    return 0;

}

// el arreglo pasado a la funcion se degrada a un puntero, por ende se deve pasar el tama;o del arreglo
double getTotal(double precios[], int tam){
    double total = 0;

    for(int i = 0; i < tam; i++){
        total += precios[i];
    }
    return total;
}
