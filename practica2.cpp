#include <iostream>
#include <string>

#define VERDE  "\033[32m"
#define CIAN   "\033[36m"
#define ROJO   "\033[31m"
#define RESET  "\033[0m"
#define NEGRITA "\033[1m"

int main() {
    std::string ejercicio;
    float pesoCorporal;

    std::cout << CIAN << "Hola, Mundo!" << RESET << std::endl;
    std::cout << VERDE << "Bienvenido a C++" << RESET << std::endl;
    std::cout << ROJO << "¿Cuál es tu peso corporal?" << RESET << std::endl;
    std::cin >> pesoCorporal;
    std::cout << "Tu peso corporal es: " << NEGRITA << pesoCorporal << " kg" << RESET << std::endl;
    return 0;
}