#include <iostream>

// Definimos los "interruptores" de color
#define ROJO  "\033[31m"
#define VERDE "\033[32m"
#define AMARILLO "\033[33m"
#define RESET "\033[0m"

int main() {
    // 1. Encendemos el rojo
    // 2. Escribimos "Hola"
    // 3. Apagamos el rojo (RESET)
    // 4. Escribimos el resto normal
    
    std::cout << ROJO << "Hola" << RESET << " Mundo" << std::endl;
    std::cout << VERDE << " Ricardo " << RESET << ROJO << " Fuentes " << RESET << std::endl;
    std::cout << AMARILLO << " C++ " << RESET << " es un lenguaje de programación " << ROJO << " poderoso " << RESET << std::endl;

    return 0;
}