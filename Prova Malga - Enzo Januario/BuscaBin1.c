#include <stdio.h>
#include <stdlib.h>

int buscabin(int *vetor, int inicio, int fim, int chave){

   int meio;

   while (inicio <= fim)
   {
    meio = inicio + (fim  - inicio) / 2;
    if (vetor[meio] == chave)
    {
        return meio;
    }
    else if (vetor[meio] > chave)
    {
        fim = meio - 1;
    }
    else{
        inicio = meio + 1;
    }
    
   } 
    return -1;
} 

int main(){

    int tam, i, j, aux, busca, indice, resultado;

    indice = 0;

    printf("Insira o tamanho do vetor: ");
    scanf("%d", &tam);

    int vet[tam];

    for (i = 0; i < tam; i++)
    {
        printf("Insira um elemento: ");
        scanf("%d", &vet[i]);
    }

   for (i = tam - 1 ; i > 0; i--)
   {
    for (j = 0; j < i; j++)
    {
        if (vet[j] > vet[j + 1])
        {
            aux = vet[j];
            vet[j] = vet[j + 1];
            vet[j + 1] = aux;
        }
     }
   }

    printf("Insira um elemento para ser buscado: ");
    scanf("%d", &busca);

    resultado = buscabin(vet, 0, tam, busca);

    if (resultado != -1)
    {
        printf("O valor foi encontrado na posicao %d", resultado + 1);
    }
    else
    {
        printf("O valor nao foi encontrado");
    }

}