#include <iostream>
using namespace std;

int main() {

    int factorial;
    int result = 1;
    bool condicion = true;


    while (condicion)
    {
        //menu para el usuario
        cout<<"Calculando factorial...."<<endl;
        cout<<"Si desea salir digite cero."<<endl;
        cout<<"Factorial de que numero desea: ";
        cin>>factorial;//alamcenamos el digito ingresado por el usuario

        //validamos si el usarioa quiere salir.
        if (factorial == 0)
        {
           condicion = false;
           cout<<"Gracias por usar nuestra calculadora de factorial";
           continue;
        }
        
        //calculando factorial con for
        for (int i = 1; i <= factorial; i++)
        {
            result *= i;
        }

        //mostramos resultado de la factorial
        cout<<"El factorial de "<<factorial<<"! es: "<<result<<endl;

        //reiniciamos el resultado por temas de que puede seguir alamcemando resutlados anteriores
        result = 1;
        
    }
    
    return 0;
}