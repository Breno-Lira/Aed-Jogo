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
    char nome[10];
    double posx;
    double posy;
    double posxataque;
    double posyataque;
    int lane;
    struct Tropa *prox;
}Tropa;


void InitInimigo(Inimigo *inimigo, const char* foto, double vida,int xp,int dano, double posX, double posY ,double velocidade, bool vivo);
void InitBoss(Boss *boss, const char* fotos[8], double vida, int dano, double posX, double posY, double velocidade, bool vivo);
void InitTropas(Tropa *tropas, const char* foto, const char* fotoAtaque , char nome[10] ,double posx, double posy ,double posxataque ,int posyataque);
void DrawInimigo(Inimigo *inimigo, int larguraBarra);
void DrawInimigo2(Inimigo *inimigo, int larguraBarra);
void DrawBoss(Boss *boss, int larguraBarra);
void BossRecebeDano(Boss *boss, int dano);
void DrawAtaqueReginaldo(Inimigo *inimigos, Tropa *Reginaldo, int *numInimigos, Boss *chefe, bool boss);
void Menu();
void inserirTropa(Tropa **head, Tropa **tail, Tropa *tropa ,float posX, float posY, int lane);
void imprimirTropaCompleta(Tropa *head, Tropa *tail ,Inimigo *inimigos1, Inimigo *inimigos2, Inimigo *inimigos3 ,int *numInimigos1, int *numInimigos2, int *numInimigos3,Boss *bossTubarao, bool boss);
void SalvarTelacongelada(Tropa *head, Tropa *tail, RenderTexture2D telaCongelada, Texture2D praia, Rectangle botaoQuadrado, Rectangle botaoQuadrado2, Rectangle botaoQuadrado3,Rectangle botaoPosicionar, 
                         Texture2D icone, Inimigo* inimigos1, int numInimigos1, Inimigo* inimigos2, int numInimigos2, Inimigo* Inimigos3,
                         int numInimigos3, Boss* bossTubarao, int largurabarra, int largurabarraBoss, bool boss);

