#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *entrada = fopen("requisicoes.txt", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir requisicoes.txt\n");
        return 1;
    }


    FILE *saida = fopen("relatorio.txt", "w");
    if (saida == NULL) {
        printf("Erro ao abrir relatorio.txt\n");
        fclose(entrada);
        return 1;
    }



    int n = 0;
    fscanf(entrada, "%d", &n);


    int qtd2xx = 0, qtd3xx = 0, qtd4xx = 0, qtd5xx = 0;
    int soma = 0;
    int maiorTempo = -1;
    char endpointMaisLento[51] = "";


    for (int i = 0; i < n; i++) {
        char endpoint[51];
        int codigo = 0;
        int tempo = 0;

        fscanf(entrada, "%50s %d %d", endpoint, &codigo, &tempo);

        if (codigo >= 200 && codigo <= 299) {
            qtd2xx++;
        } else if (codigo >= 300 && codigo <= 399) {
            qtd3xx++;
        } else if (codigo >= 400 && codigo <= 499) {
            qtd4xx++;
        } else if (codigo >= 500 && codigo <= 599) {
            qtd5xx++;
        }

        soma += tempo;

        if (tempo > maiorTempo) {
            maiorTempo = tempo;
            strcpy(endpointMaisLento, endpoint);
        }
    }


    double media = (double) soma / n;
    double taxaErro = 100.0 * (qtd4xx + qtd5xx) / n;


    char status[10];
    if (taxaErro < 10.0) {
        strcpy(status, "SAUDAVEL");
    } else if (taxaErro < 30.0) {
        strcpy(status, "ATENCAO");
    } else {
        strcpy(status, "CRITICO");
    }


    fprintf(saida, "=== RELATORIO DE REQUISICOES ===\n");
    fprintf(saida, "Total de requisicoes: %d\n", n);
    fprintf(saida, "Sucesso (2xx): %d\n", qtd2xx);
    fprintf(saida, "Redirecionamento (3xx): %d\n", qtd3xx);
    fprintf(saida, "Erro de cliente (4xx): %d\n", qtd4xx);
    fprintf(saida, "Erro de servidor (5xx): %d\n", qtd5xx);
    fprintf(saida, "Tempo medio de resposta: %.2f ms\n", media);
    fprintf(saida, "Mais lenta: %s (%d ms)\n", endpointMaisLento, maiorTempo);
    fprintf(saida, "Taxa de erro: %.2f%%\n", taxaErro);
    fprintf(saida, "STATUS: %s\n", status);


    fclose(entrada);
    fclose(saida);

    return 0;
}