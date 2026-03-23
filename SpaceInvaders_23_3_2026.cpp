#include "raylib.h"
#include <vector>

// --- CLASE ENEMIGO ---
class Enemy {
public:
    Vector2 position;
    float speedY = 120.0f;
    Color color; // El color se guarda aquí para que sea estable
    bool active = true;

    // Constructor: Se ejecuta UNA VEZ al crear el enemigo
    Enemy(float x, float y) : position({x, y}) {
        PickRandomColor();
    }

    // Función auxiliar para cambiar el color solo cuando queremos
    void PickRandomColor() {
        std::vector<Color> possibleColors = { RED, GOLD, MAROON, ORANGE, PURPLE };
        color = possibleColors[GetRandomValue(0, possibleColors.size() - 1)];
    }

    void Update(float dt) {
        position.y += speedY * dt;

        // Si sale por abajo, reaparece arriba con nuevo color
        if (position.y > GetScreenHeight()) {
            Respawn();
        }
    }

    void Respawn() {
        position.y = (float)GetRandomValue(-150, -50);
        position.x = (float)GetRandomValue(50, GetScreenWidth() - 50);
        PickRandomColor();
    }

    void Draw() {
        DrawRectangleV(position, {40, 30}, color);
    }
};

// --- CLASE NAVE ---
class Ship {
public:
    Vector2 position;
    float speed = 450.0f;
    Color myColor;

    Ship(float x, float y) : position({x, y}) {
        // La nave elige su color al inicio y no cambia más
        myColor = SKYBLUE; 
    }

    void Update(float dt) {
        if (IsKeyDown(KEY_LEFT) && position.x > 0) position.x -= speed * dt;
        if (IsKeyDown(KEY_RIGHT) && position.x < GetScreenWidth() - 40) position.x += speed * dt;
    }

    void Draw() {
        DrawRectangleV(position, {40, 20}, myColor);
        DrawRectangle(position.x + 15, position.y - 10, 10, 10, myColor);
    }
};

// --- ESTRUCTURA BALA ---
struct Bullet {
    Vector2 position;
    bool active = false;
};

int main() {
    // Configuración inicial
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Space Invaders - C++ Santiago Edition");
    SetTargetFPS(60);

    // Inicialización de objetos
    Ship player((float)screenWidth / 2, (float)screenHeight - 50);
    
    std::vector<Bullet> bullets(10);
    std::vector<Enemy> enemies;

    // Crear 8 enemigos iniciales
    for (int i = 0; i < 8; i++) {
        enemies.push_back(Enemy(50.0f + i * 90.0f, (float)GetRandomValue(-200, 0)));
    }

    int score = 0;
    bool gameOver = false;

    // Bucle principal
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (!gameOver) {
            // 1. Actualizar Jugador
            player.Update(dt);

            // 2. Disparo (Lógica de entrada)
            if (IsKeyPressed(KEY_SPACE)) {
                for (auto& b : bullets) {
                    if (!b.active) {
                        b.position = { player.position.x + 15, player.position.y };
                        b.active = true;
                        break;
                    }
                }
            }

            // 3. Actualizar Balas y Colisiones
            for (auto& b : bullets) {
                if (b.active) {
                    b.position.y -= 600.0f * dt;
                    if (b.position.y < 0) b.active = false;

                    for (auto& e : enemies) {
                        if (CheckCollisionRecs({b.position.x, b.position.y, 10, 20}, {e.position.x, e.position.y, 40, 30})) {
                            b.active = false;
                            e.Respawn(); // El enemigo vuelve arriba con otro color
                            score += 100;
                        }
                    }
                }
            }

            // 4. Actualizar Enemigos y Condición de Derrota
            for (auto& e : enemies) {
                e.Update(dt);
                // Si un enemigo toca la altura de la nave, perdemos
                if (e.position.y + 30 >= player.position.y) gameOver = true;
            }
        }

        // --- DIBUJADO ---
        BeginDrawing();
            ClearBackground(BLACK);

            if (!gameOver) {
                player.Draw();
                for (auto& e : enemies) e.Draw();
                for (const auto& b : bullets) {
                    if (b.active) DrawRectangleV(b.position, {10, 20}, WHITE);
                }

                DrawText(TextFormat("SCORE: %05d", score), 20, 20, 20, RAYWHITE);
            } else {
                DrawText("GAME OVER", screenWidth/2 - 140, screenHeight/2 - 50, 50, RED);
                DrawText(TextFormat("FINAL SCORE: %d", score), screenWidth/2 - 80, screenHeight/2 + 20, 20, RAYWHITE);
                DrawText("Presiona ESC para salir", screenWidth/2 - 90, screenHeight/2 + 60, 15, GRAY);
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}