#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include "grafolista.h"


typedef struct {
    int *dados;
    int capacidade;
    int inicio;
    int fim;
    int tamanho;
} Fila;


Fila *criar_fila(int capacidade);
void liberar_fila(Fila *fila);
int fila_vazia(Fila *fila);
int fila_cheia(Fila *fila);
void enfileirar(Fila *fila, int valor);
int desenfileirar(Fila *fila);


void bfs(GrafoLista *g, int origem, int *dist, int *pred);


int eh_bipartido(GrafoLista *g);

int contar_componentes(GrafoLista *g);

#endif
