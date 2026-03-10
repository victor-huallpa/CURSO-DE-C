#include <iostream>
// #include <ctime>

using namespace std;

int main(){

    srand(time(NULL));//establecemos la semilla y dentro colocamos el tiempo para  que la semilla cambie 

    int num = (rand()%20)+ 1; //genera numero aleatorios del 1 al 20

    cout<<num;
    

    return 0;
}