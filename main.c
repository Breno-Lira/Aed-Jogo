#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/raylib.h"
#include "include/raymath.h"
#include "include/rpng.h"
#include "include/raygui.h"

typedef struct Inimigo{
    Texture foto;
    double vida;
    double vidaMax;
    int xp;
    int dano;
    double posX;
    double velocidade;
}Inimigo;

void InitInimigo(Inimigo *inimigo, const char* foto, double vida,int xp,int dano, double posX, double velocidade);
void DrawInimigo(Inimigo *inimigo, int larguraBarra);

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
    Inimigo inimigoTeste2;
    InitInimigo(&inimigoTeste, "./textures/inimigo.png", 500, 100, 20, 700, 0.8);
    InitInimigo(&inimigoTeste2, "./textures/inimigo.png", 500, 100, 20, 1200, 2);
    

    float posxataque = 25;
    int largurabarra = 50;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(praia, 0, 0, WHITE);
        DrawTexture(torre, 20, 480-torre.height, WHITE);

        if (posxataque  < inimigoTeste.posX-20){
            DrawTexture(ReginaldoAtaque, posxataque, 480-ReginaldoAtaque.height, WHITE);
            posxataque += 3;
        }
        else{
            posxataque = 25;
            inimigoTeste.vida -= 100; 
        }
        
        DrawInimigo(&inimigoTeste, largurabarra);
        DrawInimigo(&inimigoTeste2, largurabarra);
        
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}


void InitInimigo(Inimigo *inimigo, const char* foto, double vida,int xp,int dano, double posX, double velocidade) {
    inimigo->foto = LoadTexture(foto);
    inimigo->vida = vida;
    inimigo->vidaMax = vida;
    inimigo->dano = dano;
    inimigo->posX = posX;
    inimigo->velocidade = velocidade;
}

void DrawInimigo(Inimigo *inimigo, int larguraBarra){ 
    if (inimigo->posX >= 100){
            inimigo->posX -= inimigo->velocidade;
        }

    if (inimigo->vida > 0) {

        DrawTexture(inimigo->foto, inimigo->posX, 500 - inimigo->foto.height, WHITE);
        
        int larguraAtual = (inimigo->vida * larguraBarra) / inimigo->vidaMax;
        Color corBarra = GREEN;
        if (inimigo->vida <= 340 && inimigo->vida > 150) {
            corBarra = ORANGE;
        } 
        else if (inimigo->vida <= 150) {
            corBarra = RED;
        }

        DrawRectangle(inimigo->posX + 40, 500 - inimigo->foto.height - 10, larguraAtual, 5, corBarra);
        DrawRectangleLines(inimigo->posX + 40, 500 - inimigo->foto.height - 10, larguraBarra, 5, BLACK);
    } 
    else {
        //inimigo->vida = inimigo->vidaMax;
        inimigo->posX = 1800;
        UnloadTexture(inimigo->foto);
    }

}