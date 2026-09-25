#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "planaridade.h"

static int contar_arestas(GrafoLista *g) {
    int m = 0;
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->listas[i];
        while (atual != NULL) {
            if (i < atual->destino) { 
                m++;
            }
            atual = atual->proximo;
        }
    }
    return m;
}

int eh_planar_euler(GrafoLista *g) {
    int n = g->num_vertices;
    if (n <= 2) return 1;

    int m = contar_arestas(g);

    if (m <= 3 * n - 6) {
        return 1;
    }
    return 0;
}

static int tem_aresta(GrafoLista *g, int u, int v) {
    No *atual = g->listas[u];
    while (atual != NULL) {
        if (atual->destino == v) return 1;
        atual = atual->proximo;
    }
    return 0;
}

static int contem_subdivisao_k5(GrafoLista *g) {
    int V = g->num_vertices;
    if (V < 5) return 0;

    for (int a = 0; a < V; a++) {
        for (int b = a + 1; b < V; b++) {
            for (int c = b + 1; c < V; c++) {
                for (int d = c + 1; d < V; d++) {
                    for (int e = d + 1; e < V; e++) {
                        int v[5] = {a, b, c, d, e};
                        int completo = 1;
                        for (int i = 0; i < 5; i++) {
                            for (int j = i + 1; j < 5; j++) {
                                if (!tem_aresta(g, v[i], v[j])) {
                                    completo = 0;
                                    break;
                                }
                            }
                            if (!completo) break;
                        }
                        if (completo) return 1; 
                    }
                }
            }
        }
    }
    return 0;
}

static int contem_subdivisao_k33(GrafoLista *g) {
    int V = g->num_vertices;
    if (V < 6) return 0;

    for (int a = 0; a < V; a++) {
        for (int b = a + 1; b < V; b++) {
            for (int c = b + 1; c < V; c++) {
                for (int d = 0; d < V; d++) {
                    if (d == a || d == b || d == c) continue;
                    for (int e = d + 1; e < V; e++) {
                        if (e == a || e == b || e == c) continue;
                        for (int f = e + 1; f < V; f++) {
                            if (f == a || f == b || f == c) continue;

                            int g1[3] = {a, b, c};
                            int g2[3] = {d, e, f};
                            int bipartido = 1;

                            for (int i = 0; i < 3; i++) {
                                for (int j = 0; j < 3; j++) {
                                    if (!tem_aresta(g, g1[i], g2[j])) {
                                        bipartido = 0;
                                        break;
                                    }
                                }
                                if (!bipartido) break;
                            }
                            if (bipartido) return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int eh_planar_forca_bruta(GrafoLista *g) {
    if (!eh_planar_euler(g)) {
        return 0;
    }

    if (contem_subdivisao_k5(g) || contem_subdivisao_k33(g)) {
        return 0;
    }

    return 1;
}