
#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "grafo_lista_ponderado.h"

int bellman_ford(
    GrafoListaPonderado *g,
    int origem,
    int *dist,
    int *pred
);

void reconstruir_ciclo_negativo(
    int n,
    int *pred,
    int vertice
);

#endif
