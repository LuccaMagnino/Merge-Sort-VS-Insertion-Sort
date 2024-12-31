#include <stdio.h>
#include <stdlib.h>
#include "nu.h"

struct elemento
{
    int valor;
    struct elemento *proximo;
};

typedef struct elemento Elemento;

Lista *cria_lista()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    if (lista != NULL)
    {
        *lista = NULL;
    }
    else
    {
        printf("Erro na alocacao da lista!\n");
        exit(1);
    }
    return lista;
}

void libera_lista(Lista *lista)
{
    if (lista != NULL)
    {
        Elemento *no;
        while ((*lista) != NULL)
        {
            no = *lista;
            *lista = (*lista)->proximo;
            free(no);
        }
        free(lista);
    }
    else
    {
        printf("Erro na alocacao da lista!\n");
        exit(1);
    }
}

int insertion(Lista *lista, int valor)
{
    if (lista == NULL)
    {
        printf("Erro na alocacao da lista!\n");
        exit(1);
    }
    Elemento *no = (Elemento *)malloc(sizeof(Elemento));
    if (no == NULL)
    {
        printf("Erro na alocacao do no!\n");
        exit(1);
    }
    no->valor = valor;
    no->proximo = NULL;

    if (*lista == NULL)
    { 
        *lista = no;
    }
    else
    {
        Elemento *aux = *lista;
        while (aux->proximo != NULL)
        {
            aux = aux->proximo;
        }
        aux->proximo = no;
    }
    return 1;
}

int ordenar_crescente(Lista *lista)
{
    if (lista == NULL || *lista == NULL)
    {
        printf("Erro na alocacao da lista!\n");
        exit(1);
    }

    Lista ordenado = NULL;
    Elemento *atual = *lista;

    while (atual != NULL)
    {
        Elemento *proximo = atual->proximo;

        if (ordenado == NULL || atual->valor < ordenado->valor)
        {
            atual->proximo = ordenado;
            ordenado = atual;
        }
        else
        {
            Elemento *aux = ordenado;
            while (aux->proximo != NULL && aux->proximo->valor < atual->valor)
            {
                aux = aux->proximo;
            }
            atual->proximo = aux->proximo;
            aux->proximo = atual;
        }
        atual = proximo;
    }

    *lista = ordenado;
    return 1;
}

int ordenar_decrescente(Lista *lista)
{
    if (lista == NULL || *lista == NULL)
    {
        printf("Erro na alocacao da lista!\n");
        exit(1);
    }

    if (ordenar_crescente(lista))
    {
        Elemento *anterior = NULL;
        Elemento *atual = *lista;
        Elemento *proximo;

        while (atual != NULL)
        {
            proximo = atual->proximo;
            atual->proximo = anterior;
            anterior = atual;
            atual = proximo;
        }

        *lista = anterior;
        return 1;
    }
    return 0;
}

void imprime_lista(Lista *lista)
{
    if (lista == NULL)
    {
        printf("Errona alocacao da lista!\n");
        exit(1);
    }

    Elemento *no = *lista;
    while (no != NULL)
    {
        printf("%d\n", no->valor);
        no = no->proximo;
    }
}
