#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


int showMenu();
void cadastroUsuario();
void cadastroProduto();
void fluxoProduto();


void main() {

    int acao;

    acao = showMenu();

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

    return;
}

void fluxoProduto() {
    printf("Fluxo de produto!");
}


void cadastroProduto() {
    printf("Cadastro de produto!");
}

void cadastroUsuario() {
    printf("====================\n\n");
    printf("Cadastro de usuario!\n\n");
    printf("====================\n\n");





}

int showMenu() {

    int acao;

    printf("Escolha a acao desejada:\n");
    printf("1. Cadastro de usuario\n");
    printf("2. Cadastro de produto\n");
    printf("3. Adicionar fluxo de produtos\n\n");

    printf("Digite o numero correspondente a acao: ");
    scanf("%d", &acao);

    while (acao < 1 || acao > 3) {
        printf("\nNumero digitado nao corresponde a uma acao existente.\n");
        printf("Digite novamente a acao desejada: ");
        scanf("%d", &acao);
    }

    printf("\n\n");
    return acao;
}
