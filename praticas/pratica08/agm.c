
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "agm.h"


int dsu_init(DSU *d, int n) {
    if (d == NULL || n <= 0)
        return 0;

    d->n = n;
    d->pai = malloc(n * sizeof(int));
    d->rank = calloc(n, sizeof(int));

    if (d->pai == NULL || d->rank == NULL) {
        free(d->pai);
        free(d->rank);
        d->pai = NULL;
        d->rank = NULL;
        d->n = 0;
        return 0;
    }

    for (int i = 0; i < n; i++)
        d->pai[i] = i;

    return 1;
}

void dsu_free(DSU *d) {
    if (d == NULL)
        return;

    free(d->pai);
    free(d->rank);

    d->pai = NULL;
    d->rank = NULL;
    d->n = 0;
}

int find(DSU *d, int x) {
    if (d == NULL || x < 0 || x >= d->n)
        return -1;

    if (d->pai[x] != x)
        d->pai[x] = find(d, d->pai[x]);

    return d->pai[x];
}

void unir(DSU *d, int x, int y) {
    int rx = find(d, x);
    int ry = find(d, y);

    if (rx == -1 || ry == -1 || rx == ry)
        return;

    if (d->rank[rx] < d->rank[ry]) {
        d->pai[rx] = ry;
    } else if (d->rank[rx] > d->rank[ry]) {
        d->pai[ry] = rx;
    } else {
        d->pai[ry] = rx;
        d->rank[rx]++;
    }
}


static int comparar_arestas(const void *a, const void *b) {
    const Aresta *x = a;
    const Aresta *y = b;

    if (x->peso < y->peso) return -1;
    if (x->peso > y->peso) return 1;
    return 0;
}

int kruskal(
    Aresta arestas[],
    int E,
    int V,
    Aresta resultado[],
    int *peso_total
) {
    if (peso_total == NULL || V <= 0 || E < 0 ||
        (E > 0 && arestas == NULL) ||
        (V > 1 && resultado == NULL))
        return 0;

    *peso_total = 0;

    if (V == 1)
        return 1;

    Aresta *ordenadas = NULL;

    if (E > 0) {
        ordenadas = malloc((size_t)E * sizeof(Aresta));
        if (ordenadas == NULL)
            return 0;

        for (int i = 0; i < E; i++) {
            if (arestas[i].u < 0 || arestas[i].u >= V ||
                arestas[i].v < 0 || arestas[i].v >= V) {
                free(ordenadas);
                return 0;
            }
            ordenadas[i] = arestas[i];
        }
    }

    qsort(ordenadas, E, sizeof(Aresta), comparar_arestas);

    DSU d;
    if (!dsu_init(&d, V)) {
        free(ordenadas);
        return 0;
    }

    int selecionadas = 0;

    for (int i = 0; i < E && selecionadas < V - 1; i++) {
        int u = ordenadas[i].u;
        int v = ordenadas[i].v;

        if (find(&d, u) != find(&d, v)) {
            resultado[selecionadas++] = ordenadas[i];
            *peso_total += ordenadas[i].peso;
            unir(&d, u, v);
        }
    }

    dsu_free(&d);
    free(ordenadas);

    return selecionadas == V - 1;
}

/* ==================== PRIM ==================== */

typedef struct Adjacencia {
    int destino;
    int peso;
    struct Adjacencia *prox;
} Adjacencia;

typedef struct {
    int *heap;
    int *pos;
    int *chave;
    int tamanho;
} Heap;

static void trocar(Heap *h, int i, int j) {
    int temp = h->heap[i];
    h->heap[i] = h->heap[j];
    h->heap[j] = temp;

    h->pos[h->heap[i]] = i;
    h->pos[h->heap[j]] = j;
}

static void subir(Heap *h, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;

        if (h->chave[h->heap[pai]] <=
            h->chave[h->heap[i]])
            break;

        trocar(h, i, pai);
        i = pai;
    }
}

