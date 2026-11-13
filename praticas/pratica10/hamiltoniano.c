
#include "hamiltoniano.h"
#include <stdlib.h>

static bool backtracking(
    int **grafo,
    int n,
    int *caminho,
    bool *visitado,
    int pos
) {
    if (pos == n) {
        return true;
    }

    int atual = caminho[pos - 1];

    for (int v = 0; v < n; v++) {
        if (!visitado[v] && grafo[atual][v] != 0) {
            caminho[pos] = v;
            visitado[v] = true;

            if (backtracking(grafo, n, caminho,
                             visitado, pos + 1)) {
                return true;
            }

            visitado[v] = false;
        }
    }

    return false;
}

bool encontrar_caminho_hamiltoniano_bt(
    int **grafo,
    int n,
    int *caminho
) {
    if (!grafo || !caminho || n <= 0) {
        return false;
    }

    bool *visitado = calloc(n, sizeof(bool));

    if (!visitado) {
        return false;
    }

    // Fixa o vértice inicial em 0.
    caminho[0] = 0;
    visitado[0] = true;

    bool resultado = (n == 1) ||
        backtracking(grafo, n, caminho, visitado, 1);

    free(visitado);
    return resultado;
}
