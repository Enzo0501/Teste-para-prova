#include <stdlib.h>
#include <stdio.h>

int main(){

    int tam , i, j, aux;

    printf("Insira o tamanho do vetor: ");
    scanf("%d", &tam);

    int vet[tam];

    for (i = 0; i < tam; i++)
    {
        printf("Insira um elemento: ");
        scanf("%d", &vet[i]);
    }

    for (i = 1; i < tam; i++)
    {
        aux = vet[i];
        j = i - 1;
        while ((j >= 0) && (aux < vet[j]))
        {
          vet[j+1] = vet[j];
          j--;
        }
        vet[j+1] = aux;
        
    }

    printf("Vetor ordenado: ");
    for (i = 0; i < tam; i++)
    {
        printf("%d ", vet[i]);
    }
    
    
}