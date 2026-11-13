#ifndef COBERTURA_H
#define COBERTURA_H

#define MAX_VERTICES 20

typedef struct {
    int n;
    int adj[MAX_VERTICES][MAX_VERTICES];
} Grafo;

int eh_cobertura(const Grafo *g, const int sol[]);
int cobertura_gulosa(const Grafo *g, int sol[]);
int cobertura_minima_bt(const Grafo *g, int sol[]);
void gerar_grafo(Grafo *g, int n, unsigned int *seed);

#endif