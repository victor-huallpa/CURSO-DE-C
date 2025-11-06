#include <iostream>
#include <string>

using namespace std;
int anstrong(const string& numTex);
int main (){
    int num;
    string convert;

    cout<<"Ingrese un numero: ";
    cin>>num;

    convert = to_string(num);

    anstrong(convert);
    return 0;
}

int anstrong(const string& numTex){

}
