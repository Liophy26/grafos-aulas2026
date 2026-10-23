
#ifndef GRAFO_LISTA_PONDERADO_H
#define GRAFO_LISTA_PONDERADO_H

typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta *prox;
} Aresta;

typedef struct {
    int num_vertices;
    Aresta **lista;
} GrafoListaPonderado;

GrafoListaPonderado *criar_grafo(int num_vertices);

int adicionar_aresta(
    GrafoListaPonderado *g,
    int origem,
    int destino,
    int peso
);

void liberar_grafo(GrafoListaPonderado *g);

void imprimir_grafo(GrafoListaPonderado *g);

#endif
