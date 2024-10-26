#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/raylib.h"
#include "include/raymath.h"
#include "include/rpng.h"
#include "include/raygui.h"



int main(void){   
    const int screenWidth = 776;
    const int screenHeight = 522;
    InitWindow(screenWidth, screenHeight, "Minha Primeira Tela com Raylib");
    Texture praia, inimigo, torre;
    praia = LoadTexture("./textures/Praia.png");
    inimigo = LoadTexture("./textures/inimigo.png");
    torre = LoadTexture("./textures/Torre-Reginaldo.png");
    SetTargetFPS(60);

    float posX = 600;
    int vida = 500;
    int vidaMax = 500; // Vida máxima do inimigo
    int larguraBarra = 50; // Largura máxima da barra de vida


    while (!WindowShouldClose()) {
        if (posX >= 100){
            posX -= 0.8;
        }
       
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(praia, 0, 0, WHITE);
        DrawTexture(torre, 20, 480-torre.height, WHITE);
        
         if (vida > 0){
           DrawTexture(inimigo, posX, 500 - inimigo.height, WHITE);
           vida--;
           int larguraAtual = (vida * larguraBarra) / vidaMax;
           
           if (vida>340){
            DrawRectangle(posX+40 , 500 - inimigo.height - 10, larguraAtual, 5, GREEN); 
           }
           else if (vida>150){
             DrawRectangle(posX+40 , 500 - inimigo.height - 10, larguraAtual, 5, ORANGE); 
           }
           else{
            DrawRectangle(posX+40 , 500 - inimigo.height - 10, larguraAtual, 5, RED); 
           }
           DrawRectangleLines(posX+40 , 500 - inimigo.height - 10, larguraBarra, 5, BLACK); 
        }
        else{
            vida = 500;
            posX = 600;
        }
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}


