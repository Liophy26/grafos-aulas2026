#include <stdio.h>
#include <stdlib.h>
#include "busca_profundidade.h"

Pilha *criar_pilha(int capacidade)
{
    if (capacidade <= 0)
        return NULL;

    Pilha *pilha = malloc(sizeof(Pilha));

    if (pilha == NULL)
        return NULL;

    pilha->dados = malloc(sizeof(int) * capacidade);

    if (pilha->dados == NULL) {
        free(pilha);
        return NULL;
    }

    pilha->capacidade = capacidade;
    pilha->topo = -1;

    return pilha;
}

void liberar_pilha(Pilha *pilha)
{
    if (pilha == NULL)
        return;

    free(pilha->dados);
    free(pilha);
}

int pilha_vazia(Pilha *pilha)
{
    return pilha == NULL || pilha->topo == -1;
}

int pilha_cheia(Pilha *pilha)
{
    return pilha != NULL &&
           pilha->topo == pilha->capacidade - 1;
}

void empilhar(Pilha *pilha, int valor)
{
    if (pilha == NULL || pilha_cheia(pilha))
        return;

    pilha->dados[++pilha->topo] = valor;
}

int desempilhar(Pilha *pilha)
{
    if (pilha_vazia(pilha))
        return -1;

    return pilha->dados[pilha->topo--];
}

void dfs_recursiva(GrafoLista *g, int u, int *visitado)
{
    if (g == NULL || visitado == NULL)
        return;

    if (u < 0 || u >= g->numVertices)
        return;

    visitado[u] = 1;

    printf("%d ", u);

    No *atual = g->listas[u];

    while (atual != NULL) {
        int v = atual->destino;

        if (!visitado[v]) {
            dfs_recursiva(g, v, visitado);
        }

        atual = atual->prox;
    }
}

void dfs_iterativa(GrafoLista *g, int origem, int *visitado)
{
    if (g == NULL || visitado == NULL)
        return;

    if (origem < 0 || origem >= g->numVertices)
        return;

    Pilha *pilha = criar_pilha(g->numVertices);

    if (pilha == NULL)
        return;

    empilhar(pilha, origem);

    while (!pilha_vazia(pilha)) {
        int u = desempilhar(pilha);

        if (visitado[u])
            continue;

        visitado[u] = 1;

        printf("%d ", u);

        No *atual = g->listas[u];

        while (atual != NULL) {
            if (!visitado[atual->destino])
                empilhar(pilha, atual->destino);

            atual = atual->prox;
        }
    }

    liberar_pilha(pilha);
}

static int dfs_ciclo(GrafoLista *g, int u, int pai, int *visitado)
{
    visitado[u] = 1;

    No *atual = g->listas[u];

    while (atual != NULL) {
        int v = atual->destino;

        if (!visitado[v]) {
            if (dfs_ciclo(g, v, u, visitado))
                return 1;
        }
        else if (v != pai) {
            return 1;
        }

        atual = atual->prox;
    }

    return 0;
}

int tem_ciclo(GrafoLista *g)
{
    if (g == NULL)
        return 0;

    int n = g->numVertices;

    int *visitado = calloc(n, sizeof(int));

    if (visitado == NULL)
        return 0;

    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            if (dfs_ciclo(g, i, -1, visitado)) {
                free(visitado);
                return 1;
            }
        }
    }

    free(visitado);

    return 0;
}
