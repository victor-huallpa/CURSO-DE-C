#include <iostream>
using namespace std;

class AccesoSistema{
    public:
    bool login(string user,string pass){
        return(user=="admin"&&pass=="1234");
    }
};

int main(){
    string user="a",pass;
    int n=0;
    AccesoSistema c;
    while(n<3){
        if(user!="admin"){
            cout<<"Ingrese usuario: ";cin>>user;
            cout<<"Ingrese clave: ";cin>>pass;
            if(c.login(user,pass)){
                cout<<"Acceso Concedido";
                break;
            }
            else if(user!="admin"){
                cout<<"Usuario no existe\n";
            }
            else cout<<"Clave incorrecta\n";
            n++;
        }
        else{
            cout<<"Ingrese usuario : admin\n";
            cout<<"Ingrese clave :";cin>>pass;
            if (pass!="1234"){
                cout<<"Clave incorrecta";
                n++;
            }
            else break;
        }
    }
}