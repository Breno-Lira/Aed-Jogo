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
    Texture foto[8];
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
     int frameAtaque;      
    int indiceAtaque;
} Boss;

typedef struct Tropa{
    Texture foto, fotoAtaque;
    double posx;
    double posy;
    double posxataque;
    double posyataque;
}Tropa;


void InitInimigo(Inimigo *inimigo, const char* foto, double vida,int xp,int dano, double posX, double posY ,double velocidade, bool vivo);
void InitBoss(Boss *boss, const char* fotos[8], double vida, int dano, double posX, double posY, double velocidade, bool vivo);
void InitTropas(Tropa *tropas, const char* foto, const char* fotoAtaque , double posx, double posy ,double posxataque ,int posyataque);
void DrawInimigo(Inimigo *inimigo, int larguraBarra);
void DrawBoss(Boss *boss, int larguraBarra);
void BossRecebeDano(Boss *boss, int dano);
void DrawAtaqueReginaldo(Inimigo *inimigos, Tropa *Reginaldo, int *numInimigos, Boss *chefe, bool boss);
void Menu();

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
    
    /*InitInimigo(&inimigos1[numInimigos1++], "./textures/inimigo.png", 800, 100, 40, 700, 415 , 0.8, true);
    InitInimigo(&inimigos1[numInimigos1++], "./textures/inimigo.png", 500, 100, 20, 1200, 415 , 1.5, true);

    InitInimigo(&inimigos2[numInimigos2++], "./textures/inimigo.png", 800, 100, 40, 700, 320 , 0.5, true);
    InitInimigo(&inimigos2[numInimigos2++], "./textures/inimigo.png", 500, 100, 20, 1000, 320 , 1.0, true);
    InitInimigo(&inimigos2[numInimigos2++], "./textures/inimigo.png", 500, 100, 20, 1050, 320 , 1.0, true);*/

    Boss bossTubarao;
    const char* fotosTubarao[8] = {
    "./textures/Tubarao1.png", "./textures/Tubarao2.png",
    "./textures/Tubarao4.png", "./textures/Tubarao8.png", "./textures/Tubarao10.png", 
    "./textures/Tubarao11.png", "./textures/Tubarao12.png", "./textures/Tubarao3.png"
    }; 

    InitBoss(&bossTubarao, fotosTubarao, 50000, 400, 700, screenHeight-230, 1.0, true);
    
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

void InitBoss(Boss *boss, const char* fotos[8], double vida, int dano, double posX, double posY, double velocidade, bool vivo) {
    for (int i = 0; i < 8; i++) {
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
    boss->frameAtaque = 0;
    boss->indiceAtaque = 0;

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
    if (boss->vida > 0) {

        if (boss->posX >= 120) {
            boss->posX -= boss->velocidade;

            int imagemIndex = (boss->frameDano > 0) ? 1 : 0;  
            DrawTexture(boss->foto[imagemIndex], boss->posX, boss->posY-10, WHITE);

            
            if (boss->frameDano > 0) {
                boss->frameDano--;
            }

        }
        else{

            // Ativação da sequência de ataque
            const int ataqueFrames[] = {2, 1, 3, 5, 6, 7};

            // Desenha o frame atual da sequência de ataque
            int indice = ataqueFrames[boss->indiceAtaque];
            if (indice == 3){
                DrawTexture(boss->foto[indice], boss->posX, boss->posY - 40, WHITE);
            }
            else if (indice == 4){
                DrawTexture(boss->foto[indice], boss->posX-40, boss->posY - 60, WHITE);
            }
            else if (indice == 5){
                DrawTexture(boss->foto[indice], boss->posX-220, boss->posY - 70, WHITE);
            }
            else if (indice == 6){
                DrawTexture(boss->foto[indice], boss->posX-240, boss->posY - 80, WHITE);
            }
            else{
                DrawTexture(boss->foto[indice], boss->posX, boss->posY - 40, WHITE);
            }
            
            

            if (boss->frameAtaque >= 15) { 
                boss->indiceAtaque = (boss->indiceAtaque + 1) % 6; 
                boss->frameAtaque = 0; 
            } else {
                boss->frameAtaque++;
            }

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
        for (int i = 0; i < 7; i++) {
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

void Menu(){
    Rectangle botaojogar = {100, 150, 200, 50};
    Rectangle botaoranking = {100, 150, 200, 50};
    Rectangle botaoexit = {100, 150, 200, 50};  

        while (!WindowShouldClose()) {

        if (CheckCollisionPointRec(GetMousePosition(), botaojogar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            DrawText("Play Clicked!", 300, 150, 20, DARKGREEN);
        }

        if (CheckCollisionPointRec(GetMousePosition(), botaoranking) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            DrawText("Ranking Clicked!", 300, 250, 20, DARKGREEN);
        }

        if (CheckCollisionPointRec(GetMousePosition(), botaoexit) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            DrawText("Exit Clicked!", 300, 350, 20, DARKGREEN);
        }
    }

    CloseWindow();
}