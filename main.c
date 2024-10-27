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
    bool vivo;
}Inimigo;

void InitInimigo(Inimigo *inimigo, const char* foto, double vida,int xp,int dano, double posX, double velocidade, bool vivo);
void DrawInimigo(Inimigo *inimigo, int larguraBarra);
void DrawAtaqueReginaldo(Inimigo *inimigos, Texture ReginaldoAtaque, double *posxataque);

int main(void){   
    const int screenWidth = 776;
    const int screenHeight = 522;
    InitWindow(screenWidth, screenHeight, "Minha Primeira Tela com Raylib");

    Texture praia, torre;
    praia = LoadTexture("./textures/Praia.png");
    torre = LoadTexture("./textures/Torre-Reginaldo.png");

    SetTargetFPS(60);

    Inimigo inimigos[2];
    int numInimigos = 0;
    InitInimigo(&inimigos[numInimigos++], "./textures/inimigo.png", 500, 100, 20, 700, 0.8, true);
    InitInimigo(&inimigos[numInimigos++], "./textures/inimigo.png", 500, 100, 20, 1200, 2.5, true);
    
    Texture ReginaldoAtaque = LoadTexture("./textures/Reginaldo-ataque.png");
    double posxataque = 25;

    int largurabarra = 50;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(praia, 0, 0, WHITE);
        DrawTexture(torre, 20, 480-torre.height, WHITE);

        DrawAtaqueReginaldo(inimigos , ReginaldoAtaque , &posxataque);
        
         for (int i = 0; i < numInimigos; i++) {
            DrawInimigo(&inimigos[i], largurabarra);
        }
        
        



        EndDrawing();
    }

    for (int i = 0; i < numInimigos; i++) {
        UnloadTexture(inimigos[i].foto); 
    }

    CloseWindow();

    return 0;
}


void InitInimigo(Inimigo *inimigo, const char* foto, double vida,int xp,int dano, double posX, double velocidade, bool vivo) {
    inimigo->foto = LoadTexture(foto);
    inimigo->vida = vida;
    inimigo->vidaMax = vida;
    inimigo->dano = dano;
    inimigo->posX = posX;
    inimigo->velocidade = velocidade;
    inimigo->vivo = vivo;
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
        inimigo->vivo = false;
        inimigo->posX = 20000;
        UnloadTexture(inimigo->foto);
    }

}


void DrawAtaqueReginaldo(Inimigo *inimigos, Texture ReginaldoAtaque, double *posxataque) {
    bool vivos = false;
    for (int i = 0; i < 2; i++) {
        if (inimigos[i].vivo == true){
            vivos = true;
        }
    }

    for (int i = 0; i < 2; i++) {
        if (*posxataque < inimigos[i].posX - 20 && vivos) {
            DrawTexture(ReginaldoAtaque, *posxataque, 480 - ReginaldoAtaque.height, WHITE);
            *posxataque += 3;
        } else {
            *posxataque = 25;
            inimigos[i].vida -= 100;
        }
    }
}