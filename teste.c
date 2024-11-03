#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct usuario{
    char nome[30];
    int nivel;
    int score;
    struct usuario *prox;
    struct usuario *ant;
}usuario;

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

void salvarDados(char *nome, int nivel, int score) {
    FILE *arquivo = fopen("scoreboard.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "%s %d %d\n", nome, nivel, score);
        fclose(arquivo);
    } else {
        printf("Arquivo nao encontrado!");
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


void printar(usuario *head){
    while(head != NULL){
        printf("%s %d\n", head->nome, head->score);
        head = head->prox;
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


int main(){

    usuario *head = NULL;

    printf("oi");
    salvarDados("Lucas", 10, 111);
    
    lerDados(&head);

    printar(head);
    
    //organizar(&head);

    return 0;
}