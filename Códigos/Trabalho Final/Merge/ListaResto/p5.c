#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ListaDinEncadInt.h"

/*
merge: ok  
mergeSort: ok
gerarSequenciasNumericas: ok
exibirArray: ok
mergeStrings: ok
mergeSortStrings: ok
lerNomesDoArquivo:ok
exibirNomes: ok
escreverNomesEmArquivo: ok
liberarNomes: ok
gera_sequencia_crescente: ok
gera_sequencia_aleatoria: ok
ListaDinEncadInt: ok
main: falta revisar

Tempos de execuçao: ok
quantidade de troca de elementos: ok
complexidade assintótica:
Gráfico com comportamento dos dados e comparação dos resultados:

*/

// Função para juntar os subarrays (Merge Sort para Inteiros) com contador de movimentações
void merge(int arr[], int left, int mid, int right, int ordem, long long int *contador) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Alocar memória para os subarrays temporários
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        fprintf(stderr, "Erro na alocação de memória em merge.\n");
        exit(EXIT_FAILURE);
    }

    // Copiar dados para os subarrays temporários
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    // Mesclar os subarrays de volta para arr[left..right]
    int i_idx = 0, j_idx = 0, k = left;
    while (i_idx < n1 && j_idx < n2) {
        if ((ordem && L[i_idx] <= R[j_idx]) || (!ordem && L[i_idx] > R[j_idx])) {
            arr[k++] = L[i_idx++];
            (*contador)++; // Incrementa o contador de movimentações
        } else {
            arr[k++] = R[j_idx++];
            (*contador)++; // Incrementa o contador de movimentações
        }
    }

    // Copiar os elementos restantes de L[], se houver
    while (i_idx < n1) {
        arr[k++] = L[i_idx++];
        (*contador)++; // Incrementa o contador de movimentações
    }

    // Copiar os elementos restantes de R[], se houver
    while (j_idx < n2) {
        arr[k++] = R[j_idx++];
        (*contador)++; // Incrementa o contador de movimentações
    }

    // Liberar memória alocada para os subarrays temporários
    free(L);
    free(R);
}

// Merge Sort para Inteiros com contador de movimentações
void mergeSort(int arr[], int left, int right, int ordem, long long int *contador) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, ordem, contador);
        mergeSort(arr, mid + 1, right, ordem, contador);
        merge(arr, left, mid, right, ordem, contador);
    }
}

// Geradora de sequências numéricas
void gerarSequenciasNumericas(int* arr, int n, int tipo) {
    if (tipo == 1) { // Crescente
        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
    } else if (tipo == 2) { // Aleatória
        for (int i = 0; i < n; i++)
            arr[i] = rand() % n + 1;
    } else if (tipo == 3) { // Decrescente
        for (int i = 0; i < n; i++)
            arr[i] = n - i;
    }
}

// Função para exibir um array de inteiros (apenas os primeiros n elementos)
void exibirArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
        if (i % 20 == 19) printf("\n"); 
    }
    printf("\n");
}

// Define o tamanho máximo de um nome e o número máximo de nomes
#define MAX_NOME_LEN 100
#define MAX_NOMES 10000000

