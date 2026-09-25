#include <stdio.h>
#include "grafo_lista.h"
#include "busca_grafo.h"

int main(){
    GrafoLista *grafo = criar_grafo(5);
    adicionar_aresta(grafo, 0, 1);
    adicionar_aresta(grafo, 0, 2);
    adicionar_aresta(grafo, 1, 3);
    adicionar_aresta(grafo, 2, 3);
    adicionar_aresta(grafo, 3, 4);
    for(int i = 0; i< grafo->num_vertice; i++){
        printf("%i: ->", i+1);
        No *no = grafo->lista[i];
        while (no != NULL){
            printf("%i ->", no->vertice+1);
            no = no->proximo;
        }
    printf("\n");
    }

    int pilha[10];
    dfs(grafo, 0, pilha);
    printf("\n");
    dfs(grafo, 1, pilha);
    printf("\n");
    dfs(grafo, 2, pilha);
    printf("\n");
    dfs(grafo, 3, pilha);
    printf("\n");
    dfs(grafo, 4, pilha);
    printf("\n");



    return 0;
}