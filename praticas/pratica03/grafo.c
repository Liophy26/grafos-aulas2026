#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

GrafoLista *criar_grafo(int num_vertices) {
if (num_vertices <= 0) {
return NULL;
}

GrafoLista *g = malloc(sizeof(GrafoLista));

if (g == NULL) {
    return NULL;
}

g->num_vertices = num_vertices;

g->adj = calloc(num_vertices, sizeof(No *));

if (g->adj == NULL) {
    free(g);
    return NULL;
}

return g;


}

void adicionar_aresta(GrafoLista *g, int origem, int destino) {
if (g == NULL) {
return;
}

if (origem < 0 || origem >= g->num_vertices ||
    destino < 0 || destino >= g->num_vertices) {
    return;
}

No *novo = malloc(sizeof(No));

if (novo == NULL) {
    return;
}

novo->destino = destino;
novo->prox = g->adj[origem];
g->adj[origem] = novo;


}

void liberar_grafo(GrafoLista *g) {
if (g == NULL) {
return;
}

for (int i = 0; i < g->num_vertices; i++) {
    No *atual = g->adj[i];

    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

free(g->adj);
free(g);


}

void imprimir_grafo(GrafoLista *g) {
if (g == NULL) {
return;
}

for (int i = 0; i < g->num_vertices; i++) {
    printf("%d:", i);

    No *atual = g->adj[i];

    while (atual != NULL) {
        printf(" %d", atual->destino);
        atual = atual->prox;
    }

    printf("\n");
}


}