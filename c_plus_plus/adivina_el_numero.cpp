#include <iostream>
// #include <ctime>

using namespace std;

int main (){

    int num, adivinar, intentos=0;

    srand(time(NULL));

    num = rand()%100 + 1;

    cout<<"+++++++++++++++++ ADIVINA EL NUMERO +++++++++++++++++++++\n\n";

    do
    {
        cout<<"Ingrese un numero del 1 al 100: ";
        cin>> adivinar;

        intentos++;

        if(adivinar > num){
            cout<<"mas bajo"<<endl;
        }
        else if(adivinar < num){
            cout<<"mas alto"<<endl;
        }else{
            cout<<"Correcto! \n"<<"intentos "<<intentos;
        }
    } while (num != adivinar);
    

    return 0;
}