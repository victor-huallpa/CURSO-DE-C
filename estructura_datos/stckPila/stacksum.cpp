#include <iostream>
#include <stack>

using namespace std;


int main (){
    int sumTo = 0;
    stack<int> pila;
    pila.push(10);
    pila.push(20);
    pila.push(30);

    for (int i = pila.size(); i > 0; i--)
    {
        sumTo += pila.top();
        pila.pop();
    }

    cout<<"La suma total es: "<<sumTo<<endl;

    return 0;
}