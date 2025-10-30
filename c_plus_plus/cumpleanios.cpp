#include <iostream>
#include <ctime>

using namespace std;

void felizcumpleanos();

int main (){
    int repeticion;

    cout<<"cuantas veces queires cantar feliz cumpleanos: ";
    cin>>repeticion;


    for(int i = 1; i <= repeticion; i++){
        felizcumpleanos();

    }

    return 0;

}

void felizcumpleanos(){
    cout<<"que los cumplas feliz\n";
    cout<<"que los cumplas feliz\n";
    cout<<"que los cumplas a ti]\n";
    cout<<"que los cumplas feliz\n\n";
}

