#include <stdio.h>
#include <string.h>

// Criação da struct Territorio
// Essa estrutura armazena o nome do território,
// a cor do exército e a quantidade de tropas
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {

    // Declaração do vetor que armazenará 5 territórios
    struct Territorio territorios[5];

    int i;

    // Laço para cadastro dos territórios
    for(i = 0; i < 5; i++) {

        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);

        // Entrada do nome do território
        printf("Nome do territorio: ");
        scanf("%s", territorios[i].nome);

        // Entrada da cor do exército
        printf("Cor do exercito (ex: Azul, Verde): ");
        scanf("%s", territorios[i].cor);

        // Entrada da quantidade de tropas
        printf("Numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados cadastrados
    
    printf("\nCadastro inicial concluido com sucesso!\n\n");
    
    printf("======================================\n");
    printf("     MAPA DO MUNDO - ESTADO ATUAL     \n");
    printf("======================================\n");

    // Laço para mostrar os dados armazenados
    for(i = 0; i < 5; i++) {

        printf("\nTERRITORIO %d:\n", i + 1);
        printf("  - Nome: %s\n", territorios[i].nome);
        printf("  - Cor do exercito: %s\n", territorios[i].cor);
        printf("  - Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
