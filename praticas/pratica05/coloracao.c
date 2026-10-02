#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coloracao.h"

GrafoLista* criar_grafo(int num_vertices) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->listas = (No**) malloc(num_vertices * sizeof(No*));
    for (int i = 0; i < num_vertices; i++) {
        g->listas[i] = NULL;
    }
    return g;
}

void destruir_grafo(GrafoLista *g) {
    if (g == NULL) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->listas[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->listas);
    free(g);
}

void inserir_aresta_nao_direcionada(GrafoLista *g, int u, int v) {
    if (u < 0 || u >= g->num_vertices || v < 0 || v >= g->num_vertices) return;

    No *novo1 = (No*) malloc(sizeof(No));
    novo1->destino = v;
    novo1->proximo = g->listas[u];
    g->listas[u] = novo1;

    No *novo2 = (No*) malloc(sizeof(No));
    novo2->destino = u;
    novo2->proximo = g->listas[v];
    g->listas[v] = novo2;
}

void imprimir_grafo(GrafoLista *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        printf("Vertice %d:", i);
        No *atual = g->listas[i];
        while (atual != NULL) {
            printf(" -> %d", atual->destino);
            atual = atual->proximo;
        }
        printf("\n");
    }
}

int* coloracao_gulosa(GrafoLista *g, int *num_cores) {
    int V = g->num_vertices;
    int *cores = (int*) malloc(V * sizeof(int));
    int *disponivel = (int*) malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        cores[i] = -1;
    }

    cores[0] = 0;
    int max_cor = 0;

    for (int u = 1; u < V; u++) {
        for (int c = 0; c < V; c++) {
            disponivel[c] = 1;
        }

        No *atual = g->listas[u];
        while (atual != NULL) {
            int v = atual->destino;
            if (cores[v] != -1) {
                disponivel[cores[v]] = 0; 
            }
            atual = atual->proximo;
        }

        int cr;
        for (cr = 0; cr < V; cr++) {
            if (disponivel[cr] == 1) {
                break;
            }
        }

        cores[u] = cr;
        if (cr > max_cor) {
            max_cor = cr;
        }
    }

    free(disponivel);
    *num_cores = max_cor + 1;
    return cores;
}

typedef struct {
    int vertice;
    int grau;
} VerticeGrau;

int* coloracao_welsh_powell(GrafoLista *g, int *num_cores) {
    int V = g->num_vertices;
    VerticeGrau *vg = (VerticeGrau*) malloc(V * sizeof(VerticeGrau));

    for (int i = 0; i < V; i++) {
        vg[i].vertice = i;
        vg[i].grau = 0;
        No *atual = g->listas[i];
        while (atual != NULL) {
            vg[i].grau++;
            atual = atual->proximo;
        }
    }

    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < V - i - 1; j++) {
            if (vg[j].grau < vg[j + 1].grau) {
                VerticeGrau temp = vg[j];
                vg[j] = vg[j + 1];
                vg[j + 1] = temp;
            }
        }
    }

    int *cores = (int*) malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        cores[i] = -1;
    }

    int *disponivel = (int*) malloc(V * sizeof(int));
    int max_cor = 0;

    for (int i = 0; i < V; i++) {
        int u = vg[i].vertice;

        for (int c = 0; c < V; c++) {
            disponivel[c] = 1;
        }

        No *atual = g->listas[u];
        while (atual != NULL) {
            int v = atual->destino;
            if (cores[v] != -1) {
                disponivel[cores[v]] = 0;
            }
            atual = atual->proximo;
        }

        int cr;
        for (cr = 0; cr < V; cr++) {
            if (disponivel[cr] == 1) {
                break;
            }
        }

        cores[u] = cr;
        if (cr > max_cor) {
            max_cor = cr;
        }
    }

    free(vg);
    free(disponivel);
    *num_cores = max_cor + 1;
    return cores;
}

int eh_bipartido(GrafoLista *g) {
    int V = g->num_vertices;
    int *cores = (int*) malloc(V * sizeof(int));
    
    for (int i = 0; i < V; i++) {
        cores[i] = -1;
    }

    int *fila = (int*) malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        if (cores[i] == -1) {
            cores[i] = 0;
            int inicio = 0, fim = 0;
            fila[fim++] = i;

            while (inicio < fim) {
                int u = fila[inicio++];

                No *atual = g->listas[u];
                while (atual != NULL) {
                    int v = atual->destino;

                    if (cores[v] == -1) {
                        cores[v] = 1 - cores[u]; 
                        fila[fim++] = v;
                    } else if (cores[v] == cores[u]) {
                        free(cores);
                        free(fila);
                        return 0;
                    }
                    atual = atual->proximo;
                }
            }
        }
    }

    free(cores);
    free(fila);
    return 1;
}