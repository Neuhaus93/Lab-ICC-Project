#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define NUMACOES 4
#define TRANSACTION_SUCCESS 0
#define TRANSACTION_FAILURE 1
#define MAX 256

/**
 *  Aluno: Lucas Arendt Neuhaus
 *  nUSP: 8552501
 */

void registerNewUser();
void registerNewItem();
int printMainMenu();
int printFlowMenu();
int printBuyMenu(float);
int printSellMenu(float);
int printListedItems(bool);
double convertCost(char *, int);
void stockFlow();
void buyProduct();
void sellProduct();
int transaction(double);
int actionValidate(int, int);
void printHeader(char *);
void pause();

struct user
{
  char nome[60];
  char telefone[60];
};

struct item
{
  char nome[60];
  char preco[60];
};

void main()
{
  int action = printMainMenu();
  system("cls");

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
  struct user newUser;
  char usuario[123], novoUsuario[123];
  int isNewUser = 1;

  printHeader("Cadastro de usuario!");

  if ((users = fopen("users.txt", "r+")) == NULL)
  {
    printf("\nErro abrindo o arquivo.\n");
    return;
  }

  printf("Digite o nome do usuario: ");
  gets(newUser.nome);
  printf("Digite o telefone de %s: ", newUser.nome);
  gets(newUser.telefone);

  strcpy(novoUsuario, newUser.nome);
  strcat(novoUsuario, " - ");
  strcat(novoUsuario, newUser.telefone);
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
  struct item newItem;
  char produto[123], novoProduto[123];
  int ehNovoProduto = 1;

  printHeader("Cadastro de produto!");

  if ((stock = fopen("stock.txt", "r+")) == NULL)
  {
    printf("\nErro abrindo o arquivo.\n");
    return;
  }

  printf("Digite o nome do produto: ");
  gets(newItem.nome);
  printf("Digite o preco do produto: ");
  gets(newItem.preco);

  strcpy(novoProduto, newItem.nome);
  strcat(novoProduto, " | R$");
  strcat(novoProduto, newItem.preco);
  // strcat(novoProduto, " | ");
  // strcat(novoProduto, "0");
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
      sellProduct();
      break;

    default:
      printf("Erro no programa!\n\n");
      return;
    }
  }
}

void buyProduct()
{
  FILE *stock, *cash_register;
  int action, count, indexCounter = 1, itemIndex, costIndex, quantIndex, balanceIndex = 2;
  int buyQuant, quantInStock;
  double totalCost;
  char aux[15], item[15], costStr[10], quantStr[10], balanceStr[10];

  system("cls");
  printHeader("Registrar compra de produto!");
  count = printListedItems(true);
  action = actionValidate(count, 2);

  // Go back to the previous menu
  if (count == action)
    return;

  itemIndex = (3 + action * 3);
  costIndex = itemIndex + 2;
  quantIndex = itemIndex + 4;

  if ((stock = fopen("stock.txt", "r")) == NULL)
  {
    printf("\nErro abrindo o arquivo 'stock.txt'.\n");
    return;
  }
  if ((cash_register = fopen("cash_register.txt", "r")) == NULL)
  {
    printf("\nErro abrindo o arquivo 'cash_register.txt'.\n");
    return;
  }
  while (feof(stock) == 0)
  {
    fscanf(stock, "%s", aux);
    if (indexCounter == itemIndex)
      strcpy(item, aux);
    if (indexCounter == costIndex)
    {
      strcpy(costStr, aux);
    }
    if (indexCounter == costIndex)
    {
      strcpy(quantStr, aux);
      break;
    }
    indexCounter++;
  }
  indexCounter = 0;
  while (feof(cash_register) == 0)
  {
    fscanf(cash_register, "%s", aux);
    if (indexCounter == balanceIndex)
      strcpy(balanceStr, aux);
    indexCounter++;
  }
  fclose(stock);
  fclose(cash_register);

  quantInStock = atof(quantStr);

  printf("\n\nSaldo atual: R$%s", balanceStr);
  printf("\nDigite o numero de unidades de %s (%s/un) voce deseja comprar: ", item, costStr);
  scanf("%d", &buyQuant);
  totalCost = convertCost(costStr, strlen(costStr)) * buyQuant;

  action = printBuyMenu(totalCost);

  if (action == 2)
    return;

  if (transaction(-totalCost) == TRANSACTION_SUCCESS)
  {
    printf("\nCompra realizada com suceso!");
    Sleep(1250);
  }
  else
  {
    printf("\nSem saldo suficiente no caixa para a transacao!");
    Sleep(1250);
  }
}

