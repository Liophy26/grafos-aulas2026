
#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista_ponderado.h"

GrafoListaPonderado *criar_grafo(int num_vertices) {
    if (num_vertices <= 0)
        return NULL;

    GrafoListaPonderado *g =
        malloc(sizeof(GrafoListaPonderado));

    if (g == NULL)
        return NULL;

    g->num_vertices = num_vertices;
    g->lista = calloc(num_vertices, sizeof(Aresta *));

    if (g->lista == NULL) {
        free(g);
        return NULL;
    }

    return g;
}

int adicionar_aresta(
    GrafoListaPonderado *g,
    int origem,
    int destino,
    int peso
) {
    if (g == NULL ||
        origem < 0 || origem >= g->num_vertices ||
        destino < 0 || destino >= g->num_vertices) {
        return 0;
    }

    Aresta *nova = malloc(sizeof(Aresta));

    if (nova == NULL)
        return 0;

    nova->destino = destino;
    nova->peso = peso;
    nova->prox = g->lista[origem];

    g->lista[origem] = nova;

    return 1;
}

void liberar_grafo(GrafoListaPonderado *g) {
    if (g == NULL)
        return;

    for (int i = 0; i < g->num_vertices; i++) {
        Aresta *atual = g->lista[i];

        while (atual != NULL) {
            Aresta *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(g->lista);
    free(g);
}

void imprimir_grafo(GrafoListaPonderado *g) {
    if (g == NULL)
        return;

    for (int i = 0; i < g->num_vertices; i++) {
        printf("%d:", i);

        Aresta *atual = g->lista[i];

        while (atual != NULL) {
            printf(" -> [%d, peso=%d]",
                   atual->destino,
                   atual->peso);

            atual = atual->prox;
        }

        printf("\n");
    }
}
