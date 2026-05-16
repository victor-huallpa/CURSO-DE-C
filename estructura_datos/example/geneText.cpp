#include <iostream>
#include <fstream>
#include <string>
#include <random>

int main(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 25);
    std::uniform_int_distribution<> dist2(1, 5);

    int numPa;
    int numCarac;

    std::cout<<"Cuantas palabras qeuire generar: ";
    std::cin>>numPa;

    // std::cout<<"Cuantos caracteres cada palabra:";
    // std::cin>>numCarac;

    std::ofstream archi("lineas_text.txt");


    std::string linea = "";

    for(int i = 0; i < numPa; i++){
        linea = "";
        numCarac = dist2(gen);
        linea = "Linea " + std::to_string(i+1);


        // for (int j = 0; j < numCarac; j++)
        // {
        //     int n = dist(gen);
        //     char let = 'a' + n;
        //     linea += let;
        // }
        if (i == numPa-1)
        {
            archi << linea;
            continue;
        }
        
        archi << linea << std::endl;
    }
    // std::ofstream archi("lineas_text.txt");

    // archi << linea;
    archi.close();

    return 0;
}