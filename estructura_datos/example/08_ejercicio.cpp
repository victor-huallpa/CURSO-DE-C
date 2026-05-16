#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

int main(){
    queue<string> colaPa;
    queue<string> colaImpa;
    string linea;
    int cont = 0;

    ifstream archi("lineas_text.txt");

    if (!archi) cout<<"Error";

    while (getline(archi, linea))
    {
        if (cont%2 == 0)
        {
            colaPa.push(linea);
            continue;
        }
        colaImpa.push(linea);
        
    }
    
    for (int i = colaPa.size(); i> 0; i--)
    {
        cout<<colaPa.front()<<endl;
        colaPa.pop();
    }
    for (int i = colaImpa.size(); i> 0; i--)
    {
        cout<<colaImpa.front()<<endl;
        colaPa.pop();
    }
    

    return 0;
}