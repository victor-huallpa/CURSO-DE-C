#include <iostream>

using namespace std;

int main(){
    //variables
    bool condition = true;
    int numF;
    int res = 0;
    int in = 1;
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
            if (i<numF-1)
            {
                cout<<res<<", ";

                if (i == 1)
                {
                    continue;
                }
            }else{
                cout<<res<<endl;
            }
            
            // usamos varaible temporal
            res = des;
            des+=in;            
            in = res;

        }
        res = 0;
        in = 1;
        des = 1;
        

    }
    

    return 0;

}