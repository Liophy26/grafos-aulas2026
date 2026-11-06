
#include <stdio.h>
#include <time.h>
#include "cobertura.h"

int main(void) {

    int tamanhos[] = {5, 8, 10, 12, 15};
    int total = sizeof(tamanhos) / sizeof(tamanhos[0]);

    unsigned int seed = 12345;

    printf("\n");
    printf("===============================================\n");
    printf("       EXPERIMENTO - COBERTURA MINIMA\n");
    printf("===============================================\n");

    printf("\n%-8s %-12s %-12s %-15s\n",
           "N", "BT (s)", "Guloso (s)", "Solucao BT");

    printf("------------------------------------------------\n");

    for (int k = 0; k < total; k++) {

        Grafo g;

        int sol_bt[MAX_VERTICES] = {0};
        int sol_gulosa[MAX_VERTICES] = {0};

        int n = tamanhos[k];

        gerar_grafo(&g, n, &seed);

        clock_t inicio = clock();

        int resultado_bt =
            cobertura_minima_bt(&g, sol_bt);

        clock_t fim = clock();

        double tempo_bt =
            (double)(fim - inicio) / CLOCKS_PER_SEC;

        // Guloso.
        inicio = clock();

        int resultado_guloso =
            cobertura_gulosa(&g, sol_gulosa);

        fim = clock();

        double tempo_guloso =
            (double)(fim - inicio) / CLOCKS_PER_SEC;

        printf("%-8d %-12.6f %-12.6f %-15d\n",
               n,
               tempo_bt,
               tempo_guloso,
               resultado_bt);

        printf("         Solucao gulosa: %d vertices\n",
               resultado_guloso);

        printf("         BT valida: %s | Gulosa valida: %s\n",
               eh_cobertura(&g, sol_bt) ? "SIM" : "NAO",
               eh_cobertura(&g, sol_gulosa) ? "SIM" : "NAO");

        printf("------------------------------------------------\n");
    }

    printf("\nExperimento finalizado!\n");

    return 0;
}
