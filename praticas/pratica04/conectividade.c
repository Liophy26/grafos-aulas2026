#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conectividade.h"

GrafoLista* criar_grafo(int num_vertices) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->listas = (No**) malloc(num_vertices * sizeof(No*));
    for (int i = 0; i < num_vertices; i++) {
        g->listas[i] = NULL;
    }
    return g;
}

void destruir_grafo(GrafoLista *g) {
    if (g == NULL) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->listas[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->listas);
    free(g);
}

void inserir_aresta_nao_direcionada(GrafoLista *g, int u, int v) {
    if (u < 0 || u >= g->num_vertices || v < 0 || v >= g->num_vertices) return;

    No *novo1 = (No*) malloc(sizeof(No));
    novo1->destino = v;
    novo1->proximo = g->listas[u];
    g->listas[u] = novo1;

    No *novo2 = (No*) malloc(sizeof(No));
    novo2->destino = u;
    novo2->proximo = g->listas[v];
    g->listas[v] = novo2;
}

static void tarjan_articulacoes_util(GrafoLista *g, int u, int *visitado, int *descoberta, 
                                    int *low, int *pai, int *articulacoes, int *tempo) {
    int filhos = 0;
    visitado[u] = 1;
    (*tempo)++;
    descoberta[u] = *tempo;
    low[u] = *tempo;

    No *atual = g->listas[u];
    while (atual != NULL) {
        int v = atual->destino;

        if (!visitado[v]) {
            filhos++;
            pai[v] = u;
            tarjan_articulacoes_util(g, v, visitado, descoberta, low, pai, articulacoes, tempo);

            if (low[v] < low[u]) {
                low[u] = low[v];
            }

            if (pai[u] == -1 && filhos > 1) {
                articulacoes[u] = 1;
            }

            if (pai[u] != -1 && low[v] >= descoberta[u]) {
                articulacoes[u] = 1;
            }
        } else if (v != pai[u]) {
            if (descoberta[v] < low[u]) {
                low[u] = descoberta[v];
            }
        }
        atual = atual->proximo;
    }
}

void dfs_articulacoes(GrafoLista *g, int *articulacoes) {
    int V = g->num_vertices;
    int *visitado = (int*) malloc(V * sizeof(int));
    int *descoberta = (int*) malloc(V * sizeof(int));
    int *low = (int*) malloc(V * sizeof(int));
    int *pai = (int*) malloc(V * sizeof(int));

    memset(visitado, 0, V * sizeof(int));
    memset(articulacoes, 0, V * sizeof(int));
    for (int i = 0; i < V; i++) {
        pai[i] = -1;
    }

    int tempo = 0;
    for (int i = 0; i < V; i++) {
        if (!visitado[i]) {
            tarjan_articulacoes_util(g, i, visitado, descoberta, low, pai, articulacoes, &tempo);
        }
    }

    free(visitado);
    free(descoberta);
    free(low);
    free(pai);
}

static void pontes_util(GrafoLista *g, int u, int *visitado, int *descoberta, 
                        int *low, int *pai, int *tempo) {
    visitado[u] = 1;
    (*tempo)++;
    descoberta[u] = *tempo;
    low[u] = *tempo;

    No *atual = g->listas[u];
    while (atual != NULL) {
        int v = atual->destino;

        if (!visitado[v]) {
            pai[v] = u;
            pontes_util(g, v, visitado, descoberta, low, pai, tempo);

            if (low[v] < low[u]) {
                low[u] = low[v];
            }

            if (low[v] > descoberta[u]) {
                printf("Ponte encontrada: %d - %d\n", u, v);
            }
        } else if (v != pai[u]) {
            if (descoberta[v] < low[u]) {
                low[u] = descoberta[v];
            }
        }
        atual = atual->proximo;
    }
}

void detectar_pontes(GrafoLista *g) {
    int V = g->num_vertices;
    int *visitado = (int*) malloc(V * sizeof(int));
    int *descoberta = (int*) malloc(V * sizeof(int));
    int *low = (int*) malloc(V * sizeof(int));
    int *pai = (int*) malloc(V * sizeof(int));

    memset(visitado, 0, V * sizeof(int));
    for (int i = 0; i < V; i++) {
        pai[i] = -1;
    }

    int tempo = 0;
    for (int i = 0; i < V; i++) {
        if (!visitado[i]) {
            pontes_util(g, i, visitado, descoberta, low, pai, &tempo);
        }
    }

    free(visitado);
    free(descoberta);
    free(low);
    free(pai);
}