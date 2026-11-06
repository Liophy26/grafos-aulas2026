
#include <stdio.h>
#include <string.h>
#include "cobertura.h"

int eh_cobertura(const Grafo *g, const int sol[]) {
    for (int i = 0; i < g->n; i++) {
        for (int j = i + 1; j < g->n; j++) {

            if (g->adj[i][j] &&
                !sol[i] && !sol[j]) {
                return 0;
            }
        }
    }

    return 1;
}

static int grau_restante(const Grafo *g,
                         const int sol[],
                         int v) {
    int grau = 0;

    for (int j = 0; j < g->n; j++) {
        if (g->adj[v][j] && !sol[j]) {
            grau++;
        }
    }

    return grau;
}

int cobertura_gulosa(const Grafo *g, int sol[]) {
    memset(sol, 0, MAX_VERTICES * sizeof(int));

    int quantidade = 0;

    while (!eh_cobertura(g, sol)) {
        int melhor = -1;
        int maior_grau = -1;

        for (int v = 0; v < g->n; v++) {
            if (!sol[v]) {
                int grau = grau_restante(g, sol, v);

                if (grau > maior_grau) {
                    maior_grau = grau;
                    melhor = v;
                }
            }
        }

        if (melhor == -1 || maior_grau == 0)
            break;

        sol[melhor] = 1;
        quantidade++;
    }

    return quantidade;
}

static int encontrar_aresta(const Grafo *g,
                            const int sol[],
                            int *u,
                            int *v) {
    for (int i = 0; i < g->n; i++) {
        for (int j = i + 1; j < g->n; j++) {
            if (g->adj[i][j] &&
                !sol[i] && !sol[j]) {
                *u = i;
                *v = j;
                return 1;
            }
        }
    }

    return 0;
}

static int limite_inferior(const Grafo *g,
                           const int sol[]) {
    int arestas = 0;
    int max_grau = 0;

    for (int i = 0; i < g->n; i++) {
        if (sol[i])
            continue;

        int grau = grau_restante(g, sol, i);

        if (grau > max_grau)
            max_grau = grau;

        for (int j = i + 1; j < g->n; j++) {
            if (g->adj[i][j] &&
                !sol[j]) {
                arestas++;
            }
        }
    }

    if (arestas == 0)
        return 0;

    if (max_grau == 0)
        return g->n + 1;

    return (arestas + max_grau - 1) / max_grau;
}

static void backtracking(const Grafo *g,
                         int sol[],
                         int atual[],
                         int quantidade,
                         int *melhor) {

    if (quantidade >= *melhor)
        return;

    int u, v;

    if (!encontrar_aresta(g, sol, &u, &v)) {
        *melhor = quantidade;
        memcpy(atual, sol, MAX_VERTICES * sizeof(int));
        return;
    }

    int limite = limite_inferior(g, sol);

    if (quantidade + limite >= *melhor)
        return;

    if (grau_restante(g, sol, u) <
        grau_restante(g, sol, v)) {
        int temp = u;
        u = v;
        v = temp;
    }

    sol[u] = 1;

    backtracking(g, sol, atual,
                 quantidade + 1, melhor);

    sol[u] = 0;

    sol[v] = 1;

    backtracking(g, sol, atual,
                 quantidade + 1, melhor);

    sol[v] = 0;
}

int cobertura_minima_bt(const Grafo *g, int sol[]) {
    int atual[MAX_VERTICES] = {0};
    int melhor_sol[MAX_VERTICES] = {0};
    int melhor = cobertura_gulosa(g, melhor_sol);

    memset(atual, 0, sizeof(atual));
    backtracking(g, atual, melhor_sol, 0, &melhor);
    memcpy(sol, melhor_sol, sizeof(melhor_sol));
    return melhor;
}

void gerar_grafo(Grafo *g, int n, unsigned int *seed) {
    g->n = n;

    memset(g->adj, 0, sizeof(g->adj));

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            *seed = (*seed * 1103515245u + 12345u);
            int valor = (*seed / 65536u) % 100;
            if (valor < 35) {
                g->adj[i][j] = 1;
                g->adj[j][i] = 1;
            }
        }
    }
}
