#include <iostream>
void punteroD(int **p);

using namespace std;

int main(){
    int val = 10;
    int *p = &val;

    cout << "El valor de val es: "<<*p<<endl;
    punteroD(&p);
    cout << "El nuevo valor de val es: "<<*p<<endl;
    cout << "El nuevo valor de val es: "<<val<<endl;

    return 0;
}

void punteroD(int **p){
    static int newN = 15;
    //cambiamos a donde apunta el puntero original
    *p = &newN;
}