#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Alunos
{
    char nome[30];
    int matricula;
    int idade;
};

int main(){

    FILE *arquivo;
    int quant, i;
    char c;

    printf("Insira a quant de alunos que deseja cadastrar: ");
    scanf("%d", &quant);

    struct Alunos *alunos = (struct Alunos *) malloc (quant * sizeof(struct Alunos));

    for ( i = 0; i < quant; i++)
    {
        printf("Insira o nome do aluno(%d): ", i+1);
        fflush(stdin);
        gets(alunos[i].nome);
        printf("Insira o numero da matricula: ");
        scanf("%d", &alunos[i].matricula);
        printf("Insira a idade do aluno: ");
        scanf("%d", &alunos[i].idade);
        fprintf(arquivo, "\n");
    }

    arquivo = fopen("registro.txt", "w");

    if (arquivo == NULL)
    {
        printf("nao foi possivel abrir o arquivo");
        return 1;
    }

    for (i = 0; i < quant; i++)
    {
        fprintf(arquivo, "Aluno: %s\n", alunos[i].nome);
        fprintf(arquivo, "Matricula: %d\n", alunos[i].matricula);
        fprintf(arquivo, "Idade: %d\n", alunos[i].idade);
        fprintf(arquivo, "\n");
    }
    
    fclose(arquivo);

    
    arquivo = fopen("registro.txt", "r");

    if (arquivo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo");
        return 1;
    }

    while ((c = fgetc(arquivo)) != EOF)
    {
        printf("%c", c);
    }

    fclose(arquivo);
 
}