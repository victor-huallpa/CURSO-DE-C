// Lee las primeras 50 líneas de entrada y escríbelas en orden inverso. Lee las siguientes 50 líneas y escríbelas también en orden inverso. 
// Repite este proceso hasta que no queden más líneas por leer; en ese momento, 
// las líneas restantes se mostrarán en orden inverso.

//LIFO: ultimo en enetrar primero en sali (last in, first out)


#include <iostream>
#include <stack>
#include <fstream>


int main(){
    std::ifstream archi("lineas_text.txt");
    std::stack<std::string> pila;

    std::string linea;

    if(!archi){
        std::cout<<"error.";    
    }
    int contador=0;

    while (getline(archi, linea))
    {
        pila.push(linea);//apila el valor
        contador++;
        if (contador == 50)
        {
            while (!pila.empty())
            {
                std::cout<<pila.top()<<std::endl;//top deveuevl el valor 
                pila.pop();//elimina el valor
            }
            contador = 0;
            
        }
        
    }

    while (!pila.empty()) {
        std::cout << pila.top() << std::endl;
        pila.pop();
    }
        
    return 0;
}