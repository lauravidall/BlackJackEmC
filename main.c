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
    char nome[50];
    float pontuacao;
};

struct highscore{
    struct jogador player;
    struct highscore *prox;
};

void ordenarLista(struct highscore **cabeca, struct jogador player);
void escreverLista(struct highscore *cabeca, FILE *fptr);
void printarLista(struct highscore *cabeca);
void freeLista(struct highscore **cabeca);

void inserirNaListaCirc(struct deck **head, struct deck **tail, char carta[]);
void printarListaCirc(struct deck *head, struct deck *tail);
void resetarJogo(struct deck **head, struct deck **tail);
void excluirCarta(struct deck **head, struct deck **tail, char carta[]);
void adicionandoCartas(struct deck **head, struct deck **tail);
int contarCartas(struct deck *head);
void extrairCarta(struct deck **head, struct deck **tail, struct carta *destino);
int calcularPontuacao(struct carta array[], int numCartas);

void ordenarCartasDaMao(struct carta array[], int contadorDeCartas);
int valorCarta(char *c);

int main(){

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

    int contadorDeCartas=2;
    int contadorRodadas = 0;
    ordenarCartasDaMao(arrayJogador, contadorDeCartas);

    for(int i=0;i<2;i++){
        printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
    }
    printf("\n");

    int pontoDealer = calcularPontuacao(arrayDealer, 2);
    int pontoJogador = calcularPontuacao(arrayJogador, 2);

    while(contadorRodadas<4){
        printf("\nRodada %i/4\n", contadorRodadas+1);
        printf("Sua pontuação: %.1f\n", scoreJogador);
        if(pontoJogador==21){
           printf("--------------------------------------\n");
            printf("|        Parabéns, você venceu!     |\n");
            printf("-------------------------------------\n");
            scoreJogador++;
            contadorRodadas++;
            resetarJogo(&head, &tail); 
            adicionandoCartas(&head,&tail); 
            
            for(int i=0;i<2;i++){ 
                extrairCarta(&head,&tail,&arrayDealer[i]);
            }
            for(int i=0;i<2;i++){ 
                extrairCarta(&head,&tail,&arrayJogador[i]);
            }
            contadorDeCartas=2;
            pontoDealer=calcularPontuacao(arrayDealer, 2);
            pontoJogador=calcularPontuacao(arrayJogador, contadorDeCartas);
            printf("\n");
            printf("Carta do dealer: %s",arrayDealer[0].carta);
            printf("\n");
            ordenarCartasDaMao(arrayJogador, contadorDeCartas);
            for(int i=0;i<contadorDeCartas;i++){
                printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
            }
            printf("\n");
        }else if(pontoJogador>21){
            printf("Pontos estourados! Tente na próxima!");
            scoreJogador--;
            contadorRodadas++;
            resetarJogo(&head, &tail); 
            adicionandoCartas(&head,&tail); 
            
            for(int i=0;i<2;i++){ 
                extrairCarta(&head,&tail,&arrayDealer[i]);
            }
            for(int i=0;i<2;i++){ 
                extrairCarta(&head,&tail,&arrayJogador[i]);
            }
            contadorDeCartas=2;
            pontoDealer = calcularPontuacao(arrayDealer, 2);
            pontoJogador = calcularPontuacao(arrayJogador, contadorDeCartas);
            printf("\n");
            printf("Carta do dealer: %s",arrayDealer[0].carta);
            printf("\n");
            for(int i=0;i<contadorDeCartas;i++){
                printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
            }
            printf("\n");
        }else if(pontoDealer==21){
            printf("--------------------------------------\n");
            printf("|            Dealer venceu!           |\n");
            printf("--------------------------------------\n");
            printf("Mão vitoriosa do dealer:\n");
            for(int i=0;i<2;i++){
                if(i==1) printf("%s",arrayDealer[i].carta);
                else printf("%s e ",arrayDealer[i].carta);
            }
            scoreJogador--;
            if (scoreJogador < 0) scoreJogador = 0;
            contadorRodadas++;

            resetarJogo(&head, &tail); 
            adicionandoCartas(&head,&tail); 
            
            for(int i=0;i<2;i++){ 
                extrairCarta(&head,&tail,&arrayDealer[i]);
            }
            for(int i=0;i<2;i++){ 
                extrairCarta(&head,&tail,&arrayJogador[i]);
            }
            contadorDeCartas = 2;
            pontoDealer = calcularPontuacao(arrayDealer, 2);
            pontoJogador = calcularPontuacao(arrayJogador, contadorDeCartas);
            printf("\n");
            ordenarCartasDaMao(arrayJogador, contadorDeCartas);
            for(int i=0;i<contadorDeCartas;i++){
                printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
            }
            printf("\n");
        }else if(pontoJogador<21){
            int escolha;
            printf("\n--------------------------------------------------");
            printf("\n%s, Você deseja:\n[1] - Pegar mais uma carta\n[2] - Manter a mão atual\n[3] - Desistir (você irá perder 0,5 ponto)\n[4] - Verificar novamente a carta do Dealer\n",player.nome);
            printf("Digite a sua escolha: ");
            scanf("%d",&escolha);
            printf("--------------------------------------------------\n");
            if(escolha==1){
                extrairCarta(&head,&tail,&arrayJogador[contadorDeCartas]);
                contadorDeCartas++;
                printf("--------------------------------------\n");
                printf("|  A carta que você recebeu foi: %s  |\n",arrayJogador[contadorDeCartas-1].carta);
                printf("--------------------------------------\n");
                ordenarCartasDaMao(arrayJogador, contadorDeCartas); 
                for(int i=0;i<contadorDeCartas;i++){
                    printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                }
                printf("\n");
                pontoJogador = calcularPontuacao(arrayJogador, contadorDeCartas);
                if(pontoJogador>21){
                    printf("----------------------------------------\n");
                    printf("| Pontos estourados! Tente na próxima! |\n");
                    printf("----------------------------------------\n");
                    scoreJogador--;
                    if (scoreJogador < 0) scoreJogador = 0;
                    contadorRodadas++;
                    resetarJogo(&head, &tail); 
                    adicionandoCartas(&head,&tail);
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayDealer[i]);
                    }
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayJogador[i]);
                    }
                    contadorDeCartas=2;
                    pontoDealer = calcularPontuacao(arrayDealer, 2);
                    pontoJogador = calcularPontuacao(arrayJogador, contadorDeCartas);
                    printf("\n");
                    printf("Carta do dealer: %s",arrayDealer[0].carta);
                    printf("\n");
                    ordenarCartasDaMao(arrayJogador, contadorDeCartas);
                    for(int i=0;i<contadorDeCartas;i++){
                        printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                    }
                    printf("\n");
                }else if(pontoJogador==21){
                    printf("--------------------------------------\n");
                    printf("|         Parabéns, você venceu!     |\n");
                    printf("--------------------------------------\n");
                    scoreJogador++;
                    resetarJogo(&head, &tail); 
                    adicionandoCartas(&head,&tail); 
                    
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayDealer[i]);
                    }
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayJogador[i]);
                    }
                    contadorDeCartas=2;
                    pontoDealer=calcularPontuacao(arrayDealer, 2);
                    pontoJogador=calcularPontuacao(arrayJogador, contadorDeCartas);
                    printf("\n");
                    printf("Carta do dealer: %s",arrayDealer[0].carta);
                    printf("\n");
                    ordenarCartasDaMao(arrayJogador, contadorDeCartas);
                    for(int i=0;i<contadorDeCartas;i++){
                        printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                    }
                    printf("\n");
                    if(pontoDealer==21 && pontoJogador==21){
                        printf("--------------------------------------\n");
                        printf("|      Houve um empate na rodada      |\n");
                        printf("--------------------------------------\n");
                        resetarJogo(&head, &tail); 
                        adicionandoCartas(&head,&tail);
                        
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
                        
                        ordenarCartasDaMao(arrayJogador, contadorDeCartas); 
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                        contadorDeCartas=2;
                    }else if(pontoJogador==21){
                        printf("--------------------------------------\n");
                        printf("|              %s venceu!            |\n",player.nome);
                        printf("--------------------------------------\n");
                        scoreJogador++;
                        resetarJogo(&head, &tail);
                        adicionandoCartas(&head,&tail); 
                        
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
                        ordenarCartasDaMao(arrayJogador, contadorDeCartas);
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                        contadorDeCartas=2;
                    }else if(pontoJogador>21){
                        printf("----------------------------------------\n");
                        printf("| Pontos estourados! Tente na próxima! |\n");
                        printf("----------------------------------------\n");
                        scoreJogador--;
                        if (scoreJogador < 0) scoreJogador = 0;
                        resetarJogo(&head, &tail); 
                        adicionandoCartas(&head,&tail); 
                        
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
                        ordenarCartasDaMao(arrayJogador, contadorDeCartas); 
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                        contadorDeCartas=2;
                    }else if(pontoDealer>21){
                        printf("---------------------------------------\n");
                        printf("|Pontos do dealer estourados! Parabéns!|\n");
                        printf("---------------------------------------\n");
                        scoreJogador++;
                        resetarJogo(&head, &tail); 
                        adicionandoCartas(&head,&tail); 
                        
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
                        ordenarCartasDaMao(arrayJogador, contadorDeCartas); 
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                        contadorDeCartas=2;
                    }
                    contadorRodadas++;
                }
            }else if(escolha==2){
                ordenarCartasDaMao(arrayJogador, contadorDeCartas);
                printf("--------------------------------------------------------------\n");
                printf("                     Sua mão é: ");
                for(int i=0;i<contadorDeCartas;i++){
                        if(i==contadorDeCartas - 1) printf("%s\n",arrayJogador[i].carta);
                        else printf("%s e ",arrayJogador[i].carta);
                    }
                printf("--------------------------------------------------------------\n");
                printf("Sua mão está com a pontuação: %i\n", pontoJogador);
                printf("Deseja contar as cartas agora?\nSua mão será comparada com a do dealer e a mais próxima de 21 vencerá [S/N]\n");
                printf("Digite a sua decisão: ");
                char decisao;
                scanf(" %c", &decisao);
                if(decisao == 'S' || decisao == 's'){
                    char vencedor = (pontoJogador > pontoDealer) ? 'J' : 'D';
                    if(vencedor == 'J'){
                        printf("--------------------------------------\n");
                        printf("|              %s venceu!            |\n",player.nome);
                        printf("--------------------------------------\n");
                        scoreJogador++;
                        resetarJogo(&head, &tail);
                        adicionandoCartas(&head,&tail);
                        
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayDealer[i]);
                        }
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayJogador[i]);
                        }
                        contadorDeCartas = 2;
                        pontoDealer = calcularPontuacao(arrayDealer, 2);
                        pontoJogador = calcularPontuacao(arrayJogador, contadorDeCartas);
                        printf("\n");
                        printf("Carta do dealer: %s",arrayDealer[0].carta);
                        printf("\n");
                        ordenarCartasDaMao(arrayJogador, contadorDeCartas);
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                    } 
                    else{
                        printf("--------------------------------------\n");
                        printf("|            Dealer venceu!          |\n");
                        printf("--------------------------------------\n");
                        printf("Pontuação vitoriosa do dealer:\n%i\n", pontoDealer);
                        printf("Mão vitoriosa do dealer:\n");
                        for(int i=0;i<2;i++){ 
                            if (i==1) printf("%s",arrayDealer[i].carta);
                            else printf("%s e ",arrayDealer[i].carta);
                        }
                        scoreJogador--;
                        if (scoreJogador < 0) scoreJogador = 0;
                        resetarJogo(&head, &tail); 
                        adicionandoCartas(&head,&tail); 
                        
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayDealer[i]);
                        }
                        for(int i=0;i<2;i++){ 
                            extrairCarta(&head,&tail,&arrayJogador[i]);
                        }
                        contadorDeCartas = 2;
                        pontoDealer = calcularPontuacao(arrayDealer, 2);
                        pontoJogador = calcularPontuacao(arrayJogador, contadorDeCartas);
                        printf("\n");
                        printf("Carta do dealer: %s",arrayDealer[0].carta);
                        printf("\n");
                        ordenarCartasDaMao(arrayJogador, contadorDeCartas);
                        for(int i=0;i<contadorDeCartas;i++){
                            printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                        }
                        printf("\n");
                    }
                    contadorRodadas++;
                }
            }else if(escolha==3){
                scoreJogador = scoreJogador - 0.5;
                if (scoreJogador < 0) scoreJogador = 0;
                contadorRodadas++;
                resetarJogo(&head, &tail);
                adicionandoCartas(&head,&tail);
                
                for(int i=0;i<2;i++){ 
                    extrairCarta(&head,&tail,&arrayDealer[i]);
                }
                for(int i=0;i<2;i++){ 
                    extrairCarta(&head,&tail,&arrayJogador[i]);
                }
                contadorDeCartas = 2;
                pontoDealer = calcularPontuacao(arrayDealer, 2);
                pontoJogador = calcularPontuacao(arrayJogador, contadorDeCartas);
                printf("\n");
                printf("Carta do dealer: %s",arrayDealer[0].carta);
                printf("\n");
                ordenarCartasDaMao(arrayJogador, contadorDeCartas);
                for(int i=0;i<contadorDeCartas;i++){
                    printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                }
                printf("\n");
                }else if(pontoJogador==21){
                    printf("--------------------------------------\n");
                    printf("|              %s venceu!            |\n",player.nome);
                    printf("--------------------------------------\n");
                    resetarJogo(&head, &tail); 
                    adicionandoCartas(&head,&tail); 
                    
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayDealer[i]);
                    }
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayJogador[i]);
                    }
                    printf("\n");
                    printf("Carta do dealer: %s",arrayDealer[0].carta);
                    printf("\n");
                    ordenarCartasDaMao(arrayJogador, contadorDeCartas); 
                    for(int i=0;i<2;i++){
                        printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                    }
                    printf("\n");
                    scoreJogador++;
                    contadorDeCartas=2;
                }else if(pontoJogador>21){
                    printf("----------------------------------------\n");
                    printf("| Pontos estourados! Tente na próxima! |\n");
                    printf("----------------------------------------\n");
                    resetarJogo(&head, &tail); 
                    adicionandoCartas(&head,&tail); 
                    
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayDealer[i]);
                    }
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayJogador[i]);
                    }
                    printf("\n");
                    printf("Carta do dealer: %s",arrayDealer[0].carta);
                    printf("\n");
                    ordenarCartasDaMao(arrayJogador, contadorDeCartas); 
                    for(int i=0;i<2;i++){
                        printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                    }
                    printf("\n");
                    contadorDeCartas=2;
                }else if(pontoDealer>21){
                    printf("---------------------------------------\n");
                    printf("|Pontos do dealer estourados! Parabéns!|\n");
                    printf("---------------------------------------\n");
                    scoreJogador++;
                    if (scoreJogador < 0) scoreJogador = 0;
                    contadorDeCartas=2;
                }else if(pontoJogador>21){
                    printf("----------------------------------------\n");
                    printf("| Pontos estourados! Tente na próxima! |\n");
                    printf("----------------------------------------\n");
                    resetarJogo(&head, &tail); 
                    adicionandoCartas(&head,&tail); 
                    
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayDealer[i]);
                    }
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayJogador[i]);
                    }
                    printf("\n");
                    printf("Carta do dealer: %s",arrayDealer[0].carta);
                    printf("\n");
                    ordenarCartasDaMao(arrayJogador, contadorDeCartas); 
                    for(int i=0;i<2;i++){
                        printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                    }
                    printf("\n");
                    contadorDeCartas=2;
                }else if(pontoDealer>21){
                    printf("---------------------------------------\n");
                    printf("|Pontos do dealer estourados! Parabéns!|\n");
                    printf("---------------------------------------\n");
                    resetarJogo(&head, &tail); 
                    adicionandoCartas(&head,&tail); 
                    
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayDealer[i]);
                    }
                    for(int i=0;i<2;i++){ 
                        extrairCarta(&head,&tail,&arrayJogador[i]);
                    }
                    printf("\n");
                    printf("Carta do dealer: %s",arrayDealer[0].carta);
                    printf("\n");
                    ordenarCartasDaMao(arrayJogador, contadorDeCartas); 
                    for(int i=0;i<2;i++){
                        printf("Carta de número %d do jogador: %s\n",i+1, arrayJogador[i].carta);
                    }
                    printf("\n");
                    contadorDeCartas=2;
                    contadorRodadas++;
            }else if(escolha==4){
                printf("\nCarta do Dealer: %s",arrayDealer[0].carta);
            }else{
                printf("Resposta inválida! Escolha [1], [2], [3] ou [4].");
            }
        }
    }
    printf("--------------------------------------\n");
    printf("|             Fim de Jogo!           |\n");
    printf("--------------------------------------\n");
    player.pontuacao = scoreJogador;
    printf("%s, sua PONTUAÇÃO foi: %.1f\n",player.nome, player.pontuacao);

    printf("\n");
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
    if(*cabeca==NULL || (*cabeca)->player.pontuacao<player.pontuacao){
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
        printf("Pontuação: %.1f\n", cabeca->player.pontuacao);
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

void excluirCarta(struct deck **head, struct deck **tail, char carta[]){ 
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

int valorCarta(char *c) {
    if (c[0] == '1' && c[1] == '0') {
        return 10;
    }else if (c[0] >= '1' && c[0] <= '9') {
        return c[0] - '0';  
    } else if (c[0] == 'J') {
        return 11;
    } else if (c[0] == 'Q') {
        return 12;
    } else if (c[0] == 'K') {
        return 13;
    } else if (c[0] == 'A') {
        return 14;
    }
    return -1; 
}

void ordenarCartasDaMao(struct carta array[], int contadorDeCartas) {
    int LEN = contadorDeCartas;
    for (int i = 1; i < LEN; i++) {
        int j = i;
        while (j > 0 && valorCarta(array[j].carta) < valorCarta(array[j - 1].carta)) {
            struct carta aux = array[j - 1];
            array[j - 1] = array[j];
            array[j] = aux;
            --j;
        }
    }
}