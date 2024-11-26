#include <stdio.h>
#include <stdlib.h>

void quick(int vet[], int inicio, int fim)
{
    int pivo = inicio, ch, i, j;

    for(i = inicio+1; i <= fim ;i++){
        j = i;
        if(vet[j] < vet[pivo]){
            ch = vet[j];
            while(j > pivo){
                vet[j] = vet[j-1];
                j--;
            }
            vet[j] = ch;
            pivo++;
        }
    }

    if(pivo-1 >= inicio)
        quick(vet,inicio,pivo-1);
    if(pivo+1 <= fim)
        quick(vet,pivo+1,fim);

}


int main(){

    int i, j, tam, escolha, aux, menor;

    printf("Insira o tamanho do vetor: ");
    scanf("%d", &tam);

    int vet[tam];

    for (i = 0; i < tam; i++)
    {
        printf("Insira um elemento: ");
        scanf("%d", &vet[i]);
    }

    printf("\n####METODOS DE ORDENACAO####");
    printf("\n[1] Bubble");
    printf("\n[2] Insertion");
    printf("\n[3] Selection");
    printf("\n[4] Quick");
    printf("\nEscolha um dos metodos: ");
    scanf("%d", &escolha);

    if (escolha == 1)
    {
        for (i = tam - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (vet[j] > vet[j+1])
            {
                aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
            }
            
        }
        
    }
    }

    else if (escolha == 2)
    {
    
    for (i = 1; i < tam; i++){
        aux = vet[i];
        j = i - 1;
        while ((j >= 0) && (aux < vet[j]))
        {
          vet[j+1] = vet[j];
          j--;
        }
        vet[j+1] = aux;
        
     }
    }
    
    else if (escolha == 3)
    {
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
    }

    else{
        quick(vet,0,tam-1);
    }


    printf("Vetor ordenado: ");
    for (i = 0; i < tam; i++)
    {
        printf("%d ", vet[i]);
    }
    

}
