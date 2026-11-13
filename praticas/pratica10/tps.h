
#ifndef TPS_H
#define TPS_H

typedef struct {
    int custo;
    int *caminho;
    int tamanho;
} ResultadoTSP;

ResultadoTSP tsp_forca_bruta(int **grafo, int n);

ResultadoTSP tsp_vizinho_mais_proximo(int **grafo, int n);

ResultadoTSP tsp_insercao(int **grafo, int n);

int **grafo_para_tsp(int **grafo, int n);

void liberar_resultado(ResultadoTSP resultado);

#endif
