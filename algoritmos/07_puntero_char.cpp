#include <iostream>
#include <string>

int longitud(char *str);

using namespace std;

int main(){
    string str = "pedrito";


    cout<<"La lognitud del string '"<<str<<"' es de: "<<longitud(&str[0])<<endl;


    return 0;
}

int longitud(char *str){
    int cont = 0;
    while (*(str+cont) != '\0')//el final de un strin es '\0
    {
        cont += 1;
        // str++;
        // cout<<"hello"<<endl;
    }
    return cont;

}