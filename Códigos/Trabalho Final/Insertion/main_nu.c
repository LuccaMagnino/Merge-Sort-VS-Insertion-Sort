#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nu.h"

void gerar_ordenacao(Lista *lista, int n)
{
    for (int i = 1; i <= n; i++)
    {
        insertion(lista, i);
    }
}

int main()
{
    int n; //10² ate 10^8
    printf("Digite ate que numero deseja ordenar: \n");
    scanf("%d", &n);

    clock_t begin = clock();

    printf("Seguem os numeros de 1 ate %d: \n", n);

    printf("Numeros em ordem crescente:\n");

    Lista *lista = cria_lista();
    gerar_ordenacao(lista, n);
    ordenar_crescente(lista);
    imprime_lista(lista);
    libera_lista(lista);

    printf("\n-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#\n\n");

    printf("Numeros em ordem decrescente:\n");
    lista = cria_lista();
    gerar_ordenacao(lista, n);
    ordenar_decrescente(lista);
    imprime_lista(lista);
    libera_lista(lista);

    printf("\n-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#\n\n");

    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Tempo demorado: %lf segundos", time_spent);

    return 0;
}
//10² = 0,109 segundos
//10³ = 0,914 segundos
//10^4 = 11,339 segundos
//10^5 = 211,388 segundos
//10^6 =
//10^7 =
//10^8 =