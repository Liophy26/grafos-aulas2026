#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista* criar_grafo_lista(int n) {
    GrafoLista* g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->n = n;
    g->adj = (No**) calloc(n, sizeof(No*));
    return g;
}

void inserir_aresta_lista(GrafoLista* g, int origem, int destino) {
    No* novo = (No*) malloc(sizeof(No));
    novo->destino = destino;
    novo->prox = g->adj[origem];
    g->adj[origem] = novo;
}

void remover_aresta_lista(GrafoLista* g, int origem, int destino) {
    No* atual = g->adj[origem];
    No* anterior = NULL;
    while (atual != NULL) {
        if (atual->destino == destino) {
            if (anterior == NULL) {
                g->adj[origem] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

int grau_lista(GrafoLista* g, int v) {
    int grau = 0;
    No* atual = g->adj[v];
    while (atual != NULL) {
        grau++;
        atual = atual->prox;
    }
    return grau;
}

int sao_adjacentes_lista(GrafoLista* g, int origem, int destino) {
    No* atual = g->adj[origem];
    while (atual != NULL) {
        if (atual->destino == destino) return 1;
        atual = atual->prox;
    }
    return 0;
}

void imprimir_lista(GrafoLista* g) {
    printf("Listas de Adjacencia:\n");
    for (int i = 0; i < g->n; i++) {
        printf("%d -> ", i);
        No* atual = g->adj[i];
        while (atual != NULL) {
            printf("%d ", atual->destino);
            atual = atual->prox;
        }
        printf("\n");
    }
}

void liberar_grafo_lista(GrafoLista* g) {
    for (int i = 0; i < g->n; i++) {
        No* atual = g->adj[i];
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->adj);
    free(g);
}
