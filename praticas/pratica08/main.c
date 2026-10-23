
#include <stdio.h>
#include "agm.h"

static void mostrar_resultado(
    const char *nome,
    int sucesso,
    Aresta resultado[],
    int V,
    int peso_total
) {
    printf("\n=== %s ===\n", nome);

    if (!sucesso) {
        printf("Nao foi possivel construir uma AGM.\n");
        printf("O grafo pode ser desconectado ou invalido.\n");
        return;
    }

    printf("Arestas selecionadas:\n");

    for (int i = 0; i < V - 1; i++) {
        printf("%d -- %d (peso %d)\n",
               resultado[i].u,
               resultado[i].v,
               resultado[i].peso);
    }

    printf("Peso total da AGM: %d\n", peso_total);
}

int main(void) {
    int V = 5;
    int E = 7;

    Aresta arestas[] = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };

    Aresta resultado_kruskal[V - 1];
    Aresta resultado_prim[V - 1];

    int peso_kruskal = 0;
    int peso_prim = 0;

    int ok_kruskal = kruskal(
        arestas, E, V,
        resultado_kruskal, &peso_kruskal
    );

    int ok_prim = prim(
        arestas, E, V,
        resultado_prim, &peso_prim
    );

    printf("Arvore Geradora Minima (AGM)\n");

    mostrar_resultado(
        "Kruskal",
        ok_kruskal,
        resultado_kruskal,
        V,
        peso_kruskal
    );

    mostrar_resultado(
        "Prim",
        ok_prim,
        resultado_prim,
        V,
        peso_prim
    );

    return 0;
}
