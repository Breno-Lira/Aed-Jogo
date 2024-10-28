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

typedef struct Boss {
    Texture foto[12];
    double vida;
    double vidaMax;
    int dano;
    double posX;
    double posY;
    double velocidade;
    bool vivo;
    int frameAtual;      
    bool tomandoDano;
    int frameDano;    
} Boss;

typedef struct Tropa{
    Texture foto, fotoAtaque;
    double posx;
    double posy;
    double posxataque;
    double posyataque;
}Tropa;


void InitInimigo(Inimigo *inimigo, const char* foto, double vida,int xp,int dano, double posX, double posY ,double velocidade, bool vivo);
void InitBoss(Boss *boss, const char* fotos[7], double vida, int dano, double posX, double posY, double velocidade, bool vivo);
void InitTropas(Tropa *tropas, const char* foto, const char* fotoAtaque , double posx, double posy ,double posxataque ,int posyataque);
void DrawInimigo(Inimigo *inimigo, int larguraBarra);
void DrawBoss(Boss *boss, int larguraBarra);
void BossRecebeDano(Boss *boss, int dano);
void DrawAtaqueReginaldo(Inimigo *inimigos, Tropa *Reginaldo, int *numInimigos, Boss *chefe, bool boss);

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

    Boss bossTubarao;
    const char* fotosTubarao[7] = {
    "./textures/Tubarao1.png", "./textures/Tubarao2.png",
    "./textures/Tubarao4.png", "./textures/Tubarao8.png", "./textures/Tubarao10.png", 
    "./textures/Tubarao11.png", "./textures/Tubarao 12.png"
    };

    InitBoss(&bossTubarao, fotosTubarao, 20000, 400, 700, screenHeight-230, 0.3, true);
    
    int largurabarra = 50;
    int largurabarraBoss = 400;
    bool boss = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(praia, 0, 0, WHITE);

        DrawTexture(Reginaldo.foto, Reginaldo.posx, Reginaldo.posy, WHITE);
        DrawTexture(Reginaldo2.foto, Reginaldo2.posx, Reginaldo2.posy, WHITE);

        DrawAtaqueReginaldo(inimigos1 , &Reginaldo , &numInimigos1, &bossTubarao, boss);

        DrawAtaqueReginaldo(inimigos2 , &Reginaldo2 , &numInimigos2, &bossTubarao, boss);
        
        
         for (int i = 0; i < numInimigos1; i++) {
            DrawInimigo(&inimigos1[i], largurabarra);
        }

        for (int i = 0; i < numInimigos2; i++) {
            DrawInimigo(&inimigos2[i], largurabarra);
        }

        if (numInimigos1+numInimigos2+numInimigos3<=0){
            boss = true;
            DrawBoss(&bossTubarao, largurabarraBoss);
            if (bossTubarao.vivo == false){
                DrawRectangle(300, 90, 200, 50, BROWN);
                DrawText ("YOU WIN!", 350 , 100, 20 ,YELLOW);
            }
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

void InitBoss(Boss *boss, const char* fotos[7], double vida, int dano, double posX, double posY, double velocidade, bool vivo) {
    for (int i = 0; i < 7; i++) {
        boss->foto[i] = LoadTexture(fotos[i]);
    }
    boss->vida = vida;
    boss->vidaMax = vida;
    boss->dano = dano;
    boss->posX = posX;
    boss->posY = posY;
    boss->velocidade = velocidade;
    boss->vivo = vivo;
    boss->frameAtual = 0;
    boss->tomandoDano = false;
    boss->frameDano = 0;

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

void DrawBoss(Boss *boss, int larguraBarra) {
    if (boss->posX >= 100) {
        boss->posX -= boss->velocidade;
    }

    if (boss->vida > 0) {
        
        int imagemIndex = (boss->frameDano > 0) ? 1 : 0;  
        DrawTexture(boss->foto[imagemIndex], boss->posX, boss->posY, WHITE);

        
        if (boss->frameDano > 0) {
            boss->frameDano--;
        }

        
        int barraPosX = (772 - larguraBarra) / 2;
        int barraPosY = 70;
        int larguraAtual = (boss->vida * larguraBarra) / boss->vidaMax;

        Color corBarra = RED;
        DrawText("TUBARÃO DE BOA VIAGEM", barraPosX + 50, 40, 20, BLACK);
        DrawRectangle(barraPosX, barraPosY, larguraAtual, 20, corBarra);
        DrawRectangleLines(barraPosX, barraPosY, larguraBarra, 20, BLACK);
    } 
    else {
        boss->vivo = false;
        boss->posX = 20000;
        for (int i = 0; i < 12; i++) {
            UnloadTexture(boss->foto[i]);
        }
    }
}

void DrawAtaqueReginaldo(Inimigo *inimigos, Tropa *Reginaldo, int *numInimigos, Boss *chefe ,bool boss) {
    int alvoIndex = -1;
    double menorDistancia = 10000; 

    if (boss == false){
        for (int i = 0; i < *numInimigos; i++) {
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
                    inimigos[alvoIndex] = inimigos[*numInimigos - 1];
                    (*numInimigos)--;
                }
            }
        }
    }
    else{
         if (Reginaldo->posxataque < chefe->posX - 20 && chefe->posX < 780) {
                DrawTexture(Reginaldo->fotoAtaque, Reginaldo->posxataque, Reginaldo->posyataque, WHITE);
                Reginaldo->posxataque += 3;
            } 
            else {
                Reginaldo->posxataque = 25;
                BossRecebeDano(chefe, 100);
            }
    }

}

void BossRecebeDano(Boss *boss, int dano) {
    boss->vida -= dano;
    boss->tomandoDano = true;
    boss->frameDano = 40; 
}