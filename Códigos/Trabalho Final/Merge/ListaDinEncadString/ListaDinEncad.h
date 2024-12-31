// ListaDinEncad.h

#ifndef LISTADINENCAD_H
#define LISTADINENCAD_H

typedef struct elemento* Lista;

// Criação da lista
Lista* cria_lista();

// Liberação da lista
void libera_lista(Lista* li);

// Inserção no final da lista
int insere_lista_final(Lista* li, char* nome);

// Impressão da lista
void imprime_lista(Lista* li, int limite);

// Ordenação da lista com merge sort
void merge_sort(Lista* li, int ordem);

// Obter a contagem de trocas realizadas durante a ordenação
int get_swap_count(Lista* li);

// Escrever a lista ordenada em um arquivo de texto
int write_lista_to_file(Lista* li, const char* filename);

#endif // LISTADINENCAD_H
