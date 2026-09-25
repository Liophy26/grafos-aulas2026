#ifndef CONECTIVIDADE_H
#define CONECTIVIDADE_H

typedef struct No {
    int destino;
    struct No *proximo;
} No;

typedef struct GrafoLista {
    int num_vertices;
    No **listas;
} GrafoLista;

GrafoLista* criar_grafo(int num_vertices);
void destruir_grafo(GrafoLista *g);
void inserir_aresta_nao_direcionada(GrafoLista *g, int u, int v);

void dfs_articulacoes(GrafoLista *g, int *articulacoes);
void detectar_pontes(GrafoLista *g);

#endif 