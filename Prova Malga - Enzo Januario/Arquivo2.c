#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE *arquivo;
    char c;

    arquivo = fopen("arquivo.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    while((c = fgetc(arquivo)) != EOF){
        printf("%c", c);
    }


    fclose(arquivo);
}