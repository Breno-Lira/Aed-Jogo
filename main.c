#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
    int lane;
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
    int posicao;
    int custo;
    int fase;
    int tempoAtaque;
    struct Tropa *prox;
}Tropa;

typedef struct NodeTropa {
    Tropa tropa;
    struct NodeTropa *esquerda;
    struct NodeTropa *direita;
} NodeTropa;

typedef struct usuario {
    char nome[30];
    int nivel;
    int score;
    struct usuario *prox;
    struct usuario *ant;
} usuario;

typedef enum GameScreen { MENU, CAPTURA_NOME , RANKING ,NIVEL ,JOGO, JOGO2, JOGO3 ,FIM} GameScreen;

void InitInimigo(Inimigo *inimigo, const char* foto, double vida,int xp,int dano, double posX, double posY ,double velocidade, bool vivo, int lane);
void InitBoss(Boss *boss, const char* fotos[8], double vida, int dano, double posX, double posY, double velocidade, bool vivo);
void InitTropas(Tropa *tropas, const char* foto, const char* fotoAtaque , char nome[10] ,double posx, double posy ,double posxataque ,int posyataque, int custo, int fase);
void DrawInimigo(Inimigo *inimigo, double *vidaPraia);
void DrawBoss(Boss *boss, double *vidaPraia);
void BossRecebeDano(Boss *boss, int dano);
void DrawAtaqueReginaldo(Inimigo *inimigos, Tropa *Reginaldo, int *numInimigos, Boss *chefe, bool boss);
void Menu(GameScreen *currentScreen);
void inserirTropa(Tropa **head, Tropa **tail, Tropa *tropa ,float posX, float posY, int lane, int posicao);
void imprimirTropaCompleta(Tropa *head, Tropa *tail ,Inimigo *inimigos1, Inimigo *inimigos2, Inimigo *inimigos3 ,int *numInimigos1, int *numInimigos2, int *numInimigos3,Boss *bossTubarao, bool boss);
void SalvarTelacongelada(Tropa *head, Tropa *tail, RenderTexture2D telaCongelada, Texture2D mapa, 
                         Inimigo* inimigos1, int numInimigos1, Inimigo* inimigos2, int numInimigos2, Inimigo* Inimigos3,
                         int numInimigos3, Boss* bossTubarao, bool boss, Rectangle botaoRemover, double *vidaPraia);
void adicionarTropa(Tropa **head, Tropa **tail, Tropa *tropa, Tropa *tropa2, Tropa *tropa3,
                        Tropa *tropa4, Tropa *tropa5, Tropa *tropa6, RenderTexture2D telaCongelada, Texture2D mapa,
                         Inimigo *inimigos1, int numInimigos1, Inimigo *inimigos2, int numInimigos2, 
                        Inimigo *inimigos3, int numInimigos3, Boss *bossTubarao, bool boss, Rectangle botaoRemover, double *vidaPraia);
void removerTropaBotao(Tropa **head, Tropa **tail, RenderTexture2D telaCongelada, Texture2D mapa, 
                      Inimigo *inimigos1, int numInimigos1,Inimigo *inimigos2, int numInimigos2, Inimigo *inimigos3, int numInimigos3, 
                      Boss *bossTubarao,  bool boss, Rectangle botaoRemover, double *vidaPraia);
void RemoverTropa(Tropa **head, Tropa **tail, int posicao);
void DrawAtaqueCaboclo(Inimigo *inimigos, Tropa *Caboclo, int *numInimigos, Boss *chefe ,bool boss);
void inserirTropaArvore(NodeTropa **raiz, Tropa *tropa);
bool verificarDisponibilidadeTropa(NodeTropa *raiz, char nomeTropa[10], int faseAtual, int xpDisponivel);
void DrawAtaqueLampiao(Inimigo *inimigos, Tropa *Lampiao, int *numInimigos, Boss *chefe ,bool boss);
void DrawAtaqueLaursa(Inimigo *inimigos, Tropa *LaUrsa, int *numInimigos, Boss *chefe ,bool boss);
void DrawAtaqueFrevista(Inimigo *inimigos, Tropa *Frevista, int *numInimigos, Boss *chefe ,bool boss);
void CapturarNome(GameScreen *currentScreen, char *nomeJogador);
void salvarDados(char *nome, int nivel, int score);
void inserir(usuario **head, char *nome, int nivel, int score);
void lerDados(usuario **head);
void organizar(usuario **head);
void trocar(usuario **head, usuario *ant, usuario *prox);
void DrawAtaqueGonzaga(Inimigo *inimigos, Inimigo *inimigos2, Inimigo *inimigos3,Tropa *Gonzaga, int *numInimigos, 
 int *numInimigos2, int *numInimigos3, Boss *chefe ,bool boss);

bool AtacarInimigosNaLane(Inimigo *inimigos, int *numInimigos, Tropa *Gonzaga, int danoPorAtaque);
void DrawBossBoto(Boss *boss, double *vidaPraia);

bool casa1=true;
bool casa2=true;
bool casa3=true;
bool casa4=true;
bool casa5=true;
bool casa6=true;

Rectangle botaoPosicionar = { 348, 14, 40, 40 }; 
Rectangle botaoPosicionar2 = { 412, 14, 40, 40 }; 
Rectangle botaoPosicionar3 = { 476, 14, 40, 40 }; 
Rectangle botaoPosicionar4 = { 545, 14, 40, 40 }; 
Rectangle botaoPosicionar5 = { 612, 14, 40, 40 }; 
Rectangle botaoPosicionar6 = { 674, 14, 40, 40 }; 
Rectangle botaoRemover = { 917, 11, 50, 50 }; 

Rectangle botaoQuadrado = { 20, 260, 64, 64 }; 
Rectangle botaoQuadrado2 = { 20, 390, 64, 64 };
Rectangle botaoQuadrado3 = { 20, 520, 64, 64 };

Rectangle botaoQuadrado4 = { 100, 300, 64, 64 }; 
Rectangle botaoQuadrado5 = { 100, 430, 64, 64 };
Rectangle botaoQuadrado6 = { 100, 540, 64, 64 };

int largurabarra = 50;
int largurabarraBoss = 400; 
int largurabarraxp = 500; 
int experiencia = 0;
int experienciaMax = 1000;
bool boss = false;
bool range;
int nivelXp=4;
int scoreTotal=0;
double larguraxp=0;
int contLampiao1=0;
int contLampiao2=0;
int contLampiao3=0;
double vidaPraiaMax = 10000; 
int fase = 1;

