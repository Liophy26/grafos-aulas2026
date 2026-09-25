#include <stdio.h>
#include <stdlib.h>
#include "conectividade.h"
#include "planaridade.h"

int main() {
    printf(" Testando conectividade\n");

    GrafoLista *g1 = criar_grafo(5);
    inserir_aresta_nao_direcionada(g1, 0, 1);
    inserir_aresta_nao_direcionada(g1, 1, 2);
    inserir_aresta_nao_direcionada(g1, 1, 3);
    inserir_aresta_nao_direcionada(g1, 3, 4);

    int *articulacoes = (int*) malloc(g1->num_vertices * sizeof(int));
    dfs_articulacoes(g1, articulacoes);

    printf("Vertices de Articulacao: ");
    for (int i = 0; i < g1->num_vertices; i++) {
        if (articulacoes[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    printf("Pontes no Grafo:\n");
    detectar_pontes(g1);

    free(articulacoes);
    destruir_grafo(g1);

    printf(" Testando planaridade de um grafo nao planar\n");

    GrafoLista *k5 = criar_grafo(5);
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            inserir_aresta_nao_direcionada(k5, i, j);
        }
    }

    printf("K5 eh planar (Euler)? %s\n", eh_planar_euler(k5) ? "Sim" : "Nao");
    printf("K5 eh planar (Forca Bruta)? %s\n", eh_planar_forca_bruta(k5) ? "Sim" : "Nao");

    
    printf(" Testando planaridade de um grafo planar\n");
    GrafoLista *g_planar = criar_grafo(4);
    inserir_aresta_nao_direcionada(g_planar, 0, 1);
    inserir_aresta_nao_direcionada(g_planar, 1, 2);
    inserir_aresta_nao_direcionada(g_planar, 2, 3);
    inserir_aresta_nao_direcionada(g_planar, 3, 0);
    inserir_aresta_nao_direcionada(g_planar, 0, 2);

    printf("g_planar eh planar (Euler)? %s\n", eh_planar_euler(g_planar) ? "Sim" : "Nao");
    printf("g_planar eh planar (Forca Bruta)? %s\n", eh_planar_forca_bruta(g_planar) ? "Sim" : "Nao");

    destruir_grafo(g_planar);

    destruir_grafo(k5);

    return 0;
}