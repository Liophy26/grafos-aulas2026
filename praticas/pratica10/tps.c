
#include "tps.h"
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/* Calcula o custo de um ciclo */
static int calcular_custo(
    int **grafo,
    int *caminho,
    int n
) {
    int custo = 0;

    for (int i = 0; i < n - 1; i++) {
        custo += grafo[caminho[i]][caminho[i + 1]];
    }

    custo += grafo[caminho[n - 1]][caminho[0]];

    return custo;
}

/* Troca dois elementos */
static void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Permutações para força bruta */
static void permutar(
    int **grafo,
    int n,
    int *caminho,
    int pos,
    int *melhorCusto,
    int *melhorCaminho
) {
    if (pos == n) {
        int custo = calcular_custo(grafo, caminho, n);

        if (custo < *melhorCusto) {
            *melhorCusto = custo;

            for (int i = 0; i < n; i++) {
                melhorCaminho[i] = caminho[i];
            }
        }

        return;
    }

    for (int i = pos; i < n; i++) {
        trocar(&caminho[pos], &caminho[i]);

        permutar(
            grafo, n, caminho, pos + 1,
            melhorCusto, melhorCaminho
        );

        trocar(&caminho[pos], &caminho[i]);
    }
}

/* TSP por força bruta */
ResultadoTSP tsp_forca_bruta(int **grafo, int n) {
    ResultadoTSP resultado = {INT_MAX, NULL, n};

    if (!grafo || n <= 0) return resultado;

    resultado.caminho = malloc(n * sizeof(int));

    int *caminho = malloc(n * sizeof(int));

    if (!resultado.caminho || !caminho) {
        free(resultado.caminho);
        free(caminho);
        resultado.caminho = NULL;
        return resultado;
    }

    caminho[0] = 0;

    for (int i = 1; i < n; i++) {
        caminho[i] = i;
    }

    // Fixa a origem em 0: gera (n-1)! permutações.
    permutar(
        grafo, n, caminho, 1,
        &resultado.custo, resultado.caminho
    );

    free(caminho);

    return resultado;
}

/* Vizinho mais próximo */
ResultadoTSP tsp_vizinho_mais_proximo(int **grafo, int n) {
    ResultadoTSP resultado = {INT_MAX, NULL, n};

    if (!grafo || n <= 0) return resultado;

    resultado.caminho = malloc(n * sizeof(int));
    bool *visitado = calloc(n, sizeof(bool));

    if (!resultado.caminho || !visitado) {
        free(resultado.caminho);
        free(visitado);
        resultado.caminho = NULL;
        return resultado;
    }

    int atual = 0;
    resultado.caminho[0] = 0;
    visitado[0] = true;

    for (int i = 1; i < n; i++) {
        int menor = INT_MAX;
        int proximo = -1;

        for (int j = 0; j < n; j++) {
            if (!visitado[j] && grafo[atual][j] < menor) {
                menor = grafo[atual][j];
                proximo = j;
            }
        }

        if (proximo == -1) {
            resultado.custo = INT_MAX;
            free(visitado);
            return resultado;
        }

        resultado.caminho[i] = proximo;
        visitado[proximo] = true;
        atual = proximo;
    }

    resultado.custo = calcular_custo(
        grafo, resultado.caminho, n
    );

    free(visitado);
    return resultado;
}

/* Inserção do vértice mais próximo */
ResultadoTSP tsp_insercao(int **grafo, int n) {
    ResultadoTSP resultado = {INT_MAX, NULL, n};

    if (!grafo || n <= 0) return resultado;

    resultado.caminho = malloc(n * sizeof(int));
    bool *incluido = calloc(n, sizeof(bool));

    if (!resultado.caminho || !incluido) {
        free(resultado.caminho);
        free(incluido);
        resultado.caminho = NULL;
        return resultado;
    }

    if (n == 1) {
        resultado.caminho[0] = 0;
        resultado.custo = grafo[0][0];
        free(incluido);
        return resultado;
    }

    // Ciclo inicial com os vértices 0 e 1.
    resultado.caminho[0] = 0;
    resultado.caminho[1] = 1;

    incluido[0] = true;
    incluido[1] = true;

    int quantidade = 2;

    while (quantidade < n) {
        int escolhido = -1;
        int menorDistancia = INT_MAX;

        // Escolhe o vértice não incluído mais próximo
        // de algum vértice do ciclo.
        for (int v = 0; v < n; v++) {
            if (incluido[v]) continue;

            for (int i = 0; i < quantidade; i++) {
                int u = resultado.caminho[i];

                if (grafo[u][v] < menorDistancia) {
                    menorDistancia = grafo[u][v];
                    escolhido = v;
                }
            }
        }

        if (escolhido == -1) break;

        // Encontra a posição que causa o menor aumento
        // no custo do ciclo.
        int melhorPosicao = 0;
        int menorAumento = INT_MAX;

        for (int i = 0; i < quantidade; i++) {
            int atual = resultado.caminho[i];
            int proximo = resultado.caminho[
                (i + 1) % quantidade
            ];

            int aumento =
                grafo[atual][escolhido] +
                grafo[escolhido][proximo] -
                grafo[atual][proximo];

            if (aumento < menorAumento) {
                menorAumento = aumento;
                melhorPosicao = i + 1;
            }
        }

        // Insere o vértice na posição encontrada.
        for (int i = quantidade; i > melhorPosicao; i--) {
            resultado.caminho[i] =
                resultado.caminho[i - 1];
        }

        resultado.caminho[melhorPosicao] = escolhido;

        incluido[escolhido] = true;
        quantidade++;
    }

    resultado.custo = calcular_custo(
        grafo, resultado.caminho, n
    );

    free(incluido);
    return resultado;
}

/* Redução de grafo para TSP */
int **grafo_para_tsp(int **grafo, int n) {
    if (!grafo || n <= 0) return NULL;

    int **matriz = malloc(n * sizeof(int *));

    if (!matriz) return NULL;

    for (int i = 0; i < n; i++) {
        matriz[i] = malloc(n * sizeof(int));

        if (!matriz[i]) {
            for (int j = 0; j < i; j++) {
                free(matriz[j]);
            }

            free(matriz);
            return NULL;
        }

        for (int j = 0; j < n; j++) {
            if (i == j) {
                matriz[i][j] = 0;
            } else {
                matriz[i][j] =
                    (grafo[i][j] != 0) ? 1 : 2;
            }
        }
    }

    return matriz;
}

/* Libera o resultado */
void liberar_resultado(ResultadoTSP resultado) {
    free(resultado.caminho);
}
