#include <stdio.h>
#include <stdlib.h>

int main(){

    int i, j, aux;
    int tam;
    
    printf("Insira o tamanho do vetor: ");
    scanf("%d", &tam);

    int vet[tam];

    for (i = 0; i < tam; i++)
    {
        printf("Insira um elemento: ");
        scanf("%d", &vet[i]);
    }
    

    for (i = tam - 1; i > 0; i--)
    {
        for (j = 0; j < tam; j++)
        {
            if (vet[j] > vet[j+1])
            {
                aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
            }
            
        }
        
    }

    printf("Vetor ordenado: ");

    for (i = 0; i < tam; i++)
    {
        printf("%d ", vet[i]);
    }
    
    
}