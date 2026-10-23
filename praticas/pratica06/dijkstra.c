#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "dijkstra.h"

static void trocar(MinHeap *heap, int i, int j) {
    NoHeap temp = heap->dados[i];
    heap->dados[i] = heap->dados[j];
    heap->dados[j] = temp;

    heap->posicao[heap->dados[i].vertice] = i;
    heap->posicao[heap->dados[j].vertice] = j;
}

static void subir(MinHeap *heap, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;

        if (heap->dados[pai].distancia <=
            heap->dados[i].distancia)
            break;

        trocar(heap, i, pai);
        i = pai;
    }
}

static void descer(MinHeap *heap, int i) {
    while (1) {
        int menor = i;
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;

        if (esq < heap->tamanho &&
            heap->dados[esq].distancia <
            heap->dados[menor].distancia)
            menor = esq;

        if (dir < heap->tamanho &&
            heap->dados[dir].distancia <
            heap->dados[menor].distancia)
            menor = dir;

        if (menor == i)
            break;

        trocar(heap, i, menor);
        i = menor;
    }
}

/* Criação e liberação do grafo */

GrafoListaPonderado *criar_grafo(int num_vertices) {
    if (num_vertices <= 0)
        return NULL;

    GrafoListaPonderado *g = malloc(sizeof(*g));
    if (!g)
        return NULL;

    g->num_vertices = num_vertices;
    g->listas = calloc(num_vertices, sizeof(Aresta *));

    if (!g->listas) {
        free(g);
        return NULL;
    }

    return g;
}

void adicionar_aresta(GrafoListaPonderado *g, int origem,
                      int destino, int peso) {
    if (!g || origem < 0 || origem >= g->num_vertices ||
        destino < 0 || destino >= g->num_vertices || peso < 0)
        return;

    Aresta *a = malloc(sizeof(*a));
    if (!a)
        return;

    a->destino = destino;
    a->peso = peso;
    a->prox = g->listas[origem];
    g->listas[origem] = a;
}

void liberar_grafo(GrafoListaPonderado *g) {
    if (!g)
        return;

    for (int i = 0; i < g->num_vertices; i++) {
        Aresta *atual = g->listas[i];

        while (atual) {
            Aresta *prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }

    free(g->listas);
    free(g);
}

/* MinHeap */

MinHeap *criar_min_heap(int capacidade) {
    if (capacidade <= 0)
        return NULL;

    MinHeap *heap = malloc(sizeof(*heap));
    if (!heap)
        return NULL;

    heap->dados = malloc(capacidade * sizeof(NoHeap));
    heap->posicao = malloc(capacidade * sizeof(int));

    if (!heap->dados || !heap->posicao) {
        free(heap->dados);
        free(heap->posicao);
        free(heap);
        return NULL;
    }

    heap->capacidade = capacidade;
    heap->tamanho = 0;

    for (int i = 0; i < capacidade; i++)
        heap->posicao[i] = -1;

    return heap;
}

void liberar_min_heap(MinHeap *heap) {
    if (!heap)
        return;

    free(heap->dados);
    free(heap->posicao);
    free(heap);
}

NoHeap extrair_minimo(MinHeap *heap) {
    NoHeap invalido = {-1, INF};

    if (!heap || heap->tamanho == 0)
        return invalido;

    NoHeap minimo = heap->dados[0];
    heap->posicao[minimo.vertice] = -1;

    heap->tamanho--;

    if (heap->tamanho > 0) {
        heap->dados[0] = heap->dados[heap->tamanho];
        heap->posicao[heap->dados[0].vertice] = 0;
        descer(heap, 0);
    }

    return minimo;
}

void diminuir_chave(MinHeap *heap, int vertice,
                    int nova_distancia) {
    if (!heap || vertice < 0 ||
        vertice >= heap->capacidade)
        return;

    int i = heap->posicao[vertice];

    if (i < 0 || nova_distancia > heap->dados[i].distancia)
        return;

    heap->dados[i].distancia = nova_distancia;
    subir(heap, i);
}

/* Algoritmo de Dijkstra */

void dijkstra(GrafoListaPonderado *g, int origem,
              int *dist, int *pred) {
    if (!g || !dist || !pred || origem < 0 ||
        origem >= g->num_vertices)
        return;

    int n = g->num_vertices;
    MinHeap *heap = criar_min_heap(n);

    if (!heap)
        return;

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        pred[i] = -1;
        heap->dados[i].vertice = i;
        heap->dados[i].distancia = INF;
        heap->posicao[i] = i;
    }

    heap->tamanho = n;
    dist[origem] = 0;
    diminuir_chave(heap, origem, 0);

    while (heap->tamanho > 0) {
        NoHeap no = extrair_minimo(heap);
        int u = no.vertice;

        if (no.distancia == INF)
            break;

        for (Aresta *a = g->listas[u]; a; a = a->prox) {
            int v = a->destino;

            if (heap->posicao[v] == -1)
                continue;

            /* Evita overflow na soma das distâncias. */
            if (dist[u] > INF - a->peso)
                continue;

            int nova_distancia = dist[u] + a->peso;

            if (nova_distancia < dist[v]) {
                dist[v] = nova_distancia;
                pred[v] = u;
                diminuir_chave(heap, v, nova_distancia);
            }
        }
    }

    liberar_min_heap(heap);
}


