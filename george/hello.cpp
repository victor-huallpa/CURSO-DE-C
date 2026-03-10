#include <iostream>

// using namespace std;
namespace datos {
    int numero = 1;
    // int cout = 45;
}

using std::cout;

// using datos::cout;
// using datos::numero;
int main (){

    int num = 0;
    int num1;


    cout<<datos::numero<<std::endl;
    cout<<datos::numero<<std::endl;
    std::cin>>num;
    // cout<<datos::cout<<endl;

    cout<<"hello world";
    return 0;
}

void saludo(){
    
    cout<<"hola";
}