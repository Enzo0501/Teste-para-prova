#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define N 5

void bubbleSort(char (*V)[30], int Fim)
{
    int i, j;
    char temp[30];
    for(i = 1; i < Fim; i++)
    {
        for (j = 0; j < Fim-1; j++)
        {
            if(strcmp(V[j], V[j+1]) > 0)
            {
                strcpy(temp, V[j]);
                strcpy(V[j], V[j+1]);
                strcpy(V[j+1], temp);
            }
        }
    }
}

// Busca sequencial
int buscaSequencial(char (*V)[30], int Fim, char* nome)
{
    for (int i = 0; i < Fim; i++)
    {
        if (strcmp(V[i], nome) == 0)
            return i; // Retorna a posição do nome
    }
    return -1; // Nome não encontrado
}

// Busca binária
int buscaBinaria(char (*V)[30], int Fim, char* nome)
{
    int inicio = 0, fim = Fim - 1, meio;
    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;
        int comparacao = strcmp(V[meio], nome);
        if (comparacao == 0)
            return meio; // Retorna a posição do nome
        else if (comparacao < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1; // Nome não encontrado
}

int main()
{
    setlocale(LC_ALL, ""); // Suporte a caracteres acentuados
   
    char vet[N][30];
    char nomeBusca[30];
    int i, posicao, escolha;

    // Entrada de nomes
    for (i = 0; i < N; i++)
    {
        printf("Favor informar o nome da %iª pessoa: ", i + 1);
        gets(vet[i]);
    }

    // Escolha do tipo de busca
    printf("\nEscolha o tipo de busca:\n");
    printf("1 - Busca Sequencial\n");
    printf("2 - Busca Binária\n");
    printf("Opção: ");
    scanf("%d", &escolha);
    getchar(); // Limpa o buffer do teclado

    // Solicita o nome para buscar
    printf("\nDigite o nome que deseja buscar: ");
    gets(nomeBusca);

    if (escolha == 1)
    {
        // Busca sequencial
        printf("\nUtilizando busca sequencial:\n");
        posicao = buscaSequencial(vet, N, nomeBusca);
        if (posicao != -1)
            printf("Nome encontrado na posição %d.\n", posicao + 1);
        else
            printf("Nome não encontrado.\n");
    }
    else if (escolha == 2)
    {
        // Ordenação necessária para busca binária
        bubbleSort(vet, N);

        // Exibição dos nomes ordenados
        printf("\n\n################## NOMES ORDENADOS ##################\n");
        for (i = 0; i < N; i++)
        {
            printf("%s\n", vet[i]);
        }

        // Busca binária
        printf("\nUtilizando busca binária:\n");
        posicao = buscaBinaria(vet, N, nomeBusca);
        if (posicao != -1)
            printf("Nome encontrado na posição %d.\n", posicao + 1);
        else
            printf("Nome não encontrado.\n");
    }
    else
    {
        printf("Opção inválida.\n");
    }

    return 0;
}
