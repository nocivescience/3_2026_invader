#include <iostream>
#include <vector>
#include <string>

// Definimos los colores (Códigos ANSI)
#define RESET   "\033[0m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// --- LA CLASE (El molde) ---
class Guerrero {
public:
    std::string nombre, apellido, sexo;
    int nivel;
    int fuerza;

    // Constructor: Define cómo nace un guerrero
    Guerrero(std::string n, std::string a, std::string s, int f) {
        nombre = n;
        apellido = a;
        sexo = s;
        fuerza = f;
        nivel = 1;
    }

    // Un método: Algo que el guerrero sabe hacer
    void MostrarStatus() {
        // Usamos los códigos de color antes de cada dato
        std::cout << CYAN << ">>> [" 
                  << YELLOW << BOLD << nombre << " " << apellido << RESET << CYAN << "  " 
                  << BLUE << sexo << CYAN << "] " 
                  << RESET << " - Nivel: " << GREEN << nivel << RESET
                  << " | Fuerza: " << BOLD << fuerza << "kg" << RESET << std::endl;
    }
};

int main() {
    // El vector es nuestra "lista dinámica" (como en Python)
    std::vector<Guerrero> dojo;
    int opcion = 0;

    std::cout << "--- BIENVENIDO AL DOJO C++ ---" << std::endl;

    while (opcion != 3) {
        
        std::cout << "\n1. Entrenar nuevo guerrero" << std::endl;
        std::cout << "2. Mostrar lista de guerreros" << std::endl;
        std::cout << "3. Salir del dojo" << std::endl;
        std::cout << "Selecciona una opción: ";
        std::cin >> opcion;

        if (opcion == 1) {
            std::string nombre;
            std::string apellido;
            int fuerza;
            std::string sexo;
            std::cout << "Nombre: ";
            std::cin >> nombre;
            std::cout << "Apellido: ";
            std::cin >> apellido;
            std::cout << "Sexo: ";
            std::cin >> sexo;
            std::cout << "Fuerza (kg): ";
            std::cin >> fuerza;

            // Creamos el objeto y lo metemos al vector
            dojo.push_back(Guerrero(nombre, apellido, sexo, fuerza));
            std::cout << "¡Guerrero entrenando!" << std::endl;
        } 
        else if (opcion == 2) {
            std::cout << "\n--- LISTA DE ENTRENAMIENTO ---" << std::endl;
            // Usamos un bucle moderno de C++ para recorrer la lista
            for (auto& g : dojo) {
                g.MostrarStatus();
            }
        }
    }

    std::cout << "Dojo cerrado. ¡Sigue entrenando!" << std::endl;
    return 0;
}