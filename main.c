#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/raylib.h"
#include "include/raymath.h"
#include "include/rpng.h"
#include "include/raygui.h"


int main(void)
{
    // Inicializa a janela
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Minha Primeira Tela com Raylib");

    // Define a taxa de frames por segundo
    SetTargetFPS(60);

    // Loop principal do jogo
    while (!WindowShouldClose()) // Verifica se a janela deve fechar
    {
        // Começa o desenho
        BeginDrawing();

        // Limpa a tela com uma cor de fundo
        ClearBackground(RAYWHITE);

        // Exibe uma mensagem no centro da tela
        DrawText("Ola, Mundo!", 190, 200, 20, LIGHTGRAY);

        // Finaliza o desenho
        EndDrawing();
    }

    // Fecha a janela e limpa os recursos
    CloseWindow();

    return 0;
}


