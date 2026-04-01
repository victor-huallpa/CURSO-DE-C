#include <iostream>


using namespace std;

void orden(char * word, int n);

int main(){

    char words[10] = "ehlol";
    char hello[10] = "hello";
    int cont = 0;
    for (int i = 0; i < 5; i++)
    {
        if (hello[cont] != words[i])
        {
            continue;
        }
        orden(&words[i], cont);
        i = 0;
        cont++;

           
    }
    



    return 0;
}

void orden(char * word, int n){
    char pre = *word;
}