void sellProduct()
{
  FILE *stock;
  int action, count, indexCounter = 1, itemIndex, costIndex, quantIndex;
  int sellQuant, quantInStock;
  double totalCost;
  char aux[15], item[15], costStr[10], quantStr[10];

  system("cls");
  printHeader("Registrar venda de produto!");
  count = printListedItems(true);
  action = actionValidate(count, 2);

  // Go back to the previous menu
  if (count == action)
    return;

  itemIndex = (3 + action * 3);
  costIndex = itemIndex + 2;
  quantIndex = itemIndex + 4;

  if ((stock = fopen("stock.txt", "r")) == NULL)
  {
    printf("\nErro abrindo o arquivo 'stock.txt'.\n");
    return;
  }
  while (feof(stock) == 0)
  {
    fscanf(stock, "%s", aux);
    if (indexCounter == itemIndex)
      strcpy(item, aux);
    if (indexCounter == costIndex)
    {
      strcpy(costStr, aux);
    }
    if (indexCounter == costIndex)
    {
      strcpy(quantStr, aux);
      break;
    }
    indexCounter++;
  }
  fclose(stock);

  quantInStock = atof(quantStr);

  printf("\n\nDigite o numero de unidades de %s (%s/un) voce deseja vender: ", item, costStr);
  scanf("%d", &sellQuant);
  totalCost = convertCost(costStr, strlen(costStr)) * sellQuant;

  action = printSellMenu(totalCost);

  if (action == 2)
    return;

  if (transaction(totalCost) == TRANSACTION_SUCCESS)
  {
    printf("\nVenda realizada com suceso!");
    Sleep(1250);
  }
  else
  {
    printf("\nOcorreu um erro na venda do produto!");
    Sleep(1250);
  }
}

/**
 *  Converts the cost string from the stock.txt file to a double. 
 * 
 *  @param  {char[]}    costStr 
 *  @param  {int}       strSize Length of the costStr
 * 
 *  @return {double}    Cost converted to a double 
 */
double convertCost(char *costStr, int strSize)
{
  char aux[10];

  strncpy(aux, costStr + 2, strSize - 2);
  return atof(aux);
}

/**
 *  Completes a buy or sell transaction, adding or substracting the value (if possible) out of the cash_register.txt file
 * 
 * @param {double}  value The transaction value
 * 
 * @return {int}    Returns the constant TRANSACTION_FAILURE if an error ocurred, or if not enough money in the cash_register, or
 *                    returns the constant TRANSACTION_SUCESS if it was a success.
 */
int transaction(double value)
{
  FILE *cash_register, *fptr2;
  char lineContent[30], temp[] = "temp.txt", str[MAX];
  char *balanceStr;
  int line = 0, lno = 2, linectr = 0;
  double balance;

  if ((cash_register = fopen("cash_register.txt", "r")) == NULL)
  {
    printf("\nErro abrindo o arquivo 'cash_register.txt'.\n");
    return TRANSACTION_FAILURE;
  }

  if ((fptr2 = fopen(temp, "w")) == NULL)
  {
    printf("\nErro abrir um arquivo temporario para escrever!!'.\n");
    return TRANSACTION_FAILURE;
  }

  while (line <= 1)
  {
    fgets(lineContent, 123, cash_register);
    line++;
  }

  balanceStr = malloc(strlen(lineContent) + 1);

  balance = atof(lineContent);
  if (balance + value > 0.0)
  {
    balance += value;
  }
  else
  {
    return TRANSACTION_FAILURE;
  }

  rewind(cash_register);

  snprintf(balanceStr, sizeof(balanceStr), "%.2f", balance);

  while (!feof(cash_register))
  {
    strcpy(str, "\0");
    fgets(str, MAX, cash_register);
    if (!feof(cash_register))
    {
      linectr++;
      if (linectr != lno)
      {
        fprintf(fptr2, "%s", str);
      }
      else
      {
        fprintf(fptr2, "%s\n", balanceStr);
      }
    }
  }
  fclose(cash_register);
  fclose(fptr2);
  remove("cash_register.txt");
  rename(temp, "cash_register.txt");

  free(balanceStr);
  return TRANSACTION_SUCCESS;
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
 *  Prints the flow menu, shown when the user selects the action (3) in the main menu.
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
 *  Prints the buy menu.
 */
int printBuyMenu(float totalCost)
{
  int action;

  printf("\nO total ficou R$%0.2f.\n\n", totalCost);
  printf(" 1. Finalizar compra\n");
  printf(" 2. Cancelar compra\n");

  printf("\n====================\n\n");

  action = actionValidate(2, 1);

  return action;
}

/**
 *  Prints the sell menu.
 */
int printSellMenu(float totalCost)
{
  int action;

  printf("\nO total ficou R$%0.2f.\n\n", totalCost);
  printf(" 1. Finalizar venda\n");
  printf(" 2. Cancelar venda\n");

  printf("\n====================\n\n");

  action = actionValidate(2, 1);

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
