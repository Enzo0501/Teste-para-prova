
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

//============================================
void printfVet(int *V  , int N){
    int i;
    for(i = 0; i < N; i++)
        printf("%2d ",V[i]);
    printf("\n");
}

void printfLinha(){
    printf("----------------------------------------------\n");
}
//============================================

int particiona(int *V, int inicio, int final ){
    int esq, dir, pivo, aux;
    esq = inicio;
    dir = final;
    pivo = V[inicio];
    while(esq < dir){
        while(V[esq] <= pivo)
            esq++;
        while(V[dir] > pivo)
            dir--;
        if(esq < dir){
            aux = V[esq];
            V[esq] = V[dir];
            V[dir] = aux;
        }
    }
    V[inicio] = V[dir];
    V[dir] = pivo;
    return dir;
}

void quickSort(int *V, int inicio, int fim) {
    int pivo;
    if(fim > inicio){
        pivo = particiona(V, inicio, fim);
        quickSort(V, inicio, pivo-1);
        quickSort(V, pivo+1, fim);
    }
}

//============================================

int main(){
	
	setlocale(LC_ALL, "PORTUGUESE");
    int n, i;
	printf("Favor informar o número de valores que deseja ordenar");
	scanf("%d", &n);
	int vet[n];
	
	for(i=0; i<n; i++)
	{
		printf("Favor informar o %iº valor: ", i+1);
		scanf("%d", &vet[i]);
	}

    printf("Sem ordenar:\n");
    printfVet(vet,n);
    printfLinha();

    quickSort(vet,0,n-1);//OK
    printf("Ordenado:\n");
    printfVet(vet,n);

    system("pause");
    return 0;
}