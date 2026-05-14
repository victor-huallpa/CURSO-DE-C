#include <iostream>

using namespace std;

int factorial(int num);

int main () {
    int fac;
    cout<<"Calculando factorial...\n";
    cout<<"Ingrese numero: ";
    cin>>fac;

    cout<<"El dactoria es: "<<factorial(fac)<<endl;

    return 0;
}

int factorial(int num){
    // cout<<num<<endl;
    if(num == 0){
        return 1;
    }else{
        return num * factorial(num -1);
        
    }
}
