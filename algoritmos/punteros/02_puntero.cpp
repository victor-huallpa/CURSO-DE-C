#include <iostream>

using namespace std;

int main(){
    int a = 5;
    int *pnt = &a;

    cout<<"El valor de a es: "<<a<<endl;
    cout<<"La direccion de memoria de a es: "<<&a<<endl;
    

    //cambiando el valor de a aptravez del puntero

    *pnt = 10;
    cout<<"EL nuevo valor de a es: "<<a<<endl;


}