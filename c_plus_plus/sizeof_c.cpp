#include <iostream>

using namespace std;

int main(){
    // sizeof ayuda a identificar el dam;o en bytes de los tipos de datos alnacenados en una variable o directamente eal tipo 
    // tambie nisrve para poder calcular el tama;o de los arreglos
    double numero = 2.5;
    int num = 1;
    string nombre = "alexander";
    char nota = 'f';
    bool bolean = true;

    char calificaciones[] = {'a', 'b', 'c', 'd', 'e', 'f'};

    cout<< sizeof(numero)<<" bytes" <<endl;
    cout<< sizeof(num)<<" bytes"<<endl;
    cout<< sizeof(nombre)<<" bytes"<<endl;
    cout<< sizeof(nota)<<" bytes"<<endl;
    cout<< sizeof(bolean)<<" bytes"<<endl;
    cout<< sizeof(calificaciones)<<" bytes"<<endl;
    //tam;o de un arreglo
    cout<< sizeof(calificaciones)/sizeof(calificaciones[0])<<" elementos de el array"<<endl;
    cout<< sizeof(calificaciones)/sizeof(char)<<" elementos de el array"<<endl;


    string estudiantes[] = {"estudiantes1", "estudiante2","estudiante3"};

    cout<< sizeof(estudiantes)/sizeof(estudiantes[0])<<endl;
    cout<< sizeof(estudiantes)/sizeof(string)<<endl;
}