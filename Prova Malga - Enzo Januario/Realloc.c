#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, M, i;
    int *id;

    printf("Informe quantos usuarios voce deseja cadastrar: ");
    scanf("%d", &N);

    id = (int*) malloc(N * sizeof(int));
    if (id == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    for (i = 0; i < N; i++) {
        printf("Informe o id do usuario %d: ", i + 1);
        scanf("%d", &id[i]);
    }

    printf("\nUsuarios cadastrados inicialmente:\n");
    for (i = 0; i < N; i++) {
        printf("Id %d: %d\n", i + 1, id[i]);
    }

    printf("\nInforme a nova quantidade de usuarios: ");
    scanf("%d", &M);

    id = (int*) realloc(id, M * sizeof(int));
    if (id == NULL) {
        printf("Erro ao realocar memoria.\n");
        return 1;
    }

    if (M > N) {
        for (i = N; i < M; i++) {
            printf("Informe o id do usuario %d: ", i + 1);
            scanf("%d", &id[i]);
        }
    }

    printf("\nUsuarios cadastrados apos a realocacao:\n");
    for (i = 0; i < M; i++) {
        printf("Id %d: %d\n", i + 1, id[i]);
    }

    free(id);

    return 0;
}
