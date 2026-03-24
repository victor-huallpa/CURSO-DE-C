#include <iostream>
void punteroD(int **p);

using namespace std;

int main(){
    int val = 10;
    int *p = &val;

    cout << "El valor de val es: "<<*p<<endl;
    punteroD(&p);
    cout << "El nuevo valor de val es: "<<*p<<endl;

    return 0;
}

void punteroD(int **p){
    **p = 15;
}