#include <stdio.h>
#include <stdlib.h>
#include "grafolista.h"

GrafoLista *criar_grafo(int numVertices)
{
    if (numVertices <= 0)
        return NULL;

    GrafoLista *g = malloc(sizeof(GrafoLista));

    if (g == NULL)
        return NULL;

    g->numVertices = numVertices;

    g->listas = calloc(numVertices, sizeof(No *));

    if (g->listas == NULL) {
        free(g);
        return NULL;
    }

    return g;
}

void liberar_grafo(GrafoLista *g)
{
    if (g == NULL)
        return;

    for (int i = 0; i < g->numVertices; i++) {
        No *atual = g->listas[i];

        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(g->listas);
    free(g);
}

void adicionar_aresta(GrafoLista *g, int origem, int destino)
{
    if (g == NULL)
        return;

    if (origem < 0 || origem >= g->numVertices ||
        destino < 0 || destino >= g->numVertices)
        return;

    No *novo = malloc(sizeof(No));

    if (novo == NULL)
        return;

    novo->destino = destino;
    novo->prox = g->listas[origem];

    g->listas[origem] = novo;
}

void adicionar_aresta_nao_direcionada(GrafoLista *g, int u, int v)
{
    adicionar_aresta(g, u, v);
    adicionar_aresta(g, v, u);
}

void imprimir_grafo(GrafoLista *g)
{
    if (g == NULL)
        return;

    printf("\nGrafo:\n");

    for (int i = 0; i < g->numVertices; i++) {
        printf("%d: ", i);

        No *atual = g->listas[i];

        while (atual != NULL) {
            printf("%d -> ", atual->destino);
            atual = atual->prox;
        }

        printf("NULL\n");
    }
}
