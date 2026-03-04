#include <iostream>
using namespace std;

int datos(int numd);
int menu();
// int datos(int numd);


int main() {
    
    int user1;
    int user2;
    int option;
    bool cond = true;
    bool condition = true;


    cout<<"Bienvenido a nuestra calculadora basica!\n";
    while (condition)
    {
        option = menu();

        switch (option)
        {
        case 1:
            user1 = datos(1);
            user2 = datos(2);
            cout<<"La suma es: "<< user1 + user2<<endl;
            break;
        case 2:
            user1 = datos(1);
            user2 = datos(2);
            cout<<"La resta es: "<< user1 - user2<<endl;
            break;
        case 3:
            user1 = datos(1);
            user2 = datos(2);
            cout<<"La multiplicacion es: "<< user1 * user2<<endl;
            break;
        case 4:
            
            while (cond)
            {
                user1 = datos(1);
                user2 = datos(2);
                if (user2 == 0)
                {
                    cout<<"Lo siento una divicion por 0 no se puede dar.\n";
                    cout<<"Vuelva a ingresar los datos.\n";
                    continue;
                }
                cond = false;
            }
            
            cout<<"La divicion es: "<< user1 / user2<<endl;
            break;
        case 5:
            cout<<"Gracias por usar nuestra calculadora de operaciones basicas!\n";
            condition = false;
            break;
        default:
            cout<<"Lo siento la opcion que ingreso no existe!\nVuelva a intentarlo.\n";
            break;
        }
    }
    
    return 0;
}

int menu(){
    int option;

    cout<<"Ingrese la opracion que desea realizar: \n";
    cout<<"1 : suma.\n";
    cout<<"2 : resta.\n";
    cout<<"3 : multiplicacion.\n";
    cout<<"4 : divicion.\n";
    cout<<"5 : salir.\n";
    cin>>option;

    return option;
}

int datos(int numd){
    int num;
    cout<<"Ingrese dato "<<numd<< ": "<<endl;
    cin>>num;
    return num;
}
