#include <iostream>
#include <string>

using namespace std;

int main (){
    string words[10] = {"holu", "hallu", "hola", "hello", "Hola"};
    int count = 5;

    for (int i = 0; i < count; i++)
    {
        if (words[i] == "Hola")
        {
            cout<<"saludo encontrado en la posicion "<<i+1<<endl;
        }
        
    }
    
    
    
    return 0;

}