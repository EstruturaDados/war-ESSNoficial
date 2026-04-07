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

    printf("====================================\n");
    printf("    MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("====================================\n");

    for(int i=0;i<TOTAL;i++){

        printf("\n%d. %s (Exercito %s, Tropas: %d)",
        i+1,
        mapa[i].nome,
        mapa[i].cor,
        mapa[i].tropas);

    }

    printf("\n");
}


// Sistema de ataque
void atacar(Territorio *atacante, Territorio *defensor){

    int dadoAtacante = rand()%6+1;
    int dadoDefensor = rand()%6+1;

    printf("\n--- RESULTADO DA BATALHA ---\n");

    printf("O atacante %s (%s) rolou: %d\n",
    atacante->nome,
    atacante->cor,
    dadoAtacante);

    printf("O defensor %s (%s) rolou: %d\n",
    defensor->nome,
    defensor->cor,
    dadoDefensor);


    if(dadoAtacante > dadoDefensor){

        printf("\nVITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");

        defensor->tropas--;

        // conquista território
        if(defensor->tropas <=0){

            printf("CONQUISTA! O territorio %s foi conquistado pelo Exercito %s!\n",defensor->nome,atacante->cor);

            strcpy(defensor->cor,atacante->cor);

            defensor->tropas = 1;

            atacante->tropas--;
        }
    }
    else if(dadoDefensor > dadoAtacante){

        printf("\nVITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");

        atacante->tropas--;

        if(atacante->tropas <0)
        atacante->tropas=0;
    }
    else{

        printf("\nEMPATE! Nenhuma tropa perdida.\n");
    }

}


// Liberação memória
void liberarMemoria(Territorio *mapa){

    free(mapa);
}


// Verifica vitória do jogo
int verificarVitoria(Territorio *mapa){

    char corBase[10];

    strcpy(corBase,mapa[0].cor);

    for(int i=1;i<TOTAL;i++){

        if(strcmp(corBase,mapa[i].cor)!=0){

            return 0;
        }
    }

    return 1;
}



// MAIN
int main(){

    Territorio *mapa;

    int atacante;
    int defensor;

    srand(time(NULL));

    mapa = calloc(TOTAL,sizeof(Territorio));

    if(mapa==NULL){

        printf("Erro de memoria");

        return 1;
    }


    printf("====================================\n");
    printf(" WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("====================================\n");


    cadastrarTerritorios(mapa);


    while(1){

        exibirTerritorios(mapa);

        // verifica vitória
        if(verificarVitoria(mapa)){

            printf("\nUM EXERCITO DOMINOU O MUNDO!\n");

            printf("Vencedor: %s\n",mapa[0].cor);

            break;
        }


        printf("\n--- FASE DE ATAQUE ---\n");

        printf("Escolha o territorio atacante (1 a 5, ou 0 para sair): ");

        scanf("%d",&atacante);

        if(atacante==0)
        break;


        if(atacante<1 || atacante>5){

            printf("Escolha invalida!\n");

            continue;
        }


        if(mapa[atacante-1].tropas<=1){

            printf("Tropas insuficientes para atacar!\n");

            continue;
        }


        printf("Escolha o territorio defensor: ");

        scanf("%d",&defensor);


        if(defensor<1 || defensor>5){

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


        printf("\nPressione Enter para continuar para o proximo turno...");

        while(getchar()!='\n');

        getchar();

    }


    liberarMemoria(mapa);

    printf("\nJogo encerrado.\n");

    return 0;
}
