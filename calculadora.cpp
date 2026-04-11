#include <iostream>
#include <string>

// Colores para que se vea profesional en tu Manjaro
#define VERDE  "\033[32m"
#define CIAN   "\033[36m"
#define ROJO   "\033[31m"
#define RESET  "\033[0m"
#define NEGRITA "\033[1m"

int main() {
    std::string ejercicio;
    std::string respuestaMaraka;
    float pesoCorporal;
    float lastre;
    int repeticiones;

    std::cout << CIAN << "--- CALCULADORA DE POTENCIA ---" << RESET << std::endl;

    // Uso de >> para capturar datos
    std::cout << "1. Nombre del ejercicio: ";
    std::cin >> ejercicio;

    std::cout << "2. Ingresa tu peso corporal (kg): ";
    std::cin >> pesoCorporal;

    std::cout << "3. Ingresa el lastre usado (kg): ";
    std::cin >> lastre;

    std::cout << "4. ¿Cuántas repeticiones hiciste?: ";
    std::cin >> repeticiones;

    std::cout << "5. te gustan las mujeres? (si/no): ";
    std::cin >> respuestaMaraka;

    // Lógica matemática
    float cargaTotal = pesoCorporal + lastre;
    float volumenTotal = cargaTotal * repeticiones;
    

    // Resultado final con colores
    std::cout << "\n" << VERDE << "=== RESULTADOS DEL ENTRENAMIENTO ===" << RESET << std::endl;
    std::cout << "Ejercicio: " << NEGRITA << ejercicio << RESET << std::endl;
    std::cout << "Carga por repetición: " << cargaTotal << " kg" << std::endl;
    std::cout << "Volumen total movido: " << VERDE << volumenTotal << " kg" << RESET << std::endl;
    std::cout << ROJO << "Marako? " << NEGRITA << respuestaMaraka << RESET << std::endl;

    return 0;
}