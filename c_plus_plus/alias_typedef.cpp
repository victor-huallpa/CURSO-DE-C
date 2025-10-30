#include <iostream>
#include <vector>

// typedef std::vector<std::pair<std::string, int>> pair_list_t;

//genera un alias para tipos de datos
typedef std::string text_t;
// en caso de que queramos dar alias a una instaicia nos mandara erros porque no es u ntipo de dato ya que es una varaible ay creada
// typedef std::cout imprimir;

//forma correcta 
typedef std::ostream salida_t;
salida_t& imprimir = std::cout;
typedef std::istream entrada_t;
entrada_t& capturar = std::cin;


int main(){
    // pair_list_t pair_list;
    int dato;

    text_t nombre = "alex\n\n";

    imprimir<<nombre<<"hello\n\n";

    imprimir<<"ingrese su edad: ";
    capturar>>dato;

    return 0;
}