#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

typedef struct No {
    int destino;
    struct No *prox;
} No;

typedef struct {
    int numVertices;
    No **listas;
} GrafoLista;


GrafoLista *criar_grafo(int numVertices);
void liberar_grafo(GrafoLista *g);


void adicionar_aresta(GrafoLista *g, int origem, int destino);
void adicionar_aresta_nao_direcionada(GrafoLista *g, int u, int v);


void imprimir_grafo(GrafoLista *g);

#endif