// Função para juntar os subarrays (Merge Sort para Strings) com contador de movimentações
void mergeStrings(char **arr, int left, int mid, int right, int ordem, long long int *contador) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Alocar memória para arrays temporários
    char **L = (char **)malloc(n1 * sizeof(char *));
    char **R = (char **)malloc(n2 * sizeof(char *));
    if (L == NULL || R == NULL) {
        fprintf(stderr, "Erro de alocação de memória em mergeStrings.\n");
        exit(EXIT_FAILURE);
    }

    // Copiar dados para os arrays temporários L[] e R[]
    for (int i = 0; i < n1; i++) {
        L[i] = strdup(arr[left + i]);
        if (L[i] == NULL) {
            fprintf(stderr, "Erro de alocação de memória em strdup.\n");
            exit(EXIT_FAILURE);
        }
    }
    for (int j = 0; j < n2; j++) {
        R[j] = strdup(arr[mid + 1 + j]);
        if (R[j] == NULL) {
            fprintf(stderr, "Erro de alocação de memória em strdup.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Mesclar os arrays temporários de volta para arr[left..right]
    int i_idx = 0, j_idx = 0, k = left;

    while (i_idx < n1 && j_idx < n2) {
        int cmp = strcmp(L[i_idx], R[j_idx]);
        if ((ordem && cmp <= 0) || (!ordem && cmp > 0)) {
            free(arr[k]); // Liberar a string antiga
            arr[k] = strdup(L[i_idx]);
            if (arr[k] == NULL) {
                fprintf(stderr, "Erro de alocação de memória em strdup.\n");
                exit(EXIT_FAILURE);
            }
            (*contador)++; // Incrementa o contador de movimentações
            i_idx++;
        } else {
            free(arr[k]); // Liberar a string antiga
            arr[k] = strdup(R[j_idx]);
            if (arr[k] == NULL) {
                fprintf(stderr, "Erro de alocação de memória em strdup.\n");
                exit(EXIT_FAILURE);
            }
            (*contador)++; // Incrementa o contador de movimentações
            j_idx++;
        }
        k++;
    }

    // Copiar os elementos restantes de L[], se houver
    while (i_idx < n1) {
        free(arr[k]); // Liberar a string antiga
        arr[k] = strdup(L[i_idx]);
        if (arr[k] == NULL) {
            fprintf(stderr, "Erro de alocação de memória em strdup.\n");
            exit(EXIT_FAILURE);
        }
        (*contador)++; // Incrementa o contador de movimentações
        i_idx++;
        k++;
    }

    // Copiar os elementos restantes de R[], se houver
    while (j_idx < n2) {
        free(arr[k]); // Liberar a string antiga
        arr[k] = strdup(R[j_idx]);
        if (arr[k] == NULL) {
            fprintf(stderr, "Erro de alocação de memória em strdup.\n");
            exit(EXIT_FAILURE);
        }
        (*contador)++; // Incrementa o contador de movimentações
        j_idx++;
        k++;
    }

    // Liberar memória dos arrays temporários
    for (int i = 0; i < n1; i++) {
        free(L[i]);
    }
    for (int j = 0; j < n2; j++) {
        free(R[j]);
    }
    free(L);
    free(R);
}

// Merge Sort para Strings com contador de movimentações
void mergeSortStrings(char **arr, int left, int right, int ordem, long long int *contador) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordenar a primeira e a segunda metade
        mergeSortStrings(arr, left, mid, ordem, contador);
        mergeSortStrings(arr, mid + 1, right, ordem, contador);

        // Mesclar as duas metades ordenadas
        mergeStrings(arr, left, mid, right, ordem, contador);
    }
}

// Função para ler nomes de um arquivo
int lerNomesDoArquivo(const char *nomeArquivo, char ***nomes, int maxNomes) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return -1;
    }

    int count = 0;
    char buffer[MAX_NOME_LEN];

    // Alocar memória para o array de ponteiros
    *nomes = (char **)malloc(maxNomes * sizeof(char *));
    if (*nomes == NULL) {
        fprintf(stderr, "Erro de alocação de memória para nomes.\n");
        fclose(arquivo);
        return -1;
    }

    while (fgets(buffer, MAX_NOME_LEN, arquivo) != NULL && count < maxNomes) {
        // Remover o caractere de nova linha, se presente
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        // Alocar memória para cada nome e copiar o conteúdo
        (*nomes)[count] = strdup(buffer);
        if ((*nomes)[count] == NULL) {
            fprintf(stderr, "Erro de alocação de memória para um nome.\n");
            // Liberar nomes já alocados
            for (int i = 0; i < count; i++) {
                free((*nomes)[i]);
            }
            free(*nomes);
            fclose(arquivo);
            return -1;
        }
        count++;
    }

    fclose(arquivo);
    return count;
}

// Função para exibir um array de nomes (apenas os primeiros n_exibir)
void exibirNomes(char **nomes, int n, int n_exibir) {
    for (int i = 0; i < n && i < n_exibir; i++) {
        printf("%s\n", nomes[i]);
    }
    if (n > n_exibir) {
        printf("... (total de %d nomes)\n", n);
    }
}

// Função para escrever nomes em um arquivo
void escreverNomesEmArquivo(const char *nomeArquivo, char **nomes, int n) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao criar o arquivo %s.\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "%s\n", nomes[i]);
    }

    fclose(arquivo);
}

// Função para liberar a memória alocada para os nomes
void liberarNomes(char **nomes, int n) {
    for (int i = 0; i < n; i++) {
        free(nomes[i]);
    }
    free(nomes);
}

//A partir daqui colocamos a função da lista numérica


Lista* gera_sequencia_crescente(int tamanho) {
    Lista* li = cria_lista_int();
    for (int i = 1; i <= tamanho; i++) {
        insere_lista_final_int(li, i);
    }
    return li;
}

Lista* gera_sequencia_aleatoria(int tamanho) {
    Lista* li = cria_lista_int();
    //srand(time(NULL));
    for (int i = 0; i < tamanho; i++) {
        insere_lista_final_int(li, rand() % tamanho + 1); // Gera números entre 1 e 100(GPT)
    }
    return li;
}

