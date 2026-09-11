#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "grafolista.h"

typedef struct {
    int *dados;
    int topo;
    int capacidade;
} Pilha;

Pilha *criar_pilha(int capacidade);
void liberar_pilha(Pilha *pilha);
int pilha_vazia(Pilha *pilha);
int pilha_cheia(Pilha *pilha);
void empilhar(Pilha *pilha, int valor);
int desempilhar(Pilha *pilha);

void dfs_recursiva(GrafoLista *g, int u, int *visitado);

void dfs_iterativa(GrafoLista *g, int origem, int *visitado);

int tem_ciclo(GrafoLista *g);

#endif
