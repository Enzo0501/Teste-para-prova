#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE *arquivo;
    char c;
    int quant;
    
    quant = 0;

    arquivo = fopen("arquivo.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    while ((c = fgetc(arquivo)) != EOF)
    {
        if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        {
            quant++;
        }
    }

    printf("Quantidade de vogais: %d", quant);

    fclose(arquivo);
      
}