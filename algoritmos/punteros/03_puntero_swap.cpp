
#include <iostream>
using namespace std;

void swap(int *a, int *b);

int main(){
    int x = 10;
    int y = 5;

    cout<<"El valor de x es: "<<x<<endl;
    cout<<"El valor de y es: "<<y<<endl;

    swap(&x, &y);

    cout<<"El nuevo valor de x es: "<<x<<endl;
    cout<<"El nuevo valor de y es: "<<y<<endl;

    return 0;
}

//intercambiando valores a traves de punteros y variable temporal.
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
