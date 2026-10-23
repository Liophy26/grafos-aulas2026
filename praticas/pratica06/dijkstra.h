#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define INF 1000000000

typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta *prox;
} Aresta;

typedef struct {
    int num_vertices;
    Aresta **listas;
} GrafoListaPonderado;

typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; 
} MinHeap;

/* Grafo */
GrafoListaPonderado *criar_grafo(int num_vertices);
void adicionar_aresta(GrafoListaPonderado *g, int origem,
                      int destino, int peso);
void liberar_grafo(GrafoListaPonderado *g);

/* MinHeap */
MinHeap *criar_min_heap(int capacidade);
void liberar_min_heap(MinHeap *heap);
NoHeap extrair_minimo(MinHeap *heap);
void diminuir_chave(MinHeap *heap, int vertice, int nova_distancia);

/* Dijkstra e caminho */
void dijkstra(GrafoListaPonderado *g, int origem,
              int *dist, int *pred);
int *reconstruir_caminho(int origem, int destino, int *pred);

#endif