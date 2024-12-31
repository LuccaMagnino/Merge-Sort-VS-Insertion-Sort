// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDinEncad.h"
#include <time.h>

int main() {
    Lista* li = cria_lista();
    int opcao, ordem, max_linhas;
    char nome[50];
    const char* arquivo = "nomes_aleatorios.txt"; 

    // Declaração das variáveis para medição de tempo
    clock_t inicio, fim;
    double tempo_decorrido;

    // Variável para contar trocas
    int swap_count = 0;

    FILE* fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo '%s'.\n", arquivo);
        libera_lista(li);
        return 1;
    }

    printf("Quantas linhas deseja ler do arquivo '%s'? ", arquivo);
    if (scanf("%d", &max_linhas) != 1 || max_linhas <= 0) {
        printf("Entrada inválida.\n");
        fclose(fp);
        libera_lista(li);
        return 1;
    }
    getchar(); // Limpa o buffer do teclado

    printf("Escolha a ordenação:\n");
    printf("1 - Crescente\n");
    printf("2 - Decrescente\n");
    if (scanf("%d", &opcao) != 1 || (opcao != 1 && opcao != 2)) {
        printf("Erro na leitura da opção.\n");
        fclose(fp);
        libera_lista(li);
        return 1;
    }
    getchar(); // Limpa o buffer do teclado

    // Ler o arquivo até o número de linhas pedido
    int linha_atual = 0;
    while (linha_atual < max_linhas && fgets(nome, sizeof(nome), fp) != NULL) {
        nome[strcspn(nome, "\n")] = '\0'; 
        if (!insere_lista_final(li, nome)) {
            printf("Erro ao inserir '%s' na lista.\n", nome);
            fclose(fp);
            libera_lista(li);
            return 1;
        }
        linha_atual++;
    }
    fclose(fp); 

    ordem = (opcao == 1) ? 1 : -1;

    // Medição de tempo antes da ordenação
    inicio = clock();
    merge_sort(li, ordem);
    fim = clock();

    // Cálculo do tempo passado
    tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // Obter a contagem de trocas
    swap_count = get_swap_count(li);

    printf("Tempo de ordenação: %f segundos\n", tempo_decorrido);
    printf("Número de trocas realizadas: %d\n", swap_count);

    // Gerar o arquivo de nomes ordenados
    const char* arquivo_saida = "nomes_ordenados.txt";
    if (write_lista_to_file(li, arquivo_saida)) {
        printf("Arquivo '%s' gerado com sucesso.\n", arquivo_saida);
    } else {
        printf("Falha ao gerar o arquivo '%s'.\n", arquivo_saida);
    }

    // Opcional: Imprimir a lista ordenada no console
    // imprime_lista(li, linha_atual);

    libera_lista(li);

    return 0;
}
