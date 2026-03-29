#include <iostream>

using namespace std;


void datos(int *n);
int mayor(int *n);

int main (){

    int num[3];
    int conti;

    cout<<"-----BIENVENIDO-----\n";
    while (true)
    {

        cout<<"El mayor de 3\n"<<endl;
        datos(&num[0]);
        cout<<"\n";
        cout<<"El mayor de los tres numeros es: "<<mayor(&num[0])<<"\n"<<endl;

        cout<<"Continuar? :\n1: no\n2: si:\n....";
        cin>>conti;

        if (conti == 1)
        {
            cout<<"\nGracias por usar nuestra APP calculando el mayor de 3.";
            break;
        }
        


        /* code */
    }
    

    return 0;
}


void datos(int *n){
    for (int i = 0; i < 3; i++)
    {
        cout<<"Ingrese el valor "<<i+1<<": ";
        cin>>*(n+i);
    }
}

int mayor(int *n){

    if (*n > *(n+1) && *n > *(n+2))
    {
        return *n;    
    }else if (*(n+1) > *n && *(n+1) > *(n+2) )
    {
        return *(n+1);
    }else{
        return *(n+2);
    }
    
}