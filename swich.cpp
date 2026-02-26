#include <iostream>
using namespace std;

int main() {
    int opciones;
    cout << "ingresse una opcion de operacion: "<< endl;
    cout << "1: suma "<< endl;
    cout << "2: resta "<< endl;
    cin>>opciones;

    switch (opciones)
    {
        case 1:
            /* code */
            
            break;//se coloca break para evitar que entre al siguiente caso
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        
        default://ejecuta si ningun caso es valido
            // codigo
            break;
    }
    
    
    return 0;
}
