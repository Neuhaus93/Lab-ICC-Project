#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


int showMenu();
void cadastroUsuario();
void cadastroProduto();
void fluxoProduto();
void pause();


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

//    printf("\nNovo Usuario: %s", novoUsuario);


    while( fgets (usuario, 123, arq) != NULL ) {
//        printf("[%d] - Usuario: *%s* - Novo usuario: *%s*\n", counter++, novoUsuario,usuario);
        isNewUser = strcmp(novoUsuario, usuario);
        if (isNewUser == 0) {
            printf("\n--- Usuario ja existe! ---");
            printf("\nVoltando para o menu inicial...");
            printf("\nPrecione [Enter] para continuar!");
            pause();
            system("cls");
            break;
        }
    }

    if (isNewUser != 0) {
        fputs(novoUsuario, arq);
        printf("\nNovo usuario adicionado!!");
    }

    fclose(arq);
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

    system("cls");
    return acao;
}

void pause () {
  printf ( "Press [Enter] to continue . . ." );
  fflush ( stdout );
  getchar();
}
