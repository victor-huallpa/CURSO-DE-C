#include <iostream>

using namespace std;

int main(){
    //variables
    bool condition = true;
    int numF;
    int ini = 0;
    int des = 1;
    
    cout<<"Bienvenido a calculando primeros numeros de Fibonacci!"<<endl;

    //interaz
    while (condition)
    {
        //menu user
        cout<<"Ingrese la cantidad de numero de Fibonacci que quieres o cero para salir: ";
        cin>>numF;

        if (numF == 0)
        {
            condition = false;
            cout<<"Gracias por calcular con nosotros los numeros de Fibonacci!... Hasta la proxima...";
            continue;
        }
        

        for (int i = 0; i < numF; i++)
        {
            if (i < numF - 1)
            {
                cout<<ini<<", ";
                if (i != 0)
                {
                    ini = des;
                    des = ini + des;
                }
                continue;
            }

            cout << ini<<endl;
            cout<<"son todos. "<<endl; 

            ini = 0;
            des = 1; 
        }
        

    }
    

    return 0;

}