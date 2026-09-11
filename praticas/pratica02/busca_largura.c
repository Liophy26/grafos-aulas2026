#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"

Fila *criar_fila(int capacidade)
{
    if (capacidade <= 0)
        return NULL;

    Fila *fila = malloc(sizeof(Fila));

    if (fila == NULL)
        return NULL;

    fila->dados = malloc(sizeof(int) * capacidade);

    if (fila->dados == NULL) {
        free(fila);
        return NULL;
    }

    fila->capacidade = capacidade;
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;

    return fila;
}

void liberar_fila(Fila *fila)
{
    if (fila == NULL)
        return;

    free(fila->dados);
    free(fila);
}

int fila_vazia(Fila *fila)
{
    return fila == NULL || fila->tamanho == 0;
}

int fila_cheia(Fila *fila)
{
    return fila != NULL && fila->tamanho == fila->capacidade;
}

void enfileirar(Fila *fila, int valor)
{
    if (fila == NULL || fila_cheia(fila))
        return;

    fila->dados[fila->fim] = valor;
    fila->fim = (fila->fim + 1) % fila->capacidade;
    fila->tamanho++;
}

int desenfileirar(Fila *fila)
{
    if (fila_vazia(fila))
        return -1;

    int valor = fila->dados[fila->inicio];

    fila->inicio = (fila->inicio + 1) % fila->capacidade;
    fila->tamanho--;

    return valor;
}

void bfs(GrafoLista *g, int origem, int *dist, int *pred)
{
    if (g == NULL || dist == NULL || pred == NULL)
        return;

    if (origem < 0 || origem >= g->numVertices)
        return;

    int n = g->numVertices;

    for (int i = 0; i < n; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }

    Fila *fila = criar_fila(n);

    if (fila == NULL)
        return;

    dist[origem] = 0;
    enfileirar(fila, origem);

    while (!fila_vazia(fila)) {
        int u = desenfileirar(fila);

        No *atual = g->listas[u];

        while (atual != NULL) {
            int v = atual->destino;

            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                pred[v] = u;

                enfileirar(fila, v);
            }

            atual = atual->prox;
        }
    }

    liberar_fila(fila);
}

int eh_bipartido(GrafoLista *g)
{
    if (g == NULL)
        return 0;

    int n = g->numVertices;

    int *cor = malloc(sizeof(int) * n);

    if (cor == NULL)
        return 0;

    for (int i = 0; i < n; i++)
        cor[i] = -1;

    Fila *fila = criar_fila(n);

    if (fila == NULL) {
        free(cor);
        return 0;
    }

    for (int inicio = 0; inicio < n; inicio++) {

        if (cor[inicio] != -1)
            continue;

        cor[inicio] = 0;
        enfileirar(fila, inicio);

        while (!fila_vazia(fila)) {
            int u = desenfileirar(fila);

            No *atual = g->listas[u];

            while (atual != NULL) {
                int v = atual->destino;

                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    enfileirar(fila, v);
                }
                else if (cor[v] == cor[u]) {
                    liberar_fila(fila);
                    free(cor);
                    return 0;
                }

                atual = atual->prox;
            }
        }
    }

    liberar_fila(fila);
    free(cor);

    return 1;
}

int contar_componentes(GrafoLista *g)
{
    if (g == NULL)
        return 0;

    int n = g->numVertices;
    int *visitado = calloc(n, sizeof(int));

    if (visitado == NULL)
        return 0;

    Fila *fila = criar_fila(n);

    if (fila == NULL) {
        free(visitado);
        return 0;
    }

    int componentes = 0;

    for (int inicio = 0; inicio < n; inicio++) {

        if (visitado[inicio])
            continue;

        componentes++;

        visitado[inicio] = 1;
        enfileirar(fila, inicio);

        while (!fila_vazia(fila)) {
            int u = desenfileirar(fila);

            No *atual = g->listas[u];

            while (atual != NULL) {
                int v = atual->destino;

                if (!visitado[v]) {
                    visitado[v] = 1;
                    enfileirar(fila, v);
                }

                atual = atual->prox;
            }
        }
    }

    liberar_fila(fila);
    free(visitado);

    return componentes;
}
