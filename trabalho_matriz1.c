#include <stdio.h>
#include <locale.h>
#define MAX 100

// Verifica se o número já existe no CONJUNTO
int numberAlreadyExistsInIndex(int m, int n, int matriz[m][n], int linha_escolhida, int num)
{
    for (int i = 0; i < n; i++) {
        if (matriz[linha_escolhida][i] == num) {
            return 1; // Número já existe
        }
    }

    return 0; // Número válido
}

// Função que mostra a matriz/conjunto na tela
void showMatrix(int m, int n, int matriz[m][n], int linha, int count)
{
    if (linha == -1) {
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", matriz[i][j]);
            }
            printf("\n");
        }
    } else if (linha >= 0 && linha < count) {
        printf("Imprimindo conjunto...\n");
        printf("Conjunto %d = [ ", linha);
        for (int j = 0; j < n; j++) {
            printf("%d ", matriz[linha][j]);
            if (j < n - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    } else {
        printf("ERRO - Índice inválido para exibição.\n");
    }
}

// Função que zera a matriz inteira ou uma linha especifica
// Caso queira zerar a matriz inteira, o ultimo argumento deve ser -1
// Caso queira zerar apenas uma linha, o ultimo argumento deve ser a linha que deve ser zerada
void resetMatrix(int m, int n, int matriz[m][n], int linha)
{
    if (linha == -1) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                matriz[i][j] = 0;
            }
        }
    }
    else if (linha >= 0 && linha < m) {
        for (int j = 0; j < n; j++) {
            matriz[linha][j] = 0;
        }
    }
}

int searchGroup(int m, int n, int matriz[m][n], int indexs[], int chave)
{
    int count = 0;
    for (int i = 0; i < m; i++) {
        if (numberAlreadyExistsInIndex(m, n, matriz, i, chave)) {
            indexs[count++] = i;
        }
    }

    return count;
}

void backToMenu()
{
    printf("\nVoltando para o menu...\n");
}

void preState(
    int m, 
    int *indexOne, 
    int *indexTwo,
    int option) 
{        
    char *type = (option == 4) ? "união" : "interseção"; //Muda de acordo com o case escolhido. Se for o 4, irá aparecer união ao invés de intersecção

    printf("Escolha dois índices para fazer a %s: \n", type);
    printf("Primeiro índice: ");
    scanf("%d", indexOne);
    printf("Segundo índice: ");
    scanf("%d", indexTwo);
    //scanf("%d%d", indexOne, indexTwo);
    printf("\n");

    while ((*indexOne < 0 || *indexTwo < 0) || (*indexOne >= m || *indexTwo >= m)) {
        printf("ERRO - Indice inválido!\nDigite um número entre 0 e %d: ", m - 1);
        scanf("%d%d", indexOne, indexTwo);
    }
}

void canNotBeNullMatrix(int count, int m)
{
    if (count < 2) {
        printf("ERRO - É necessário ao menos dois conjuntos para realizar a ação.\n");
        backToMenu();
        return;
    } 

    if (count >= m) {
        printf("AVISO - Nesse caso será possível passar o máximo de linhas, pois será inserido um conjunto necessário na matriz\n");
    }
}


void showMatrixWithZeros(int count, int n, int matriz[MAX][MAX])//Função que mostra a matriz alterada pelo case 4
{
    int totalColunas = n * 2;

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < totalColunas; j++) {
            if (j < n) {
                printf("%d ", matriz[i][j]);
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }

    // Imprime a última linha (união), com todas as colunas preenchidas
    for (int j = 0; j < totalColunas; j++) {
        printf("%d ", matriz[count][j]);
    }
    printf("\n");
}

