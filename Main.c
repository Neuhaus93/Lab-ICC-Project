#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define NUMACOES 4


int showMenu();
int menuFluxo();
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
    FILE *produtos, *caixa;
    char produto[123];
    int acaoFluxo = 3;

    printf("====================\n\n");
    printf("Registrar fluxo de produto!\n\n");
    printf("====================\n\n");

    if((produtos = fopen("produtos.txt", "r+"))==NULL) {
        printf("\nErro abrindo o arquivo 'produtos.txt'.\n");
        return;
    }

    if((caixa = fopen("caixa.txt", "r+"))==NULL) {
        printf("\nErro abrindo o arquivo 'caixa.txt'.\n");
        return;
    }

    printf("Produtos em estoque:\n\n");
    while( fgets (produto, 123, produtos) != NULL ) {
        printf("%s", produto);
    }
    printf("\n====================\n\n");

    fflush(stdin);
    acaoFluxo = menuFluxo();
    printf("O valor de 'acaoFluxo e: %d\n", acaoFluxo);
    Sleep(5);

    while (acaoFluxo != 3) {

        switch(acaoFluxo) {
            case 1:
                printf("Comprando algum produto!\n\n");
                break;

            case 2:
                printf("Vendendo algum produto!\n\n");
                break;

            default:
                printf("Erro no programa!\n\n");
                return;
        }

        acaoFluxo = menuFluxo();
    }

    // Fechando os arquivos .txt abertos (caixa.txt && produtos.txt)
    fclose(caixa);
    fclose(produtos);

//    pause();
    system("cls");
}

int menuFluxo() {
    int acao, aux, isValid;
    char term;

    printf("Escolha a acao desejada:\n");
    printf("1. Compra de produto\n");
    printf("2. Venda de produto\n");
    printf("3. Voltar ao menu inicial\n\n");

    printf("-> Digite o numero correspondente a acao: ");
    while (isValid != 2) {
        isValid = 2;
        fflush(stdin);
        aux = scanf("%d%c", &acao, &term);
        if (aux != 2 || term != '\n') {
            printf("\nO valor digitado nao corresponde a um inteiro.\n");
            printf("-> Digite novamente a acao desejada: ");
            isValid--;
        } else if (acao < 1 || acao > 3) {
            printf("\nNumero digitado nao corresponde a uma acao existente.\n");
            printf("-> Digite novamente a acao desejada: ");
            isValid--;
        }
    }

    system("cls");
    return acao;
}

int showMenu() {
    int acao, aux, isValid;
    char term;

    printf("Escolha a acao desejada:\n");
    printf("1. Cadastro de usuario\n");
    printf("2. Cadastro de produto\n");
    printf("3. Adicionar fluxo de produtos\n");
    printf("4. Sair do programa\n\n");

    printf("-> Digite o numero correspondente a acao: ");
    while (isValid != 2) {
        isValid = 2;
        fflush(stdin);
        aux = scanf("%d%c", &acao, &term);
        if (aux != 2 || term != '\n') {
            printf("\nO valor digitado nao corresponde a um inteiro.\n");
            printf("-> Digite novamente a acao desejada: ");
            isValid--;
        } else if (acao < 1 || acao > NUMACOES) {
            printf("\nNumero digitado nao corresponde a uma acao existente.\n");
            printf("-> Digite novamente a acao desejada: ");
            isValid--;
        }
    }

    system("cls");
    return acao;
}

void cadastroProduto() {
    FILE *arq;
    char produto[123], novoProduto[123];
    char novoProdutoPreco[60], novoProdutoNome[60];
    int ehNovoProduto = 1;

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
    strcat(novoProduto, " | R$");
    strcat(novoProduto, novoProdutoPreco);
    strcat(novoProduto, " | ");
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
    char usuario[123], novoUsuario[123];
    char novoUsuarioTelefone[60], novoUsuarioNome[60];
    int isNewUser = 1;

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

void pause () {
  printf ( "\n\nPressione qualquer tecla para continuar...\n\n" );
  getch();
}
