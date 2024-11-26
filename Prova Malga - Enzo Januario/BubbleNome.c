#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

#define N 5


void bubbleSort(char (*V)[30], int Fim)
{
    int i, j;
    char temp[30];
    for(i = 1; i < Fim; i++)
    {
        for (j = 0; j < Fim-1; j++)
        {
            if(strcmp(V[j],V[j+1]) > 0)
            {
                strcpy(temp,V[j]);
                strcpy(V[j],V[j+1]);
                strcpy(V[j+1],temp);
            }
        }
    }
}

int main()
{
   
    char vet[N][30];
    int i;

    for (i=0; i<N; i++)
    {
        printf("Favor informar o nome da %i pessoa: ", i+1);
        gets(vet[i]);
    }

    bubbleSort(vet, N);

    printf("\n\n################## NOMES ORDENADOS ##################\n");

    for(i=0; i<N; i++)
    {
        printf("%s\n",vet[i]);
    }
}