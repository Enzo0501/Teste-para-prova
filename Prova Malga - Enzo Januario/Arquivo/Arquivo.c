#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    FILE *arquivo;
    char frase[30];

    arquivo = fopen("teste.txt", "w");

    printf("Insira uma frase: ");
    fflush(stdin);
    gets(frase);

    fprintf(arquivo, "%s", frase);

    fclose(arquivo);

    arquivo = fopen("teste.txt", "r");

    char c;

    if (arquivo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo :-(");
        return 1;
    }
    

    printf("o que esta escrito no arquivo: ");

    while ((c = fgetc(arquivo)) != EOF)
    {
        printf("%c", c);
    }
    
    fclose(arquivo);
}