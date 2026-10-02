#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"

void imprimir_coloracao(const char *algoritmo, int *cores, int num_vertices, int num_cores) {
    printf("[%s] Total de cores utilizadas: %d\n", algoritmo, num_cores);
    printf("Atribuicao de Cores aos Vertices:\n");
    for (int i = 0; i < num_vertices; i++) {
        printf("  Vertice %d -> Cor %d\n", i, cores[i]);
    }
}

int main() {
    printf(" Testando Grafo Bipartido com Ciclo Par - C4\n");
    
    GrafoLista *c4 = criar_grafo(4);
    inserir_aresta_nao_direcionada(c4, 0, 1);
    inserir_aresta_nao_direcionada(c4, 1, 2);
    inserir_aresta_nao_direcionada(c4, 2, 3);
    inserir_aresta_nao_direcionada(c4, 3, 0);

    printf("Verificacao: %s\n", eh_bipartido(c4) ? "Eh Bipartido (2-coloriavel)" : "NAO eh Bipartido");

    int num_cores_g = 0;
    int *cores_g = coloracao_gulosa(c4, &num_cores_g);
    imprimir_coloracao("Gulosa", cores_g, c4->num_vertices, num_cores_g);
    free(cores_g);

    destruir_grafo(c4);

    printf(" Testando Grafo nao bipartido com Ciclo Impar - C3\n");

    GrafoLista *c3 = criar_grafo(3);
    inserir_aresta_nao_direcionada(c3, 0, 1);
    inserir_aresta_nao_direcionada(c3, 1, 2);
    inserir_aresta_nao_direcionada(c3, 2, 0);

    printf("Verificacao: %s\n", eh_bipartido(c3) ? "Eh Bipartido" : "NAO eh Bipartido (Possui ciclo impar)");

    int num_cores_wp = 0;
    int *cores_wp = coloracao_welsh_powell(c3, &num_cores_wp);
    imprimir_coloracao("Welsh", cores_wp, c3->num_vertices, num_cores_wp);
    free(cores_wp);

    destruir_grafo(c3);

    printf(" Testando Gulosa vs Welsh\n");

    GrafoLista *g_complexo = criar_grafo(6);
    inserir_aresta_nao_direcionada(g_complexo, 0, 1);
    inserir_aresta_nao_direcionada(g_complexo, 0, 2);
    inserir_aresta_nao_direcionada(g_complexo, 0, 3);
    inserir_aresta_nao_direcionada(g_complexo, 0, 4);
    inserir_aresta_nao_direcionada(g_complexo, 0, 5);
    inserir_aresta_nao_direcionada(g_complexo, 1, 2);
    inserir_aresta_nao_direcionada(g_complexo, 3, 4);

    printf("Verificacao Bipartido: %s\n", eh_bipartido(g_complexo) ? "Eh Bipartido" : "Nao eh Bipartido");

    cores_g = coloracao_gulosa(g_complexo, &num_cores_g);
    imprimir_coloracao("Gulosa Arbitraria", cores_g, g_complexo->num_vertices, num_cores_g);
    free(cores_g);

    printf("\n");

    cores_wp = coloracao_welsh_powell(g_complexo, &num_cores_wp);
    imprimir_coloracao("Welsh com Grau Decrescente", cores_wp, g_complexo->num_vertices, num_cores_wp);
    free(cores_wp);

    destruir_grafo(g_complexo);

    return 0;
}