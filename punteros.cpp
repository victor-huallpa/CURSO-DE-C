#include <iostream>
using namespace std;

void cambio(int* a){
    *a = 10;
}

int main() {
    int lista[1000];
    // int list2[1000];
    for (int i = 0; i < 1000; i++)
    {
        if (i == 2)
        {
            lista[i] = 5;
        }
        
    }
    
    int x = 10;
    int y = 9;


    // int z = x;

    // x = 12;
    // z = 15;

    bool boleano = true;
    //puntero
    // cambio(x);

    // int* p = &x;

    cout << x<<endl;
    cout << y<<endl;
    cambio(&x);
    cambio(&y);
    // *p = 20;
    cout << x<<endl;
    cout << y<<endl;


    // cout<< *p<<endl;

    cout << x<<endl;
    //direcciones de memoria
    cout << &x<<endl;
    cout << &boleano;

    




    
    return 0;
}
