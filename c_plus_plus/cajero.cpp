
#include <iostream>
#include <iomanip>
//ayuda con los tipos de datos a verifcar si es int o texto
#include <limits>

using std::cout;
using std::cin;
using std::endl;

//funciones 
void mostrarSaldo(double saldo);
double deposito();
double retirar(double saldo);

int main (){
    double saldo = 500;
    // char opc = 0;
    int opc = 0;


    do
    {
        cout<<"*******************\n";
        cout<<"Ingrese una opcion: \n";
        cout<<"*******************\n\n";
        cout<<"1. Mostrar saldo\n";
        cout<<"2. Depositar dinero\n";
        cout<<"3. Retirar dinero\n";
        cout<<"4. Salir\n";
        cin>>opc;

        if(cin.fail()){ // 🔹 Verifica si la entrada falló
            cin.clear(); // limpia el estado de error
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // descarta lo que haya quedado en el buffer

            cout << "\033[2J\033[1;1H";
            cout << "Entrada invalida. Por favor ingrese un número válido.\n\n";
            continue; // vuelve a mostrar el menú
        }

        switch (opc)
        {
        case 1:
            mostrarSaldo(saldo);
            break;
        case 2:
            saldo  += deposito();
            mostrarSaldo(saldo);
            break;
        case 3:
            saldo -= retirar(saldo);
            mostrarSaldo(saldo);
            break;
        case 4:
            cout<<"Gracias por usar nuestra app!..\n";
            break;
        
        default:
                //limpiar consola con metodo ANSI
            cout << "\033[2J\033[1;1H";
            cout<<"Lo siento esta opcion "<<opc<< " no esta disponible.\nintentelo de nuevo.\n";
            break;
        }
    } while (opc != 4);
    
    

    return 0;
}

void mostrarSaldo(double saldo){
    //fixed ayuda a manipular el flujo emn este cas odesde el punto lfotante pertenece a la libreria iomanip
    cout<<"Su saldo es: $"<<std::setprecision(2)<<std::fixed<<saldo<<endl<<endl;
}

double deposito(){
    double monto = 0;
    //limpiar consola con metodo ANSI
    cout << "\033[2J\033[1;1H";
    do
    {
        cout<<"\nIngrese el monto a despositar: ";
        cin>>monto;
        
        if(monto < 0){
            cout<<"\nLo siento no puedes depositar montos negativos, vuelve a intentarlo\n";
        }

    } while (monto < 0);
    
    
    return monto;
}

double retirar(double saldo){
    double monto = 0;
    //limpiar consola con metodo ANSI
    cout << "\033[2J\033[1;1H";

    cout<<"Ingrese el monto a retirar: ";
    cin>>monto;
    if(monto > saldo){
        cout<<"Fondos insuficientes\n";
        return 0.0;
    }else if(monto<0){
        cout<<"Cantidad invalida...\nCancelando retiro\n";
        return 0;
    }else{
        return monto;
    }
}