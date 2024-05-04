#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
int contarCartas(struct deck *head);
void extrairCarta(struct deck **head, struct deck **tail, struct carta *destino);
int calcularPontuacao(struct carta array[], int numCartas);

int main(){

    float scoreDealer=0;
    float scoreJogador=0;

    srand(time(NULL));

    struct deck *head = NULL;
    struct deck *tail = NULL;

    struct highscore *cabeca = NULL;
    FILE *fptr;
    struct jogador player;

    printf("----------------------------\n");
    printf("|                          |\n");
    printf("|   BEM-VINDO AO CASSINO   |\n");
    printf("|                          |\n");
    printf("----------------------------\n");

    printf("\nDigite o nome do jogador: ");
    scanf("%s", player.nome);
    
    adicionandoCartas(&head,&tail);

    struct carta arrayDealer[2];
    struct carta arrayJogador[12];

    for(int i=0;i<2;i++){ 
        extrairCarta(&head,&tail,&arrayDealer[i]);
    }
    for(int i=0;i<2;i++){ 
        extrairCarta(&head,&tail,&arrayJogador[i]);
    }
    printf("\n");
    printf("Carta do dealer: %s",arrayDealer[0].carta);
    printf("\n");
    for(int i=0;i<2;i++){
        printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
    }
    printf("\n");

    int pontoDealer = calcularPontuacao(arrayDealer, 2);
    int pontoJogador = calcularPontuacao(arrayJogador, 2);

    int contadorDeCartas=2;
    int contadorRodadas = 0;

    while(pontoDealer<21 && pontoJogador<21 && contadorRodadas<=4){
        if(pontoJogador>21){
            printf("Pontos estourados! Tente na próxima!");
            resetarJogo(&head, &tail); //
            adicionandoCartas(&head,&tail); //
            //chamar função de dar free e logo depois adicionar
            for(int i=0;i<2;i++){ 
                extrairCarta(&head,&tail,&arrayDealer[i]);
            }
            for(int i=0;i<2;i++){ 
                extrairCarta(&head,&tail,&arrayJogador[i]);
            }
            printf("\n");
            printf("Carta do dealer: %s",arrayDealer[0].carta);
            printf("\n");
            for(int i=0;i<2;i++){
                printf("%s e ",arrayJogador[i].carta);
            }
            printf("\n");
            contadorDeCartas=2;
        }else if(pontoJogador<21){
            int escolha;
            printf("\n--------------------------------------------------");
            printf("\n%s, você deseja:\n[1] - pegar mais uma carta\n[2] - manter a mão atual\n[3] - desistir (você irá perder 0,5 ponto)\n[4] - verificar novamente a carta do Dealer\n[5] - consultar saldo de pontos\n",player.nome);
            printf("Digite a sua escolha: ");
            scanf("%d",&escolha);
            printf("--------------------------------------------------\n");
            if(escolha==1){
                for(int i=0;i<1;i++){ 
                    extrairCarta(&head,&tail,&arrayJogador[contadorDeCartas]);
                    contadorDeCartas++;
                }
                printf("--------------------------------------\n");
                printf("|  A carta que você recebeu foi: %s  |\n",arrayJogador[contadorDeCartas-1].carta);
                printf("--------------------------------------\n");
                for(int i=0;i<contadorDeCartas;i++){
                    printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                }
                printf("\n");
                int pontoJogador;
                pontoJogador = calcularPontuacao(arrayJogador, contadorDeCartas);
                if(pontoJogador>21){
                    printf("--------------------------------------\n");
                    printf("|           Você perdeu!              |\n");
                    printf("--------------------------------------\n");
                    scoreJogador--;
                    resetarJogo(&head, &tail); //
                    adicionandoCartas(&head,&tail); //
                    //chamar função de dar free e logo depois adicionar
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayDealer[i]);
                    }
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayJogador[i]);
                    }
                    printf("\n");
                    printf("Carta do dealer: %s",arrayDealer[0].carta);
                    printf("\n");
                    for(int i=0;i<2;i++){
                        printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                    }
                    printf("\n");
                    contadorDeCartas=2;
                    if(pontoDealer==21 && pontoJogador==21){
                        printf("--------------------------------------\n");
                        printf("|      Houve um empate na rodada 1    |\n");
                        printf("--------------------------------------\n");
                        resetarJogo(&head, &tail); //
                        adicionandoCartas(&head,&tail); //
                        //chamar função de dar free e logo depois adicionar
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayDealer[i]);
                        }
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayJogador[i]);
                        }
                        printf("\n");
                        for(int i=0;i<2;i++){ 
                            printf("%s e ",arrayDealer[i].carta);
                        }
                        printf("\n");
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                        contadorDeCartas=2;
                    }else if(pontoDealer==21){
                        printf("--------------------------------------\n");
                        printf("|            Dealer venceu!           |\n");
                        printf("--------------------------------------\n");
                        resetarJogo(&head, &tail); //
                        adicionandoCartas(&head,&tail); //
                        //chamar função de dar free e logo depois adicionar
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayDealer[i]);
                        }
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayJogador[i]);
                        }
                        printf("\n");
                        for(int i=0;i<2;i++){ 
                            printf("%s e ",arrayDealer[i].carta);
                        }
                        printf("\n");
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                        scoreDealer++;
                        contadorDeCartas=2;
                    }else if(pontoJogador==21){
                        printf("--------------------------------------\n");
                        printf("|              %s venceu!             |\n",player.nome);
                        printf("--------------------------------------\n");
                        resetarJogo(&head, &tail); //
                        adicionandoCartas(&head,&tail); //
                        //chamar função de dar free e logo depois adicionar
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayDealer[i]);
                        }
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayJogador[i]);
                        }
                        printf("\n");
                        for(int i=0;i<2;i++){ 
                            printf("%s e ",arrayDealer[i].carta);
                        }
                        printf("\n");
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                        contadorDeCartas=2;
                        scoreJogador++;
                    }else if(pontoJogador>21){
                        printf("---------------------------------------\n");
                        printf("| Pontos estourados! Tente na próxima! |\n");
                        printf("---------------------------------------\n");
                        resetarJogo(&head, &tail); //
                        adicionandoCartas(&head,&tail); //
                        //chamar função de dar free e logo depois adicionar
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayDealer[i]);
                        }
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayJogador[i]);
                        }
                        printf("\n");
                        for(int i=0;i<2;i++){ 
                            printf("%s e ",arrayDealer[i].carta);
                        }
                        printf("\n");
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                        contadorDeCartas=2;
                    }else if(pontoDealer>21){
                        printf("---------------------------------------\n");
                        printf("|Pontos do dealer estourados! Parabéns!|\n");
                        printf("---------------------------------------\n");
                        resetarJogo(&head, &tail); //
                        adicionandoCartas(&head,&tail); //
                        //chamar função de dar free e logo depois adicionar
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayDealer[i]);
                        }
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayJogador[i]);
                        }
                        printf("\n");
                        for(int i=0;i<2;i++){ 
                            printf("%s e ",arrayDealer[i].carta);
                        }
                        printf("\n");
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                        contadorDeCartas=2;
                    }
                    contadorRodadas++;
                }else if(pontoJogador==21){
                    printf("--------------------------------------\n");
                    printf("|         Parabéns, você venceu!      |\n");
                    printf("--------------------------------------\n");
                    scoreJogador++;
                    resetarJogo(&head, &tail); //
                    adicionandoCartas(&head,&tail); //
                    contadorDeCartas=2;
                    //chamar função de dar free e logo depois adicionar
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayDealer[i]);
                    }
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayJogador[i]);
                    }
                    printf("\n");
                    printf("Carta do dealer: %s",arrayDealer[0].carta);
                    printf("\n");
                    for(int i=0;i<contadorDeCartas;i++){
                        printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                    }
                    printf("\n");
                    if(pontoDealer==21 && pontoJogador==21){
                        printf("--------------------------------------\n");
                        printf("|      Houve um empate na rodada 1    |\n");
                        printf("--------------------------------------\n");
                        resetarJogo(&head, &tail); //
                        adicionandoCartas(&head,&tail); //
                        //chamar função de dar free e logo depois adicionar
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayDealer[i]);
                        }
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayJogador[i]);
                        }
                        printf("\n");
                        for(int i=0;i<2;i++){ 
                            printf("%s e ",arrayDealer[i].carta);
                        }
                        printf("\n");
                        // aqui vai a ordenação do array jogador
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                        contadorDeCartas=2;
                    }else if(pontoDealer==21){
                        printf("--------------------------------------\n");
                        printf("|            Dealer venceu!           |\n");
                        printf("--------------------------------------\n");
                        resetarJogo(&head, &tail); //
                        adicionandoCartas(&head,&tail); //
                        //chamar função de dar free e logo depois adicionar
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayDealer[i]);
                        }
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayJogador[i]);
                        }
                        printf("\n");
                        for(int i=0;i<2;i++){ 
                            printf("%s e ",arrayDealer[i].carta);
                        }
                        printf("\n");
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                        scoreDealer++;
                        contadorDeCartas=2;
                    }else if(pontoJogador==21){
                        printf("--------------------------------------\n");
                        printf("|              %s venceu!             |\n",player.nome);
                        printf("--------------------------------------\n");
                        resetarJogo(&head, &tail); //
                        adicionandoCartas(&head,&tail); //
                        //chamar função de dar free e logo depois adicionar
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayDealer[i]);
                        }
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayJogador[i]);
                        }
                        printf("\n");
                        for(int i=0;i<2;i++){ 
                            printf("%s e ",arrayDealer[i].carta);
                        }
                        printf("\n");
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                        scoreJogador++;
                        contadorDeCartas=2;
                    }else if(pontoJogador>21){
                        printf("---------------------------------------\n");
                        printf("| Pontos estourados! Tente na próxima! |\n");
                        printf("---------------------------------------\n");
                        resetarJogo(&head, &tail); //
                        adicionandoCartas(&head,&tail); //
                        //chamar função de dar free e logo depois adicionar
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayDealer[i]);
                        }
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayJogador[i]);
                        }
                        printf("\n");
                        for(int i=0;i<2;i++){ 
                            printf("%s e ",arrayDealer[i].carta);
                        }
                        printf("\n");
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                        contadorDeCartas=2;
                    }else if(pontoDealer>21){
                        printf("---------------------------------------\n");
                        printf("|Pontos do dealer estourados! Parabéns!|\n");
                        printf("---------------------------------------\n");
                        resetarJogo(&head, &tail); //
                        adicionandoCartas(&head,&tail); //
                        //chamar função de dar free e logo depois adicionar
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayDealer[i]);
                        }
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayJogador[i]);
                        }
                        printf("\n");
                        for(int i=0;i<2;i++){ 
                            printf("%s e ",arrayDealer[i].carta);
                        }
                        printf("\n");
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                        contadorDeCartas=2;
                    }
                    contadorRodadas++;
                }
            }else if(escolha==2){
                printf("--------------------------------------------------------------\n");
                printf("                     Sua mão é: ");
                for(int i=0;i<contadorDeCartas;i++){
                            if(i==contadorDeCartas - 1) printf("%s\n",arrayJogador[i].carta);
                            else printf("%s e ",arrayJogador[i].carta);
                    }
                printf("--------------------------------------------------------------\n");
            }else if(escolha==3){
                printf("Seu score era %.2f e passou a ser %.2f",scoreJogador,scoreJogador-0.5);
                scoreJogador = scoreJogador - 0.5;
                resetarJogo(&head, &tail); //
                adicionandoCartas(&head,&tail); //
                //chamar função de dar free e logo depois adicionar
                for(int i=0;i<2;i++){ 
                    extrairCarta(&head,&tail,&arrayDealer[i]);
                }
                for(int i=0;i<2;i++){ 
                    extrairCarta(&head,&tail,&arrayJogador[i]);
                }
                printf("\n");
                for(int i=0;i<2;i++){ 
                    printf("%s e ",arrayDealer[i].carta);
                }
                printf("\n");
                for(int i=0;i<2;i++){
                    printf("%s e ",arrayJogador[i].carta);
                }
                printf("\n");
                contadorDeCartas=2;
                if(pontoDealer==21 && pontoJogador==21){
                    printf("--------------------------------------\n");
                    printf("|      Houve um empate na rodada 1    |\n");
                    printf("--------------------------------------\n");
                    resetarJogo(&head, &tail); //
                    adicionandoCartas(&head,&tail); //
                    //chamar função de dar free e logo depois adicionar
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayDealer[i]);
                    }
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayJogador[i]);
                    }
                    printf("\n");
                    printf("Carta do dealer: %s",arrayDealer[0].carta);
                    printf("\n");
                    for(int i=0;i<2;i++){
                        printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                    }
                    printf("\n");
                    contadorDeCartas=2;
                }else if(pontoDealer==21){
                    printf("--------------------------------------\n");
                    printf("|            Dealer venceu!           |\n");
                    printf("--------------------------------------\n");
                    resetarJogo(&head, &tail); //
                    adicionandoCartas(&head,&tail); //
                    //chamar função de dar free e logo depois adicionar
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayDealer[i]);
                    }
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayJogador[i]);
                    }
                    printf("\n");
                    printf("Carta do dealer: %s",arrayDealer[0].carta);
                    printf("\n");
                    for(int i=0;i<2;i++){
                        printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                    }
                    printf("\n");
                    scoreDealer++;
                    contadorDeCartas=2;
                }else if(pontoJogador==21){
                    printf("--------------------------------------\n");
                    printf("|              %s venceu!             |\n",player.nome);
                    printf("--------------------------------------\n");
                    resetarJogo(&head, &tail); //
                    adicionandoCartas(&head,&tail); //
                    //chamar função de dar free e logo depois adicionar
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayDealer[i]);
                    }
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayJogador[i]);
                    }
                    printf("\n");
                    printf("Carta do dealer: %s",arrayDealer[0].carta);
                    printf("\n");
                    for(int i=0;i<2;i++){
                        printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                    }
                    printf("\n");
                    scoreJogador++;
                    contadorDeCartas=2;
                }else if(pontoJogador>21){
                    printf("---------------------------------------\n");
                    printf("| Pontos estourados! Tente na próxima! |\n");
                    printf("---------------------------------------\n");
                    resetarJogo(&head, &tail); //
                    adicionandoCartas(&head,&tail); //
                    //chamar função de dar free e logo depois adicionar
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayDealer[i]);
                    }
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayJogador[i]);
                    }
                    printf("\n");
                    printf("Carta do dealer: %s",arrayDealer[0].carta);
                    printf("\n");
                    for(int i=0;i<2;i++){
                        printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                    }
                    printf("\n");
                    contadorDeCartas=2;
                }else if(pontoDealer>21){
                    printf("---------------------------------------\n");
                    printf("|Pontos do dealer estourados! Parabéns!|\n");
                    printf("---------------------------------------\n");
                    resetarJogo(&head, &tail); //
                    adicionandoCartas(&head,&tail); //
                    //chamar função de dar free e logo depois adicionar
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayDealer[i]);
                    }
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayJogador[i]);
                    }
                    printf("\n");
                    printf("Carta do dealer: %s",arrayDealer[0].carta);
                    printf("\n");
                    for(int i=0;i<2;i++){
                        printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                    }
                    printf("\n");
                    contadorDeCartas=2;
                }
                contadorRodadas++;
            }else if(escolha==4){
                printf("\nCarta do Dealer: %s",arrayDealer[0].carta);
            }else if(escolha==5){
                int pontoJogador;
                pontoJogador = calcularPontuacao(arrayJogador, contadorDeCartas);
                printf("\nSomatório cartas Jogador: %d\n",pontoJogador);
            }else{
                printf("Resposta inválida! Escolha [1], [2], [3], [4] ou [5]!");
                continue;
            }
        }
    }

    printf("\n");
    player.pontuacao = scoreJogador;  
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
    while(cabeca!=NULL && posicao<=3){
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

int contarCartas(struct deck *head){
    if(head == NULL){
        return 0;
    } 
    struct deck *temp = head;
    int cont=0;
    do{
        cont++;
        temp = temp->prox;
    }while(temp!=head);
    return cont;
}

void extrairCarta(struct deck **head, struct deck **tail, struct carta *destino){
    int totalCartas = contarCartas(*head);
    if(totalCartas==0){
        return;
    } 
    int cartaIndex = rand()%totalCartas;
    struct deck *temp = *head;

    for(int i=0;i<cartaIndex;i++){
        temp = temp->prox;
    }
    strcpy(destino->carta, temp->carta);
    if(temp->prox==temp){
        *head = *tail = NULL;
    }else{
        temp->ant->prox = temp->prox;
        temp->prox->ant = temp->ant;
        if(temp==*head){
            *head = temp->prox;
        } 
        if(temp==*tail){
            *tail = temp->ant;
        } 
    }
    free(temp);
}

int calcularPontuacao(struct carta array[], int numCartas) {
    int soma = 0;
    char valor;

    for(int i=0;i<numCartas;i++){
        valor = array[i].carta[0];
        if(valor=='A'){
            soma+=11; 
        }else if(valor=='J'||valor=='Q'||valor=='K'){
            soma+=10;
        }else if(valor=='1'&&array[i].carta[1]=='0'){
            soma+=10; 
        }else{
            soma+=valor-'0'; 
        }
    }

    return soma;
}