int main() {

    srand(time(NULL));
    int n = 100000; 

    // Variáveis para armazenar os tempos de ordenação
    double tempo_num_crescente = 0.0;
    double tempo_num_aleatorio = 0.0;
    double tempo_num_decrescente = 0.0;
    double tempo_str_crescente = 0.0;
    double tempo_str_decrescente = 0.0;

    // Variáveis para armazenar os contadores de movimentações
    long long int movimentacoes_num_crescente = 0;
    long long int movimentacoes_num_aleatorio = 0;
    long long int movimentacoes_num_decrescente = 0;
    long long int movimentacoes_str_crescente = 0;
    long long int movimentacoes_str_decrescente = 0;

    printf("Testando sequências numéricas...\n");
    for (int i = 1; i <= 3; i++) {
        // Alocar memória para o array de números
        int* arr = (int*)malloc(n * sizeof(int));
        if (!arr) {
            printf("Erro ao alocar memória.\n");
            exit(1);
        }

        // Gerar a sequência numérica de acordo com o tipo
        gerarSequenciasNumericas(arr, n, i);
        printf("\nSequência %d inicial (primeiros 20 elementos):\n", i);
        exibirArray(arr, n < 20 ? n : 20); // Exibe apenas os primeiros 20 números

        clock_t start_time, end_time;
        double cpu_time_used;

        start_time = clock(); // Início da ordenação

        // Executar a ordenação de acordo com o tipo
        if (i == 1) {
            printf("Ordenando sequência crescente...\n");
            mergeSort(arr, 0, n - 1, 1, &movimentacoes_num_crescente);
        } else if (i == 2) {
            printf("Ordenando sequência aleatória...\n");
            mergeSort(arr, 0, n - 1, 1, &movimentacoes_num_aleatorio);
        } else if (i == 3) {
            printf("Ordenando sequência decrescente...\n");
            mergeSort(arr, 0, n - 1, 0, &movimentacoes_num_decrescente);
        }

        end_time = clock(); // Fim da ordenação
        cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

        printf("Tempo de ordenação: %.6f segundos\n", cpu_time_used);

        // Armazenar os tempos em variáveis separadas
        if (i == 1) {
            tempo_num_crescente = cpu_time_used;
        } else if (i == 2) {
            tempo_num_aleatorio = cpu_time_used;
        } else if (i == 3) {
            tempo_num_decrescente = cpu_time_used;
        }

        // Exibir o número de movimentações
        if (i == 1) {
            printf("Número de movimentações: %lld\n", movimentacoes_num_crescente);
        } else if (i == 2) {
            printf("Número de movimentações: %lld\n", movimentacoes_num_aleatorio);
        } else if (i == 3) {
            printf("Número de movimentações: %lld\n", movimentacoes_num_decrescente);
        }

        printf("Resultado (primeiros 20 elementos):\n");
        exibirArray(arr, n < 20 ? n : 20); // Exibe apenas os primeiros 20 números para verificação
        free(arr); // Liberar memória alocada
    }

    printf("\nTestando entradas textuais...\n");

    char **nomes = NULL;
    int num_nomes;

    // Ler nomes do arquivo "nomes_aleatorios.txt"
    num_nomes = lerNomesDoArquivo("nomes_aleatorios.txt", &nomes, MAX_NOMES);
    if (num_nomes < 0) {
        return 1; // Erro ao ler o arquivo
    }

    printf("Total de nomes lidos: %d\n", num_nomes);

    printf("\nOriginal (primeiros 20 nomes):\n");
    exibirNomes(nomes, num_nomes, 20);

    // Ordenar em ordem crescente
    printf("\nOrdenando em ordem crescente...\n");
    clock_t start_time_str, end_time_str;
    double cpu_time_used_str;

    start_time_str = clock(); // Início da ordenação
    mergeSortStrings(nomes, 0, num_nomes - 1, 1, &movimentacoes_str_crescente);
    end_time_str = clock(); // Fim da ordenação
    cpu_time_used_str = ((double) (end_time_str - start_time_str)) / CLOCKS_PER_SEC;

    tempo_str_crescente = cpu_time_used_str;

    printf("Tempo de ordenação: %.6f segundos\n", cpu_time_used_str);
    printf("Número de movimentações: %lld\n", movimentacoes_str_crescente);

    // Salvar nomes ordenados em arquivo
    escreverNomesEmArquivo("nomes_ordenados_crescente_vetor.txt", nomes, num_nomes);
    printf("Ordenados (Crescente) salvos em 'nomes_ordenados_crescente_vetor.txt'\n");

    // Ordenar em ordem decrescente
    printf("\nOrdenando em ordem decrescente...\n");
    start_time_str = clock(); // Início da ordenação
    mergeSortStrings(nomes, 0, num_nomes - 1, 0, &movimentacoes_str_decrescente);
    end_time_str = clock(); // Fim da ordenação
    cpu_time_used_str = ((double) (end_time_str - start_time_str)) / CLOCKS_PER_SEC;

    tempo_str_decrescente = cpu_time_used_str;

    printf("Tempo de ordenação: %.6f segundos\n", cpu_time_used_str);
    printf("Número de movimentações: %lld\n", movimentacoes_str_decrescente);

    // Salvar nomes ordenados em arquivo
    escreverNomesEmArquivo("nomes_ordenados_decrescente_vetor.txt", nomes, num_nomes);
    printf("Ordenados (Decrescente) salvos em 'nomes_ordenados_decrescente_vetor.txt'\n");

    // Liberar memória alocada
    liberarNomes(nomes, num_nomes);

    // Exibir todos os tempos e movimentações de ordenação no terminal
    printf("\n=== Resumo dos Tempos e Movimentações de Ordenação ===\n");
    printf("Ordenação de Números:\n");
    printf("  - Crescente:   %.6f segundos, %lld movimentações\n", tempo_num_crescente, movimentacoes_num_crescente);
    printf("  - Aleatória:   %.6f segundos, %lld movimentações\n", tempo_num_aleatorio, movimentacoes_num_aleatorio);
    printf("  - Decrescente: %.6f segundos, %lld movimentações\n", tempo_num_decrescente, movimentacoes_num_decrescente);
    printf("\nOrdenação de Strings:\n");
    printf("  - Crescente:   %.6f segundos, %lld movimentações\n", tempo_str_crescente, movimentacoes_str_crescente);
    printf("  - Decrescente: %.6f segundos, %lld movimentações\n", tempo_str_decrescente, movimentacoes_str_decrescente);
    printf("========================================================\n");


    // A partir daqui temos o código da lista numérica

    double tempo_a, tempo_b, tempo_c;
    long long trocas_a, trocas_b, trocas_c;
    clock_t inicio_lista_num, fim_lista_num;
    double tempo_decorrido;

    // Ordenação da lista_a (sequência crescente)
    Lista* lista_a = gera_sequencia_crescente(n);
    printf("Lista crescente:\n");
    imprime_lista_int(lista_a);
    
    troca_count = 0; // Reseta o contador de trocas
    inicio_lista_num = clock();
    merge_sort_int(lista_a, 1);
    fim_lista_num = clock();
    tempo_a = ((double)(fim_lista_num - inicio_lista_num)) / CLOCKS_PER_SEC;
    trocas_a = troca_count; // Captura o número de trocas
    
    printf("Tempo de ordenação da lista_a: %f segundos\n", tempo_a);
    printf("Número de trocas na lista_a: %lld\n", trocas_a);
    
    printf("Lista ordenada crescente:\n");
    imprime_lista_int(lista_a);
    libera_lista_int(lista_a);
    
    // Ordenação da lista_b (sequência aleatória)
    Lista* lista_b = gera_sequencia_aleatoria(n);
    printf("Lista aleatória:\n");
    imprime_lista_int(lista_b);
    
    troca_count = 0; // Reseta o contador de trocas
    inicio_lista_num = clock();
    merge_sort_int(lista_b, 1);
    fim_lista_num = clock();
    tempo_b = ((double)(fim_lista_num - inicio_lista_num)) / CLOCKS_PER_SEC;
    trocas_b = troca_count; // Captura o número de trocas
    
    printf("Tempo de ordenação da lista_b: %f segundos\n", tempo_b);
    printf("Número de trocas na lista_b: %lld\n", trocas_b);
    
    printf("Lista ordenada crescente:\n");
    imprime_lista_int(lista_b);
    libera_lista_int(lista_b);
    
    // Ordenação da lista_c (sequência crescente para decrescente)
    Lista* lista_c = gera_sequencia_crescente(n);
    printf("Lista crescente:\n");
    imprime_lista_int(lista_c);
    
    troca_count = 0; // Reseta o contador de trocas
    inicio_lista_num = clock();
    merge_sort_int(lista_c, -1);
    fim_lista_num = clock();
    tempo_c = ((double)(fim_lista_num - inicio_lista_num)) / CLOCKS_PER_SEC;
    trocas_c = troca_count; // Captura o número de trocas
    
    printf("Tempo de ordenação da lista_c: %f segundos\n", tempo_c);
    printf("Número de trocas na lista_c: %lld\n", trocas_c);
    
    printf("Lista ordenada decrescente:\n");
    imprime_lista_int(lista_c);
    libera_lista_int(lista_c);
    
    // Relatório Final
    printf("\n=== Relatório Final ===\n");
    printf("Operação\t\tTempo (s)\tTrocas\n");
    printf("Lista A (Crescente)\t%f\t%lld\n", tempo_a, trocas_a);
    printf("Lista B (Aleatória)\t%f\t%lld\n", tempo_b, trocas_b);
    printf("Lista C (Decrescente)\t%f\t%lld\n", tempo_c, trocas_c);

    return 0;
}
