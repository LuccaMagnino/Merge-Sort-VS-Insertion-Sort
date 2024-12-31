import numpy as np
import matplotlib.pyplot as plt

# Tamanho das entradas
entradas = [10**2, 10**3, 10**4, 10**5, 10**6, 10**7, 10**8]

# Insertion Sort (Lista Encadeada)
tempos_insertion_lista = [0.109, 0.914, 11.339, 211.388, 21138.8, 2113880.0, 211388000.0]  # Exemplos
movimentacoes_insertion_lista = [100, 1000, 10000, 100000, 10**12, 10**14, 10**16]

# Merge Sort (Lista Encadeada)
tempos_merge_lista = [0.02, 0.15, 1.8, 25, 299.88, 3498.60, 39984.0]  # Exemplos
movimentacoes_merge_lista = [80, 800, 8000, 80000, 19931568, 232534966, 2657542475]

# Merge Sort (Vetores)
tempos_merge_vetor = [0.01, 0.1, 1.5, 20, 239.98, 2799.72, 31996.8]  # Exemplos
movimentacoes_merge_vetor = [70, 700, 7000, 70000, 19931568, 232534966, 2657542475]

# Insertion Sort (Vetores)
tempos_insertion_vetor = [0.1, 1, 50, 2000, 40000, 800000, 16000000]  # Pior caso (O(n^2))
movimentacoes_insertion_vetor = [100, 5000, 500000, 20000000, 800000000, 32000000000, 1280000000000]

# Gráfico de tempos de execução
plt.figure(figsize=(12, 6))
plt.plot(entradas, tempos_insertion_lista, label='Insertion Sort (Lista Encadeada)', marker='o')
plt.plot(entradas, tempos_merge_lista, label='Merge Sort (Lista Encadeada)', marker='s')
plt.plot(entradas, tempos_merge_vetor, label='Merge Sort (Vetor)', marker='^')
plt.plot(entradas, tempos_insertion_vetor, label='Insertion Sort (Vetor)', marker='d')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Tamanho da Entrada')
plt.ylabel('Tempo de Execução (s)')
plt.title('Tempo de Execução por Algoritmo e Implementação')
plt.legend()
plt.grid(True, which="both", linestyle='--', linewidth=0.5)
plt.savefig("tempo_execucao_algoritmos.png")
plt.show()

# Gráfico de movimentações
plt.figure(figsize=(12, 6))
plt.plot(entradas, movimentacoes_insertion_lista, label='Insertion Sort (Lista Encadeada)', marker='o')
plt.plot(entradas, movimentacoes_merge_lista, label='Merge Sort (Lista Encadeada)', marker='s')
plt.plot(entradas, movimentacoes_merge_vetor, label='Merge Sort (Vetor)', marker='^')
plt.plot(entradas, movimentacoes_insertion_vetor, label='Insertion Sort (Vetor)', marker='d')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('Tamanho da Entrada')
plt.ylabel('Número de Trocas')
plt.title('Número de Trocas por Algoritmo e Implementação')
plt.legend()
plt.grid(True, which="both", linestyle='--', linewidth=0.5)
plt.savefig("numero_trocas_algoritmos.png")
plt.show()