#include <iostream>

using namespace std;

int main (){

    string students[] = {"maria", "Jose", "Ana"};

    // bulce foreach

    for (string student : students)
    {
        cout<<student<<endl;
    }

    int notas[] = {02, 12, 15, 16};
    //bucle foreach

    for(int nota : notas){
        cout<<nota<<endl;
    }

    //honta el foearc sirve apra iterar sobre arreglos ya que no son muy flexibles.
    
}