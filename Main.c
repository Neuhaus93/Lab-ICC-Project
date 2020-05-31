#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#define NUMACOES 4


int showMenu();
void cadastroUsuario();
void cadastroProduto();
void fluxoProduto();
void pause();


void main() {

    int acao = 4;

    acao = showMenu();

    while (acao != 4) {

        switch(acao) {
            case 1:
                cadastroUsuario();
                break;

            case 2:
                cadastroProduto();
                break;

            case 3:
                fluxoProduto();
                break;

            default:
                printf("Erro no programa!");
                return;
        }

        acao = showMenu();
    }

    printf("Finalizando o programa...\n\n");

    return;
}

void fluxoProduto() {
    printf("Fluxo de produto!");
}


void cadastroProduto() {
    FILE *arq;
    char produto[123], novoProdutoNome[60], novoProduto[123];
    char novoProdutoPreco[60];
    int ehNovoProduto = 1, counter = 0;

    printf("====================\n\n");
    printf("Cadastro de produto!\n\n");
    printf("====================\n\n");

    if((arq = fopen("produtos.txt", "r+"))==NULL) {
        printf("\nErro abrindo o arquivo.\n");
        return;
    }

    printf("Digite o nome do produto: ");
    scanf("%s", &novoProdutoNome);
    printf("Digite o preco do produto: ");
    scanf("%s", &novoProdutoPreco);

    strcpy(novoProduto, novoProdutoNome);
    strcat(novoProduto, " - ");
    strcat(novoProduto, novoProdutoPreco);
    strcat(novoProduto, " - ");
    strcat(novoProduto, "0");
    strcat(novoProduto, "\n");


    while( fgets (produto, 123, arq) != NULL ) {
        ehNovoProduto = strcmp(novoProduto, produto);
        if (ehNovoProduto == 0) {
            printf("\n--- Produto ja existe! ---");
            printf("\nVoltando para o menu inicial...");
            pause();
            break;
        }
    }

    if (ehNovoProduto != 0) {
        fputs(novoProduto, arq);
        printf("\nNovo produto adicionado!!");
        pause();
    }

    fclose(arq);

    system("cls");

}

void cadastroUsuario() {

    FILE *arq;
    char usuario[123], novoUsuarioNome[60];
    char novoUsuarioTelefone[60], novoUsuario[123];
    int isNewUser = 1, counter = 0;

    printf("====================\n\n");
    printf("Cadastro de usuario!\n\n");
    printf("====================\n\n");

    if((arq = fopen("usuarios.txt", "r+"))==NULL) {
        printf("\nErro abrindo o arquivo.\n");
        return;
    }

    printf("Digite o nome do usuario: ");
    scanf("%s", &novoUsuarioNome);
    printf("Digite o telefone de %s: ", novoUsuarioNome);
    scanf("%s", &novoUsuarioTelefone);

    strcpy(novoUsuario, novoUsuarioNome);
    strcat(novoUsuario, " - ");
    strcat(novoUsuario, novoUsuarioTelefone);
    strcat(novoUsuario, "\n");


    while( fgets (usuario, 123, arq) != NULL ) {
        isNewUser = strcmp(novoUsuario, usuario);
        if (isNewUser == 0) {
            printf("\n--- Usuario ja existe! ---");
            printf("\nVoltando para o menu inicial...");
            pause();
            break;
        }
    }

    if (isNewUser != 0) {
        fputs(novoUsuario, arq);
        printf("\nNovo usuario adicionado!!");
        pause();
    }

    fclose(arq);

    system("cls");
}

int showMenu() {

    int acao, aux;
    char term;

    printf("Escolha a acao desejada:\n");
    printf("1. Cadastro de usuario\n");
    printf("2. Cadastro de produto\n");
    printf("3. Adicionar fluxo de produtos\n");
    printf("4. Sair do programa\n\n");

    printf("Digite o numero correspondente a acao: ");
    aux = scanf("%d%c", &acao, &term);

    while(aux != 2 || term != '\n') {
        printf("\nO valor digitado nao corresponde a um inteiro.\n");
        printf("Digite novamente a acao desejada: ");
        fflush(stdin);
        aux = scanf("%d%c", &acao, &term);


        while (acao < 1 || acao > NUMACOES) {
            printf("\nNumero digitado nao corresponde a uma acao existente.\n");
            printf("Digite novamente a acao desejada: ");
            fflush(stdin);
            aux = scanf("%d%c", &acao, &term);
        }

    }

    system("cls");
    return acao;
}

void pause () {
  printf ( "\n\nPressione qualquer tecla para continuar...\n\n" );
  getch();
}
