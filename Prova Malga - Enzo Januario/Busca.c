#include <stdio.h>
#include <stdlib.h>

int main(){

    int busca, i, aux;
    int tam;
    aux = 0;

    printf("Insira o tamanho dp vetor: ");
    scanf("%d", &tam);

    int lista[tam];

    for (i = 0; i < tam; i++)
    {
        printf("Insira o elemento: ");
        scanf("%d", &lista[i]);
    }
    
    printf("Insira o numero que deseja buscar: ");
    scanf("%d", &busca);

    for (i = 0; i < tam; i++)
    {
       if (lista[i] == busca)
       {
        aux = i + 1;
       }
    }
    if (aux > 0)
    {
        printf("O elemento foi entrado na posicao: %d", aux);
    }
    else{
        printf("O elemento nao foi encontrado");
    }
    
}