int main(void){   
    const int screenWidth = 1316;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Minha Primeira Tela com Raylib");
    Tropa *head = NULL;
    Tropa *tail = NULL;
    NodeTropa *arvore = NULL;
    usuario *head2 = NULL;

    Texture praia, ponte, forte;
    praia = LoadTexture("./textures/praiaNova.png");
    ponte = LoadTexture("./textures/ponte3.png");
    forte = LoadTexture("./textures/fortedas5.png");
    

    SetTargetFPS(90);

    Tropa Reginaldo, Reginaldo2, Reginaldo3, Reginaldo4, Reginaldo5, Reginaldo6;
    Tropa Caboclo, Caboclo2,Caboclo3, Lampiao, Lampiao2, Lampiao3;
    Tropa LaUrsa, LaUrsa2, LaUrsa3, Frevista, Frevista2, Frevista3;
    Tropa Gonzaga1, Gonzaga2, Gonzaga3;
    InitTropas(&Reginaldo, "./textures/Torre-Reginaldo.png" , "./textures/Reginaldo-ataque.png" , "Reginaldo" , 20, 290, 25, 300, 1, 1);
    InitTropas(&Reginaldo2, "./textures/Torre-Reginaldo.png" , "./textures/Reginaldo-ataque.png" , "Reginaldo" , 20, 390 , 25 , 400, 1, 1);
    InitTropas(&Reginaldo3, "./textures/Torre-Reginaldo.png" , "./textures/Reginaldo-ataque.png" , "Reginaldo" , 20, 520, 25 , 530, 1, 1);
    InitTropas(&Reginaldo4, "./textures/Torre-Reginaldo.png" , "./textures/Reginaldo-ataque.png" , "Reginaldo" , 20, 290, 25, 300, 1, 1);
    InitTropas(&Reginaldo5, "./textures/Torre-Reginaldo.png" , "./textures/Reginaldo-ataque.png" , "Reginaldo" , 20, 390 , 25 , 400, 1, 1);
    InitTropas(&Reginaldo6, "./textures/Torre-Reginaldo.png" , "./textures/Reginaldo-ataque.png" , "Reginaldo" , 20, 520, 25 , 530, 1, 1);

    InitTropas(&Caboclo, "./textures/Caboclo2.png" , "./textures/Caboclo-ataque.png" , "CabocloLa" , 20, 290, 25, 300, 2, 1);
    InitTropas(&Caboclo2, "./textures/Caboclo2.png" , "./textures/Caboclo-ataque.png" , "CabocloLa" , 20, 290, 25, 300, 2, 1);
    InitTropas(&Caboclo3, "./textures/Caboclo2.png" , "./textures/Caboclo-ataque.png" , "CabocloLa" , 20, 290, 25, 300, 2, 1);

    InitTropas(&Lampiao, "./textures/lampiao2.png" , "./textures/lampiao-ataque.png" , "Lampiao12" , 20, 290, 25, 300, 2, 1);
    InitTropas(&Lampiao2, "./textures/lampiao2.png" , "./textures/lampiao-ataque.png" , "Lampiao12" , 20, 290, 25, 300, 2, 1);
    InitTropas(&Lampiao3, "./textures/lampiao2.png" , "./textures/lampiao-ataque.png" , "Lampiao12" , 20, 290, 25, 300, 2, 1);

    InitTropas(&LaUrsa, "./textures/laUrsa3.png" , "./textures/laUrsa-ataque.png" , "Alaursa34" , 20, 290, 25, 300, 2, 1);
    InitTropas(&LaUrsa2, "./textures/laUrsa3.png" , "./textures/laUrsa-ataque.png" , "Alaursa34" , 20, 290, 25, 300, 2, 1);
    InitTropas(&LaUrsa3, "./textures/laUrsa3.png" , "./textures/laUrsa-ataque.png", "Alaursa34" , 20, 290, 25, 300, 2, 1);

    InitTropas(&Frevista, "./textures/frevista2.png", "./textures/sombrinha.png" , "Frevista5" , 20, 290, 25, 300, 2, 1);
    InitTropas(&Frevista2, "./textures/frevista2.png" , "./textures/sombrinha.png" , "Frevista5" , 20, 290, 25, 300, 2, 1);
    InitTropas(&Frevista3, "./textures/frevista2.png" , "./textures/sombrinha.png" , "Frevista5" , 20, 290, 25, 300, 2, 1);
    Frevista.tempoAtaque=5;
    Frevista2.tempoAtaque=5;
    Frevista3.tempoAtaque=5;

    InitTropas(&Gonzaga1, "./textures/ganzaga.png", "./textures/ganzaga.png" , "L.Gonzaga" , 20, 290, 25, 300, 2, 1);
    InitTropas(&Gonzaga2, "./textures/ganzaga.png" , "./textures/ganzaga.png" , "L.Gonzaga" , 20, 290, 25, 300, 2, 1);
    InitTropas(&Gonzaga3, "./textures/ganzaga.png" , "./textures/ganzaga.png" , "L.Gonzaga" , 20, 290, 25, 300, 2, 1);

    inserirTropaArvore(&arvore, &Reginaldo);
    inserirTropaArvore(&arvore, &Caboclo);
    inserirTropaArvore(&arvore, &Lampiao);
    inserirTropaArvore(&arvore, &LaUrsa);
    inserirTropaArvore(&arvore, &Frevista);

    Inimigo inimigos3[10];
    Inimigo inimigos2[10];
    Inimigo inimigos1[10];
    int numInimigos3 = 0;
    int numInimigos2 = 0;
    int numInimigos1 = 0;
    
    
    InitInimigo(&inimigos1[numInimigos1++], "./textures/aguaViva.png", 800, 750, 7, 1400, 250 , 1.5, true, 1);
    InitInimigo(&inimigos1[numInimigos1++], "./textures/aguaViva.png", 900, 750, 7, 1500, 250 , 1.5, true, 1);
    
    InitInimigo(&inimigos2[numInimigos2++], "./textures/Ourico.png", 2500, 750, 2, 1400, 380 , 0.5, true, 2);
    InitInimigo(&inimigos2[numInimigos2++], "./textures/Ourico.png", 2500, 750, 2, 1500, 380 , 0.5, true, 2);
    InitInimigo(&inimigos2[numInimigos2++], "./textures/peixeleao.png", 500, 750, 2, 1550, 380 , 0.5, true, 2);

    InitInimigo(&inimigos3[numInimigos3++], "./textures/peixeleao.png", 800, 800, 4, 1400, 510 , 0.5, true, 3);
    InitInimigo(&inimigos3[numInimigos3++], "./textures/peixeleao.png", 1500, 900, 2, 1500, 510 , 2.5, true, 3);
    InitInimigo(&inimigos3[numInimigos3++], "./textures/peixeleao.png", 500, 1000, 2, 1550, 510 , 1.5, true, 3);
    InitInimigo(&inimigos3[numInimigos3++], "./textures/peixeleao.png", 500, 1500, 2, 1650, 510 , 1.5, true, 3);

    Inimigo inimigos6[10];
    Inimigo inimigos5[10];
    Inimigo inimigos4[10];
    int numInimigos6 = 0;
    int numInimigos5 = 0;
    int numInimigos4 = 0;

    InitInimigo(&inimigos4[numInimigos4++], "./textures/piranha.png", 800, 750, 7, 1400, 250 , 1.5, true, 1);
    InitInimigo(&inimigos4[numInimigos4++], "./textures/piranha.png", 900, 750, 7, 1500, 250 , 1.5, true, 1);
    
    InitInimigo(&inimigos5[numInimigos5++], "./textures/jacare.png", 2500, 750, 2, 1400, 380 , 0.5, true, 2);
    InitInimigo(&inimigos5[numInimigos5++], "./textures/jacare.png", 500, 750, 2, 1550, 380 , 0.5, true, 2);

    InitInimigo(&inimigos6[numInimigos6++], "./textures/caranguejo.png", 800, 800, 4, 1400, 510 , 0.5, true, 3);
    InitInimigo(&inimigos6[numInimigos6++], "./textures/caranguejo.png", 500, 1500, 2, 1650, 510 , 1.5, true, 3);

    Inimigo inimigos9[10];
    Inimigo inimigos8[10];
    Inimigo inimigos7[10];
    int numInimigos9 = 0;
    int numInimigos8 = 0;
    int numInimigos7 = 0;

    InitInimigo(&inimigos7[numInimigos7++], "./textures/aguaViva.png", 800, 750, 7, 1400, 250 , 1.5, true, 1);
    InitInimigo(&inimigos7[numInimigos7++], "./textures/aguaViva.png", 900, 750, 7, 1500, 250 , 1.5, true, 1);
    
    InitInimigo(&inimigos8[numInimigos8++], "./textures/Ourico.png", 2500, 750, 2, 1400, 380 , 0.5, true, 2);
    InitInimigo(&inimigos8[numInimigos8++], "./textures/peixeleao.png", 500, 750, 2, 1550, 380 , 0.5, true, 2);

    InitInimigo(&inimigos9[numInimigos9++], "./textures/peixeleao.png", 800, 800, 4, 1400, 510 , 0.5, true, 3);
    InitInimigo(&inimigos9[numInimigos9++], "./textures/peixeleao.png", 500, 1500, 2, 1650, 510 , 1.5, true, 3);



    Boss bossTubarao, bossBoto, bossBoitata;
    const char* fotosTubarao[8] = {
    "./textures/Tubarao1.png", "./textures/Tubarao2.png",
    "./textures/Tubarao4.png", "./textures/Tubarao8.png", "./textures/Tubarao10.png", 
    "./textures/Tubarao11.png", "./textures/Tubarao12.png", "./textures/Tubarao3.png"}; 

    const char* fotosBoto[8] = {
    "./textures/Boto1.png", "./textures/Boto1.png",
    "./textures/Boto2.png", "./textures/Boto2.png", "./textures/Boto3.png", 
    "./textures/Boto3.png", "./textures/Boto4.png", "./textures/Boto4.png"}; 
    
    InitBoss(&bossTubarao, fotosTubarao, 30000, 30, 1550, screenHeight-300, 2.6, true);
    
    InitBoss(&bossBoto, fotosBoto, 40000, 15, 1550, screenHeight-300, 1.6, true);

    InitBoss(&bossBoitata, fotosTubarao, 40000, 20, 1550, screenHeight-300, 2.6, true);

    InitAudioDevice();
    Music soundpraia = LoadMusicStream("./audio/GarotaIpanema.mp3");
    Music soundBoss = LoadMusicStream("./audio/Jaws.mp3");
    double vidaPraia = 10000;

    GameScreen currentScreen = JOGO2;
    Texture selecao;
    Rectangle pause = { 1250, 8, 40, 40 };

    bool ReginaldoDisponivel;
    bool CabocloDisponivel;
    bool LampiaoDisponivel;
    bool LaUrsaDisponivel;
    bool FrevistaDisponivel;
    bool GonzagaDisponivel;

    Texture iconeReginaldoPB, iconeCaboclo, iconeCabocloPB, iconeLampiao, iconeLampiaoPB, 
    iconeLaursa, iconeLaursaPB, iconeFrevista, iconeFrevistaPB;

    iconeReginaldoPB = LoadTexture("./textures/iconeReginaldoPB.png");

    iconeCaboclo = LoadTexture("./textures/iconeCaboclo.png");
    iconeCabocloPB = LoadTexture("./textures/iconeCabocloPB.png");

    iconeLampiao = LoadTexture("./textures/iconeLampiao.png");
    iconeLampiaoPB = LoadTexture("./textures/iconeLampiaoPB.png");

    iconeLaursa = LoadTexture("./textures/iconeLaursa.png");
    iconeLaursaPB = LoadTexture("./textures/iconeLaursaPB.png");

    iconeFrevista = LoadTexture("./textures/iconeFrevista.png");
    iconeFrevistaPB = LoadTexture("./textures/iconeFrevistaPB.png");

    char nomeJogador[20] = "";

    while (!WindowShouldClose() && currentScreen != FIM) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Vector2 mousePosition = GetMousePosition();

        switch (currentScreen)
        {
        case MENU:
            Menu(&currentScreen);
            break;

        case CAPTURA_NOME:
            CapturarNome(&currentScreen, nomeJogador);
            break;

        case NIVEL:
             casa1=true;
             casa2=true;
             casa3=true;
             casa4=true;
             casa5=true;
             casa6=true;
             Rectangle botaoVoltar = { 32, 30, 70, 35 }; 
             Rectangle botaoComecar = { 560, 460, 170, 70 };
            if (fase == 1){
                selecao = LoadTexture("./textures/selecao.png");
                DrawTexture(selecao, 0, 0, WHITE); 
                DrawRectangleRec( botaoComecar , (Color){ 255, 255, 255, 0 });
                DrawRectangleRec( botaoVoltar , (Color){ 255, 255, 255, 0 });
               
                if (CheckCollisionPointRec(mousePosition, botaoComecar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        currentScreen = JOGO;
                        break;
                }
                if (CheckCollisionPointRec(mousePosition, botaoVoltar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        currentScreen = MENU;
                        break;
                }

            }
            else if (fase == 2){
                selecao = LoadTexture("./textures/selecao.png");
                vidaPraia = 10000;
                nivelXp=2;
                head = NULL;
                DrawTexture(selecao, 0, 0, WHITE); 
                DrawRectangleRec( botaoComecar , (Color){ 255, 255, 255, 0 });
                DrawRectangleRec( botaoVoltar , (Color){ 255, 255, 255, 0 });
               
                if (CheckCollisionPointRec(mousePosition, botaoComecar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        currentScreen = JOGO2;
                        break;
                }
                if (CheckCollisionPointRec(mousePosition, botaoVoltar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        currentScreen = MENU;
                        break;
                }
            }
            else if (fase == 3){
                selecao = LoadTexture("./textures/selecao.png");
                vidaPraia = 10000;
                nivelXp=3;
                head = NULL;
                DrawTexture(selecao, 0, 0, WHITE); 
                DrawRectangleRec( botaoComecar , (Color){ 255, 255, 255, 0 });
                DrawRectangleRec( botaoVoltar , (Color){ 255, 255, 255, 0 });
               
                if (CheckCollisionPointRec(mousePosition, botaoComecar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        currentScreen = JOGO3;
                        break;
                }
                if (CheckCollisionPointRec(mousePosition, botaoVoltar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        currentScreen = MENU;
                        break;
                }
            }

            break;



        case JOGO:

            if (boss){
                UpdateMusicStream(soundBoss);  
            } 
            DrawTexture(praia, 0, 0, WHITE); 

            ReginaldoDisponivel = verificarDisponibilidadeTropa(arvore, "Reginaldo", fase, nivelXp);
            CabocloDisponivel = verificarDisponibilidadeTropa(arvore, "CabocloLa", fase, nivelXp);
            LampiaoDisponivel = verificarDisponibilidadeTropa(arvore, "Lampiao12", fase, nivelXp);
            LaUrsaDisponivel = verificarDisponibilidadeTropa(arvore, "Alaursa34", fase, nivelXp);
            FrevistaDisponivel = verificarDisponibilidadeTropa(arvore, "Frevista5", fase, nivelXp);

            if(!boss){
                UpdateMusicStream(soundpraia); 
                PlayMusicStream(soundpraia);
            }

            if (!ReginaldoDisponivel){
                //DrawRectangle(348, 14, 40, 40 , RED);
                DrawTexture(iconeReginaldoPB, 350, 15, WHITE);
            }
            else{
                DrawRectangleRec(botaoPosicionar, (Color){ 255, 255, 255, 0 }); 
            }

            if (CabocloDisponivel){
                DrawRectangleRec(botaoPosicionar2, (Color){ 255, 255, 255, 0 });
                DrawTexture(iconeCaboclo, 413, 7, WHITE); 
            }
            else{
                DrawTexture(iconeCabocloPB, 413, 7, WHITE);
            }

            if (LampiaoDisponivel){
                DrawRectangleRec(botaoPosicionar3, (Color){ 255, 255, 255, 0 });
                DrawTexture(iconeLampiao, 476, 16, WHITE); 
            }
            else{
                DrawTexture(iconeLampiaoPB, 476, 16, WHITE); 
            }

            if (LaUrsaDisponivel){
                DrawRectangleRec(botaoPosicionar4, (Color){ 255, 255, 255, 0 });
                DrawTexture(iconeLaursa, 540, 14, WHITE); 
            }
            else{
                DrawTexture(iconeLaursaPB, 540, 16, WHITE); 
            }

            if (FrevistaDisponivel){
                DrawRectangleRec(botaoPosicionar5, (Color){ 255, 255, 255, 0 });
                DrawTexture(iconeFrevista, 605, 14, WHITE); 
            }
            else{
                DrawRectangleRec(botaoPosicionar5, (Color){ 255, 255, 255, 0 });
                DrawTexture(iconeFrevistaPB, 605, 14, WHITE); 
            }
            
            DrawRectangleRec(botaoRemover, (Color){ 255, 255, 255, 0 }); 

            larguraxp = (double)experiencia / experienciaMax * largurabarraxp;

            
            if (experiencia >= experienciaMax) {
                    experiencia = experiencia % experienciaMax; 
                    nivelXp++; 
            }

            DrawRectangle(382, 69, (int)larguraxp, 5, BLUE);

            char nivelTexto[20];
            sprintf(nivelTexto, "Nível: %d", nivelXp);
            DrawText(nivelTexto, 500, 80, 20, BLACK); 
            
            // Calcula a porcentagem de vida
            float porcentagemVida = (vidaPraia / vidaPraiaMax) * 100;

            // Converte a porcentagem para string e exibe no botão de vida
            char textoVida[10];
            snprintf(textoVida, sizeof(textoVida), "%.0f%%", porcentagemVida);
            DrawText(textoVida, 220, 18 , 30 , RED);

            DrawRectangleRec(pause, (Color){ 255, 255, 255, 0 });

            if (CheckCollisionPointRec(mousePosition, pause) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossTubarao.vivo){
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                bool pausa = true;

                SalvarTelacongelada(head, tail, telaCongelada, praia, inimigos1, numInimigos1, 
                    inimigos2, numInimigos2, inimigos3, numInimigos3, &bossTubarao,  boss, botaoRemover, &vidaPraia);

                while (pausa && !WindowShouldClose()) {
                    BeginDrawing();
                    DrawTextureRec(telaCongelada.texture, (Rectangle){ 0, 0, (float)telaCongelada.texture.width, (float)-telaCongelada.texture.height }, (Vector2){ 0, 0 }, WHITE);
                    DrawText("JOGO PAUSADO", 550, 300, 30, BLACK);
                    EndDrawing(); 
                    Vector2 mousePosition = GetMousePosition();

                    if (CheckCollisionPointRec(mousePosition, pause) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        pausa = false;
                    }
                    
                }

            }

            //"Tela de derrota"
            if (vidaPraia <= 0) {
                Rectangle botaosair = { 270, 250, 100, 100 };
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                SalvarTelacongelada(head, tail, telaCongelada, praia, inimigos1, numInimigos1, 
                            inimigos2, numInimigos2, inimigos3, numInimigos3, &bossTubarao,  boss, botaoRemover, &vidaPraia);

                            
                while(1){
                    BeginDrawing();
                    Vector2 mousePosition = GetMousePosition();
                    DrawTextureRec(telaCongelada.texture, (Rectangle){ 0, 0, (float)telaCongelada.texture.width, (float)-telaCongelada.texture.height }, (Vector2){ 0, 0 }, WHITE);
                    DrawText("Você foi derrotado!", 230, 200, 40, RED);
                    DrawRectangleRec(botaosair, RED);
                    if (CheckCollisionPointRec(mousePosition, botaosair) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        currentScreen = FIM;
                        break;
                    }
                    EndDrawing();
                }
            }
            //Fim da tela de derrota
            

            //Inicio selecao personagem
            if (CheckCollisionPointRec(mousePosition, botaoPosicionar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossTubarao.vivo && ReginaldoDisponivel) { 
            
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = true;

                adicionarTropa(&head, &tail, &Reginaldo, &Reginaldo2, &Reginaldo3,
                            &Reginaldo4, &Reginaldo5, &Reginaldo6, telaCongelada, 
                            praia,  inimigos1, numInimigos1, inimigos2, numInimigos2, 
                            inimigos3, numInimigos3, &bossTubarao,  boss, botaoRemover, &vidaPraia);
            }
            else if(CheckCollisionPointRec(mousePosition, botaoPosicionar2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossTubarao.vivo && CabocloDisponivel){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = true;

                 adicionarTropa(&head, &tail, &Caboclo, &Caboclo2, &Caboclo3,
                            &Reginaldo4, &Reginaldo5, &Reginaldo6, telaCongelada, 
                            praia,  inimigos1, numInimigos1, inimigos2, numInimigos2, 
                            inimigos3, numInimigos3, &bossTubarao,  boss, botaoRemover, &vidaPraia);
            }
            else if(CheckCollisionPointRec(mousePosition, botaoPosicionar3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossTubarao.vivo && LampiaoDisponivel){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = true;

                 adicionarTropa(&head, &tail, &Lampiao, &Lampiao2, &Lampiao3,
                            &Reginaldo4, &Reginaldo5, &Reginaldo6, telaCongelada, 
                            praia,  inimigos1, numInimigos1, inimigos2, numInimigos2, 
                            inimigos3, numInimigos3, &bossTubarao,  boss, botaoRemover, &vidaPraia);
            }
            else if(CheckCollisionPointRec(mousePosition, botaoPosicionar4) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossTubarao.vivo  && FrevistaDisponivel){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = false;

                 adicionarTropa(&head, &tail, &LaUrsa, &LaUrsa2, &LaUrsa3,
                            &LaUrsa, &LaUrsa2, &LaUrsa3, telaCongelada, 
                            praia,  inimigos1, numInimigos1, inimigos2, numInimigos2, 
                            inimigos3, numInimigos3, &bossTubarao,  boss, botaoRemover, &vidaPraia);

            }
            else if(CheckCollisionPointRec(mousePosition, botaoPosicionar5) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossTubarao.vivo){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = false;

                 adicionarTropa(&head, &tail, &Frevista, &Frevista2, &Frevista3,
                            &Frevista, &Frevista2, &Frevista3, telaCongelada, 
                            praia,  inimigos1, numInimigos1, inimigos2, numInimigos2, 
                            inimigos3, numInimigos3, &bossTubarao,  boss, botaoRemover, &vidaPraia);

            }
            else if(CheckCollisionPointRec(mousePosition, botaoPosicionar6) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossTubarao.vivo){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = false;

                 adicionarTropa(&head, &tail, &Gonzaga1, &Gonzaga2, &Gonzaga3,
                            &Gonzaga1, &Gonzaga2, &Gonzaga3, telaCongelada, 
                            praia,  inimigos1, numInimigos1, inimigos2, numInimigos2, 
                            inimigos3, numInimigos3, &bossTubarao,  boss, botaoRemover, &vidaPraia);

            }
            else if(CheckCollisionPointRec(mousePosition, botaoRemover) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossTubarao.vivo){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

                removerTropaBotao(&head, &tail, telaCongelada, praia,
                        inimigos1, numInimigos1,
                        inimigos2, numInimigos2, inimigos3, numInimigos3, 
                        &bossTubarao,  boss, botaoRemover, &vidaPraia);

                
            }
            //Fim selecao de personagem 
    

            for (int i = 0; i < numInimigos1; i++) {
                DrawInimigo(&inimigos1[i],  &vidaPraia);
            }
            
            for (int i = 0; i < numInimigos2; i++) {
                DrawInimigo(&inimigos2[i],  &vidaPraia);
            }

            for (int i = 0; i < numInimigos3; i++) {
                DrawInimigo(&inimigos3[i],  &vidaPraia);
            }


            if (numInimigos1+numInimigos2+numInimigos3<=0){
                boss = true;
                DrawBoss(&bossTubarao,  &vidaPraia);
                PlayMusicStream(soundBoss);

                if (bossTubarao.vivo == false){
                    Rectangle botaoWin = { 650, 400, 100, 100 };
                    fase=2;
                    boss = false;
                    Vector2 mousePosition = GetMousePosition();
                    DrawRectangle(620, 290, 200, 50, BROWN);
                    DrawRectangleRec(botaoWin, BROWN);
                    DrawText("YOU WIN!", 650, 300, 20, BLACK);
                    DrawText("Continuar!", 650, 400, 20, BLACK);
                    if (CheckCollisionPointRec(mousePosition, botaoWin) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        currentScreen = NIVEL;
                        break;
                    } 
                }
            }

            imprimirTropaCompleta(head, tail, inimigos1, inimigos2, inimigos3, &numInimigos1, &numInimigos2, &numInimigos3, &bossTubarao, boss);

            break;

            //-------------------------------------- FASE 2 AQUI -----------------------------------------------------------------
            case JOGO2:

            if (boss){
                UpdateMusicStream(soundBoss);  
            } 
            DrawTexture(ponte, 0, 0, WHITE); 

            ReginaldoDisponivel = verificarDisponibilidadeTropa(arvore, "Reginaldo", fase, nivelXp);
            CabocloDisponivel = verificarDisponibilidadeTropa(arvore, "CabocloLa", fase, nivelXp);
            LampiaoDisponivel = verificarDisponibilidadeTropa(arvore, "Lampiao12", fase, nivelXp);
            LaUrsaDisponivel = verificarDisponibilidadeTropa(arvore, "Alaursa34", fase, nivelXp);
            FrevistaDisponivel = verificarDisponibilidadeTropa(arvore, "Frevista5", fase, nivelXp);

            if(!boss){
                UpdateMusicStream(soundpraia); 
                PlayMusicStream(soundpraia);
            }

            if (!ReginaldoDisponivel){
                //DrawRectangle(348, 14, 40, 40 , RED);
                DrawTexture(iconeReginaldoPB, 350, 15, WHITE);
            }
            else{
                DrawRectangleRec(botaoPosicionar, (Color){ 255, 255, 255, 0 }); 
            }

            if (CabocloDisponivel){
                DrawRectangleRec(botaoPosicionar2, (Color){ 255, 255, 255, 0 });
                DrawTexture(iconeCaboclo, 413, 7, WHITE); 
            }
            else{
                DrawTexture(iconeCabocloPB, 413, 7, WHITE);
            }

            if (LampiaoDisponivel){
                DrawRectangleRec(botaoPosicionar3, (Color){ 255, 255, 255, 0 });
                DrawTexture(iconeLampiao, 476, 16, WHITE); 
            }
            else{
                DrawTexture(iconeLampiaoPB, 476, 16, WHITE); 
            }

            if (LaUrsaDisponivel){
                DrawRectangleRec(botaoPosicionar4, (Color){ 255, 255, 255, 0 });
                DrawTexture(iconeLaursa, 540, 14, WHITE); 
            }
            else{
                DrawTexture(iconeLaursaPB, 540, 16, WHITE); 
            }

            if (FrevistaDisponivel){
                DrawRectangleRec(botaoPosicionar5, (Color){ 255, 255, 255, 0 });
                DrawTexture(iconeFrevista, 605, 14, WHITE); 
            }
            else{
                DrawRectangleRec(botaoPosicionar5, (Color){ 255, 255, 255, 0 });
                DrawTexture(iconeFrevistaPB, 605, 14, WHITE); 
            }
            
            DrawRectangleRec(botaoPosicionar6, PURPLE);

            DrawRectangleRec(botaoRemover, (Color){ 255, 255, 255, 0 }); 

            larguraxp = (double)experiencia / experienciaMax * largurabarraxp;

            
            if (experiencia >= experienciaMax) {
                    experiencia = experiencia % experienciaMax; 
                    nivelXp++; 
            }

            DrawRectangle(386, 73, (int)larguraxp, 5, BLUE);

            sprintf(nivelTexto, "Nível: %d", nivelXp);
            DrawText(nivelTexto, 500, 80, 20, BLACK); 
            
            porcentagemVida = (vidaPraia / vidaPraiaMax) * 100;

            snprintf(textoVida, sizeof(textoVida), "%.0f%%", porcentagemVida);
            DrawText(textoVida, 220, 18 , 30 , RED);

            DrawRectangleRec(pause, (Color){ 255, 255, 255, 0 });

            if (CheckCollisionPointRec(mousePosition, pause) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossTubarao.vivo){
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                bool pausa = true;

                SalvarTelacongelada(head, tail, telaCongelada, ponte, inimigos4, numInimigos4, 
                    inimigos5, numInimigos5, inimigos6, numInimigos6, &bossBoto,  boss, botaoRemover, &vidaPraia);

                while (pausa && !WindowShouldClose()) {
                    BeginDrawing();
                    DrawTextureRec(telaCongelada.texture, (Rectangle){ 0, 0, (float)telaCongelada.texture.width, (float)-telaCongelada.texture.height }, (Vector2){ 0, 0 }, WHITE);
                    DrawText("JOGO PAUSADO", 550, 300, 30, BLACK);
                    EndDrawing(); 
                    Vector2 mousePosition = GetMousePosition();

                    if (CheckCollisionPointRec(mousePosition, pause) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        pausa = false;
                    }
                    
                }

            }

            //"Tela de derrota"
            if (vidaPraia <= 0) {
                Rectangle botaosair = { 270, 250, 100, 100 };
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                SalvarTelacongelada(head, tail, telaCongelada, ponte, inimigos4, numInimigos4, 
                            inimigos5, numInimigos5, inimigos6, numInimigos6, &bossBoto,  boss, botaoRemover, &vidaPraia);

                            
                while(1){
                    BeginDrawing();
                    Vector2 mousePosition = GetMousePosition();
                    DrawTextureRec(telaCongelada.texture, (Rectangle){ 0, 0, (float)telaCongelada.texture.width, (float)-telaCongelada.texture.height }, (Vector2){ 0, 0 }, WHITE);
                    DrawText("Você foi derrotado!", 230, 200, 40, RED);
                    DrawRectangleRec(botaosair, RED);
                    if (CheckCollisionPointRec(mousePosition, botaosair) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        currentScreen = FIM;
                        break;
                    }
                    EndDrawing();
                }
            }
            //Fim da tela de derrota
            

            //Inicio selecao personagem
            if (CheckCollisionPointRec(mousePosition, botaoPosicionar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossBoto.vivo && ReginaldoDisponivel) { 
            
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = true;

                adicionarTropa(&head, &tail, &Reginaldo, &Reginaldo2, &Reginaldo3,
                            &Reginaldo4, &Reginaldo5, &Reginaldo6, telaCongelada, 
                            ponte,  inimigos4, numInimigos4, inimigos5, numInimigos5, 
                            inimigos6, numInimigos6, &bossBoto,  boss, botaoRemover, &vidaPraia);
            }
            else if(CheckCollisionPointRec(mousePosition, botaoPosicionar2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossBoto.vivo && CabocloDisponivel){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = true;

                 adicionarTropa(&head, &tail, &Caboclo, &Caboclo2, &Caboclo3,
                            &Reginaldo4, &Reginaldo5, &Reginaldo6, telaCongelada, 
                            ponte,  inimigos4, numInimigos4, inimigos5, numInimigos5, 
                            inimigos6, numInimigos6, &bossBoto,  boss, botaoRemover, &vidaPraia);
            }
            else if(CheckCollisionPointRec(mousePosition, botaoPosicionar3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossBoto.vivo && LampiaoDisponivel){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = true;

                 adicionarTropa(&head, &tail, &Lampiao, &Lampiao2, &Lampiao3,
                            &Reginaldo4, &Reginaldo5, &Reginaldo6, telaCongelada, 
                            ponte,  inimigos4, numInimigos4, inimigos5, numInimigos5, 
                            inimigos6, numInimigos6, &bossBoto,  boss, botaoRemover, &vidaPraia);
            }
            else if(CheckCollisionPointRec(mousePosition, botaoPosicionar4) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossBoto.vivo  && LaUrsaDisponivel){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = false;

                 adicionarTropa(&head, &tail, &LaUrsa, &LaUrsa2, &LaUrsa3,
                            &LaUrsa, &LaUrsa2, &LaUrsa3, telaCongelada, 
                            ponte,  inimigos4, numInimigos4, inimigos5, numInimigos5, 
                            inimigos6, numInimigos6, &bossBoto,  boss, botaoRemover, &vidaPraia);

            }
            else if(CheckCollisionPointRec(mousePosition, botaoPosicionar5) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossBoto.vivo){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = false;

                 adicionarTropa(&head, &tail, &Frevista, &Frevista2, &Frevista3,
                            &Frevista, &Frevista2, &Frevista3, telaCongelada, 
                            ponte,  inimigos4, numInimigos4, inimigos5, numInimigos5, 
                            inimigos6, numInimigos6, &bossBoto,  boss, botaoRemover, &vidaPraia);

            }
            else if(CheckCollisionPointRec(mousePosition, botaoPosicionar6) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossBoto.vivo){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = false;

                 adicionarTropa(&head, &tail, &Gonzaga1, &Gonzaga2, &Gonzaga3,
                            &Gonzaga1, &Gonzaga2, &Gonzaga3, telaCongelada, 
                            ponte,  inimigos4, numInimigos4, inimigos5, numInimigos5, 
                            inimigos6, numInimigos6, &bossBoto,  boss, botaoRemover, &vidaPraia);

            }
            else if(CheckCollisionPointRec(mousePosition, botaoRemover) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossBoto.vivo){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

                removerTropaBotao(&head, &tail, telaCongelada, ponte,
                        inimigos4, numInimigos4,
                        inimigos5, numInimigos5, inimigos6, numInimigos6, 
                        &bossBoto,  boss, botaoRemover, &vidaPraia);

                
            }
            //Fim selecao de personagem 
    

            for (int i = 0; i < numInimigos4; i++) {
                DrawInimigo(&inimigos4[i], &vidaPraia);
            }
            
            for (int i = 0; i < numInimigos5; i++) {
                DrawInimigo(&inimigos5[i], &vidaPraia);
            }

            for (int i = 0; i < numInimigos6; i++) {
                DrawInimigo(&inimigos6[i], &vidaPraia);
            }


            if (numInimigos4+numInimigos5+numInimigos6<=0){
                boss = true;
                DrawBossBoto(&bossBoto,  &vidaPraia);
                PlayMusicStream(soundBoss);

                if (bossBoto.vivo == false){
                    Rectangle botaoWin = { 650, 400, 100, 100 };
                    fase=3;
                    boss = false;
                    Vector2 mousePosition = GetMousePosition();
                    DrawRectangle(620, 290, 200, 50, BROWN);
                    DrawRectangleRec(botaoWin, BROWN);
                    DrawText("YOU WIN!", 650, 300, 20, BLACK);
                    DrawText("Continuar!", 650, 400, 20, BLACK);
                    if (CheckCollisionPointRec(mousePosition, botaoWin) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        currentScreen = NIVEL;
                        break;
                    } 
                }
            }

            imprimirTropaCompleta(head, tail, inimigos4, inimigos5, inimigos6, &numInimigos4, &numInimigos5, &numInimigos6, &bossBoto, boss);

            break;

            //-------------------------------------- FASE 3 AQUI -----------------------------------------------------------------
            case JOGO3:


            if (boss){
                UpdateMusicStream(soundBoss);  
            } 
            DrawTexture(forte, 0, 0, WHITE); 

            ReginaldoDisponivel = verificarDisponibilidadeTropa(arvore, "Reginaldo", fase, nivelXp);
            CabocloDisponivel = verificarDisponibilidadeTropa(arvore, "CabocloLa", fase, nivelXp);
            LampiaoDisponivel = verificarDisponibilidadeTropa(arvore, "Lampiao12", fase, nivelXp);
            LaUrsaDisponivel = verificarDisponibilidadeTropa(arvore, "Alaursa34", fase, nivelXp);
            FrevistaDisponivel = verificarDisponibilidadeTropa(arvore, "Frevista5", fase, nivelXp);
            GonzagaDisponivel = verificarDisponibilidadeTropa(arvore, "Frevista5", fase, nivelXp);

            if(!boss){
                UpdateMusicStream(soundpraia); 
                PlayMusicStream(soundpraia);
            }

            if (!ReginaldoDisponivel){
                DrawRectangle(348, 14, 40, 40 , RED);
            }
            else{
                DrawRectangleRec(botaoPosicionar, (Color){ 255, 255, 255, 0 }); 
            }
            if (CabocloDisponivel){
                DrawRectangleRec(botaoPosicionar2, GREEN); 
            }
            else{
                DrawRectangleRec(botaoPosicionar2, RED);
            }
            DrawRectangleRec(botaoPosicionar3, BLUE);
            DrawRectangleRec(botaoPosicionar4, ORANGE);
            DrawRectangleRec(botaoPosicionar5, YELLOW);
            DrawRectangleRec(botaoPosicionar6, PURPLE);
            DrawRectangleRec(botaoRemover, (Color){ 255, 255, 255, 0 }); 

            larguraxp = (double)experiencia / experienciaMax * largurabarraxp;

            
            if (experiencia >= experienciaMax) {
                    experiencia = experiencia % experienciaMax; 
                    nivelXp++; 
            }

            DrawRectangle(382, 69, (int)larguraxp, 5, BLUE);

            sprintf(nivelTexto, "Nível: %d", nivelXp);
            DrawText(nivelTexto, 500, 80, 20, BLACK); 
            
            porcentagemVida = (vidaPraia / vidaPraiaMax) * 100;

            snprintf(textoVida, sizeof(textoVida), "%.0f%%", porcentagemVida);
            DrawText(textoVida, 220, 18 , 30 , RED);

            DrawRectangleRec(pause, (Color){ 255, 255, 255, 0 });

            if (CheckCollisionPointRec(mousePosition, pause) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossBoitata.vivo){
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                bool pausa = true;

                SalvarTelacongelada(head, tail, telaCongelada, forte, inimigos7, numInimigos7, 
                    inimigos8, numInimigos8, inimigos9, numInimigos9, &bossBoitata,  boss, botaoRemover, &vidaPraia);

                while (pausa && !WindowShouldClose()) {
                    BeginDrawing();
                    DrawTextureRec(telaCongelada.texture, (Rectangle){ 0, 0, (float)telaCongelada.texture.width, (float)-telaCongelada.texture.height }, (Vector2){ 0, 0 }, WHITE);
                    DrawText("JOGO PAUSADO", 550, 300, 30, BLACK);
                    EndDrawing(); 
                    Vector2 mousePosition = GetMousePosition();

                    if (CheckCollisionPointRec(mousePosition, pause) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        pausa = false;
                    }
                    
                }

            }

            //"Tela de derrota"
            if (vidaPraia <= 0) {
                Rectangle botaosair = { 270, 250, 100, 100 };
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                SalvarTelacongelada(head, tail, telaCongelada, forte, inimigos7, numInimigos7, 
                            inimigos8, numInimigos8, inimigos9, numInimigos9, &bossBoitata,  boss, botaoRemover, &vidaPraia);

                            
                while(1){
                    BeginDrawing();
                    Vector2 mousePosition = GetMousePosition();
                    DrawTextureRec(telaCongelada.texture, (Rectangle){ 0, 0, (float)telaCongelada.texture.width, (float)-telaCongelada.texture.height }, (Vector2){ 0, 0 }, WHITE);
                    DrawText("Você foi derrotado!", 230, 200, 40, RED);
                    DrawRectangleRec(botaosair, RED);
                    if (CheckCollisionPointRec(mousePosition, botaosair) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        currentScreen = FIM;
                        break;
                    }
                    EndDrawing();
                }
            }
            //Fim da tela de derrota
            

            //Inicio selecao personagem
            if (CheckCollisionPointRec(mousePosition, botaoPosicionar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossBoitata.vivo && ReginaldoDisponivel) { 
            
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = true;

                adicionarTropa(&head, &tail, &Reginaldo, &Reginaldo2, &Reginaldo3,
                            &Reginaldo4, &Reginaldo5, &Reginaldo6, telaCongelada, 
                            forte,  inimigos7, numInimigos7, inimigos8, numInimigos8, 
                            inimigos9, numInimigos9, &bossBoitata,  boss, botaoRemover, &vidaPraia);
            }
            else if(CheckCollisionPointRec(mousePosition, botaoPosicionar2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossBoitata.vivo && CabocloDisponivel){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = true;

                 adicionarTropa(&head, &tail, &Caboclo, &Caboclo2, &Caboclo3,
                            &Reginaldo4, &Reginaldo5, &Reginaldo6, telaCongelada, 
                            forte,  inimigos7, numInimigos7, inimigos8, numInimigos8, 
                            inimigos9, numInimigos9, &bossBoitata,  boss, botaoRemover, &vidaPraia);
            }
            else if(CheckCollisionPointRec(mousePosition, botaoPosicionar3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossBoitata.vivo && LampiaoDisponivel){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = true;

                 adicionarTropa(&head, &tail, &Lampiao, &Lampiao2, &Lampiao3,
                            &Reginaldo4, &Reginaldo5, &Reginaldo6, telaCongelada, 
                            forte,  inimigos7, numInimigos7, inimigos8, numInimigos8, 
                            inimigos9, numInimigos9, &bossBoitata,  boss, botaoRemover, &vidaPraia);
            }
            else if(CheckCollisionPointRec(mousePosition, botaoPosicionar4) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossBoitata.vivo  && LaUrsaDisponivel){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = false;

                 adicionarTropa(&head, &tail, &LaUrsa, &LaUrsa2, &LaUrsa3,
                            &LaUrsa, &LaUrsa2, &LaUrsa3, telaCongelada, 
                            forte,  inimigos7, numInimigos7, inimigos8, numInimigos8, 
                            inimigos9, numInimigos9, &bossBoitata,  boss, botaoRemover, &vidaPraia);

            }
            else if(CheckCollisionPointRec(mousePosition, botaoPosicionar5) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossBoitata.vivo && FrevistaDisponivel){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = false;

                 adicionarTropa(&head, &tail, &Frevista, &Frevista2, &Frevista3,
                            &Frevista, &Frevista2, &Frevista3, telaCongelada, 
                            forte,  inimigos7, numInimigos7, inimigos2, numInimigos2, 
                            inimigos3, numInimigos3, &bossBoitata,  boss, botaoRemover, &vidaPraia);

            }
            else if(CheckCollisionPointRec(mousePosition, botaoPosicionar6) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossBoitata.vivo && GonzagaDisponivel){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
                range = false;

                 adicionarTropa(&head, &tail, &Gonzaga1, &Gonzaga2, &Gonzaga3,
                            &Gonzaga1, &Gonzaga2, &Gonzaga3, telaCongelada, 
                            forte,  inimigos7, numInimigos7, inimigos8, numInimigos8, 
                            inimigos9, numInimigos9, &bossBoitata,  boss, botaoRemover, &vidaPraia);

            }
            else if(CheckCollisionPointRec(mousePosition, botaoRemover) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && bossBoitata.vivo){
                
                RenderTexture2D telaCongelada = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

                removerTropaBotao(&head, &tail, telaCongelada, forte,
                        inimigos7, numInimigos7,
                        inimigos8, numInimigos8, inimigos9, numInimigos9, 
                        &bossBoto,  boss, botaoRemover, &vidaPraia);

                
            }
            //Fim selecao de personagem 
    

            for (int i = 0; i < numInimigos7; i++) {
                DrawInimigo(&inimigos7[i], &vidaPraia);
            }
            
            for (int i = 0; i < numInimigos8; i++) {
                DrawInimigo(&inimigos8[i], &vidaPraia);
            }

            for (int i = 0; i < numInimigos9; i++) {
                DrawInimigo(&inimigos9[i], &vidaPraia);
            }


            if (numInimigos7+numInimigos8+numInimigos9<=0){
                boss = true;
                DrawBoss(&bossBoitata,  &vidaPraia);
                PlayMusicStream(soundBoss);

                if (bossBoitata.vivo == false){
                    Rectangle botaoWin = { 650, 400, 100, 100 };
                    fase=3;
                    boss = false;
                    Vector2 mousePosition = GetMousePosition();
                    DrawRectangle(620, 290, 200, 50, BROWN);
                    DrawRectangleRec(botaoWin, BROWN);
                    DrawText("YOU WIN!", 650, 300, 20, BLACK);
                    DrawText("Continuar!", 650, 400, 20, BLACK);
                    if (CheckCollisionPointRec(mousePosition, botaoWin) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        currentScreen = NIVEL;
                        break;
                    } 
                }
            }

            imprimirTropaCompleta(head, tail, inimigos7, inimigos8, inimigos9, &numInimigos7, &numInimigos8, &numInimigos9, &bossBoitata, boss);

                break;

            case RANKING:
                Texture ranking;
                ranking = LoadTexture("./textures/telaRanking.png");
                DrawTexture(ranking, 0,0, WHITE);
                Rectangle btnVolar = {50, 29, 90, 50};
                DrawRectangleRec(btnVolar, (Color){ 255, 255, 255, 0 });
                Vector2 mousePosition = GetMousePosition();

                usuario *temp = NULL;
                lerDados(&temp);
                
                int posX = 530;     
                int posY = 160;     
                int spacing = 30;

                for (int i = 0; i < 10 && temp != NULL; i++) {

                    DrawText(TextFormat("%d. %s | score: %d", i + 1, temp->nome, temp->score), posX, posY + i * spacing, 20, BLACK);
                    temp = temp->prox;


                }
                

                if (CheckCollisionPointRec(mousePosition, btnVolar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        currentScreen = MENU;
                        break;
                }

                break;

            case FIM:
            break;
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
    for (int i = 0; i < numInimigos4; i++) {
        UnloadTexture(inimigos4[i].foto); 
    }

    for (int i = 0; i < numInimigos5; i++) {
        UnloadTexture(inimigos5[i].foto); 
    }

    for (int i = 0; i < numInimigos6; i++) {
        UnloadTexture(inimigos6[i].foto); 
    }
    for (int i = 0; i < numInimigos7; i++) {
        UnloadTexture(inimigos7[i].foto); 
    }

    for (int i = 0; i < numInimigos8; i++) {
        UnloadTexture(inimigos8[i].foto); 
    }

    for (int i = 0; i < numInimigos9; i++) {
        UnloadTexture(inimigos9[i].foto); 
    }

    UnloadMusicStream(soundBoss);
    CloseWindow();
    CloseAudioDevice();
    

    salvarDados(nomeJogador, fase, scoreTotal);
    lerDados(&head2);
    organizar(&head2);

    return 0;
}


void InitInimigo(Inimigo *inimigo, const char* foto, double vida,int xp,int dano, double posX, double posY,double velocidade, bool vivo, int lane) {
    inimigo->foto = LoadTexture(foto);
    inimigo->vida = vida;
    inimigo->vidaMax = vida;
    inimigo->dano = dano;
    inimigo->posX = posX;
    inimigo->posY = posY;
    inimigo->velocidade = velocidade;
    inimigo->vivo = vivo;
    inimigo->xp = xp;
    inimigo->lane = lane;
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

void InitTropas(Tropa *tropas, const char* foto, const char* fotoAtaque , char nome[10] ,double posx, double posy ,double posxataque ,int posyataque, int custo, int fase) {
    tropas->foto = LoadTexture(foto);
    tropas->fotoAtaque = LoadTexture(fotoAtaque);
    strcpy(tropas->nome, nome);
    tropas->posx = posx;
    tropas->posy = posy;
    tropas->posxataque = posxataque;
    tropas->posyataque = posyataque;
    tropas->custo = custo;
    tropas->fase = fase;
}

void DrawInimigo(Inimigo *inimigo, double *vidaPraia){ 
    if (inimigo->posX >= 140){
            inimigo->posX -= inimigo->velocidade;
        }
    else{
        *vidaPraia-=inimigo->dano;
    }


    if (inimigo->vida > 0) {
        DrawTexture(inimigo->foto, inimigo->posX, inimigo->posY, WHITE);
        
        int larguraAtual = (inimigo->vida * largurabarra) / inimigo->vidaMax;
        Color corBarra = GREEN;
        if (inimigo->vida <= 340 && inimigo->vida > 150) {
            corBarra = ORANGE;
        } 
        else if (inimigo->vida <= 150) {
            corBarra = RED;
        }

        DrawRectangle(inimigo->posX + 40, inimigo->posY - 10, larguraAtual, 5, corBarra);
        DrawRectangleLines(inimigo->posX + 40, inimigo->posY - 10, largurabarra, 5, BLACK);
    } 
    else {
        inimigo->vivo = false;
        inimigo->posX = 20000;
        UnloadTexture(inimigo->foto);
    }
}

void DrawBoss(Boss *boss, double *vidaPraia) {
    if (boss->vida > 0) {

        if (boss->posX >= 160) {
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
                *vidaPraia-=boss->dano;
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
        
        int barraPosX = (860 - largurabarra) / 2;
        int barraPosY = 120;
        int larguraAtual = (boss->vida * largurabarraBoss) / boss->vidaMax;

        Color corBarra = RED;
        DrawText("TUBARÃO DE BOA VIAGEM", barraPosX + 40, 95, 25, BLACK);
        DrawRectangle(barraPosX, barraPosY, larguraAtual, 30, corBarra);
        DrawRectangleLines(barraPosX, barraPosY, largurabarraBoss, 30, BLACK);
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
                    experiencia += alvo->xp;
                    scoreTotal+=alvo->xp;
                    inimigos[alvoIndex] = inimigos[*numInimigos - 1];
                    (*numInimigos)--;
                }
            }
            else{
                Reginaldo->posxataque = Reginaldo->posx+5;
            }
        }
    }
    else{
         if (Reginaldo->posxataque < chefe->posX - 20 && chefe->posX < 1300) {
            DrawTexture(Reginaldo->fotoAtaque, Reginaldo->posxataque, Reginaldo->posyataque, WHITE);
            Reginaldo->posxataque += 3;
        } 
        else if (Reginaldo->posxataque >= chefe->posX - 20){
            Reginaldo->posxataque = Reginaldo->posx+5;
            BossRecebeDano(chefe, 100000);
        }
        else if (Reginaldo->posxataque > Reginaldo->posx+5){
                Reginaldo->posxataque = Reginaldo->posx+5;
        }
    }

}

void BossRecebeDano(Boss *boss, int dano) {
    boss->vida -= dano;
    boss->tomandoDano = true;
    boss->frameDano = 40; 
}

void Menu(GameScreen *currentScreen){

    //Texture menu;
    //menu = LoadTexture("./textures/praia.png");
    /*
    Rectangle botaojogar = {100, 150, 200, 50};
    Rectangle botaoranking = {100, 150, 200, 50};
    Rectangle botaoexit = {100, 150, 200, 50};  */

     // Desenha os botões do menu (exemplo)
    Texture menu;
    menu = LoadTexture("./textures/telaMenu.png");
    DrawTexture(menu,0,0,WHITE);
    Rectangle botaoJogar = {500, 300, 200, 50};
    DrawRectangleRec(botaoJogar, GREEN);
    DrawText("JOGAR", 520, 310, 30, DARKGRAY);
    Vector2 mousePosition = GetMousePosition();

    if (CheckCollisionPointRec(mousePosition, botaoJogar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        *currentScreen = NIVEL;  
    } 

}

void inserirTropa(Tropa **head, Tropa **tail, Tropa *tropa ,float posX, float posY, int lane, int posicao){
    Tropa *novo = (Tropa*) malloc (sizeof(Tropa));
    double posx = posX;

    double posy = posY;
    novo = tropa;
    novo->posx = posx;
    novo->posy = posy;
    novo->posxataque = posx+5;
    novo->posyataque = posy+20;
    novo->lane = lane;
    novo->posicao = posicao;

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
            else if (strcmp(head->nome, "CabocloLa") == 0){
                if (head->lane == 1){
                    DrawAtaqueCaboclo(inimigos1 , head , numInimigos1, bossTubarao, boss);
                }
                else if (head->lane == 2){
                    DrawAtaqueCaboclo(inimigos2 , head , numInimigos2, bossTubarao, boss);
                }
                else if (head->lane == 3){
                    DrawAtaqueCaboclo(inimigos3 , head , numInimigos3, bossTubarao, boss);
                }
            }
            else if (strcmp(head->nome, "Lampiao12") == 0){
                if (head->lane == 1){
                    DrawAtaqueLampiao(inimigos1 , head , numInimigos1, bossTubarao, boss);
                }
                else if (head->lane == 2){
                    DrawAtaqueLampiao(inimigos2 , head , numInimigos2, bossTubarao, boss);
                }
                else if (head->lane == 3){
                    DrawAtaqueLampiao(inimigos3 , head , numInimigos3, bossTubarao, boss);
                }
            }
            else if (strcmp(head->nome, "Alaursa34") == 0){
                if (head->lane == 1){
                    DrawAtaqueLaursa(inimigos1 , head , numInimigos1, bossTubarao, boss);
                }
                else if (head->lane == 2){
                    DrawAtaqueLaursa(inimigos2 , head , numInimigos2, bossTubarao, boss);
                }
                else if (head->lane == 3){
                    DrawAtaqueLaursa(inimigos3 , head , numInimigos3, bossTubarao, boss);
                }
            }
            else if (strcmp(head->nome, "Frevista5") == 0){
                if (head->lane == 1){
                    DrawAtaqueFrevista(inimigos1 , head , numInimigos1, bossTubarao, boss);
                }
                else if (head->lane == 2){
                    DrawAtaqueFrevista(inimigos2 , head , numInimigos2, bossTubarao, boss);
                }
                else if (head->lane == 3){
                    DrawAtaqueFrevista(inimigos3 , head , numInimigos3, bossTubarao, boss);
                }
            }
            else if (strcmp(head->nome, "L.Gonzaga") == 0){
                if (head->lane == 1){
                    DrawAtaqueGonzaga(inimigos1 , inimigos2, inimigos3,head , numInimigos1,numInimigos2,
                    numInimigos3, bossTubarao, boss);
                }
                else if (head->lane == 2){
                    DrawAtaqueGonzaga(inimigos1,inimigos2 , inimigos3,head , numInimigos1,numInimigos2,
                    numInimigos3, bossTubarao, boss);
                }
                else if (head->lane == 3){
                    DrawAtaqueGonzaga(inimigos1,inimigos2, inimigos3 , head ,numInimigos1, numInimigos2,
                    numInimigos3, bossTubarao, boss);
                }
            }
        head = head->prox;

        }while (head!= tail->prox);
    }
}

void SalvarTelacongelada(Tropa *head, Tropa *tail, RenderTexture2D telaCongelada, Texture2D mapa,  
                          Inimigo* inimigos1, int numInimigos1, Inimigo* inimigos2, int numInimigos2, Inimigo* inimigos3,
                         int numInimigos3, Boss* bossTubarao, bool boss, Rectangle botaoRemover, double *vidaPraia){
    
            BeginTextureMode(telaCongelada);  
            ClearBackground(RAYWHITE);  
            BeginDrawing();
            DrawTexture(mapa, 0, 0, WHITE);
 
            DrawRectangle(382, 69, (int)larguraxp, 5, BLUE);
            DrawRectangleRec(botaoPosicionar, (Color){ 255, 255, 255, 0 });
            DrawRectangleRec(botaoRemover, (Color){ 255, 255, 255, 0 });
            imprimirTropaCompleta(head, tail , inimigos1, inimigos2, inimigos3,&numInimigos1, &numInimigos2, &numInimigos3, bossTubarao, boss);
            double vida = *vidaPraia;
            double porcentagemVida = (vida / vidaPraiaMax) * 100;
            char textoVida[15];
            snprintf(textoVida, sizeof(textoVida), "%.0f%%", porcentagemVida);
            DrawText(textoVida, 220, 18 , 30 , RED);
            
            for (int i = 0; i < numInimigos1; i++) {
                DrawInimigo(&inimigos1[i], vidaPraia);
            }
             for (int i = 0; i < numInimigos2; i++) {
                DrawInimigo(&inimigos2[i], vidaPraia);
            }
            for (int i = 0; i < numInimigos3; i++) {
                DrawInimigo(&inimigos3[i], vidaPraia);
            }


            if (numInimigos1+numInimigos2+numInimigos3<=0){
                boss = true;
                DrawBoss(bossTubarao, vidaPraia);
                //PlayMusicStream(soundBoss);
            }
            EndDrawing();
            EndTextureMode();
}


void RemoverTropa(Tropa **head, Tropa **tail, int posicao) { 
    if (*head != NULL) {
        Tropa *aux = *head;
        Tropa *prev = NULL;

        
        do {
            if (aux->posicao == posicao) {
               
                if (aux == *head) {
                    
                    if (aux == *tail) {
                        *head = NULL;
                        *tail = NULL; 
                    } else {
                        *head = aux->prox; 
                        (*tail)->prox = *head; 
                    }
                } 
                
                else if (aux == *tail) {
                    *tail = prev; 
                    (*tail)->prox = *head; 
                } 
                
                else {
                    if (prev != NULL) {
                        prev->prox = aux->prox; 
                    }
                }

                
                return; 
            }

            prev = aux; 
            aux = aux->prox; 
        } while (aux != *head); 
    }
}

void adicionarTropa(Tropa **head, Tropa **tail, Tropa *tropa, Tropa *tropa2, Tropa *tropa3,
                        Tropa *tropa4, Tropa *tropa5, Tropa *tropa6, RenderTexture2D telaCongelada, Texture2D mapa,  
                         Inimigo *inimigos1, int numInimigos1, Inimigo *inimigos2, int numInimigos2, 
                        Inimigo *inimigos3, int numInimigos3, Boss *bossTubarao, bool boss, Rectangle botaoRemover, double *vidaPraia) {
    
    bool botaoclicado = true;

    // Salva o estado da tela atual em telaCongelada
    SalvarTelacongelada(*head, *tail, telaCongelada, mapa, inimigos1, numInimigos1, 
                        inimigos2, numInimigos2, inimigos3, numInimigos3, bossTubarao, boss, botaoRemover, vidaPraia);

    Texture b1, b2, b3, b4, b5, b6;
            b1 = LoadTexture("./textures/areaArcoFlecha.png");
            b2 = LoadTexture("./textures/areaArcoFlecha.png");
            b3 = LoadTexture("./textures/areaArcoFlecha.png");
            b4 = LoadTexture("./textures/areaEspada.png");
            b5 = LoadTexture("./textures/areaEspada.png");
            b6 = LoadTexture("./textures/areaEspada.png");                

    // Loop de seleção de posição para o personagem Reginaldo
    while (botaoclicado && !WindowShouldClose()) {
        BeginDrawing();
        DrawTextureRec(telaCongelada.texture, (Rectangle){ 0, 0, (float)telaCongelada.texture.width, (float)-telaCongelada.texture.height }, (Vector2){ 0, 0 }, WHITE);
        if (casa1==true /*&& range == true*/){
            DrawRectangleRec(botaoQuadrado, (Color){ 255, 255, 255, 0 });
            DrawTexture(b1, 20, 260, WHITE);
        }
        if (casa2==true /*&& range == true*/){
            DrawRectangleRec(botaoQuadrado2, (Color){ 255, 255, 255, 0 });
            DrawTexture(b2, 20, 390, WHITE);
        }
        if (casa3==true /*&& range == true*/){
            DrawRectangleRec(botaoQuadrado3, (Color){ 255, 255, 255, 0 });
            DrawTexture(b3, 20, 520, WHITE);
        }
        if (casa4==true /*&& range == false*/){
            DrawRectangleRec(botaoQuadrado4, (Color){ 255, 255, 255, 0 });
            DrawTexture(b4, 100, 300, WHITE);
        }
        if (casa5==true /*&& range == false*/){
            DrawRectangleRec(botaoQuadrado5, (Color){ 255, 255, 255, 0 });
            DrawTexture(b5, 100, 430, WHITE);
        }
        if (casa6==true /*&& range == false*/){
            DrawRectangleRec(botaoQuadrado6, (Color){ 255, 255, 255, 0 });
            DrawTexture(b6, 100, 540, WHITE);
        }
        DrawText("Escolha um local...", 550, 250, 20, BLACK);
        EndDrawing();
        

        Vector2 mousePosition = GetMousePosition();

        // Verifica em qual quadrado o usuário clicou para posicionar a tropa
        if (CheckCollisionPointRec(mousePosition, botaoQuadrado) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && casa1==true /*&& range == true*/) {
            inserirTropa(head, tail, tropa, botaoQuadrado.x, botaoQuadrado.y, 1, 1);
            botaoclicado = false;
            casa1=false;
            nivelXp-=tropa->custo;
        }
        else if (CheckCollisionPointRec(mousePosition, botaoQuadrado2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && casa2==true /*&& range == true*/) {
            inserirTropa(head, tail, tropa2, botaoQuadrado2.x, botaoQuadrado2.y, 2, 2);
            botaoclicado = false;
            casa2=false;
            nivelXp-=tropa2->custo;
        }
        else if (CheckCollisionPointRec(mousePosition, botaoQuadrado3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && casa3==true /*&& range == true*/) {
            inserirTropa(head, tail, tropa3, botaoQuadrado3.x, botaoQuadrado3.y - 20, 3, 3);
            botaoclicado = false;
            casa3=false;
            nivelXp-=tropa3->custo;
        }
        else if (CheckCollisionPointRec(mousePosition, botaoQuadrado4) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && casa4==true /*&& range == false*/) {
            inserirTropa(head, tail, tropa4, botaoQuadrado4.x, botaoQuadrado4.y, 1, 4);
            botaoclicado = false;
            casa4=false;
            nivelXp-=tropa4->custo;
        }
        else if (CheckCollisionPointRec(mousePosition, botaoQuadrado5) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && casa5==true /*&& range == false*/) {
            inserirTropa(head, tail, tropa5, botaoQuadrado5.x, botaoQuadrado5.y-15, 2, 5);
            botaoclicado = false;
            casa5=false;
            nivelXp-=tropa5->custo;
        }
        else if (CheckCollisionPointRec(mousePosition, botaoQuadrado6) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && casa6==true /*&& range == false*/) {
            inserirTropa(head, tail, tropa6, botaoQuadrado6.x, botaoQuadrado6.y - 20, 3, 6);
            botaoclicado = false;
            casa6=false;
            nivelXp-=tropa6->custo;
        }
        else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            botaoclicado = false;  // Sai do loop se clicar fora dos botões
        }
    }

    UnloadRenderTexture(telaCongelada);  // Libera a memória da textura congelada
}

void removerTropaBotao(Tropa **head, Tropa **tail, RenderTexture2D telaCongelada, Texture2D mapa,
                        Inimigo *inimigos1, int numInimigos1,
                      Inimigo *inimigos2, int numInimigos2, Inimigo *inimigos3, int numInimigos3, 
                      Boss *bossTubarao, bool boss, Rectangle botaoRemover, double *vidaPraia) {

    bool botaoclicado = true;

    // Salva o estado da tela atual em telaCongelada
    SalvarTelacongelada(*head, *tail, telaCongelada, mapa, inimigos1, 
                        numInimigos1, inimigos2, numInimigos2, inimigos3, numInimigos3, bossTubarao, boss, botaoRemover, vidaPraia);

    // Loop para escolher a tropa que será removida
    while (botaoclicado && !WindowShouldClose()) {
        BeginDrawing();
        DrawTextureRec(telaCongelada.texture, (Rectangle){ 0, 0, (float)telaCongelada.texture.width, (float)-telaCongelada.texture.height }, (Vector2){ 0, 0 }, WHITE);
        DrawText("Escolha uma tropa para remover...", 550, 250, 20, BLACK);
        EndDrawing();

        Vector2 mousePosition = GetMousePosition();

        // Verifica em qual quadrado o usuário clicou para remover a tropa correspondente
        if (CheckCollisionPointRec(mousePosition, botaoQuadrado) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            RemoverTropa(head, tail, 1);
            botaoclicado = false;
            casa1=true;
        }
        else if (CheckCollisionPointRec(mousePosition, botaoQuadrado2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            RemoverTropa(head, tail, 2);
            botaoclicado = false;
            casa2=true;
        }
        else if (CheckCollisionPointRec(mousePosition, botaoQuadrado3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            RemoverTropa(head, tail, 3);
            botaoclicado = false;
            casa3=true;
        }
        else if (CheckCollisionPointRec(mousePosition, botaoQuadrado4) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            RemoverTropa(head, tail, 4);
            botaoclicado = false;
            casa4=true;
        }
        else if (CheckCollisionPointRec(mousePosition, botaoQuadrado5) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            RemoverTropa(head, tail, 5);
            botaoclicado = false;
            casa5=true;
        }
        else if (CheckCollisionPointRec(mousePosition, botaoQuadrado6) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            RemoverTropa(head, tail, 6);
            botaoclicado = false;
            casa6=true;
        }
        else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            botaoclicado = false;  // Sai do loop se clicar fora dos botões
        }
    }

    UnloadRenderTexture(telaCongelada);  // Libera a memória da textura congelada
}

void DrawAtaqueCaboclo(Inimigo *inimigos, Tropa *Caboclo, int *numInimigos, Boss *chefe ,bool boss) {
    if (boss == false){
        for (int i = 0; i < *numInimigos; i++) {
            if (Caboclo->posxataque > 1315) {
                Caboclo->posxataque = Caboclo->posx+5;
            }
            else if (Caboclo->posxataque >= inimigos[i].posX - 20 &&  Caboclo->posxataque <= inimigos[i].posX + 20){
                DrawTexture(Caboclo->fotoAtaque, Caboclo->posxataque, Caboclo->posyataque, WHITE);
                inimigos[i].vida -= 25;
                if (inimigos[i].vida <= 0) {
                    experiencia += inimigos[i].xp;
                    scoreTotal+=inimigos[i].xp;
                    inimigos[i] = inimigos[*numInimigos - 1];
                    (*numInimigos)--;
                }
            }
            else if (inimigos[i].posX < 1320) {
                DrawTexture(Caboclo->fotoAtaque, Caboclo->posxataque, Caboclo->posyataque, WHITE);
                
            } 
            
        }
        Caboclo->posxataque += 5;
    }
    
    else{
        if (Caboclo->posxataque > 1315) {
                Caboclo->posxataque = Caboclo->posx+5;
        }
        else if (Caboclo->posxataque >= chefe->posX - 20 &&  Caboclo->posxataque <= chefe->posX + 5){
                DrawTexture(Caboclo->fotoAtaque, Caboclo->posxataque, Caboclo->posyataque, WHITE);
                Caboclo->posxataque += 3;
                BossRecebeDano(chefe, 50);
        }
        else if (chefe->posX < 1320) {
                DrawTexture(Caboclo->fotoAtaque, Caboclo->posxataque, Caboclo->posyataque, WHITE);
                Caboclo->posxataque += 5;
        }
        else if (Caboclo->posxataque > Caboclo->posx+5){
                Caboclo->posxataque = Caboclo->posx+5;
        }
    }

}

void inserirTropaArvore(NodeTropa **raiz, Tropa *tropa) {
    if (*raiz == NULL) {
        NodeTropa *novoNode = (NodeTropa*)malloc(sizeof(NodeTropa));
        novoNode->tropa = *tropa;
        novoNode->esquerda = novoNode->direita = NULL;
        *raiz = novoNode; 
        return;
    }
    
    if (tropa->custo < (*raiz)->tropa.custo) {
        inserirTropaArvore(&(*raiz)->esquerda, tropa);
    } 
    else {
        inserirTropaArvore(&(*raiz)->direita, tropa);
    }
    
}

bool verificarDisponibilidadeTropa(NodeTropa *raiz, char nomeTropa[10], int faseAtual, int xpDisponivel) {
    if (raiz == NULL) {
        return false;
    }

    if (strcmp(raiz->tropa.nome, nomeTropa) == 0) {
        
        if (raiz->tropa.fase <= faseAtual && raiz->tropa.custo <= xpDisponivel) {
            return true;
        } 
        else {
            return false;
        }
    }

    if (verificarDisponibilidadeTropa(raiz->esquerda, nomeTropa, faseAtual, xpDisponivel)) {
        return true;
    }
    if (verificarDisponibilidadeTropa(raiz->direita, nomeTropa, faseAtual, xpDisponivel)) {
        return true;
    }
    return false;
}

void DrawAtaqueLampiao(Inimigo *inimigos, Tropa *Lampiao, int *numInimigos, Boss *chefe ,bool boss){
     int alvoIndex = -1;
    double menorDistancia = 10000; 
    
    Lampiao->tempoAtaque++;

    if (boss == false &&  Lampiao->tempoAtaque >= 300){
        for (int i = 0; i < *numInimigos; i++) {
            if (inimigos[i].vivo && inimigos[i].posX < menorDistancia) {
                menorDistancia = inimigos[i].posX;
                alvoIndex = i;
            }
        }

        if (alvoIndex != -1) {
            Inimigo *alvo = &inimigos[alvoIndex];
            

            if (Lampiao->posxataque < alvo->posX - 20 && alvo->posX < 1350) {
                DrawTexture(Lampiao->fotoAtaque, Lampiao->posxataque, Lampiao->posyataque, WHITE);
                Lampiao->posxataque += 3;
            } 
            else if (Lampiao->posxataque >= alvo->posX - 20){
                Lampiao->posxataque = Lampiao->posx+5;
                alvo->vida -= 1000;
                Lampiao->tempoAtaque = 0;
                if (alvo->vida <= 0) {
                    experiencia += alvo->xp;
                    scoreTotal+= alvo->xp;
                    inimigos[alvoIndex] = inimigos[*numInimigos - 1];
                    (*numInimigos)--;
                }
            }
            else{
                Lampiao->posxataque = Lampiao->posx+5;
                Lampiao->tempoAtaque = 0;
            }
        }
    }
    else if (boss == true && Lampiao->tempoAtaque >= 300) {
         if (Lampiao->posxataque < chefe->posX - 20 && chefe->posX < 1300) {
            DrawTexture(Lampiao->fotoAtaque, Lampiao->posxataque, Lampiao->posyataque, WHITE);
            Lampiao->posxataque += 3;
        } 
        else if (Lampiao->posxataque >= chefe->posX - 20){
            Lampiao->posxataque = Lampiao->posx+5;
            BossRecebeDano(chefe, 750);
            Lampiao->tempoAtaque = 0;
        }
        else if (Lampiao->posxataque > Lampiao->posx+5){
                Lampiao->posxataque = Lampiao->posx+5;
                Lampiao->tempoAtaque = 0;
        }
    }
}

void DrawAtaqueLaursa(Inimigo *inimigos, Tropa *LaUrsa, int *numInimigos, Boss *chefe ,bool boss){
    if (boss == false){
        for (int i = 0; i < *numInimigos; i++) {
            if (inimigos[i].posX <= LaUrsa->posx+150){
                DrawTexture(LaUrsa->fotoAtaque, 220, LaUrsa->posyataque-20, WHITE);
                inimigos[i].vida -= 7;
                if (inimigos[i].vida <= 0) {
                    experiencia += inimigos[i].xp;
                    scoreTotal += inimigos[i].xp;
                    inimigos[i] = inimigos[*numInimigos - 1];
                    (*numInimigos)--;
                }
            } 
        }
    }
    
    else{
        if (chefe->posX <= LaUrsa->posx+400){
                DrawTexture(LaUrsa->fotoAtaque, 200, LaUrsa->posyataque-10, WHITE);
                BossRecebeDano(chefe, 7);
            } 
    }
}

void DrawAtaqueFrevista(Inimigo *inimigos, Tropa *Frevista, int *numInimigos, Boss *chefe ,bool boss){ 
    int alvoIndex = -1;
    double menorDistancia = 10000;
    Texture ataque;
    ataque = LoadTexture("./textures/laUrsa-ataque.png");
    
    if (boss == false){
        
         for (int i = 0; i < *numInimigos; i++) {
            if (inimigos[i].vivo && inimigos[i].posX < menorDistancia) {
                menorDistancia = inimigos[i].posX;
                alvoIndex = i;
            }
        }

        if (Frevista->tempoAtaque > 0) {
                DrawTexture(Frevista->fotoAtaque, Frevista->posx+100, Frevista->posy+10, WHITE); 
        }

        if (alvoIndex != -1) {
            Inimigo *alvo = &inimigos[alvoIndex];
            
            if (Frevista->tempoAtaque > 0 && alvo->posX <= Frevista->posx + 100) {
                alvo->posX += 100;
                Frevista->tempoAtaque--; 
            }
            else if (Frevista->tempoAtaque <= 0){
                for (int i = 0; i < *numInimigos; i++) {
                    if (inimigos[i].posX <= Frevista->posx+150){
                        DrawTexture(ataque, Frevista->posx+100, Frevista->posy - 20, WHITE);
                        inimigos[i].vida -= 3;
                        if (inimigos[i].vida <= 0) {
                            experiencia += inimigos[i].xp;
                            scoreTotal += inimigos[i].xp;
                            inimigos[i] = inimigos[*numInimigos - 1];
                            (*numInimigos)--;
                        }
                    } 
                }
            }

        }
        else{
            Frevista->tempoAtaque=5;
        }
   
    }
    else{

        if (chefe->posX <= Frevista->posx+400){
                DrawTexture(ataque, 200, Frevista->posyataque-10, WHITE);
                BossRecebeDano(chefe, 3);
            } 
    }
}

 void CapturarNome(GameScreen *currentScreen, char *nomeJogador) {
    DrawText("Digite seu nome:", 250, 200, 20, DARKGRAY);
    DrawRectangle(250, 240, 300, 40, LIGHTGRAY);
    DrawText(nomeJogador, 260, 250, 20, DARKGRAY);

    int key = GetCharPressed();
    int length = strlen(nomeJogador);

    // Adiciona o caractere digitado ao nome do jogador, se o tamanho do nome for menor que 19
    if (key >= 32 && key <= 125 && length < 29) {
        nomeJogador[length] = (char)key;
        nomeJogador[length + 1] = '\0';  // Adiciona o caractere nulo no final
    }

    // Remove o último caractere se o jogador pressionar BACKSPACE
    if (IsKeyPressed(KEY_BACKSPACE) && length > 0) {
        nomeJogador[length - 1] = '\0';
    }

    // Confirma o nome ao pressionar ENTER e passa para a próxima tela
    if (IsKeyPressed(KEY_ENTER)) {
        *currentScreen = MENU; 
    }
}

void salvarDados(char *nome, int nivel, int score) {
    FILE *arquivo = fopen("scoreboard.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "%s %d %d\n", nome, nivel, score);
        fclose(arquivo);
    } else {
        printf("Arquivo nao encontrado!");
    }
}

void inserir(usuario **head, char *nome, int nivel, int score) {
    usuario *novo = (usuario *)malloc(sizeof(usuario));
    if (novo != NULL) {
        if (nome[0] != '\0') {
            strcpy(novo->nome, nome);
        }
        novo->nivel = nivel;
        novo->score = score;
        novo->prox = NULL;

        if (*head == NULL) {
            novo->ant = NULL;
            *head = novo;
        } else {
            usuario *temp = *head;
            while (temp->prox != NULL) {
                temp = temp->prox;
            }
            novo->ant = temp;
            temp->prox = novo;
        }
    } else {
        printf("Erro ao alocar memória.\n");
    }
}

void lerDados(usuario **head) {
    FILE *arquivo = fopen("scoreboard.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char nome[30];
    int nivel;
    int score;

    while (fscanf(arquivo, "%s %d %d", nome, &nivel, &score) == 3) {
        inserir(head, nome, nivel, score);
    }

    fclose(arquivo);
}

void organizar(usuario **head) {
    usuario *temp;
    int troca = 1, len = 0;

    // Calcular o comprimento da lista
    temp = *head;
    while (temp != NULL) {
        len++;
        temp = temp->prox;
    }
    int n=0;

    // Ordenar usando Bubble Sort
    while (n < len && troca ==1) {
        troca = 0;
        temp = *head; // Reinicia 'temp' no começo da lista para cada passagem

        for (int i=0; i<len-1; i++) {
            if (temp->score < temp->prox->score) {
                trocar(head, temp, temp->prox);
                troca = 1;
                temp = temp->ant;
            }
            temp = temp->prox;
        }
    }

    // Abrir arquivo para sobrescrever com os dados organizados
    FILE *arquivo = fopen("scoreboard.txt", "w");
    if (arquivo != NULL) {
        temp = *head;
        while (temp != NULL) {
            fprintf(arquivo, "%s %d %d\n", temp->nome, temp->nivel, temp->score);
            temp = temp->prox;
        }
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo para escrita.\n");
    }
}

void trocar(usuario **head, usuario *ant, usuario *prox) {
    // Caso ant seja o head, precisamos atualizar o ponteiro do head
    if (ant->ant != NULL) {
        ant->ant->prox = prox;
    } else {
        *head = prox; // Atualiza o início da lista se 'ant' for o primeiro elemento
    }

    if (prox->prox != NULL) {
        prox->prox->ant = ant;
    }

    // Troca os ponteiros entre 'ant' e 'prox'
    ant->prox = prox->prox;
    prox->ant = ant->ant;

    prox->prox = ant;
    ant->ant = prox;
}

void DrawAtaqueGonzaga(Inimigo *inimigos, Inimigo *inimigos2, Inimigo *inimigos3,Tropa *Gonzaga, int *numInimigos, 
 int *numInimigos2, int *numInimigos3 ,Boss *chefe ,bool boss){
      if (boss == false){
        bool ataqueNaLane1 = false, ataqueNaLane2 = false, ataqueNaLane3 = false;

           if (Gonzaga->lane == 1) {
            ataqueNaLane1 = AtacarInimigosNaLane(inimigos, numInimigos, Gonzaga, 5);
            ataqueNaLane2 = AtacarInimigosNaLane(inimigos2, numInimigos2, Gonzaga, 3);

            if (ataqueNaLane1 || ataqueNaLane2){ 
                DrawTexture(Gonzaga->fotoAtaque, 220, Gonzaga->posyataque - 20, WHITE);
                DrawTexture(Gonzaga->fotoAtaque, 220, Gonzaga->posyataque + 100, WHITE);
            }  
        } 
        else if (Gonzaga->lane == 2) {
            ataqueNaLane1 = AtacarInimigosNaLane(inimigos, numInimigos, Gonzaga,  2);
            ataqueNaLane2 = AtacarInimigosNaLane(inimigos2, numInimigos2, Gonzaga, 4);
            ataqueNaLane3 = AtacarInimigosNaLane(inimigos3, numInimigos3, Gonzaga, 2);

            if (ataqueNaLane1 || ataqueNaLane2 || ataqueNaLane3){ 
                DrawTexture(Gonzaga->fotoAtaque, 220, Gonzaga->posyataque - 20, WHITE);
                DrawTexture(Gonzaga->fotoAtaque, 220, Gonzaga->posyataque - 150, WHITE);
                DrawTexture(Gonzaga->fotoAtaque, 220, Gonzaga->posyataque + 90, WHITE);
            }  
        } 
        else if (Gonzaga->lane == 3) {
            ataqueNaLane2 = AtacarInimigosNaLane(inimigos2, numInimigos2, Gonzaga, 3);
            ataqueNaLane3 = AtacarInimigosNaLane(inimigos3, numInimigos3, Gonzaga, 5);

            if (ataqueNaLane2 || ataqueNaLane3){ 
                DrawTexture(Gonzaga->fotoAtaque, 220, Gonzaga->posyataque - 20, WHITE);
                DrawTexture(Gonzaga->fotoAtaque, 220, Gonzaga->posyataque - 100, WHITE);
            } 
        }
    }
    else{
        if (chefe->posX <= Gonzaga->posx+400){
                DrawTexture(Gonzaga->fotoAtaque, 200, Gonzaga->posyataque-10, WHITE);
                BossRecebeDano(chefe, 8);
            } 
    }
}

bool AtacarInimigosNaLane(Inimigo *inimigos, int *numInimigos, Tropa *Gonzaga, int danoPorAtaque) {
    bool atacou = false;  // Flag para indicar se houve ataque nesta lane
    for (int i = 0; i < *numInimigos; i++) {
        if (inimigos[i].posX <= Gonzaga->posx + 150) {
            inimigos[i].vida -= danoPorAtaque;
            atacou = true;  // Marca que houve ataque
            if (inimigos[i].vida <= 0) {
                experiencia += inimigos[i].xp;
                scoreTotal += inimigos[i].xp;
                inimigos[i] = inimigos[*numInimigos - 1];
                (*numInimigos)--;
            }
        }
    }
    return atacou;
}

void DrawBossBoto(Boss *boss, double *vidaPraia) {
    if (boss->vida > 0) {

        if (boss->posX >= 450) {
            boss->posX -= boss->velocidade;

            int imagemIndex = (boss->frameDano > 0) ? 1 : 0;  
            DrawTexture(boss->foto[imagemIndex], boss->posX, boss->posY-80, WHITE);

            if (boss->frameDano > 0) {
                boss->frameDano--;
            }

        }
        else{

            // Ativação da sequência de ataque
            const int ataqueFrames[] = {2, 2, 4, 4, 7, 7};

            // Desenha o frame atual da sequência de ataque
            int indice = ataqueFrames[boss->indiceAtaque];
            if (indice == 0){
                DrawTexture(boss->foto[indice], boss->posX, boss->posY - 80, WHITE);
            }
            else if (indice == 2){
                DrawTexture(boss->foto[indice], boss->posX-40, boss->posY - 80, WHITE);
            }
            else if (indice == 4){
                DrawTexture(boss->foto[indice], boss->posX-210, boss->posY - 80, WHITE);
            }
            else if (indice == 7){
                DrawTexture(boss->foto[indice], boss->posX-250, boss->posY - 180, WHITE);
                *vidaPraia-=boss->dano;
            }
            else{
                DrawTexture(boss->foto[indice], boss->posX, boss->posY - 80, WHITE);
            }
            
            

            if (boss->frameAtaque >= 70) { 
                boss->indiceAtaque = (boss->indiceAtaque + 1) % 6; 
                boss->frameAtaque = 0; 
            } else {
                boss->frameAtaque++;
            }

        }
        
        int barraPosX = (860 - largurabarra) / 2;
        int barraPosY = 120;
        int larguraAtual = (boss->vida * largurabarraBoss) / boss->vidaMax;

        Color corBarra = RED;
        DrawText("BOTO COR DE ROSA", barraPosX + 70, 95, 25, BLACK);
        DrawRectangle(barraPosX, barraPosY, larguraAtual, 30, corBarra);
        DrawRectangleLines(barraPosX, barraPosY, largurabarraBoss, 30, BLACK);
    } 
    else {
        boss->vivo = false;
        boss->posX = 20000;
        for (int i = 0; i < 7; i++) {
            UnloadTexture(boss->foto[i]);
        }
    }
}