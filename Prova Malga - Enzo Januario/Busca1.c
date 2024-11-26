#include <stdio.h>
#include <stdlib.h>

int main(){

    int tam, i, busca, indice;

    indice = 0;

    printf("Insira o tamanho do vetor: ");
    scanf("%d", &tam);

    int vet[tam];

    for (i = 0; i < tam; i++)
    {
        printf("Insira um elemento: ");
        scanf("%d", &vet[i]);
    }

    printf("Insira um numero para buscar no vetor: ");
    scanf("%d", &busca);

    for (i = 0; i < tam; i++)
    {
        if (busca == vet[i])
        {
            indice = i + 1;
        } 
    }

    if (indice != 0)
    {
        printf("o valor foi encontrado na posicao %d", indice);
    }
    else{
        printf("O elemento nao foi encontrado no vetor");
    }
     
}