/*
STACK: Estructura de datos dond e se apilan los elemtos y es de tipo 
LIFO(Last in, First out) ultimo en entrar, primero en salir

referecia: es como una pila de paltos de loza, quitasel que esta en la cima ya que es mas facil y apilas encima de ella o aniades mas paltos




*/
#include <iostream>
#include <stack>

using namespace std;

int main(){
    // crear stack
    stack<int> pila;

    for (int i = 0; i < 10; i++)
    {
        //aniades elementos al stack
        pila.push(i);
    }

    for (int i = 0; i < pila.size(); i++)
    {
        cout<<pila.top()<<"\n";//muestrar el ultimo elemento
        pila.pop();//eliminas el ultimn oelemento
    }
    
    
}