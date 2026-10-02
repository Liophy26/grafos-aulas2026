#ifndef COLORACAO_H
#define COLORACAO_H

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
void imprimir_grafo(GrafoLista *g);

int* coloracao_gulosa(GrafoLista *g, int *num_cores);
int* coloracao_welsh_powell(GrafoLista *g, int *num_cores);
int eh_bipartido(GrafoLista *g);

#endif