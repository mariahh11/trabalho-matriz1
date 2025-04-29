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
void showMatrix(int m, int n, int matriz[m][n], int linha)
{
    if (linha == -1) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", matriz[i][j]);
            }
            printf("\n");
        }
    } else if (linha >= 0 && linha < m) {
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

// Escaneia os valores atribuidos a matriz
void scanMatrix(int m, int n, int matrix[MAX][MAX])
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("Item [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void preState(
    int m, 
    int n, 
    int matrix[MAX][MAX],
    int *indexOne, 
    int *indexTwo,
    int option) 
{        
    scanMatrix(m, n, matrix);

    char *type = (option == 4) ? "união" : "interseção";

    printf("Escolha dois índices para fazer a %s: \n", type);
    scanf("%d%d", indexOne, indexTwo);
    printf("\n");

    while ((*indexOne < 0 || *indexTwo < 0) || (*indexOne >= m || *indexTwo >= m)) {
        printf("ERRO - Indice inválido!\nDigite um número entre 0 e %d: ", m - 1);
        scanf("%d%d", indexOne, indexTwo);
    }
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
    int matriz[MAX][MAX];
    resetMatrix(MAX, MAX, matriz, -1);

    // Loop do menu
    do {

        // Tela de menu
        printf("╔═══════════════✧═════════════★ MENU ★═════════════✧══════════════╗\n");
        printf("╏  1 - Criar um novo conjunto vazio                               ╏\n");
        printf("╏  2 - Inserir dados em um conjunto                               ╏\n");
        printf("╏  3 - Remover um conjunto                                        ╏\n");
        printf("╏  4 - Fazer união entre dois conjuntos                           ╏\n");
        printf("╏  5 - Fazer a intersecção entre dois conjuntos                   ╏\n");
        printf("╏  6 - Mostrar um conjunto                                        ╏\n");
        printf("╏  7 - Mostrar todos os conjuntos                                 ╏\n");
        printf("╏  8 - Busca por um valor                                         ╏\n");
        printf("╏  9 - Sair do programa                                           ╏\n");
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

            if (indice < 0 || indice >= m) {
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

            preState(m, n, matriz, &indexOne, &indexTwo, 4);
            
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

            // imprime a nova matriz
            for (int i = 0; i < m + 1; i++) {
                for (int j = 0; j < n * 2; j++) {
                    if (i < m) {
                        if (j < n) {
                            printf("%d ", newMatrix[i][j]);
                        }
                        else {
                            printf("0 ");
                        }
                    } else {
                        printf("%d ", newMatrix[i][j]);
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

            preState(m, n, matriz, &indexOne, &indexTwo, 5);

            int concat[n], k = 0, newMatrix[MAX][MAX];
        
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    newMatrix[i][j] = matriz[i][j];
                }
            }
        
            // interseção entre as duas linhas
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    int matrixLine = matriz[indexOne][i];
                    if ( matrixLine == matriz[indexTwo][j] && matrixLine != 0) {
                        int alreadyExists = 0;
                        for (int x = 0; x < k; x++) {
                            if (concat[x] == matrixLine) {
                                alreadyExists = 1;
                                break;
                            }
                        }
                        if (!alreadyExists) {
                            concat[k++] = matrixLine;
                        }
                    }
                }
            }
        
            for (int i = 0; i < n; i++) {
                if (i < k) {
                    newMatrix[m][i] = concat[i];
                } else {
                    newMatrix[m][i] = 0;
                }
            }
        
            // imprime a nova matriz
            for (int i = 0; i < m + 1; i++) {
                for (int j = 0; j < n; j++) {
                    printf("%d ", newMatrix[i][j]);
                }
                printf("\n");
            }
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

            showMatrix(m, n, matriz, indice);
            backToMenu();
            break;
        }

        case 7:
            printf("Vamos mostrar todos os conjuntos!\n");
            printf("Imprimindo conjuntos...\n");
            showMatrix(m, n, matriz, -1);

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
    showMatrix(m, n, matriz, -1);
    printf("Count: %d", count);

    return 0;
}
