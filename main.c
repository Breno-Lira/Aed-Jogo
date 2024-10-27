#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/raylib.h"
#include "include/raymath.h"
#include "include/rpng.h"
#include "include/raygui.h"

typedef struct Inimigo{
    Texture foto;
    int vida;
    int xp;
    int dano;
}Inimigo;


int main(void){   
    const int screenWidth = 776;
    const int screenHeight = 522;
    InitWindow(screenWidth, screenHeight, "Minha Primeira Tela com Raylib");
    Texture praia, torre, ReginaldoAtaque;
    praia = LoadTexture("./textures/Praia.png");
    torre = LoadTexture("./textures/Torre-Reginaldo.png");
    ReginaldoAtaque = LoadTexture("./textures/Reginaldo-ataque.png");
    SetTargetFPS(60);

    Inimigo inimigoTeste;
    inimigoTeste.vida = 500;
    inimigoTeste.foto = LoadTexture("./textures/inimigo.png");

    float posX = 600;
    int vida = 500;
    int vidaMax = 500; // Vida máxima do inimigo
    int larguraBarra = 50; // Largura máxima da barra de vida
    float posxataque = 25;

    while (!WindowShouldClose()) {
        if (posX >= 100){
            posX -= 0.8;
        }
       
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(praia, 0, 0, WHITE);
        DrawTexture(torre, 20, 480-torre.height, WHITE);

        if (posxataque  < posX-20){
            DrawTexture(ReginaldoAtaque, posxataque, 480-ReginaldoAtaque.height, WHITE);
            posxataque += 3;
        }
        else{
            posxataque = 25;
            vida -= 100; 
        }
        
         if (vida > 0){
           DrawTexture(inimigoTeste.foto, posX, 500 - inimigoTeste.foto.height, WHITE);
           int larguraAtual = (vida * larguraBarra) / vidaMax;
           
           if (vida>340){
            DrawRectangle(posX+40 , 500 - inimigoTeste.foto.height - 10, larguraAtual, 5, GREEN); 
           }
           else if (vida>150){
             DrawRectangle(posX+40 , 500 - inimigoTeste.foto.height - 10, larguraAtual, 5, ORANGE); 
           }
           else{
            DrawRectangle(posX+40 , 500 - inimigoTeste.foto.height - 10, larguraAtual, 5, RED); 
           }
           DrawRectangleLines(posX+40 , 500 - inimigoTeste.foto.height - 10, larguraBarra, 5, BLACK); 
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


