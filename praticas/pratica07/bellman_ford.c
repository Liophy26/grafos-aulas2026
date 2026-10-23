
#include <stdio.h>
#include <limits.h>
#include "bellman_ford.h"



int bellman_ford(
    GrafoListaPonderado *g,
    int origem,
    int *dist,
    int *pred
) {
    int n = g->num_vertices;

    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }

    dist[origem] = 0;

    for (int i = 0; i < n - 1; i++) {
        int alterou = 0;

        for (int u = 0; u < n; u++) {
            if (dist[u] == INT_MAX)
                continue;

           
          
        }

        if (!alterou)
            break;
    }

    return 1;
}

void reconstruir_ciclo_negativo(
    int n,
    int *pred,
    int vertice
) {
    int atual = vertice;

    
    for (int i = 0; i < n; i++) {
        if (atual == -1)
            return;

        atual = pred[atual];
    }

    if (atual == -1)
        return;

    int inicio = atual;

    printf("Ciclo negativo encontrado: %d", inicio);

    atual = pred[inicio];

    while (atual != -1 && atual != inicio) {
        printf(" <- %d", atual);
        atual = pred[atual];
    }

    if (atual == inicio)
        printf(" <- %d", inicio);

    printf("\n");
}
