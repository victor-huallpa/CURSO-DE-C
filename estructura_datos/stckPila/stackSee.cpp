#include <iostream>
#include <stack>

using namespace std;


int main (){
    stack<int> pila;


    for (int i = 0; i < 10; i++)
    {
        pila.push(i);
    }
    cout<<pila.size()<<endl;

    for (int i = pila.size(); i>0; i--)
    {
        cout<<pila.top()<<endl;
        pila.pop();
    }
    // cout<<pila.size()<<endl;
    
    return 0;
}