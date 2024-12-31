#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "li.h"

#define BUFFER_SIZE 1024

void arquivo(char *arquivo, Lista *lista)
{
    FILE *file = fopen(arquivo, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", arquivo);
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    
    char *nome = (char*)malloc(BUFFER_SIZE * sizeof(char));
    if (nome == NULL) {
        printf("Erro de alocação de memória\n");
        fclose(file);
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), file))
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(nome, buffer);
        insertion(lista, nome);
        nome = (char*)malloc(BUFFER_SIZE * sizeof(char));
    }

    fclose(file);
    free(nome);
}

int main()
{
    Lista *lista = cria_lista();
    clock_t begin, end;
    double time_crescente, time_decrescente;

    printf("Abrindo o arquivo!\n\n");
    arquivo("nomes_aleatorios.txt", lista);

    printf("Nomes antes de ordena-los:\n");
    imprime_lista(lista);
    printf("\n-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#\n\n");

    begin = clock();
    printf("Nomes depois de ordena-los de forma crescente:\n");
    ordenar_crescente(lista);
    end = clock();
    time_crescente = (double)(end - begin) / CLOCKS_PER_SEC;
    
    imprime_lista(lista);
    printf("\n-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#\n\n");

    begin = clock();
    printf("Nomes depois de ordena-los de forma decrescente:\n");
    ordenar_decrescente(lista);
    end = clock();
    time_decrescente = (double)(end - begin) / CLOCKS_PER_SEC;

    imprime_lista(lista);
    printf("\n-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#\n\n");

    printf("Tempo ordenação crescente: %lf segundos\n", time_crescente);
    printf("Tempo ordenação decrescente: %lf segundos\n", time_decrescente);
    printf("Tempo total de ordenação: %lf segundos\n", time_crescente + time_decrescente);

    libera_lista(lista);
    return 0;
}

//100.000 nomes = 187,635 segundos
//
