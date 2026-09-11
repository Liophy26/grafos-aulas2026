#ifndef GRAFO_H
#define GRAFO_H

typedef struct No {
int destino;
struct No *prox;
} No;

typedef struct {
int num_vertices;
No **adj;
} GrafoLista;

GrafoLista *criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista *g, int origem, int destino);
void liberar_grafo(GrafoLista *g);
void imprimir_grafo(GrafoLista *g);

#endif