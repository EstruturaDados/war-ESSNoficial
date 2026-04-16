#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL 5

// Struct dos territórios
typedef struct{
    char nome[30];
    char cor[10];
    int tropas;
}Territorio;


// Cadastro inicial
void cadastrarTerritorios(Territorio *mapa){

    for(int i=0;i<TOTAL;i++){
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL 5
#define TOTAL_MISSOES 5

// Struct dos territórios
typedef struct{
    char nome[30];
    char cor[10];
    int tropas;
}Territorio;


// ================= MISSÕES =================

// Vetor de missões
char *missoes[TOTAL_MISSOES] = {
    "Conquistar 3 territorios",
    "Possuir 10 tropas no total",
    "Eliminar o exercito Vermelho",
    "Controlar pelo menos 2 territorios",
    "Conquistar qualquer territorio inimigo"
};


// Sorteia missão
void atribuirMissao(char *destino, char *missoes[], int totalMissoes){

    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}


// Exibe missão com cor do jogador
void exibirMissao(char *missao, char *cor){

    printf("\n--- SUA MISSAO (Exercito %s) ---\n", cor);
    printf("%s\n", missao);
}


// Verifica missão (simples)
int verificarMissao(char *missao, Territorio *mapa, int tamanho){

    int totalTropas = 0;

    for(int i=0;i<tamanho;i++){
        totalTropas += mapa[i].tropas;
    }

    if(strcmp(missao,"Possuir 10 tropas no total")==0){
        return totalTropas >= 10;
    }

    if(strcmp(missao,"Eliminar o exercito Vermelho")==0){

        for(int i=0;i<tamanho;i++){
            if(strcmp(mapa[i].cor,"Vermelho")==0){
                return 0;
            }
        }
        return 1;
    }

    if(strcmp(missao,"Controlar pelo menos 2 territorios")==0){
        return 1; // simplificado
    }

    if(strcmp(missao,"Conquistar 3 territorios")==0){
        return 1; // simplificado
    }

    if(strcmp(missao,"Conquistar qualquer territorio inimigo")==0){
        return 1; // simplificado
    }

    return 0;
}


// ================= JOGO =================

// Cadastro
void cadastrarTerritorios(Territorio *mapa){

    for(int i=0;i<TOTAL;i++){

        printf("\n--- Cadastrando Territorio %d ---\n",i+1);

        printf("Nome: ");
        scanf("%s",mapa[i].nome);

        printf("Cor do exercito: ");
        scanf("%s",mapa[i].cor);

        printf("Numero de tropas: ");
        scanf("%d",&mapa[i].tropas);
    }
}


// Exibir mapa
void exibirTerritorios(Territorio *mapa){

    printf("\n====================================\n");
    printf(" MAPA DO MUNDO\n");
    printf("====================================\n");

    for(int i=0;i<TOTAL;i++){

        printf("\n%d. %s (Exercito: %s, Tropas: %d)",
        i+1,
        mapa[i].nome,
        mapa[i].cor,
        mapa[i].tropas);
    }

    printf("\n");
}


// Ataque
void atacar(Territorio *atacante, Territorio *defensor){

    int dadoAtacante = rand()%6+1;
    int dadoDefensor = rand()%6+1;

    printf("\n--- RESULTADO DA BATALHA ---\n");

    // tudo em uma linha
    printf("Ataque (%s): %d | Defesa (%s): %d\n",
    atacante->nome,
    dadoAtacante,
    defensor->nome,
    dadoDefensor);


    if(dadoAtacante > dadoDefensor){

        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");

        defensor->tropas--;

        if(defensor->tropas <=0){

            printf("CONQUISTA! %s agora pertence ao exercito %s\n", defensor->nome, atacante->cor);

            strcpy(defensor->cor,atacante->cor);
            defensor->tropas = 1;

            if(atacante->tropas >1)
                atacante->tropas--;
        }
    }
    else if(dadoDefensor > dadoAtacante){

        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");

        atacante->tropas--;

        if(atacante->tropas <0)
            atacante->tropas=0;
    }
    else{

        printf("EMPATE! Nenhuma tropa foi perdida.\n");
    }
}


// Menu
int menu(){

    int opcao;

    printf("\n--- MENU DE ACOES ---\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair\n");

    printf("Escolha sua acao: ");
    scanf("%d",&opcao);

    return opcao;
}


// Liberação memória
void liberarMemoria(Territorio *mapa, char *missao){

    free(mapa);
    free(missao);
}


// ================= MAIN =================

int main(){

    Territorio *mapa;
    char *missao;
    char corJogador[10];

    int atacante, defensor, opcao;

    srand(time(NULL));

    mapa = calloc(TOTAL,sizeof(Territorio));
    missao = (char*) malloc(100*sizeof(char));

    if(mapa==NULL || missao==NULL){
        printf("Erro de memoria");
        return 1;
    }

    printf("====================================\n");
    printf(" WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("====================================\n");

    cadastrarTerritorios(mapa);

    // jogador será o território 1 (simplificação)
    strcpy(corJogador, mapa[0].cor);

    // atribui missão
    atribuirMissao(missao, missoes, TOTAL_MISSOES);

    // tela inicial
    exibirTerritorios(mapa);
    exibirMissao(missao, corJogador);

    while(1){

        opcao = menu();

        if(opcao == 0){
            break;
        }

        else if(opcao == 1){

            printf("\nEscolha o territorio atacante: ");
            scanf("%d",&atacante);

            printf("Escolha o territorio defensor: ");
            scanf("%d",&defensor);

            if(atacante<1 || atacante>5 ||
               defensor<1 || defensor>5){

                printf("Escolha invalida!\n");
                continue;
            }

            if(strcmp(mapa[atacante-1].cor,
                      mapa[defensor-1].cor)==0){

                printf("Nao pode atacar mesma cor!\n");
                continue;
            }

            atacar(&mapa[atacante-1],
                   &mapa[defensor-1]);

            exibirTerritorios(mapa);
        }

        else if(opcao == 2){

            if(verificarMissao(missao,mapa,TOTAL)){

                printf("\nParabéns, a missão foi cumprida!\n");
            }
            else{

                printf("\nVocê ainda não cumpriu sua missão. Continue a lutar\n");
            }
        }

        else{

            printf("Opcao invalida!\n");
        }
    }

    liberarMemoria(mapa, missao);

    printf("\nEncerrando o jogo...\n");
    printf("Memória liberada com sucesso.");

    return 0;
}
