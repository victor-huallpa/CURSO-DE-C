#include <iostream>
using namespace std;

int menu(int option, int option2, bool option3);

// void saludo(){
    
//     cout<<"hola"<<endl;
// }

int main() {
    int op = 5;
    int result;

    result =  menu(op,78 , false);

    if (result == 1)
    {
        cout<<"hola";
    }else if (result == 2)
    {
        cout<<"adios";
    }
    
    
    
    return 0;
}

int menu(int option, int option2, bool option3){
    int num;
    if (option == 1)
    {
        cout<<"opcion 1: ";
        cout<<"opcion 2: ";
        cout<<"opcion 3: ";
        cout<<"opcion 4: ";
        cin>>option;
    }else if (option == 2)
    {
        cout<<"asta luego";
        option = 0;
    }
    
    

    return option;
}