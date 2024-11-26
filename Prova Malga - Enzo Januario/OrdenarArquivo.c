#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Aluno {
    char nome[30];
    int matricula;
    int idade;
};

void ordenarAlunos(struct Aluno *alunos, int n) {
    struct Aluno temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(alunos[j].nome, alunos[j + 1].nome) > 0) {
                temp = alunos[j];
                alunos[j] = alunos[j + 1];
                alunos[j + 1] = temp;
            }
        }
    }
}

int main() {
    FILE *arquivo;
    int quant, i;
    char c;

    printf("Insira a quantidade de alunos que deseja cadastrar: ");
    scanf("%d", &quant);
    getchar();

    struct Aluno *alunos = (struct Aluno *)malloc(quant * sizeof(struct Aluno));

    for (i = 0; i < quant; i++) {
        printf("Insira o nome do aluno (%d): ", i + 1);
        fgets(alunos[i].nome, 30, stdin);
        alunos[i].nome[strcspn(alunos[i].nome, "\n")] = '\0';
        printf("Insira o número da matrícula: ");
        scanf("%d", &alunos[i].matricula);
        printf("Insira a idade do aluno: ");
        scanf("%d", &alunos[i].idade);
        getchar();
    }

    ordenarAlunos(alunos, quant);

    arquivo = fopen("Alunos.txt", "w");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo para escrita.\n");
        free(alunos);
        return 1;
    }

    for (i = 0; i < quant; i++) {
        fprintf(arquivo, "Aluno: %s\n", alunos[i].nome);
        fprintf(arquivo, "Matrícula: %d\n", alunos[i].matricula);
        fprintf(arquivo, "Idade: %d\n", alunos[i].idade);
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);

    arquivo = fopen("Alunos.txt", "r");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo para leitura.\n");
        free(alunos);
        return 1;
    }

    printf("\nConteúdo do arquivo 'registro.txt':\n");
    while ((c = fgetc(arquivo)) != EOF) {
        putchar(c);
    }

    fclose(arquivo);
    free(alunos);

    return 0;
}
