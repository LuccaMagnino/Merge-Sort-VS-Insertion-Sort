
typedef struct elemento* Lista;
extern long long troca_count;


Lista* cria_lista_int();
void libera_lista_int(Lista* li);
int insere_lista_final_int(Lista* li, int valor);
void imprime_lista_int(Lista* li);
void merge_sort_int(Lista* li, int ordem);

