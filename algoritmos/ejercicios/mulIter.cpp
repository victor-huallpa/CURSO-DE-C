#include <iostream>

using namespace std;

int mulSum(int num, int mul){
    int resul = 0;
    for (int i = 0; i < num; i++)
    {
        resul += mul;
    }
    
    return resul;
}

int main(){

    cout<<"\nLa Multiplicacion es: "<<mulSum(5,5)<<"\n";
    return 0 ;
}