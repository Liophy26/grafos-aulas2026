
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "hamiltoniano.h"
#include "tps.h"

/* Cria matriz de adjacência */
int **criar_grafo(int n) {
    int **grafo = malloc(n * sizeof(int *));

    if (!grafo) return NULL;

    for (int i = 0; i < n; i++) {
        grafo[i] = calloc(n, sizeof(int));

        if (!grafo[i]) {
            for (int j = 0; j < i; j++) {
                free(grafo[j]);
            }

            free(grafo);
            return NULL;
        }
    }

    return grafo;
}

/* Libera matriz */
void liberar_grafo(int **grafo, int n) {
    if (!grafo) return;

    for (int i = 0; i < n; i++) {
        free(grafo[i]);
    }

    free(grafo);
}

/* Gera grafo completo e não direcionado */
void gerar_grafo(int **grafo, int n) {
    srand(42 + n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int peso = 1 + rand() % 100;

            grafo[i][j] = peso;
            grafo[j][i] = peso;
        }
    }
}

/* Imprime caminho */
void imprimir_caminho(int *caminho, int n) {
    if (!caminho) {
        printf("Indisponivel");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", caminho[i]);
    }

    printf("%d", caminho[0]);
}

/* Executa um algoritmo e mede tempo */
void executar_teste(
    const char *nome,
    ResultadoTSP (*algoritmo)(int **, int),
    int **grafo,
    int n
) {
    clock_t inicio = clock();

    ResultadoTSP resultado = algoritmo(grafo, n);

    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("%-24s | ", nome);

    if (resultado.caminho && resultado.custo != INT_MAX) {
        printf("%10d | %12.6f s | ",
               resultado.custo, tempo);

        imprimir_caminho(resultado.caminho, n);
        printf("\n");
    } else {
        printf("Sem resultado | %12.6f s\n", tempo);
    }

    liberar_resultado(resultado);
}

int main(void) {
    int tamanhos[] = {5, 8, 10, 12};
    int quantidade = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("===============================================\n");
    printf("       EXPERIMENTO - PROBLEMA DO TSP\n");
    printf("===============================================\n");

    for (int k = 0; k < quantidade; k++) {
        int n = tamanhos[k];

        printf("\n========== GRAFO COM %d VERTICES ==========\n", n);

        int **grafo = criar_grafo(n);

        if (!grafo) {
            printf("Erro ao alocar grafo.\n");
            return 1;
        }

        gerar_grafo(grafo, n);

        printf("\n%-24s | %-10s | %-14s | Caminho\n",
               "Algoritmo", "Custo", "Tempo");

        printf("------------------------------------------------"
               "--------------------------------\n");

        // Teste do caminho Hamiltoniano
        int *caminho = malloc(n * sizeof(int));

        if (caminho) {
            clock_t inicio = clock();

            int encontrou =
                encontrar_caminho_hamiltoniano_bt(
                    grafo, n, caminho
                );

            clock_t fim = clock();

            double tempo =
                (double)(fim - inicio) / CLOCKS_PER_SEC;

            printf("\nCaminho Hamiltoniano: %s\n",
                   encontrou ? "Encontrado" : "Nao encontrado");

            if (encontrou) {
                imprimir_caminho(caminho, n);
                printf("\n");
            }

            printf("Tempo Backtracking: %.6f segundos\n",
                   tempo);

            free(caminho);
        }

        // Algoritmos TSP
        executar_teste(
            "Forca Bruta",
            tsp_forca_bruta,
            grafo, n
        );

        executar_teste(
            "Vizinho Mais Proximo",
            tsp_vizinho_mais_proximo,
            grafo, n
        );

        executar_teste(
            "Insercao do Mais Proximo",
            tsp_insercao,
            grafo, n
        );

        // Teste da redução
        int **tsp = grafo_para_tsp(grafo, n);

        if (tsp) {
            printf("\nReducao do grafo para TSP:\n");

            executar_teste(
                "TSP apos reducao",
                tsp_vizinho_mais_proximo,
                tsp, n
            );

            liberar_grafo(tsp, n);
        }

        liberar_grafo(grafo, n);
    }

    printf("\n===============================================\n");
    printf("             FIM DOS EXPERIMENTOS\n");
    printf("===============================================\n");

    return 0;
}
