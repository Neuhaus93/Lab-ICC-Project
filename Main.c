#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define NUMACOES 4

void registerNewUser();
void registerNewItem();
int printMainMenu();
int printFlowMenu();
int printListedItems(bool);
void stockFlow();
void buyProduct();
int actionValidate(int, int);
void printHeader(char *);
void pause();

void main()
{
  int action = printMainMenu();

  while (action != 4)
  {
    switch (action)
    {
    case 1:
      registerNewUser();
      break;

    case 2:
      registerNewItem();
      break;

    case 3:
      stockFlow();
      break;

    default:
      printf("Erro no programa!");
      return;
    }
    system("cls");
    action = printMainMenu();
  }

  printHeader("Finalizando o programa...");
  return;
}

/**
 *  Register a new user in the 'users.txt' file.
 *  Before registering, checks if the user already exists, matching both name and cel phone number.
 */
void registerNewUser()
{
  FILE *users;
  char usuario[123], novoUsuario[123];
  char novoUsuarioTelefone[60], novoUsuarioNome[60];
  int isNewUser = 1;

  printHeader("Cadastro de usuario!");

  if ((users = fopen("users.txt", "r+")) == NULL)
  {
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

  while (fgets(usuario, 123, users) != NULL)
  {
    isNewUser = strcmp(novoUsuario, usuario);
    if (isNewUser == 0)
    {
      printf("\n--- Usuario ja existe! ---");
      printf("\nVoltando para o menu inicial...");
      pause();
      break;
    }
  }

  if (isNewUser != 0)
  {
    fputs(novoUsuario, users);
    printf("\nNovo usuario adicionado!!");
    pause();
  }

  fclose(users);
  system("cls");
}

/**
 *  Register a new item in the 'stock.txt' file.
 *  Before registering, checks if the item already exists, matching both name and item price.
 */
void registerNewItem()
{
  FILE *stock;
  char produto[123], novoProduto[123];
  char novoProdutoPreco[60], novoProdutoNome[60];
  int ehNovoProduto = 1;

  printHeader("Cadastro de produto!");

  if ((stock = fopen("stock.txt", "r+")) == NULL)
  {
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

  while (fgets(produto, 123, stock) != NULL)
  {
    ehNovoProduto = strcmp(novoProduto, produto);
    if (ehNovoProduto == 0)
    {
      printf("\n--- Produto ja existe! ---");
      printf("\nVoltando para o menu inicial...");
      pause();
      break;
    }
  }

  if (ehNovoProduto != 0)
  {
    fputs(novoProduto, stock);
    printf("\nNovo produto adicionado!!");
    pause();
  }

  fclose(stock);
  system("cls");
}

/**
 *  Register the flow in the quantity of an item of the stock.
 *  It can be the BUY or the SELL of the item.
 *
 */
void stockFlow()
{
  int action = -1;

  while (action != 3)
  {
    system("cls");
    printHeader("Registrar fluxo de produto!");
    printListedItems(false);
    action = printFlowMenu();

    switch (action)
    {
    case 1:
      buyProduct();
      break;

    case 2:
      printf("Vendendo algum produto!\n\n");
      break;

    default:
      printf("Erro no programa!\n\n");
      return;
    }
  }
}

void buyProduct()
{
  FILE *stock;
  int action, count, indexCounter = 1, itemIndex, costIndex;
  char aux[15], item[15], cost[5];

  system("cls");
  printHeader("Registrar compra de produto!");
  count = printListedItems(true);
  action = actionValidate(count, 2);

  // Go back to the previous menu
  if (count == action)
    return;

  if ((stock = fopen("stock.txt", "r")) == NULL)
  {
    printf("\nErro abrindo o arquivo 'stock.txt'.\n");
    return;
  }

  itemIndex = (3 + action * 5);
  costIndex = itemIndex + 2;
  while (feof(stock) == 0)
  {
    fscanf(stock, "%s", aux);
    if (indexCounter == itemIndex)
      strcpy(item, aux);
    if (indexCounter == costIndex)
    {
      strcpy(cost, aux);
      break;
    }
    indexCounter++;
  }

  printf("Quantas unidades de %s (%s/un) voce deseja comprar?", item, cost);
  Sleep(4000);

  fclose(stock);
}

/**
 *  Print the main menu, shown at the start of the application.
 */
int printMainMenu()
{
  int action;

  printHeader("Seja bem vindo!");
  printf("Escolha a acao desejada:\n");
  printf(" 1. Cadastro de usuario\n");
  printf(" 2. Cadastro de produto\n");
  printf(" 3. Adicionar fluxo de produtos\n");
  printf(" 4. Sair do programa\n");

  printf("\n====================\n\n");

  action = actionValidate(4, 1);

  system("cls");
  return action;
}

/**
 *  Print the flow menu, shown when the user selects the action (3) in the main menu.
 */
int printFlowMenu()
{
  int action;

  printf("Escolha a acao desejada:\n");
  printf(" 1. Compra de produto\n");
  printf(" 2. Venda de produto\n");
  printf(" 3. Voltar ao menu inicial\n\n");

  action = actionValidate(3, 1);

  return action;
}

/**
 *  Print all the items saved in the 'stocks.txt' file.
 *  Can print both an ordered or an unordered list.
 *
 *  @param  {bool}   isOrderedList   Rules the type of the list (ordered vs. unordered)
 *
 *  @return {int}   Return the number of items in the file, plus one in the case of the ordered
 *                      list, for an item that can be selected to go to the previous menu
 */
int printListedItems(bool isOrderedList)
{
  FILE *stock;
  char itemDetail[133], item[123], itemIndex[10];
  int count = 0;

  if ((stock = fopen("stock.txt", "r")) == NULL)
  {
    printf("\nErro abrindo o arquivo 'stock.txt'.\n");
    return -1;
  }

  printf("Produtos em estoque:\n\n");
  while (fgets(item, 123, stock) != NULL)
  {
    sprintf(itemIndex, " %d", count);
    strcpy(itemDetail, itemIndex);
    strcat(itemDetail, ". ");
    if (!isOrderedList)
      strcpy(itemDetail, " - ");
    if (count == 0)
    {
      strcpy(itemDetail, item);
    }
    else
    {
      strcat(itemDetail, item);
    }
    printf("%s", itemDetail);
    count++;
  }
  if (isOrderedList)
    printf("\n %d. Voltar para o menu anterior\n", count);
  printf("\n====================\n\n");

  fclose(stock);
  return (count);
}

/**
 *  Validates the action entered by the user.
 *  Changes text depending on what menu it is being called upon.
 *
 *  @param  {int}   actionIndexMax  The greater action value in the menu
 *  @param  {int}   menuType        The menu type, used to change the text. 1: action, 2: product
 *
 *  @return {int}   Return the action number chosen by the user, validated
 */
int actionValidate(int actionIndexMax, int menuType)
{
  int action, aux, isValid;
  char term, s1[30], s2[30], s3[30];

  char actionString1[] = "a acao que deseja: ";
  char actionString2[] = "uma acao existente.";
  char actionString3[] = "a acao desejada: ";

  char productString1[] = "ao produto que deseja: ";
  char productString2[] = "um produto existente.";
  char productString3[] = "o produto desejado: ";

  if (menuType == 1)
  {
    strcpy(s1, actionString1);
    strcpy(s2, actionString2);
    strcpy(s3, actionString3);
  }
  else
  {
    strcpy(s1, productString1);
    strcpy(s2, productString2);
    strcpy(s3, productString3);
  }

  printf("-> Digite o numero correspondente %s", s1);
  while (isValid != 2)
  {
    isValid = 2;
    fflush(stdin);
    aux = scanf("%d%c", &action, &term);
    if (aux != 2 || term != '\n')
    {
      printf("\nO valor digitado nao corresponde a um inteiro.\n");
      printf("-> Digite novamente %s", s3);
      isValid--;
    }
    else if (action < 1 || action > actionIndexMax)
    {
      printf("\nNumero digitado nao corresponde a %s\n", s2);
      printf("-> Digite novamente %s", s3);
      isValid--;
    }
  }

  return action;
}

/**
 *  Prints the same header style for every page.
 *
 *  @param  {char*} headerTitle     The title string
 */
void printHeader(char *headerTitle)
{
  printf("===============================\n\n");
  printf(" %s\n\n", headerTitle);
  printf("===============================\n\n");
}

/**
 *  Waits for the user to press anything to continue.
 */
void pause()
{
  printf("\n\nPressione qualquer tecla para continuar...\n\n");
  getch();
}
