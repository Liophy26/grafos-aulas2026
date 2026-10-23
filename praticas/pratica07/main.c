
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "grafo_lista_ponderado.h"
#include "bellman_ford.h"

int main(void) {
    int n = 4;

    GrafoListaPonderado *g = criar_grafo(n);

    if (g == NULL) {
        printf("Erro ao criar grafo.\n");
        return 1;
    }

    adicionar_aresta(g, 0, 1, 1);
    adicionar_aresta(g, 1, 2, -1);
    adicionar_aresta(g, 2, 3, -1);
    adicionar_aresta(g, 3, 1, -1);

    printf("Grafo:\n");
    imprimir_grafo(g);

    int *dist = malloc(n * sizeof(int));
    int *pred = malloc(n * sizeof(int));

    if (dist == NULL || pred == NULL) {
        printf("Erro de alocacao.\n");
        free(dist);
        free(pred);
        liberar_grafo(g);
        return 1;
    }

    if (bellman_ford(g, 0, dist, pred)) {
        printf("\nDistancias a partir do vertice 0:\n");

        for (int i = 0; i < n; i++) {
            if (dist[i] == INT_MAX)
                printf("%d: infinito\n", i);
            else
                printf("%d: %d\n", i, dist[i]);
        }
    } else {
        printf("Ciclo negativo detectado.\n");
    }

    free(dist);
    free(pred);
    liberar_grafo(g);

    return 0;
}
