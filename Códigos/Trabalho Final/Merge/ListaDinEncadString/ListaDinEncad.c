// Lista.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDinEncad.h"

// Definição da estrutura para elemento da lista
struct elemento {
    char nome[50];
    struct elemento* prox;
};

// Definição da estrutura da lista encadeada
typedef struct {
    struct elemento* head;
    struct elemento* tail;
    int length;      // Opcional: mantém o tamanho da lista
    int swap_count;  // Contador de trocas durante a ordenação
} ListaEnc;

// Criação da lista
Lista* cria_lista() {
    ListaEnc* li = malloc(sizeof(ListaEnc));
    if (li == NULL) {
        printf("Erro ao alocar memória para a lista.\n");
        exit(1);
    }
    li->head = NULL;
    li->tail = NULL;
    li->length = 0;
    li->swap_count = 0;
    return (Lista*)li;
}

// Inserção no final da lista em O(1)
int insere_lista_final(Lista* li, char* nome) {
    if (li == NULL) return 0;
    struct elemento* no = (struct elemento*)malloc(sizeof(struct elemento));
    if (no == NULL) return 0;
    strcpy(no->nome, nome);
    no->prox = NULL;

    ListaEnc* lista = (ListaEnc*)li;
    if (lista->head == NULL) {
        lista->head = no;
    } else {
        lista->tail->prox = no;
    }
    lista->tail = no;
    lista->length++;
    return 1;
}

// Liberação da lista
void libera_lista(Lista* li) {
    if (li != NULL) {
        ListaEnc* lista = (ListaEnc*)li;
        struct elemento* no = lista->head;
        while (no != NULL) {
            struct elemento* temp = no;
            no = no->prox;
            free(temp);
        }
        free(lista);
    }
}

// Impressão da lista
void imprime_lista(Lista* li, int limite) {
    if (li == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    ListaEnc* lista = (ListaEnc*)li;
    struct elemento* no = lista->head;
    int contador = 0;
    while (no != NULL && contador < limite) {
        printf("%s\n", no->nome);
        no = no->prox;
        contador++;
    }
    if (no != NULL)
        printf("... e mais.\n");
    else
        printf("Fim da Lista\n");
}

// Função para intercalação iterativa com contagem de trocas
static struct elemento* intercala_listas(struct elemento* lista1, struct elemento* lista2, int ordem, ListaEnc* lista) {
    struct elemento dummy;
    struct elemento* tail = &dummy;
    dummy.prox = NULL;

    while (lista1 != NULL && lista2 != NULL) {
        if ((ordem == 1 && strcmp(lista1->nome, lista2->nome) <= 0) ||
            (ordem == -1 && strcmp(lista1->nome, lista2->nome) > 0)) {
            tail->prox = lista1;
            lista1 = lista1->prox;
        } else {
            tail->prox = lista2;
            lista2 = lista2->prox;
        }
        tail = tail->prox;
        lista->swap_count++; // Incrementa a contagem de trocas
    }

    // Anexa o restante da lista que não terminou
    if (lista1 != NULL) tail->prox = lista1;
    else tail->prox = lista2;

    return dummy.prox;
}

// Função recursiva do mergesort top-down com contagem de trocas
static struct elemento* merge_sort_rec(struct elemento* head, int n, int ordem, ListaEnc* lista) {
    if (n < 2) return head;

    // Encontra o meio da lista
    int mid = n / 2;
    struct elemento* curr = head;
    for (int i = 1; i < mid; i++)
        curr = curr->prox;

    struct elemento* right_head = curr->prox;
    curr->prox = NULL; // Separa a lista em duas metades

    // Ordena recursivamente as duas metades
    struct elemento* left_sorted = merge_sort_rec(head, mid, ordem, lista);
    struct elemento* right_sorted = merge_sort_rec(right_head, n - mid, ordem, lista);

    // Intercala as duas metades ordenadas
    return intercala_listas(left_sorted, right_sorted, ordem, lista);
}

// Função principal do merge_sort com contagem de trocas
void merge_sort(Lista* li, int ordem) {
    if (li == NULL) return;

    ListaEnc* lista = (ListaEnc*)li;

    // Zera a contagem de trocas antes da ordenação
    lista->swap_count = 0;

    // Conta o tamanho da lista
    int n = 0;
    struct elemento* aux = lista->head;
    while (aux != NULL) {
        n++;
        aux = aux->prox;
    }

    // Executa o merge sort
    lista->head = merge_sort_rec(lista->head, n, ordem, lista);

    // Atualiza o 'tail' após a ordenação
    if (lista->head == NULL) {
        lista->tail = NULL;
    } else {
        struct elemento* tail = lista->head;
        while (tail->prox != NULL) {
            tail = tail->prox;
        }
        lista->tail = tail;
    }
}

// Obter a contagem de trocas realizadas durante a ordenação
int get_swap_count(Lista* li) {
    if (li == NULL) return 0;
    ListaEnc* lista = (ListaEnc*)li;
    return lista->swap_count;
}

// Escrever a lista ordenada em um arquivo de texto
int write_lista_to_file(Lista* li, const char* filename) {
    if (li == NULL) return 0;

    ListaEnc* lista = (ListaEnc*)li;
    FILE* fout = fopen(filename, "w");
    if (fout == NULL) {
        printf("Erro ao criar o arquivo '%s'.\n", filename);
        return 0;
    }

    struct elemento* no = lista->head;
    while (no != NULL) {
        fprintf(fout, "%s\n", no->nome);
        no = no->prox;
    }
    fclose(fout);
    return 1;
}
