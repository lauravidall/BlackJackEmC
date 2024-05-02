#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct deck{
    char carta[4]; 
    struct deck *prox;
    struct deck *ant;
};

struct carta{
    char carta[4];
};

struct jogador{
    char nome[20];
    int pontuacao;
};

struct highscore{
    struct jogador player;
    struct highscore *prox;
};

void ordenarLista(struct highscore **cabeca, struct jogador player);
void escreverLista(struct highscore *cabeca, FILE *fptr);
void printarLista(struct highscore *cabeca);
void freeLista(struct highscore **cabeca);

//mudancas 
void inserirNaListaCirc(struct deck **head, struct deck **tail, char carta[]);
void printarListaCirc(struct deck *head, struct deck *tail);
void resetarJogo(struct deck **head, struct deck **tail);
void excluirCarta(struct deck **head, struct deck **tail, char carta[]);
void adicionandoCartas(struct deck **head, struct deck **tail);

int main(){

    struct deck *head = NULL;
    struct deck *tail = NULL;

    struct highscore *cabeca = NULL;
    FILE *fptr;
    struct jogador player;

    printf("---------------------------\n");
    printf("|                         |\n");
    printf("| BEM-VINDO AO CASSINO ?? |\n");
    printf("|                         |\n");
    printf("---------------------------\n");

    printf("\nDigite o nome do jogador: ");
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
            ordenarLista(&cabeca, player);
        }
        fclose(fptr);
    }
    fptr = fopen("score.txt", "w");
    if(fptr!=NULL){
        escreverLista(cabeca, fptr);
        fclose(fptr);
    }
    printarLista(cabeca);
    freeLista(&cabeca);
    
    adicionandoCartas(&head,&tail);
    printarListaCirc(head,tail);

    printf("\npos remover: "); //resetar jogo --> ok
    resetarJogo(&head, &tail);
    printarListaCirc(head,tail);
    printf("removendo ok!\n"); //resetar jogo --> ok

    struct carta arrayDealer[2];
    struct carta arrayJogador[12];
    
}

void ordenarLista(struct highscore **cabeca, struct jogador player){
    struct highscore *novo = malloc(sizeof(struct highscore));
    if(novo==NULL){
        printf("Falha ao alocar memória");
        return;
    }
    novo->player = player;
    novo->prox = NULL;
    if(*cabeca==NULL || (*cabeca)->player.pontuacao<=player.pontuacao){
        novo->prox = *cabeca;
        *cabeca = novo;
    }else{
        struct highscore *aux = *cabeca;
        while(aux->prox!=NULL&&aux->prox->player.pontuacao>player.pontuacao){
            aux = aux->prox;
        }
        novo->prox = aux->prox;
        aux->prox = novo;
    }
}

void escreverLista(struct highscore *cabeca, FILE *fptr){
    while(cabeca!=NULL){
        fwrite(&cabeca->player, sizeof(struct jogador), 1, fptr);
        cabeca = cabeca->prox;
    }
}

void printarLista(struct highscore *cabeca){
    int posicao = 1;
    while(cabeca!=NULL){
        printf("%dº colocado:\n", posicao);
        printf("Nome: %s\n", cabeca->player.nome);
        printf("Pontuação: %d\n", cabeca->player.pontuacao);
        cabeca = cabeca->prox;
        posicao++;
    }
}

void freeLista(struct highscore **cabeca){
    while(*cabeca!=NULL){
        struct highscore *temp = *cabeca;
        *cabeca = (*cabeca)->prox;
        free(temp);
    }
}

//Mudanças 

void inserirNaListaCirc(struct deck **head, struct deck **tail, char carta[]){
    struct deck *novo = (struct deck*)malloc(sizeof(struct deck));
    struct deck *temp = (*head);
    if(novo!=NULL){
        strcpy(novo->carta, carta);
        if(*head==NULL){
            (*head) = novo;
            (*tail) = novo;
            novo->ant = novo;
            novo->prox = novo;
        }else{
            novo->prox = (*head);
            novo->ant = (*tail);
            (*head)->ant = novo;
            (*tail)->prox = novo;
            (*head) = novo;
        }
    }
}

