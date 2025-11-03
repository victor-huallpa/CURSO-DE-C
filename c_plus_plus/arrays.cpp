#include <iostream>


using std::cout, std::cin, std::endl;

int main(){
    std::string automoviles[] = {"Corvett", "Mustang", "Audi"};// esta definido el tam;o por los elementos dados

    cout<<automoviles[0]<<endl;
    cout<<automoviles[1]<<endl;
    cout<<automoviles[2]<<endl;

    //cambair valores
    automoviles[0] = "Toyota";
    cout<<automoviles[0]<<endl;

    std::string autos[3];//al ser estatico requiere definirme u ntama;o
    autos[0] = "Nisan";
    cout <<autos[0]<<endl;

    return 0;
}