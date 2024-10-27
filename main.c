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
    double posY;
    double velocidade;
    bool vivo;
}Inimigo;

typedef struct Tropa{
    Texture foto, fotoAtaque;
    double posx;
    double posy;
    double posxataque;
    double posyataque;
}Tropa;


void InitInimigo(Inimigo *inimigo, const char* foto, double vida,int xp,int dano, double posX, double posY ,double velocidade, bool vivo);
void InitTropas(Tropa *tropas, const char* foto, const char* fotoAtaque , double posx, double posy ,double posxataque ,int posyataque);
void DrawInimigo(Inimigo *inimigo, int larguraBarra);
void DrawAtaqueReginaldo(Inimigo *inimigos, Tropa *Reginaldo, int numInimigos);

int main(void){   
    const int screenWidth = 776;
    const int screenHeight = 522;
    InitWindow(screenWidth, screenHeight, "Minha Primeira Tela com Raylib");

    Texture praia;
    praia = LoadTexture("./textures/Praia.png");

    SetTargetFPS(90);

    Tropa Reginaldo, Reginaldo2;
    InitTropas(&Reginaldo, "./textures/Torre-Reginaldo.png" , "./textures/Reginaldo-ataque.png" ,  20, 400, 25, 420);

    InitTropas(&Reginaldo2, "./textures/Torre-Reginaldo.png" , "./textures/Reginaldo-ataque.png" ,  20, 320 , 25, 340);

    Inimigo inimigos3[10];
    Inimigo inimigos2[10];
    Inimigo inimigos1[10];
    int numInimigos3 = 0;
    int numInimigos2 = 0;
    int numInimigos1 = 0;
    
    InitInimigo(&inimigos1[numInimigos1++], "./textures/inimigo.png", 800, 100, 40, 700, 415 , 0.8, true);
    InitInimigo(&inimigos1[numInimigos1++], "./textures/inimigo.png", 500, 100, 20, 1200, 415 , 1.5, true);

    InitInimigo(&inimigos2[numInimigos2++], "./textures/inimigo.png", 800, 100, 40, 700, 320 , 0.5, true);
    InitInimigo(&inimigos2[numInimigos2++], "./textures/inimigo.png", 500, 100, 20, 1000, 320 , 1.0, true);
    InitInimigo(&inimigos2[numInimigos2++], "./textures/inimigo.png", 500, 100, 20, 1050, 320 , 1.0, true);

    //Texture ReginaldoAtaque = LoadTexture("./textures/Reginaldo-ataque.png");
    

    int largurabarra = 50;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(praia, 0, 0, WHITE);

        DrawTexture(Reginaldo.foto, Reginaldo.posx, Reginaldo.posy, WHITE);
        DrawTexture(Reginaldo2.foto, Reginaldo2.posx, Reginaldo2.posy, WHITE);

        DrawAtaqueReginaldo(inimigos1 , &Reginaldo , numInimigos1);

        DrawAtaqueReginaldo(inimigos2 , &Reginaldo2 , numInimigos2);
        
        
         for (int i = 0; i < numInimigos1; i++) {
            DrawInimigo(&inimigos1[i], largurabarra);
        }

        for (int i = 0; i < numInimigos2; i++) {
            DrawInimigo(&inimigos2[i], largurabarra);
        }

        EndDrawing();
    }

    for (int i = 0; i < numInimigos1; i++) {
        UnloadTexture(inimigos1[i].foto); 
    }

    for (int i = 0; i < numInimigos2; i++) {
        UnloadTexture(inimigos2[i].foto); 
    }

    for (int i = 0; i < numInimigos3; i++) {
        UnloadTexture(inimigos3[i].foto); 
    }

    CloseWindow();

    return 0;
}


void InitInimigo(Inimigo *inimigo, const char* foto, double vida,int xp,int dano, double posX, double posY,double velocidade, bool vivo) {
    inimigo->foto = LoadTexture(foto);
    inimigo->vida = vida;
    inimigo->vidaMax = vida;
    inimigo->dano = dano;
    inimigo->posX = posX;
    inimigo->posY = posY;
    inimigo->velocidade = velocidade;
    inimigo->vivo = vivo;
}

void InitTropas(Tropa *tropas, const char* foto, const char* fotoAtaque , double posx, double posy ,double posxataque ,int posyataque) {
    tropas->foto = LoadTexture(foto);
    tropas->fotoAtaque = LoadTexture(fotoAtaque);
    tropas->posx = posx;
    tropas->posy = posy;
    tropas->posxataque = posxataque;
    tropas->posyataque = posyataque;
}

void DrawInimigo(Inimigo *inimigo, int larguraBarra){ 
    if (inimigo->posX >= 100){
            inimigo->posX -= inimigo->velocidade;
        }

    if (inimigo->vida > 0) {
        DrawTexture(inimigo->foto, inimigo->posX, inimigo->posY, WHITE);
        
        int larguraAtual = (inimigo->vida * larguraBarra) / inimigo->vidaMax;
        Color corBarra = GREEN;
        if (inimigo->vida <= 340 && inimigo->vida > 150) {
            corBarra = ORANGE;
        } 
        else if (inimigo->vida <= 150) {
            corBarra = RED;
        }

        DrawRectangle(inimigo->posX + 40, inimigo->posY - 10, larguraAtual, 5, corBarra);
        DrawRectangleLines(inimigo->posX + 40, inimigo->posY - 10, larguraBarra, 5, BLACK);
    } 
    else {
        inimigo->vivo = false;
        inimigo->posX = 20000;
        UnloadTexture(inimigo->foto);
    }

}

void DrawAtaqueReginaldo(Inimigo *inimigos, Tropa *Reginaldo, int numInimigos) {
    int alvoIndex = -1;
    double menorDistancia = 10000; 

    for (int i = 0; i < numInimigos; i++) {
        if (inimigos[i].vivo && inimigos[i].posX < menorDistancia) {
            menorDistancia = inimigos[i].posX;
            alvoIndex = i;
        }
    }

    if (alvoIndex != -1) {
        Inimigo *alvo = &inimigos[alvoIndex];

        
        if (Reginaldo->posxataque < alvo->posX - 20 && alvo->posX < 780) {
            DrawTexture(Reginaldo->fotoAtaque, Reginaldo->posxataque, Reginaldo->posyataque, WHITE);
            Reginaldo->posxataque += 3;
        } 
        else {
            Reginaldo->posxataque = 25;
            alvo->vida -= 100;
            if (alvo->vida <= 0) {
                alvo->vivo = false;
            }
        }
    }
}