#include <iostream>

using namespace std;
int main(){

    int columna = 0, filas = 0;
    bool entrada = true;
    string signo;
    while (entrada)
    {
        cout<<"Filas: ";
        cin>>filas;
        
        cout<<"\nColumnas: ";
        cin>>columna;

        cout<<"\nSigno: ";
        cin>>signo;

        if(filas <= 0 || columna <= 0 || signo.empty()){
            cout<<"\n ingrese datos positivos y mayores a cero. "<<endl;
            continue;
        }
        entrada = false;
    }
    
    for(int i = 1; i <= filas ; i++){
        for(int j = 1; j <= columna; j++){
            cout<<signo<<" ";
        }
        cout<<"\n";
    }

    return 0;
}