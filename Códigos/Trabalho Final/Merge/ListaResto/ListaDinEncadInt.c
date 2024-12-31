// ListaDinEncadInt.c
#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadInt.h"

// Variável global para contar as trocas de elementos
long long troca_count = 0;

struct elemento {
    int valor;
    struct elemento* prox;
};

typedef struct elemento Elem;

Lista* cria_lista_int() {
    Lista* li = (Lista*)malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}

void libera_lista_int(Lista* li) {
    if (li != NULL) {
        Elem* no;
        while (*li != NULL) {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int insere_lista_final_int(Lista* li, int valor) {
    if (li == NULL) return 0;
    Elem* no = (Elem*)malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->valor = valor;
    no->prox = NULL;

    if (*li == NULL) { 
        *li = no;
    } else {
        Elem* aux = *li;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = no;
    }
    return 1;
}

void imprime_lista_int(Lista* li) {
    int limite = 20;
    if (li == NULL || *li == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    Elem* no = *li;
    int contador = 0;

    // Imprime os primeiros elementos até atingir o limite
    while (no != NULL && contador < limite) {
        printf("%d, ", no->valor);
        no = no->prox;
        contador++;
    }

    if (no != NULL)
        printf("...\n"); 
    else
        printf("Fim da Lista\n"); 
}

// Função para dividir a lista em duas partes
Elem* divide_lista_int(Elem* head) {
    Elem* slow = head;
    Elem* fast = head;
    Elem* prev = NULL;

    while (fast != NULL && fast->prox != NULL) {
        prev = slow;
        slow = slow->prox;
        fast = fast->prox->prox;
    }
    if (prev != NULL)
        prev->prox = NULL; 

    return slow;
}

// Função para intercalar duas listas
Elem* intercala_listas_int(Elem* lista1, Elem* lista2, int ordem) {
    if (lista1 == NULL) {
        return lista2;
    }
    if (lista2 == NULL) {
        return lista1;
    }

    Elem* result = NULL;

    if ((ordem == 1 && lista1->valor <= lista2->valor) || 
        (ordem == -1 && lista1->valor > lista2->valor)) 
        {
        result = lista1;
        troca_count++; // Incrementa o contador de trocas
        result->prox = intercala_listas_int(lista1->prox, lista2, ordem);
    } else {
        result = lista2;
        troca_count++; // Incrementa o contador de trocas
        result->prox = intercala_listas_int(lista1, lista2->prox, ordem);
    }

    return result;
}

Elem* merge_sort_rec_int(Elem* head, int ordem) {
    if (head == NULL || head->prox == NULL)
        return head;

    Elem* meio = divide_lista_int(head);
    Elem* esquerda = merge_sort_rec_int(head, ordem);
    Elem* direita = merge_sort_rec_int(meio, ordem);

    return intercala_listas_int(esquerda, direita, ordem);
}

void merge_sort_int(Lista* li, int ordem) {
    if (li == NULL || *li == NULL) return;
    *li = merge_sort_rec_int(*li, ordem);
}
