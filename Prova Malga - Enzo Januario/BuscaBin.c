#include <stdio.h>
#include <stdlib.h>

int buscaBin(int *lista, int inicio, int fim, int chave){

    int meio;

    while (inicio <= fim)
    {
        meio = inicio + (fim - inicio) / 2;
        if (lista[meio] == chave)
        {
            return meio;
        }
        else if (lista[meio] > chave)
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

    int i, j, tam, aux, escolha;
    int busca, resultado;

    printf("Informe o tamanho do vetor: ");
    scanf("%d", &tam);

    int lista[tam];

    for (i = 0; i < tam; i++)
    {
        printf("Insira um elemento: ");
        scanf("%d", &lista[i]);
    }

    printf("Qual metodo de busca vc deseja(0 - Sequencial e 1 - Binaria): ");
    scanf("%d", &escolha);

    if (escolha == 1)
    {
            for (i = tam - 1; i > 0; i--) {
            for (j = 0; j < i; j++) {
                if (lista[j] > lista[j + 1]) { 
                    aux = lista[j];
                    lista[j] = lista[j + 1];
                    lista[j + 1] = aux;
                }
            }
        }

        printf("Insira o numero que deseja buscar: ");
        scanf("%d", &busca);

        resultado = buscaBin(lista, 0, tam, busca);
    }
    
    else{
    printf("Insira o numero que deseja buscar: ");
    scanf("%d", &busca);

    for (i = 0; i < tam; i++)
    {
       if (lista[i] == busca)
       {
        resultado = i;
        break;
       }
       else{
        resultado = -1;
       }
     }
    }

    if (resultado != -1)
    {
        printf("O elemento foi encontrado na posicao %d", resultado + 1);
    }
    else{
        printf("O elemento nao foi encontrado");
    }
    
    
}