static void descer(Heap *h, int i) {
    while (1) {
        int menor = i;
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;

        if (esq < h->tamanho &&
            h->chave[h->heap[esq]] <
            h->chave[h->heap[menor]])
            menor = esq;

        if (dir < h->tamanho &&
            h->chave[h->heap[dir]] <
            h->chave[h->heap[menor]])
            menor = dir;

        if (menor == i)
            break;

        trocar(h, i, menor);
        i = menor;
    }
}

static int extrair_minimo(Heap *h) {
    int minimo = h->heap[0];

    h->pos[minimo] = -1;
    h->tamanho--;

    if (h->tamanho > 0) {
        h->heap[0] = h->heap[h->tamanho];
        h->pos[h->heap[0]] = 0;
        descer(h, 0);
    }

    return minimo;
}

static void atualizar_chave(Heap *h, int v, int nova) {
    h->chave[v] = nova;
    subir(h, h->pos[v]);
}

int prim(
    Aresta arestas[],
    int E,
    int V,
    Aresta resultado[],
    int *peso_total
) {
    if (peso_total == NULL || V <= 0 || E < 0 ||
        (E > 0 && arestas == NULL) ||
        (V > 1 && resultado == NULL))
        return 0;

    *peso_total = 0;

    if (V == 1)
        return 1;

    Adjacencia **lista = calloc(V, sizeof(Adjacencia *));
    int *chave = malloc((size_t)V * sizeof(int));
    int *pai = malloc((size_t)V * sizeof(int));
    int *heap = malloc((size_t)V * sizeof(int));
    int *pos = malloc((size_t)V * sizeof(int));

    if (!lista || !chave || !pai || !heap || !pos) {
        free(lista);
        free(chave);
        free(pai);
        free(heap);
        free(pos);
        return 0;
    }

    for (int i = 0; i < E; i++) {
        int u = arestas[i].u;
        int v = arestas[i].v;
        int w = arestas[i].peso;

        if (u < 0 || u >= V || v < 0 || v >= V)
            goto erro;

        Adjacencia *a = malloc(sizeof(Adjacencia));
        Adjacencia *b = malloc(sizeof(Adjacencia));

        if (!a || !b) {
            free(a);
            free(b);
            goto erro;
        }

        a->destino = v;
        a->peso = w;
        a->prox = lista[u];
        lista[u] = a;

        b->destino = u;
        b->peso = w;
        b->prox = lista[v];
        lista[v] = b;
    }

    for (int i = 0; i < V; i++) {
        chave[i] = INT_MAX;
        pai[i] = -1;
        heap[i] = i;
        pos[i] = i;
    }

    Heap h = {heap, pos, chave, V};
    chave[0] = 0;
    subir(&h, pos[0]);

    int selecionadas = 0;

    while (h.tamanho > 0) {
        int u = extrair_minimo(&h);

        if (chave[u] == INT_MAX)
            break;

        if (pai[u] != -1) {
            resultado[selecionadas].u = pai[u];
            resultado[selecionadas].v = u;
            resultado[selecionadas].peso = chave[u];

            *peso_total += chave[u];
            selecionadas++;
        }

        for (Adjacencia *a = lista[u];
             a != NULL; a = a->prox) {
            int v = a->destino;

            if (pos[v] != -1 && a->peso < chave[v]) {
                pai[v] = u;
                atualizar_chave(&h, v, a->peso);
            }
        }
    }

    for (int i = 0; i < V; i++) {
        Adjacencia *a = lista[i];

        while (a != NULL) {
            Adjacencia *temp = a;
            a = a->prox;
            free(temp);
        }
    }

    free(lista);
    free(chave);
    free(pai);
    free(heap);
    free(pos);

    return selecionadas == V - 1;

erro:
    for (int i = 0; i < V; i++) {
        Adjacencia *a = lista[i];

        while (a != NULL) {
            Adjacencia *temp = a;
            a = a->prox;
            free(temp);
        }
    }

    free(lista);
    free(chave);
    free(pai);
    free(heap);
    free(pos);

    return 0;
}
