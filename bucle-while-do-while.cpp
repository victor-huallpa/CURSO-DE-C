#include <iostream>
using namespace std;

int main() {

    bool condition = true; 
    bool condition2 = true; 
    int cont = 5;
    int cont2 = 3;

    do
    {
        cout << "hello" << endl;
        cont--;
        if(cont == 0){
            condition = false;
        }
    } while (condition);



    while (condition2)
    {
        cout << "hello" << endl;
        cont2--;
        if(cont2 == 0){
            condition2 = false;
        }
    }
    

    
    cout <<"estamos fuera";
    
    return 0;
}
