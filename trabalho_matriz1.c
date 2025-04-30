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

int searchGroup(int m, int n, int matriz[m][n], int indices[], int chave)
{
    int count = 0;
    for (int i = 0; i < m; i++) {
        if (numberAlreadyExistsInIndex(m, n, matriz, i, chave)) {
            indices[count++] = i;
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
    char *type = (option == 4) ? "união" : "interseção";

    printf("Escolha dois índices para fazer a %s: \n", type);
    scanf("%d%d", indexOne, indexTwo);
    printf("\n");

    while ((*indexOne < 0 || *indexTwo < 0) || (*indexOne >= m || *indexTwo >= m)) {
        printf("ERRO - Indice inválido!\nDigite um número entre 0 e %d: ", m - 1);
        scanf("%d%d", indexOne, indexTwo);
    }
}

void canNotBeNullMatrix(int count, int m)
{
    if (count < 2) {
        printf("ERRO - É necessário ao menos dois conjuntos para realizar a interseção.\n");
    } 

    if (count >= m) {
        printf("ERRO - Limite de conjuntos atingido.\n");
    }

    backToMenu();
    return;
}

int main()
{

    int m, n;
    int opcao;
    int count = 0;

    // Leitura da matriz
    printf("Primeiro, precisamos da quantidade de linhas e colunas da matriz.\n");
    printf("Linhas: ");
    scanf("%d", &m);
    printf("Colunas: ");
    scanf("%d", &n);

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
            if (count >= m) {
                printf("ERRO - Limite de conjuntos atingido.\n");
            }
            else {
                count++;
                printf("Conjunto vazio criado no índice %d.\n", count - 1);
            }
            backToMenu();
            break;
        }

        case 2:
        {
            int indice;
            int novo_valor;

            if (count == 0) {
                printf("ERRO - Nenhum conjunto criado ainda.\n");
                backToMenu();
                break;
            }

            printf("Vamos inserir dados em um conjunto!\n");
            printf("Atenção! Você não pode inserir mais de %d números, esses números não podem ser repetidos.\n", n);
            printf("Dê o índice do conjunto que você deseja alterar: ");
            scanf("%d", &indice);

            if (indice < 0 || indice >= count) {
                printf("ERRO - Esse índice não existe. Digite um índice válido.");
                backToMenu();
                break;
            }

            for (int j = 0; j < n; j++) {
                do {
                    printf("Elemento %d: ", j);
                    scanf("%d", &novo_valor);
                    if (novo_valor == 0){
                        printf("ERRO - 0 não é um valor válido!\n");
                    }else{
                        if (numberAlreadyExistsInIndex(m, n, matriz, indice, novo_valor)) {
                            printf("ERRO - Valor repetido!\n");
                        }
                        else {
                            matriz[indice][j] = novo_valor;
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
            int indice;
            if (count == 0) {
                printf("ERRO - Nenhum conjunto para remover\n");
                backToMenu();
                break;
            }
            printf("Vamos remover um conjunto!\n");
            printf("Qual conjunto você deseja remover?\nConjunto: ");
            scanf("%d", &indice);

            if (indice < 0 || indice >= count) {
                printf("ERRO - Índice inválido.\n");
            }
            else {
                for (int j = 0; j < n; j++) {
                    matriz[indice][j] = 0;
                }
                for (int i = indice; i < count - 1; i++) {
                    for (int j = 0; j < n; j++) {
                        matriz[i][j] = matriz[i + 1][j];
                    }
                }
                resetMatrix(m, n, matriz, count - 1);
                count--;
                printf("Conjunto %d removido.\n", indice);
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

            // imprime a nova matriz
            printf("\nmatriz principa (print teste, vai ser removido)\n");
            for (int i = 0; i < m + 1; i++) {
                for (int j = 0; j < n * 2; j++) {
                    if (i < m) {
                        if (j < n) {
                            printf("%d ", matriz[i][j]);
                        }
                        else {
                            printf("0 ");
                        }
                    } else {
                        printf("%d ", matriz[i][j]);
                    }
                }
                printf("\n");
            }
            backToMenu();
            break;
        }

        case 5:
        {   
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
            int indice;

            if (count == 0) {
                printf("ERRO - Nenhum conjunto criado.\n");
                backToMenu();
                break;
            }

            printf("Vamos mostar um conjunto!\n");
            printf("Por favor, informe o índice do conjunto que você deseja mostrar: ");
            scanf("%d", &indice);

            showMatrix(m, n, matriz, indice, count);
            backToMenu();
            break;
        }

        case 7:
            printf("Vamos mostrar todos os conjuntos!\n");
            printf("Imprimindo conjuntos...\n");
            showMatrix(m, n, matriz, -1, count);

            backToMenu();
            break;

        case 8:
        {
            int chave;
            printf("Vamos buscar por um valor!\n");
            printf("Digite o valor a ser procurado: ");
            scanf("%d", &chave);

            int indices[m];
            int x = searchGroup(m, n, matriz, indices, chave);

            if (x == 0) {
                printf("\nO valor %d não foi encontrado em nenhum conjunto.\n", chave);
            }
            else {
                printf("Valor encontrado!\n");
                printf("Imprimindo o(s) índice(s) onde o valor %d foi encontrados...\n", chave);
                for (int k = 0; k < x; k++) {
                    printf("%d ", indices[k]);
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
    } while (opcao != 9);

    // Imprimir a matriz final, usando pra testar o código.
    showMatrix(m, n, matriz, -1, count);
    printf("Count: %d", count);

    return 0;
}
