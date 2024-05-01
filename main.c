#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct jogador{
    char nome[20];
    int pontuacao;
};

struct highscore{
    struct jogador player;
    struct highscore *prox;
};

void ordenarLista(struct highscore **head, struct jogador player);
void escreverLista(struct highscore *head, FILE *fptr);
void printarLista(struct highscore *head);
void freeLista(struct highscore **head);

int main(){

    struct highscore *head = NULL;
    FILE *fptr;
    struct jogador player;

    printf("Digite o nome do jogador: ");
    scanf("%s", player.nome);
    player.pontuacao = 10;  
    
    fptr = fopen("score.txt", "a");
    if(fptr!=NULL){
        fwrite(&player, sizeof(struct jogador), 1, fptr);
        fclose(fptr);
    }

    fptr = fopen("score.txt", "r");
    if(fptr!=NULL){
        while(fread(&player, sizeof(struct jogador),1,fptr)==1){
            ordenarLista(&head, player);
        }
        fclose(fptr);
    }
    
    fptr = fopen("score.txt", "w");
    if(fptr!=NULL){
        escreverLista(head, fptr);
        fclose(fptr);
    }

    printarLista(head);
    freeLista(&head);
    return EXIT_SUCCESS;
}

void ordenarLista(struct highscore **head, struct jogador player){
    struct highscore *novo = malloc(sizeof(struct highscore));
    if(novo == NULL) {
        printf("Falha ao alocar memória");
        return;
    }
    novo->player = player;
    novo->prox = NULL;

    if(*head==NULL||(*head)->player.pontuacao<=player.pontuacao){
        novo->prox = *head;
        *head = novo;
    }else{
        struct highscore *aux = *head;
        while (aux->prox != NULL && aux->prox->player.pontuacao > player.pontuacao) {
            aux = aux->prox;
        }
        novo->prox = aux->prox;
        aux->prox = novo;
    }
}

void escreverLista(struct highscore *head, FILE *fptr){
    while(head!=NULL){
        fwrite(&head->player, sizeof(struct jogador), 1, fptr);
        head = head->prox;
    }
}

void printarLista(struct highscore *head){
    int posicao = 1;
    while(head!=NULL){
        printf("%dº colocado:\n", posicao);
        printf("Nome: %s\n", head->player.nome);
        printf("Pontuação: %d\n", head->player.pontuacao);
        head = head->prox;
        posicao++;
    }
}

void freeLista(struct highscore **head){
    while(*head!=NULL){
        struct highscore *temp = *head;
        *head = (*head)->prox;
        free(temp);
    }
}
