#include <stdlib.h>
#include "dag.h"

int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
if (tamanho != NULL) {
*tamanho = 0;
}

if (g == NULL || tamanho == NULL) {
return NULL;
}

int n = g->num_vertices;

int *grau_entrada = calloc(n, sizeof(int));
int *fila = malloc(n * sizeof(int));
int *ordem = malloc(n * sizeof(int));

if (grau_entrada == NULL || fila == NULL || ordem == NULL) {
free(grau_entrada);
free(fila);
free(ordem);
return NULL;
}

for (int u = 0; u < n; u++) {
No *atual = g->adj[u];

while (atual != NULL) {
grau_entrada[atual->destino]++;
atual = atual->prox;
}
}

int inicio = 0;
int fim = 0;

for (int v = 0; v < n; v++) {
if (grau_entrada[v] == 0) {
fila[fim++] = v;
}
}

int quantidade = 0;

while (inicio < fim) {
int u = fila[inicio++];

ordem[quantidade++] = u;

No *atual = g->adj[u];

while (atual != NULL) {
int v = atual->destino;

 grau_entrada[v]--;

 if (grau_entrada[v] == 0) {
     fila[fim++] = v;
 }

 atual = atual->prox;


}
}

free(grau_entrada);
free(fila);

if (quantidade != n) {
free(ordem);
*tamanho = 0;
return NULL;
}

*tamanho = quantidade;

return ordem;
}

static int dfs_topologica(
GrafoLista *g,
int u,
int *estado,
int *ordem,
int *posicao
) {
estado[u] = 1;

No *atual = g->adj[u];

while (atual != NULL) {
int v = atual->destino;
 if (estado[v] == 1) {
     return 0;
 }
 if (estado[v] == 0) {
     if (!dfs_topologica(g, v, estado, ordem, posicao)) {
         return 0;
     }
 }

 atual = atual->prox;


}
estado[u] = 2;
ordem[(*posicao)++] = u;

return 1;
}

int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
if (tamanho != NULL) {
*tamanho = 0;
}

if (g == NULL || tamanho == NULL) {
    return NULL;
}

int n = g->num_vertices;

int *estado = calloc(n, sizeof(int));
int *ordem = malloc(n * sizeof(int));

if (estado == NULL || ordem == NULL) {
    free(estado);
    free(ordem);
    return NULL;
}

int posicao = 0;

for (int v = 0; v < n; v++) {
    if (estado[v] == 0) {
        if (!dfs_topologica(g, v, estado, ordem, &posicao)) {
            free(estado);
            free(ordem);
            *tamanho = 0;
            return NULL;
        }
    }
}


for (int i = 0; i < n / 2; i++) {
    int temp = ordem[i];
    ordem[i] = ordem[n - 1 - i];
    ordem[n - 1 - i] = temp;
}

free(estado);

*tamanho = n;

return ordem;


}

static int dfs_ciclo(GrafoLista *g, int u, int *estado) {
estado[u] = 1;

No *atual = g->adj[u];

while (atual != NULL) {
    int v = atual->destino;


    if (estado[v] == 1) {
        return 1;
    }
    if (estado[v] == 0) {
        if (dfs_ciclo(g, v, estado)) {
            return 1;
        }
    }

    atual = atual->prox;
}

estado[u] = 2;

return 0;


}

int eh_dag(GrafoLista *g) {
if (g == NULL) {
return 0;
}

int n = g->num_vertices;

int *estado = calloc(n, sizeof(int));

if (estado == NULL) {
    return 0;
}

for (int v = 0; v < n; v++) {
    if (estado[v] == 0) {
        if (dfs_ciclo(g, v, estado)) {
            free(estado);
            return 0;
        }
    }
}

free(estado);

return 1;


}