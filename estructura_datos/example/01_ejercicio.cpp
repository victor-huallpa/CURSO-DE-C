// Lee la entrada línea por línea y luego escribe las líneas en orden inverso,
//  de manera que la última línea de entrada se imprima primero, luego la penúltima 
//  línea de entrada, y así sucesivamente

#include <iostream>
#include <fstream>
#include <vector>


int main(){
    std::string linea;
    std::ifstream archivo("lineas_text.txt");
    std::vector<std::string> lineas;

    if (!archivo)
    {
        std::cout<<"No se encontro el archivo";
    }

    // con entrada de archivo desde terminal

    // ./01_ejercicio < lineas_text.txt 
    // while(getline(std::cin,linea)){
    //     lineas.push_back(linea);
    //     // std::cout<<linea<<std::endl;
    // }
    while(getline(archivo,linea)){
        lineas.push_back(linea);
        // std::cout<<linea<<std::endl;
    }

    for (int i = (int)lineas.size()-1; i >= 0; i--)
    {
        std::cout<<lineas[i]<<std::endl;
    }
    
    
    return 0;
}