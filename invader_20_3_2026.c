#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define NUM_ENEMIES 10

typedef struct
{
    Vector2 position;
    bool active;
} Enemy;

typedef struct
{
    Vector2 position;
    bool active;
} Bullet;

int main()
{
    float enemySpeed = 1.0f; // Velocidad de caída
    bool gameOver = false;   // Para saber si perdimos

    // Inicialización
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Clon de Space Invaders - Raylib");
    SetTargetFPS(60);

    // Variables de la nave
    Vector2 shipPos = {SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50};
    float shipSpeed = 7.0f;

    // Variables del disparo
    Bullet bullet = {0}; // Inicializar el disparo
    bullet.active = false;
    float bulletSpeed = 10.0f;

    Enemy enemies[NUM_ENEMIES];

    for (int i = 0; i < NUM_ENEMIES; i++)
    {
        enemies[i].position = (Vector2){50 + i * 70, 50}; // Espaciados cada 70 pixeles
        enemies[i].active = true;
    }

    while (!WindowShouldClose())
    {
        // --- 1. Entrada del Usuario ---
        if (IsKeyDown(KEY_LEFT) && shipPos.x > 0)
            shipPos.x -= shipSpeed;
        if (IsKeyDown(KEY_RIGHT) && shipPos.x < SCREEN_WIDTH - 40)
            shipPos.x += shipSpeed;

        // Disparar
        if (IsKeyPressed(KEY_SPACE) && !bullet.active)
        {
            bullet.position = (Vector2){shipPos.x + 15, shipPos.y};
            bullet.active = true;
        }

        // --- 2. Actualización de Lógica ---
        if (bullet.active)
        {
            bullet.position.y -= bulletSpeed;
            // Desactivar si sale de la pantalla
            if (bullet.position.y < 0)
                bullet.active = false;
        }

        if (bullet.active)
        {
            for (int i = 0; i < NUM_ENEMIES; i++)
            {
                if (enemies[i].active)
                {
                    // Creamos rectángulos imaginarios para la colisión
                    Rectangle bulletRect = {bullet.position.x, bullet.position.y, 10, 20};
                    Rectangle enemyRect = {enemies[i].position.x, enemies[i].position.y, 40, 30};

                    if (CheckCollisionRecs(bulletRect, enemyRect))
                    {
                        enemies[i].active = false; // El enemigo muere
                        bullet.active = false;     // La bala desaparece
                    }
                }
            }
        }

        if (!gameOver)
        {
            for (int i = 0; i < NUM_ENEMIES; i++)
            {
                if (enemies[i].active)
                {
                    // 1. Los enemigos bajan constantemente
                    enemies[i].position.y += enemySpeed;

                    // 2. Condición de derrota: ¿Tocaron la altura de la nave?
                    if (enemies[i].position.y >= shipPos.y)
                    {
                        gameOver = true;
                    }
                }
            }
        }

        // --- 3. Dibujado ---
        BeginDrawing();
        ClearBackground(BLACK);

        // Dibujar Nave (un rectángulo simple o "forma de nave")
        DrawRectangleV(shipPos, (Vector2){40, 20}, LIME);
        DrawRectangle(shipPos.x + 15, shipPos.y - 10, 10, 10, LIME); // Cañón

        // Dibujar Disparo
        if (bullet.active)
        {
            DrawRectangleV(bullet.position, (Vector2){10, 20}, YELLOW);
        }

        DrawText("Usa FLECHAS para moverte y ESPACIO para disparar", 10, 10, 20, GRAY);
        if (gameOver)
        {
            DrawText("GAME OVER", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 40, RED);
            DrawText("Presiona ESC para salir", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 50, 20, GRAY);
        }
        EndDrawing();

        for (int i = 0; i < NUM_ENEMIES; i++)
        {
            if (enemies[i].active)
            {
                DrawRectangleV(enemies[i].position, (Vector2){40, 30}, RED);
            }
        }
    }

    CloseWindow();
    return 0;
}