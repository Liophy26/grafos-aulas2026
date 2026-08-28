#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"

GrafoMatriz* criar_grafo_matriz(int n) {
    GrafoMatriz* g = (GrafoMatriz*) malloc(sizeof(GrafoMatriz));
    g->n = n;
    g->adj = (int*) calloc(n * n, sizeof(int));
    return g;
}

void inserir_aresta_m(GrafoMatriz* g, int origem, int destino) {
    g->adj[origem * g->n + destino] = 1;
}

void remover_aresta_m(GrafoMatriz* g, int origem, int destino) {
    g->adj[origem * g->n + destino] = 0;
}

int grau_m(GrafoMatriz* g, int v) {
    int grau = 0;
    for (int i = 0; i < g->n; i++) {
        grau += g->adj[v * g->n + i];
    }
    return grau;
}

int sao_adjacentes_m(GrafoMatriz* g, int origem, int destino) {
    return g->adj[origem * g->n + destino];
}

void liberar_grafo_m(GrafoMatriz* g) {
    free(g->adj);
    free(g);
}

void imprimir_matriz(GrafoMatriz* g) {
    printf("Matriz de Adjacencia:\n");
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%d ", g->adj[i * g->n + j]);
        }
        printf("\n");
    }
}