#include <iostream>
using namespace std;

int main() {

    bool condicion = true;
    int multiplicador = 1;
    int multiplicando = 1;

    do
    {
        
        if (multiplicador <= 12 && multiplicador > 0)
        {
            cout << multiplicador * multiplicando<<endl;

            multiplicador ++;
        }else{
            cout<<"fin de la multiplicacion"<<endl;
            condicion = false;
        }
        


    } while (condicion);
    

    
    return 0;
}
