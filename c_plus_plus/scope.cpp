#include <iostream>


void scopes();

using namespace std;

int number1 = 10; //socpe globbal

int main(){
    int number = 12; // scope local

    using ::number1;// una forma de decir que usaremos la varaible global aqui

    scopes();

    cout<<::number1<<endl;//usamos resolucion de ambito para acceder a  la varaible global
    cout<<number1<<endl;// aunque bno se requiera l la resolucion de ambito podemos usarla porque es global
    cout<<number;//no requiere resolucion de ambito porque es local
}

void scopes(){
    //varaible local
    int number = 15;//podemso declara la misma varibale que en la fucnion int porque estan en diferentes ambitos
    cout<<number<<endl;
}