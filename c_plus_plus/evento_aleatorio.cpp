#include <iostream>
#include <ctime>

using namespace std;

int main (){

    srand(time(0));
    int randNum = rand() % 5 + 1;
    
    switch (randNum)
    {
    case 1:
        cout<<"Ganaste una calcomania para tu auto.";
        break;
    case 2:
        cout<<"Ganaste una tarjeta de regalo.";
        break;
    case 3:
        cout<<"Ganaste una camiseta.";
        break;
    case 4:
        cout<<"Ganaste un almuerzo gratis.";
        break;
    case 5:
        cout<<"Ganaste entradas para el concierto.";
        break;
    default:
        break;
    }
    return 0;
}