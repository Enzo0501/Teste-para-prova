#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE *arquivo;
    int i;

    arquivo = fopen("dados.txt", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    for (i = 0; i < 100; i++)
    {
        fprintf(arquivo, "%d\n", i+1);
    }

    fclose(arquivo);
}