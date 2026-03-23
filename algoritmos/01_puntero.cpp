#include <iostream>

using namespace std;

int main(){
    int x = 10;
    int *punt =  &x;

    cout<<"El valor de x es: "<<x<<endl;
    cout<<"La direccion de memoria de x es: "<<&x<<endl;
    cout<<"El valor del puntero es: "<<*punt<<endl;
    cout<<"La direccion del puntero es: "<<&punt<<endl;
}