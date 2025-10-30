#include <iostream>
#include <ctime>

using namespace std;

void felizcumpleanos(string nombre);

int main (){
    int repeticion;
    string nombre = "Victor";

    cout<<"Nombre del cumpleanero: ";
    cin>>nombre;

    cout<<"cuantas veces queires cantar feliz cumpleanos: ";
    cin>>repeticion;

    cout<<endl;


    for(int i = 1; i <= repeticion; i++){
        felizcumpleanos(nombre);

    }

    return 0;

}

void felizcumpleanos(string nombre){
    cout<<"que los cumplas feliz\n";
    cout<<"que los cumplas feliz\n";
    cout<<"que los cumplas "<<nombre<<endl;
    cout<<"que los cumplas feliz\n\n";
}

