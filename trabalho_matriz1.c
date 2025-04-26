#include <stdio.h>

int numero_ja_existe(int m, int n, int matriz[m][n], int linha_escolhida, int num){
    for (int i = 0; i < n; i++){
        if (matriz[linha_escolhida][i] == num){
            return 1; //Número já existe
        }
    }

    return 0; //Número válido
}


int main(){
    int m, n;
    int opcao;
    int count = 0;

    //Leitura da matriz
    printf("Primeiro, precisamos da quantidade de linhas e colunas da matriz.\n");
    printf("Linhas: ");
    scanf("%d", &m);
    printf("Colunas: ");
    scanf("%d", &n);

    //Todos os elementos da matriz são 0
    int matriz[m][n];
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            matriz[i][j] = 0;
        }
    }

    //Loop do menu
    do{
    
    //Tela de menu (podemos colocar todas as opções em um printf separado, fica um pouco mais feio mas acho mais simples deixar em um printf só)
    printf("1 - Criar um novo conjunto vazio\n2 - Inserir dados em um conjunto\n3 - Remover um conjunto\n4 - Fazer união entre dois conjuntos\n5 - Fazer a intersecção entre dois conjuntos\n6 - Mostrar um conjunto\n7 - Mostrar todos os conjuntos\n8 - Busca por um valor\n9 - Sair do programa\n");

    printf("Opção: ");
    scanf("%d", &opcao);

    switch (opcao){
        case 1:{
            //+ conjunto VAZIO
            if (count >= m){
                //Caso o usuário queira adicionar mais de m conjuntos, o programa aparece uma mensagem de erro
                printf("ERRO - Número máximo de conjuntos atingido");
                break;
            }

            //Criação do conjunto vazio
            printf("Vamos criar um novo conjunto vazio!\n");
            int conjunto[count];
            for (int i = 0; i < n; i++){
                conjunto[count] = 0;
                matriz[count][i] = conjunto[count];
            }
            count += 1;
            break;
        }

        case 2:{
            int indice;
            int novo_valor;
            printf("Vamos inserir dados em um conjunto!\n");
            printf("Atenção! Você não pode inserir mais de %d números, esses números não podem ser repetidos.\n", n);
            printf("Dê o índice do conjunto que você deseja alterar: ");
            scanf("%d", &indice);

            if (indice < 0 || indice >= m){
                printf("ERRO - Esse índice não existe. Digite um índice válido.");
            }

            for (int i = 0; i < n; i++){
               do {
                printf("Valor %d: ", i);
                scanf("%d", &novo_valor);

                if (numero_ja_existe(m, n, matriz, indice, novo_valor)){
                    printf("ERRO - Esse número já existe, selecione outro!\n");
                }else{
                    matriz[indice][i] = novo_valor;
                    break;
                }
               } while(1);
        }  
        break;
    }

        case 9:
            printf("Saindo do programa...\n");
            break; 

        default:
            //Caso o usuário digite uma opção inválida - mensagem de erro
            printf("ERRO - Opção inválida. Tente novamente.\n");
    }
    } while (opcao != 9);

    //Imprimir a matriz final, usando pra testar o código.
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("Count: %d", count);

    return 0;
}