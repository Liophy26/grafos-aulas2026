#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int main(void) {
    int n = 5;
    GrafoListaPonderado *g = criar_grafo(n);

    if (!g) {
        fprintf(stderr, "Erro ao criar o grafo.\n");
        return 1;
    }

    adicionar_aresta(g, 0, 1, 10);
    adicionar_aresta(g, 0, 2, 3);
    adicionar_aresta(g, 2, 1, 1);
    adicionar_aresta(g, 1, 3, 2);
    adicionar_aresta(g, 2, 3, 8);
    adicionar_aresta(g, 2, 4, 2);
    adicionar_aresta(g, 4, 3, 7);
    adicionar_aresta(g, 3, 4, 4);

    int dist[5];
    int pred[5];
    int origem = 0;

    dijkstra(g, origem, dist, pred);

    printf("Menores distancias a partir do vertice %d:\n",
           origem);

    for (int i = 0; i < n; i++) {
        printf("Vertice %d: ", i);

        if (dist[i] == INF) {
            printf("inalcancavel\n");
            continue;
        }

        printf("distancia = %d | caminho: ", dist[i]);

        int *caminho = reconstruir_caminho(origem, i, pred);

        if (!caminho) {
            printf("indisponivel\n");
            continue;
        }

        for (int j = 0; caminho[j] != -1; j++) {
            if (j > 0)
                printf(" -> ");

            printf("%d", caminho[j]);
        }

        printf("\n");
        free(caminho);
    }

    liberar_grafo(g);
    return 0;
}