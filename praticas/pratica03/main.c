#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"
#include "dag.h"

static void imprimir_ordem(const char *nome, int *ordem, int tamanho) {
printf("%s: ", nome);

if (ordem == NULL) {
    printf("ordenacao impossivel (o grafo possui ciclo)\n");
    return;
}

for (int i = 0; i < tamanho; i++) {
    printf("%d", ordem[i]);

    if (i < tamanho - 1) {
        printf(" -> ");
    }
}

printf("\n");


}

int main(void) {

GrafoLista *g = criar_grafo(6);

if (g == NULL) {
    fprintf(stderr, "Erro ao criar o grafo.\n");
    return 1;
}

adicionar_aresta(g, 5, 2);
adicionar_aresta(g, 5, 0);
adicionar_aresta(g, 4, 0);
adicionar_aresta(g, 4, 1);
adicionar_aresta(g, 2, 3);
adicionar_aresta(g, 3, 1);

printf("Grafo:\n");
imprimir_grafo(g);

printf("\nEh DAG? %s\n", eh_dag(g) ? "sim" : "nao");

int tamanho_kahn;
int *ordem_kahn = ordenacao_topologica_kahn(g, &tamanho_kahn);

imprimir_ordem(
    "Ordenacao por Kahn",
    ordem_kahn,
    tamanho_kahn
);

free(ordem_kahn);

int tamanho_dfs;
int *ordem_dfs = ordenacao_topologica_dfs(g, &tamanho_dfs);

imprimir_ordem(
    "Ordenacao por DFS",
    ordem_dfs,
    tamanho_dfs
);

free(ordem_dfs);

liberar_grafo(g);

printf("\nTeste com ciclo \n");

GrafoLista *ciclo = criar_grafo(3);

if (ciclo == NULL) {
    fprintf(stderr, "Erro ao criar o grafo.\n");
    return 1;
}

adicionar_aresta(ciclo, 0, 1);
adicionar_aresta(ciclo, 1, 2);
adicionar_aresta(ciclo, 2, 0);

imprimir_grafo(ciclo);

printf("\nEh DAG? %s\n", eh_dag(ciclo) ? "sim" : "nao");

int tamanho_ciclo;
int *ordem_ciclo = ordenacao_topologica_kahn(
    ciclo,
    &tamanho_ciclo
);

imprimir_ordem(
    "Kahn com ciclo",
    ordem_ciclo,
    tamanho_ciclo
);

free(ordem_ciclo);

ordem_ciclo = ordenacao_topologica_dfs(
    ciclo,
    &tamanho_ciclo
);

imprimir_ordem(
    "DFS com ciclo",
    ordem_ciclo,
    tamanho_ciclo
);

free(ordem_ciclo);

liberar_grafo(ciclo);

return 0;


}