void printarListaCirc(struct deck *head, struct deck *tail) {
    if (head == NULL) return;
    struct deck *temp = head;
    do {
        printf("carta: %s\n", temp->carta);
        temp = temp->prox;
    } while (temp != head);
}

void resetarJogo(struct deck **head, struct deck **tail){
    struct deck *temp = *head;
    struct deck *proxNode;
    if(*head!=NULL){
        do{
            proxNode = temp->prox; 
            free(temp);            
            temp = proxNode;       
        }while(temp!=*head);   
        *head = NULL;
        *tail = NULL;
    }
}

void excluirCarta(struct deck **head, struct deck **tail, char carta[]){ //alterar
    struct deck *temp = *head;
    if(*head!=NULL){
        if(*head==*tail){
            *head = *tail = NULL;
        }else{
            (*head) = (*head)->prox;
            (*tail)->prox = *head;
        }
        free(temp);
    }
}

void adicionandoCartas(struct deck **head, struct deck **tail){

    inserirNaListaCirc(head,tail,"1!");
    inserirNaListaCirc(head,tail, "1?");
    inserirNaListaCirc(head,tail, "1+");
    inserirNaListaCirc(head,tail, "1-");

    inserirNaListaCirc(head,tail,"2!");
    inserirNaListaCirc(head,tail, "2?");
    inserirNaListaCirc(head,tail, "2+");
    inserirNaListaCirc(head,tail, "2-");

    inserirNaListaCirc(head,tail,"3!");
    inserirNaListaCirc(head,tail, "3?");
    inserirNaListaCirc(head,tail, "3+");
    inserirNaListaCirc(head,tail, "3-");

    inserirNaListaCirc(head,tail,"4!");
    inserirNaListaCirc(head,tail, "4?");
    inserirNaListaCirc(head,tail, "4+");
    inserirNaListaCirc(head,tail, "4-");

    inserirNaListaCirc(head,tail,"5!");
    inserirNaListaCirc(head,tail, "5?");
    inserirNaListaCirc(head,tail, "5+");
    inserirNaListaCirc(head,tail, "5-");

    inserirNaListaCirc(head,tail,"6!");
    inserirNaListaCirc(head,tail, "6?");
    inserirNaListaCirc(head,tail, "6+");
    inserirNaListaCirc(head,tail, "6-");

    inserirNaListaCirc(head,tail,"7!");
    inserirNaListaCirc(head,tail, "7?");
    inserirNaListaCirc(head,tail, "7+");
    inserirNaListaCirc(head,tail, "7-");

    inserirNaListaCirc(head,tail,"8!");
    inserirNaListaCirc(head,tail, "8?");
    inserirNaListaCirc(head,tail, "8+");
    inserirNaListaCirc(head,tail, "8-");

    inserirNaListaCirc(head,tail,"9!");
    inserirNaListaCirc(head,tail, "9?");
    inserirNaListaCirc(head,tail, "9+");
    inserirNaListaCirc(head,tail, "9-");

    inserirNaListaCirc(head,tail,"10!");
    inserirNaListaCirc(head,tail, "10?");
    inserirNaListaCirc(head,tail, "10+");
    inserirNaListaCirc(head,tail, "10-");

    inserirNaListaCirc(head,tail, "J!");
    inserirNaListaCirc(head,tail, "J?");
    inserirNaListaCirc(head,tail, "J+");
    inserirNaListaCirc(head,tail, "J-");

    inserirNaListaCirc(head,tail, "Q!");
    inserirNaListaCirc(head,tail, "Q?");
    inserirNaListaCirc(head,tail, "Q+");
    inserirNaListaCirc(head,tail, "Q-");

    inserirNaListaCirc(head,tail, "K!");
    inserirNaListaCirc(head,tail, "K?");
    inserirNaListaCirc(head,tail, "K+");
    inserirNaListaCirc(head,tail, "K-");

    inserirNaListaCirc(head,tail, "A!");
    inserirNaListaCirc(head,tail, "A?");
    inserirNaListaCirc(head,tail, "A+");
    inserirNaListaCirc(head,tail, "A-");
}