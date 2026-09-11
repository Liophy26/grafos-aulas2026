#include "grafo_lista.h"
#include <stdlib.h>
#include <stdio.h>

//int pilha[10];
int visitado[10];
int topo = 0;

void dfs(GrafoLista *g, int u, int *p){
    visitado[u] = 1;
    p[topo++] = u;
    printf("Empilha %i, Visita %i\n", u+1, u+1);
    No *no = g->lista[u];
    while (no != NULL){
        int v = no->vertice;
        if(!visitado[u]) dfs(g, v, p);
        no = no->proximo;
    }
    topo --;
    printf("Desempilha %i\n", u+1);
}