int main(void){   
    const int screenWidth = 1320;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Minha Primeira Tela com Raylib");
    Tropa *head = NULL;
    Tropa *tail = NULL;

    Texture praia, icone;
    icone = LoadTexture("./textures/iconeReginaldo.png");
    praia = LoadTexture("./textures/praiaNova.png");

    SetTargetFPS(90);

    Tropa Reginaldo, Reginaldo2, Reginaldo3;
    InitTropas(&Reginaldo, "./textures/Torre-Reginaldo.png" , "./textures/Reginaldo-ataque.png" , "Reginaldo" , 20, 290, 25, 300);
    InitTropas(&Reginaldo2, "./textures/Torre-Reginaldo.png" , "./textures/Reginaldo-ataque.png" , "Reginaldo" , 20, 390 , 25 , 400);
    InitTropas(&Reginaldo3, "./textures/Torre-Reginaldo.png" , "./textures/Reginaldo-ataque.png" , "Reginaldo" , 20, 520, 25 , 530);

    Inimigo inimigos3[10];
    Inimigo inimigos2[10];
    Inimigo inimigos1[10];
    int numInimigos3 = 0;
    int numInimigos2 = 0;
    int numInimigos1 = 0;
    
    InitInimigo(&inimigos1[numInimigos1++], "./textures/inimigo.png", 800, 100, 40, 1400, 250 , 0.5, true);
    InitInimigo(&inimigos1[numInimigos1++], "./textures/inimigo.png", 1500, 100, 20, 1400, 250 , 2.5, true);
    
    InitInimigo(&inimigos2[numInimigos2++], "./textures/inimigo.png", 800, 100, 40, 1400, 380 , 0.5, true);
    InitInimigo(&inimigos2[numInimigos2++], "./textures/inimigo.png", 1500, 100, 20, 1500, 380 , 2.5, true);
    InitInimigo(&inimigos2[numInimigos2++], "./textures/inimigo.png", 500, 100, 20, 1550, 380 , 1.5, true);

    InitInimigo(&inimigos3[numInimigos3++], "./textures/inimigo.png", 800, 100, 40, 1400, 510 , 0.5, true);
    InitInimigo(&inimigos3[numInimigos3++], "./textures/inimigo.png", 1500, 100, 20, 1500, 510 , 2.5, true);
    InitInimigo(&inimigos3[numInimigos3++], "./textures/inimigo.png", 500, 100, 20, 1550, 510 , 1.5, true);
    InitInimigo(&inimigos3[numInimigos3++], "./textures/inimigo.png", 500, 100, 20, 1650, 510 , 1.5, true);

    Boss bossTubarao;
    const char* fotosTubarao[8] = {
    "./textures/Tubarao1.png", "./textures/Tubarao2.png",
    "./textures/Tubarao4.png", "./textures/Tubarao8.png", "./textures/Tubarao10.png", 
    "./textures/Tubarao11.png", "./textures/Tubarao12.png", "./textures/Tubarao3.png"
    }; 

    InitBoss(&bossTubarao, fotosTubarao, 20000, 400, 1450, screenHeight-300, 5, true);
    
    int largurabarra = 50;
    int largurabarraBoss = 400;
    bool boss = false;
    Rectangle botaoPosicionar = { 450, 10, 100, 30 }; 
    Rectangle botaoQuadrado = { 20, 260, 50, 50 }; 
    Rectangle botaoQuadrado2 = { 20, 390, 50, 50 };
    Rectangle botaoQuadrado3 = { 20, 520, 50, 50 };

    InitAudioDevice();
    Music soundBoss = LoadMusicStream("./audio/audio-teste2.mp3");

    //Menu();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Vector2 mousePosition = GetMousePosition();
        UpdateMusicStream(soundBoss);  

        DrawTexture(praia, 0, 0, WHITE); 
        /*DrawRectangleRec(botaoQuadrado, GREEN);
        DrawRectangleRec(botaoQuadrado2, BLUE);  
        DrawRectangleRec(botaoQuadrado3, RED);*/
        DrawRectangleRec(botaoPosicionar, GRAY);  
        DrawText("Posicionar", botaoPosicionar.x + 10, botaoPosicionar.y + 10, 20, BLACK);
        DrawTexture(icone, 300, 10, WHITE);

        //Inicio selecao personagem
        if (CheckCollisionPointRec(mousePosition, botaoPosicionar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { 
            bool botaoclicado = true;

            RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

            SalvarTelacongelada(head, tail, telaCongelada ,praia, botaoQuadrado, botaoQuadrado2, botaoQuadrado3, botaoPosicionar, 
                         icone, inimigos1, numInimigos1, inimigos2, numInimigos2, inimigos3,
                         numInimigos3, &bossTubarao, largurabarra, largurabarraBoss, boss);

            
            while (botaoclicado && !WindowShouldClose()) {
                BeginDrawing();
                DrawTextureRec(telaCongelada.texture, (Rectangle){ 0, 0, (float)telaCongelada.texture.width, (float)-telaCongelada.texture.height }, (Vector2){ 0, 0 }, WHITE);
                DrawText("Escolha um local...", 550, 300, 20, DARKGRAY);
                EndDrawing();
                Vector2 mousePosition = GetMousePosition();

                if (CheckCollisionPointRec(mousePosition, botaoQuadrado) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    inserirTropa(&head, &tail, &Reginaldo, botaoQuadrado.x, botaoQuadrado.y, 1);
                    botaoclicado = false;

                }
                else if (CheckCollisionPointRec(mousePosition, botaoQuadrado2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                   inserirTropa(&head, &tail, &Reginaldo2, botaoQuadrado2.x, botaoQuadrado2.y, 2);
                   botaoclicado = false;

                }
                else if (CheckCollisionPointRec(mousePosition, botaoQuadrado3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                   inserirTropa(&head, &tail, &Reginaldo3, botaoQuadrado3.x, botaoQuadrado3.y, 3);
                   botaoclicado = false;

                }
                
                else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){  
                    botaoclicado = false;
                }
            }

            UnloadRenderTexture(telaCongelada); 
        }   
        //Fim selecao de personagem 

       /*if (head!=NULL){
            do{

                DrawTexture(head->foto, head->posx, head->posy, WHITE);
                if (strcmp(head->nome, Reginaldo.nome) == 0){
                    if (head->lane == 1){
                        DrawAtaqueReginaldo(inimigos1 , head , &numInimigos1, &bossTubarao, boss);
                    }
                    else if (head->lane == 2){
                        DrawAtaqueReginaldo(inimigos2 , head , &numInimigos2, &bossTubarao, boss);
                    }
                }
            head = head->prox;

            }while (head!= tail->prox);
        }*/

       imprimirTropaCompleta(head, tail, inimigos1, inimigos2, inimigos3, &numInimigos1, &numInimigos2, &numInimigos3, &bossTubarao, boss);
        
        

        /*
        DrawTexture(Reginaldo.foto, Reginaldo.posx, Reginaldo.posy, WHITE);
        DrawTexture(Reginaldo2.foto, Reginaldo2.posx, Reginaldo2.posy, WHITE);        
        DrawAtaqueReginaldo(inimigos1 , &Reginaldo , &numInimigos1, &bossTubarao, boss);
        DrawAtaqueReginaldo(inimigos2 , &Reginaldo2 , &numInimigos2, &bossTubarao, boss);
        
        DrawTexture(Reginaldo3.foto, Reginaldo3.posx, Reginaldo3.posy, WHITE);
        DrawAtaqueReginaldo(inimigos3 , &Reginaldo3 , &numInimigos3, &bossTubarao, boss);*/

        for (int i = 0; i < numInimigos1; i++) {
            DrawInimigo(&inimigos1[i], largurabarra);
        }
        
        for (int i = 0; i < numInimigos2; i++) {
            DrawInimigo(&inimigos2[i], largurabarra);
        }

        for (int i = 0; i < numInimigos3; i++) {
            DrawInimigo(&inimigos3[i], largurabarra);
        }

        if (numInimigos1+numInimigos2+numInimigos3<=0){
            boss = true;
            DrawBoss(&bossTubarao, largurabarraBoss);
            //PlayMusicStream(soundBoss);

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

    UnloadMusicStream(soundBoss);
    CloseWindow();
    CloseAudioDevice();

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

void InitTropas(Tropa *tropas, const char* foto, const char* fotoAtaque , char nome[10] ,double posx, double posy ,double posxataque ,int posyataque) {
    tropas->foto = LoadTexture(foto);
    tropas->fotoAtaque = LoadTexture(fotoAtaque);
    strcpy(tropas->nome, nome);
    tropas->posx = posx;
    tropas->posy = posy;
    tropas->posxataque = posxataque;
    tropas->posyataque = posyataque;
}

void DrawInimigo(Inimigo *inimigo, int larguraBarra){ 
    if (inimigo->posX >= 140){
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

        if (boss->posX >= 140) {
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

            if (Reginaldo->posxataque < alvo->posX - 20 && alvo->posX < 1350) {
                DrawTexture(Reginaldo->fotoAtaque, Reginaldo->posxataque, Reginaldo->posyataque, WHITE);
                Reginaldo->posxataque += 3;
            } 
            else if (Reginaldo->posxataque >= alvo->posX - 20){
                Reginaldo->posxataque = Reginaldo->posx+5;
                alvo->vida -= 100;
                if (alvo->vida <= 0) {
                    inimigos[alvoIndex] = inimigos[*numInimigos - 1];
                    (*numInimigos)--;
                }
            }
        }
    }
    else{
         if (Reginaldo->posxataque < chefe->posX - 20 && chefe->posX < 1500) {
                DrawTexture(Reginaldo->fotoAtaque, Reginaldo->posxataque, Reginaldo->posyataque, WHITE);
                Reginaldo->posxataque += 3;
            } 
            else if (Reginaldo->posxataque >= chefe->posX - 20){
                Reginaldo->posxataque = Reginaldo->posx+5;
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

    Texture menu;
    menu = LoadTexture("./textures/praia.png");
    /*
    Rectangle botaojogar = {100, 150, 200, 50};
    Rectangle botaoranking = {100, 150, 200, 50};
    Rectangle botaoexit = {100, 150, 200, 50};  */

    while (!WindowShouldClose()) {
         BeginDrawing();

        DrawTexture(menu, 0, 0, WHITE);
        /*
        if (CheckCollisionPointRec(GetMousePosition(), botaojogar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

        }

        if (CheckCollisionPointRec(GetMousePosition(), botaoranking) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

        }

        if (CheckCollisionPointRec(GetMousePosition(), botaoexit) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        }*/

        EndDrawing();
    }

    CloseWindow();
}

void inserirTropa(Tropa **head, Tropa **tail, Tropa *tropa ,float posX, float posY, int lane){
    Tropa *novo = (Tropa*) malloc (sizeof(Tropa));
    double posx = posX;

    double posy = posY;
    novo = tropa;
    novo->posx = posx;
    novo->posy = posy;
    novo->posxataque = posx+5;
    novo->posyataque = posy+20;
    novo->lane = lane;

    if (*head == NULL){
        *head = novo;
        *tail = *head;
        (*head)->prox = *head; 
    }
    else{
        novo->prox = *head;
        (*tail)->prox = novo;
        *tail = novo;
    }
}

void imprimirTropaCompleta(Tropa *head, Tropa *tail ,Inimigo *inimigos1, Inimigo *inimigos2, Inimigo *inimigos3 ,int *numInimigos1, int *numInimigos2, int *numInimigos3, Boss *bossTubarao, bool boss){
    if (head!=NULL){
            do{

                DrawTexture(head->foto, head->posx, head->posy, WHITE);
                if (strcmp(head->nome, "Reginaldo") == 0){
                    if (head->lane == 1){
                        DrawAtaqueReginaldo(inimigos1 , head , numInimigos1, bossTubarao, boss);
                    }
                    else if (head->lane == 2){
                        DrawAtaqueReginaldo(inimigos2 , head , numInimigos2, bossTubarao, boss);
                    }
                    else if (head->lane == 3){
                        DrawAtaqueReginaldo(inimigos3 , head , numInimigos3, bossTubarao, boss);
                    }
                }
            head = head->prox;

            }while (head!= tail->prox);
        }
}

void SalvarTelacongelada(Tropa *head, Tropa *tail ,RenderTexture2D telaCongelada, Texture2D praia, Rectangle botaoQuadrado, Rectangle botaoQuadrado2, Rectangle botaoQuadrado3,Rectangle botaoPosicionar, 
                         Texture2D icone, Inimigo* inimigos1, int numInimigos1, Inimigo* inimigos2, int numInimigos2, Inimigo* inimigos3,
                         int numInimigos3, Boss* bossTubarao, int largurabarra, int largurabarraBoss, bool boss){
    
            BeginTextureMode(telaCongelada);  
            ClearBackground(RAYWHITE);  
            BeginDrawing();
            DrawTexture(praia, 0, 0, WHITE);
            DrawRectangleRec(botaoQuadrado, GREEN);
            DrawRectangleRec(botaoQuadrado2, BLUE);
            DrawRectangleRec(botaoQuadrado3, RED);
            DrawRectangleRec(botaoPosicionar, GRAY);
            DrawText("Posicionar", botaoPosicionar.x + 10, botaoPosicionar.y + 10, 20, BLACK);
            DrawTexture(icone, 300, 10, WHITE);
            imprimirTropaCompleta(head, tail , inimigos1, inimigos2, inimigos3,&numInimigos1, &numInimigos2, &numInimigos3, bossTubarao, boss);

            
            for (int i = 0; i < numInimigos1; i++) {
                DrawInimigo(&inimigos1[i], largurabarra);
            }
             for (int i = 0; i < numInimigos2; i++) {
                DrawInimigo(&inimigos2[i], largurabarra);
            }
            for (int i = 0; i < numInimigos3; i++) {
                DrawInimigo(&inimigos3[i], largurabarra);
            }


            if (numInimigos1+numInimigos2+numInimigos3<=0){
                boss = true;
                DrawBoss(bossTubarao, largurabarraBoss);
                //PlayMusicStream(soundBoss);
            }
            EndDrawing();
            EndTextureMode();
}