#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

int main(){
    queue<string> colaPa;
    queue<string> colaImpa;
    string linea;
    int cont = 1;

    ifstream archi("lineas_text.txt");

    if (!archi) cout<<"Error";

    while (getline(archi, linea))
    {
        if (cont%2 == 0) colaPa.push(linea);
        else  colaImpa.push(linea);
        cont++;
    }
    
    for (int i = colaPa.size(); i> 0; i--)
    {
        cout<<colaPa.front()<<endl;
        colaPa.pop();
    }

    for (int i = colaImpa.size(); i> 0; i--)
    {
        cout<<colaImpa.front()<<endl;
        colaImpa.pop();
    }
    

    return 0;
}