int *reconstruir_caminho(int origem, int destino, int *pred) {
    if (!pred || origem < 0 || destino < 0)
        return NULL;

    int *caminho = malloc((size_t)(INT_MAX > 0 ? 1 : 1) *
                          sizeof(int));
    free(caminho);

    
    int capacidade = 16;
    int tamanho = 0;
    caminho = malloc((size_t)capacidade * sizeof(int));

    if (!caminho)
        return NULL;

    int atual = destino;

    while (atual != -1) {
        if (tamanho == capacidade) {
            if (capacidade > INT_MAX / 2) {
                free(caminho);
                return NULL;
            }

            capacidade *= 2;
            int *novo = realloc(
                caminho, (size_t)capacidade * sizeof(int));

            if (!novo) {
                free(caminho);
                return NULL;
            }

            caminho = novo;
        }

        caminho[tamanho++] = atual;

        if (atual == origem)
            break;

        atual = pred[atual];

        /* Proteção contra ciclos em pred. */
        if (tamanho > capacidade - 1 && atual == destino) {
            free(caminho);
            return NULL;
        }
    }

    if (tamanho == 0 || caminho[tamanho - 1] != origem) {
        free(caminho);
        return NULL;
    }

    /* Inverte para colocar a origem primeiro. */
    for (int i = 0; i < tamanho / 2; i++) {
        int temp = caminho[i];
        caminho[i] = caminho[tamanho - 1 - i];
        caminho[tamanho - 1 - i] = temp;
    }

    int *novo = realloc(caminho,
                        (size_t)(tamanho + 1) * sizeof(int));

    if (novo)
        caminho = novo;

    caminho[tamanho] = -1;
    return caminho;
}

int *reconstruir_caminho(int origem, int destino, int *pred) {
    if (!pred || origem < 0 || destino < 0)
        return NULL;

    int capacidade = 16;
    int tamanho = 0;
    int *caminho = malloc((size_t)capacidade * sizeof(int));

    if (!caminho)
        return NULL;

    int atual = destino;

    while (atual != -1) {
        if (tamanho == capacidade) {
            if (capacidade > INT_MAX / 2) {
                free(caminho);
                return NULL;
            }

            capacidade *= 2;
            int *novo = realloc(
                caminho, (size_t)capacidade * sizeof(int));

            if (!novo) {
                free(caminho);
                return NULL;
            }

            caminho = novo;
        }

        caminho[tamanho++] = atual;

        if (atual == origem)
            break;

        atual = pred[atual];

        if (tamanho > INT_MAX / 2) {
            free(caminho);
            return NULL;
        }
    }

    if (tamanho == 0 || caminho[tamanho - 1] != origem) {
        free(caminho);
        return NULL;
    }

    for (int i = 0; i < tamanho / 2; i++) {
        int temp = caminho[i];
        caminho[i] = caminho[tamanho - 1 - i];
        caminho[tamanho - 1 - i] = temp;
    }

    int *novo = realloc(caminho,
                        (size_t)(tamanho + 1) * sizeof(int));

    if (novo)
        caminho = novo;

    caminho[tamanho] = -1;
    return caminho;
}