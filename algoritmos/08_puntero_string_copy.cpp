#include <iostream>
#include <string>

using namespace std;

void copy(char *dest, char *src);

int main(){
    // string str = "hello";
    // string copia;
    char str[] = "hello";
    char copia[10];

    //darle espacio de memoria a copia
    // copia.resize(str.size());//reservamos memoria

    cout<<"string src: "<<str<<endl;
    cout<<"string cpia: "<<copia<<endl;

    copy(&copia[0], &str[0]);

    cout<<"string src: "<<str<<endl;
    cout<<"string copia: "<<copia<<endl;

    return 0;
}

void copy(char *dest, char *src){

    while (*src != '\0')
    {
        *dest = *src;

        //hacemos que la memoria vance pra que apunte a otor lado el puntero.
        dest++;
        src++;
    }
    *dest = '\0';

}

