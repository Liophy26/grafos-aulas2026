
#ifndef AGM_H
#define AGM_H

typedef struct {
    int *pai, *rank;
    int n;
} DSU;

typedef struct {
    int u, v, peso;
} Aresta;

int dsu_init(DSU *d, int n);
void dsu_free(DSU *d);
int find(DSU *d, int x);
void unir(DSU *d, int x, int y);

int kruskal(
    Aresta arestas[],
    int E,
    int V,
    Aresta resultado[],
    int *peso_total
);

int prim(
    Aresta arestas[],
    int E,
    int V,
    Aresta resultado[],
    int *peso_total
);

#endif
