// Lee la entrada línea por línea. Si después de leer las primeras 42 líneas alguna está vacía 
// (es decir, contiene una cadena de longitud 0), imprime la línea que aparece 42 líneas antes. 
// Por ejemplo, si la línea 242 está vacía, el programa debe imprimir la línea 200. 
// Este programa debe estar diseñado para no almacenar nunca más de 43 líneas de la entrada a la vez.

//QUEUE(cola) FIFO (first in, first out)

#include <iostream>
#include <queue>
#include <fstream>

int main(){

    int conta=0;

    std::string linea;
    std::ifstream archi("lineas_text.txt");
    std::queue<std::string> cola;

    if(!archi){
        std::cout<<"error";
    }

    while(getline(archi,linea)){
        conta ++;
        if (linea == "")
        {
            if (cola.size()==43)
            {
                std::cout<<cola.front()<<std::endl;//imprime el mas antiguo(El priemro que ingreso o esta en la lista)
                // std::cout<<cola.back()<<std::endl;//imprime el mas reciente
                std::cout<<conta-42;

            }
            
        }
        cola.push(linea);
        if (cola.size() > 43)
        {
            cola.pop();//elimina el mas antiguo, el priemro en entrar;
        }
        
        
    }

    return 0;
}