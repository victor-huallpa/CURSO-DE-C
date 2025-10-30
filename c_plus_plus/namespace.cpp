#include <iostream>
namespace primero{
    int x = 1;
    int y = 11;
}
namespace segundo{
    int x = 2;
}
namespace funcion{
    void suma(int a, int b){
        std::cout<< a+b;
    }
}
int main(){
    // se sua using para usar las cosas que estan fuera odentro de clases 
    using std::cout;

    cout<<"hello\n";

    using namespace primero;//indicamos quie usaremos l oque ocntiene priemro ya no requireo '::'

    int x = 0;
    //int y = 0;// encaso este declarada y en local como namesapce primero se tomara la variable local


    //dentro de main
    std::cout<<"X = "<<x<<std::endl;// :: es resolcuion de ambitos
    // dentro de namespace primero
    std::cout<<"X = "<<primero::x<<std::endl;
    std::cout<<"X = "<<y<<std::endl;
    
    // dentro de namespace segundo
    std::cout<<"X = "<<segundo::x<<std::endl;

    // llamamos a la funcion detro de lnamespace 

    // int resultado = funcion::suma(5,4);
    // std::cout<<"5 + 4 = "<<resultado<<std::endl;
    std::cout<<"5 + 4 = ";
    funcion::suma(5,4);
    std::cout<<std::endl;

    return 0;
}