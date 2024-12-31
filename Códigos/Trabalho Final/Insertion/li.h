#include <stdio.h>

typedef struct elemento* Lista;

Lista* cria_lista();
void libera_lista(Lista* lista);
int insertion(Lista* lista, char *nome);
int ordenar_crescente(Lista* lista);
int ordenar_decrescente(Lista* lista);
void imprime_lista(Lista* lista);

