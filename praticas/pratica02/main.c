#include <stdio.h>
#include <stdlib.h>

#include "grafolista.h"
#include "busca_largura.h"
#include "busca_profundidade.h"

int main(void)
{
   
    GrafoLista *g = criar_grafo(6);

    if (g == NULL) {
        printf("Erro ao criar o grafo.\n");
        return 1;
    }

    adicionar_aresta_nao_direcionada(g, 0, 1);
    adicionar_aresta_nao_direcionada(g, 0, 2);
    adicionar_aresta_nao_direcionada(g, 1, 3);
    adicionar_aresta_nao_direcionada(g, 2, 4);
    adicionar_aresta_nao_direcionada(g, 3, 4);
    adicionar_aresta_nao_direcionada(g, 3, 5);

    imprimir_grafo(g);

   

    int n = g->numVertices;

    int *dist = malloc(sizeof(int) * n);
    int *pred = malloc(sizeof(int) * n);

    if (dist == NULL || pred == NULL) {
        printf("Erro ao alocar memoria.\n");

        free(dist);
        free(pred);
        liberar_grafo(g);

        return 1;
    }

    printf("\n--- BFS a partir do vertice 0 ---\n");

    bfs(g, 0, dist, pred);

    printf("Vertice\tDistancia\tPredecessor\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", i, dist[i], pred[i]);
    }


    int *visitado = calloc(n, sizeof(int));

    if (visitado == NULL) {
        free(dist);
        free(pred);
        liberar_grafo(g);

        return 1;
    }

    printf("\n--- DFS recursiva a partir do vertice 0 ---\n");

    dfs_recursiva(g, 0, visitado);

    printf("\n");

    free(visitado);


    visitado = calloc(n, sizeof(int));

    if (visitado == NULL) {
        free(dist);
        free(pred);
        liberar_grafo(g);

        return 1;
    }

    printf("\n--- DFS iterativa a partir do vertice 0 ---\n");

    dfs_iterativa(g, 0, visitado);

    printf("\n");

    free(visitado);

    printf("\n--- Bipartido ---\n");

    if (eh_bipartido(g))
        printf("O grafo eh bipartido.\n");
    else
        printf("O grafo NAO eh bipartido.\n");


    printf("\n--- Componentes ---\n");

    printf("Quantidade de componentes: %d\n",
           contar_componentes(g));

    printf("\n--- Ciclo ---\n");

    if (tem_ciclo(g))
        printf("O grafo possui ciclo.\n");
    else
        printf("O grafo nao possui ciclo.\n");

    free(dist);
    free(pred);

    liberar_grafo(g);

    return 0;
}
