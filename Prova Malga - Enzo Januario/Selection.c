#include <stdio.h>
#include <stdlib.h>

int main(){

    int i, j, tam, menor, aux;

    printf("Insira o tamanho do vetor: ");
    scanf("%d", &tam);

    int vet[tam];

    for (i = 0; i < tam; i++)
    {
        printf("Insira o elemento: ");
        scanf("%d", &vet[i]);
    }

    for (i = 0; i < tam - 1 ; i++)
    {
        menor = i;

        for ( j = i+1; j < tam; j++)
        {
            if (vet[j] < vet[menor])
            {
                menor = j;
            }
            
        }

        if(i != menor){
            aux = vet[i];
            vet[i] = vet[menor];
            vet[menor] = aux;
        }
        
    }

    printf("Vetor ordenado: ");
    for (i = 0; i < tam; i++)
    {
        printf("%d ", vet[i]);
    }
    
    
    
}