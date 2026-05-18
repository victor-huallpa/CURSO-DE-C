#include <iostream>
#include <stack>

using namespace std;


int main(){

    stack<int> pila;
    stack<int> pila2;

    //operaiocnes basicas.
    
    pila.push(10);//ingresar dato
    pila2.push(100);//ingresar dato
    pila.top();//mostar dato
    pila.pop();//eliminar dato
    pila.empty();//verifica si pila esta vacio
    pila.size(); //devuelve el taminio de la pila 
    pila.swap(pila2);//intercambia pilas
    
    


    return 0;
}