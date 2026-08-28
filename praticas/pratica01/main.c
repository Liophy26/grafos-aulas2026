#include <stdio.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

int main() {
    
    GrafoMatriz* gm = criar_grafo_matriz(4);
    inserir_aresta_m(gm, 0, 1);
    inserir_aresta_m(gm, 0, 2);
    inserir_aresta_m(gm, 1, 3);
    imprimir_matriz(gm);
    printf("Grau do vertice 0 (matriz): %d\n", grau_m(gm, 0));
    printf("Adjacencia 0->1 (matriz): %d\n", sao_adjacentes_m(gm, 0, 1));
    remover_aresta_m(gm, 0, 1);
    printf("Adjacencia 0->1 apos remocao (matriz): %d\n", sao_adjacentes_m(gm, 0, 1));
    liberar_grafo_m(gm);

    
    GrafoLista* gl = criar_grafo_lista(4);
    inserir_aresta_lista(gl, 0, 1); 
    inserir_aresta_lista(gl, 0, 2);
    inserir_aresta_lista(gl, 1, 3);
    imprimir_lista(gl);
    printf("Grau do vertice 0 (lista): %d\n", grau_lista(gl, 0));
    printf("Adjacencia 0->1 (lista): %d\n", sao_adjacentes_lista(gl, 0, 1));
    remover_aresta_lista(gl, 0, 1);
    printf("Adjacencia 0->1 apes remocao (lista): %d\n", sao_adjacentes_lista(gl, 0, 1));
    liberar_grafo_lista(gl);

    return 0;
}
