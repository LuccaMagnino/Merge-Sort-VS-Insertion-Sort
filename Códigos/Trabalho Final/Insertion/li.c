#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "li.h"

struct elemento
{
    char nome[100];
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

int insertion(Lista *lista, char *nome)
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

    strcpy(no->nome, nome);
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

        if (ordenado == NULL || strcmp(atual->nome, ordenado->nome) < 0)
        {
            atual->proximo = ordenado;
            ordenado = atual;
        }
        else
        {
            Elemento *aux = ordenado;
            while (aux->proximo != NULL && strcmp(aux->proximo->nome, atual->nome) < 0)
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

    return 0;
}

void imprime_lista(Lista *lista)
{
    if (lista == NULL)
    {
        printf("Erro na alocacao da lista!\n");
        exit(1);
    }

    Elemento *no = *lista;
    while (no != NULL)
    {
        printf("%s\n", no->nome);
        no = no->proximo;
    }
}