int main()
{

    int m, n;
    int opcao;
    int count = 0;
    int houveUniao = 0;

    //Introdução do programa para o usuário
    printf("★Bem vindo!★\n");
    printf("Nesse programa, poderemos fazer operações com uma matriz. Basta digitar o número correspondente da operação desejada.\n");

    // Leitura da matriz
    printf("Primeiro, precisamos da quantidade de linhas e colunas da matriz.\n");
    printf("Linhas: ");
    scanf("%d", &m);
    printf("Colunas: ");
    scanf("%d", &n);

    printf("\nDICA - Adicione os conjuntos vazios antes de começar as operações!\n");

    // Todos os elementos da matriz são 0
    int matriz[m][n];
    resetMatrix(m, n, matriz, -1);

    // Loop do menu
    do {

        // Tela de menu
        printf("╔═══════════════✧═════════════★ MENU ★════════════✧══════════════╗\n");
        printf("╏  1 - Criar um novo conjunto vazio                                ╏\n");
        printf("╏  2 - Inserir dados em um conjunto                                ╏\n");
        printf("╏  3 - Remover um conjunto                                         ╏\n");
        printf("╏  4 - Fazer união entre dois conjuntos                            ╏\n");
        printf("╏  5 - Fazer a intersecção entre dois conjuntos                    ╏\n");
        printf("╏  6 - Mostrar um conjunto                                         ╏\n");
        printf("╏  7 - Mostrar todos os conjuntos                                  ╏\n");
        printf("╏  8 - Busca por um valor                                          ╏\n");
        printf("╏  9 - Sair do programa                                            ╏\n");
        printf("╚═══════════════✧══════════════════════════════════✧══════════════╝\n");

        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
        {
            if (count >= m) {//Se o count passar da quantidade de linhas, ele impede que sejam adicionados mais conjuntos
                printf("ERRO - Limite de conjuntos atingido.\n");
            }
            else {//Caso não passe, ele adiciona mais um conjunto vazio na matriz
                count++;
                printf("Conjunto vazio criado no índice %d.\n", count - 1);
            }
            backToMenu();
            break;
        }

        case 2:
        {
            int index;
            int novo_valor;

            if (count == 0) {//Se o count for igual a zero, significa que não existe nenhum conjunto na matriz para ser alterado
                printf("ERRO - Nenhum conjunto criado ainda.\n");
                backToMenu();
                break;
            }

            printf("Vamos inserir dados em um conjunto!\n");
            printf("Atenção! Você não pode inserir mais de %d números, esses números não podem ser repetidos.\n", n);
            printf("Dê o índice do conjunto que você deseja alterar: ");
            scanf("%d", &index);

            if (index < 0 || index >= count) {//Essa parte não deixa que o usuário selecione um índice que não existe
                printf("ERRO - Esse índice não existe. Digite um índice válido.");
                backToMenu();
                break;
            }

            for (int j = 0; j < n; j++) {
                do {
                    printf("Elemento %d: ", j);
                    scanf("%d", &novo_valor);
                    if (novo_valor == 0){
                        printf("ERRO - 0 não é um valor válido!\n");//Não é possível adicionar 0 como valor
                    }else{
                        if (numberAlreadyExistsInIndex(m, n, matriz, index, novo_valor)) {//Chama a função que verifica se um número já existe no conjunto
                            printf("ERRO - Valor repetido!\n");//Não é possível adicionar um número que já existe
                        }
                        else {
                            matriz[index][j] = novo_valor;//Adiciona os valores digitados na matriz
                            break;
                        }
                    }
                } while (1);
            }
            printf("\nConjunto adicionado!\n");
            backToMenu();
            break;
        }

        case 3:
        {
            int index;
            if (count == 0) {//Não é possível remover conjuntos que não existem
                printf("ERRO - Nenhum conjunto para remover\n");
                backToMenu();
                break;
            }
            printf("Vamos remover um conjunto!\n");
            printf("Qual conjunto você deseja remover?\nConjunto: ");
            scanf("%d", &index);

            if (index < 0 || index >= count) {//Não é possível selecionar conjuntos que não existem
                printf("ERRO - Índice inválido.\n");
            }
            else {
                for (int i = index; i < count - 1; i++) {//Move o conjunto abaixo para cima
                    for (int j = 0; j < n; j++) {
                        matriz[i][j] = matriz[i + 1][j];
                    }
                }
                resetMatrix(m, n, matriz, count - 1); //Zera o conjunto selecionado
                count--;//Diminui o contador pois um conjunto foi removido
                printf("Conjunto %d removido.\n", index);
            }
            backToMenu();
            break;
        }

        case 4:
        {
           int indexOne, indexTwo;

           canNotBeNullMatrix(count, m);

           preState(m, &indexOne, &indexTwo, 4);
           
           int concat[n * 2], k = 0, newMatrix[MAX][MAX];

           //concatena as duas linhas
           for (int j = 0; j < n; j++) {
               concat[k++] = matriz[indexOne][j];
           }

            for (int j = 0; j < n; j++) {
                concat[k++] = matriz[indexTwo][j];
            }
            //=============================

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    newMatrix[i][j] = matriz[i][j];
                }
            }

            for (int i = 0; i < (n * 2); i++) {
                if (i < (n * 2)) {
                    newMatrix[m][i] = concat[i];
                }
                else {
                    newMatrix[m][i] = 0;
                }
            }

            // imprime a nova matriz para a matriz principal
            for (int i = 0; i < m + 1; i++) {
              for (int j = 0; j < n * 2; j++) {
                  if (i < m) {
                      if (j < n) {
                         matriz[i][j] = newMatrix[i][j];
                      }
                      else {
                          matriz[i][j] = 0;
                      }
                  } else {
                     matriz[i][j] = newMatrix[i][j];
                  }
              }
            }

            houveUniao = 1;
            backToMenu();
            break;
        }
        
        case 5:
        {   
            printf("Vamos fazer a intersecção entre ");
            int indexOne, indexTwo;
            canNotBeNullMatrix(count, m);
            preState(m, &indexOne, &indexTwo, 5);
            
            int intersec[n], k = 0;
        
            for (int i = 0; i < n; i++) {
                int element = matriz[indexOne][i];
            
                if (element == 0) continue;
            
                for (int j = 0; j < n; j++) {
                    if (element == matriz[indexTwo][j]) {
                        int isRepeated = 0;
                        for (int x = 0; x < k; x++) {
                            if (intersec[x] == element) {
                                isRepeated = 1;
                                break;
                            }
                        }
                        if (!isRepeated)
                            intersec[k++] = element;
                        break;
                    }
                }
            }
        
            for (int i = 0; i < n; i++) {
                matriz[count][i] = (i < k) ? intersec[i] : 0;
            }
        
            printf("Interseção adicionada como conjunto %d.\n", count);
            count++;
        
            backToMenu();
            break;
        }

        case 6:
        {
            int index;

            if (count == 0) {//Se count == 0, nenhum conjunto foi criado e volta para o menu
                printf("ERRO - Nenhum conjunto criado.\n");
                backToMenu();
                break;
            }

            printf("Vamos mostar um conjunto!\n");
            printf("Por favor, informe o índice do conjunto que você deseja mostrar: ");
            scanf("%d", &index);

            showMatrix(m, n, matriz, index, count);//Chama a função que mostra o conjunto
            backToMenu();
            break;
        }

        case 7:
            printf("Vamos mostrar todos os conjuntos!\n");
            printf("Imprimindo conjuntos...\n");
    
            if (houveUniao) {//Se houve união for verdadeiro, indica que ele passou pelo case 4 antes. Então ele vai chamar a função que imprime a matriz alterada
                showMatrixWithZeros(count + 1, n * 2, matriz);
            } else {//Se não, ele vai chamar a função de mostrar a matriz[m][n]
                showMatrix(m, n, matriz, -1, count);
            }   
    
            backToMenu();
            break;

        case 8:
        {
            int chave;
            printf("Vamos buscar por um valor!\n");
            printf("Digite o valor a ser procurado: ");
            scanf("%d", &chave);

            int indexs[m];
            int x = searchGroup(m, n, matriz, indexs, chave); //A variável x da a quantidade de vezes que existem números repetidos

            if (x == 0) {//Se x == 0, o valor não foi encontrado
                printf("\nO valor %d não foi encontrado em nenhum conjunto.\n", chave);
            }
            else {//Se for mais de zero, o programa imprime os indexs onde o valor foi encontrado
                printf("Valor encontrado!\n");
                printf("Imprimindo o(s) índice(s) onde o valor %d foi encontrados...\n", chave);
                for (int k = 0; k < x; k++) {
                    printf("%d ", indexs[k]);
                    if (k < (x - 1)) {
                        printf(", ");
                    }
                }
            }
            backToMenu();
            break;
        }

        case 9:
            printf("Saindo do programa...\n");
            break;

        default:
            // Caso o usuário digite uma opção inválida - mensagem de erro
            printf("ERRO - Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 9);//Só sai do loop se o usuário selecionar a opção 9 (sair do programa)

    return 0;
}
