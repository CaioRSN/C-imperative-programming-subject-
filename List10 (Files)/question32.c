#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char sigla[20];
    int nota_acumulada;
} CentroAcademico;


typedef struct {
    int id_trabalho;
    char sigla_centro[20];
    int nota;
} Trabalho;


void converter_txt_para_bin(char *arq_txt, char *arq_bin) {
    FILE *entrada = fopen(arq_txt, "r");
    if (entrada == NULL) {
        return;
    }

    FILE *saida = fopen(arq_bin, "wb");
    if (saida == NULL) {
        fclose(entrada);
        return;
    }

    // sessao, Q, registros (a etapa B le igual)
    int sessao = 0;
    int q = 0;
    fscanf(entrada, "%d %d", &sessao, &q);
    fwrite(&sessao, sizeof(int), 1, saida);
    fwrite(&q, sizeof(int), 1, saida);


    for (int i = 0; i < q; i++) {
        Trabalho trabalho = {0, "", 0};
        fscanf(entrada, "%d %19s %d", &trabalho.id_trabalho, trabalho.sigla_centro, &trabalho.nota);
        fwrite(&trabalho, sizeof(Trabalho), 1, saida);
    }


    fclose(entrada);
    fclose(saida);
}


void processar_planilha_bin(char *arq_bin, CentroAcademico *centros, int qtd_centros,
                            Trabalho **trabalhos, int *qtd_trabalhos) {
    FILE *arq = fopen(arq_bin, "rb");
    if (arq == NULL) {
        return;
    }


    int sessao = 0;
    int q = 0;

    fread(&sessao, sizeof(int), 1, arq);
    fread(&q, sizeof(int), 1, arq);


    for (int i = 0; i < q; i++) {
        Trabalho trabalho;
        fread(&trabalho, sizeof(Trabalho), 1, arq);

        // Trabalho ** porque o realloc pode mudar o endereco do vetor
        *trabalhos = realloc(*trabalhos, (*qtd_trabalhos + 1) * sizeof(Trabalho));
        (*trabalhos)[*qtd_trabalhos] = trabalho;
        (*qtd_trabalhos)++;

        for (int j = 0; j < qtd_centros; j++) {
            if (strcmp(centros[j].sigla, trabalho.sigla_centro) == 0) {
                centros[j].nota_acumulada += trabalho.nota;
            }
        }
    }


    fclose(arq);

}

void ordenar_centros(CentroAcademico *centros, int qtd) {
    for (int i = 1; i < qtd; i++) {
        CentroAcademico chave = centros[i];
        int j = i - 1;
        while (j >= 0 && centros[j].nota_acumulada < chave.nota_acumulada) {
            centros[j + 1] = centros[j];
            j--;
        }
        centros[j + 1] = chave;
    }
}


void ordenar_trabalhos(Trabalho *trabalhos, int qtd) {
    for (int i = 1; i < qtd; i++) {
        Trabalho chave = trabalhos[i];
        int j = i - 1;
        while (j >= 0 && trabalhos[j].nota < chave.nota) {
            trabalhos[j + 1] = trabalhos[j];
            j--;
        }
        trabalhos[j + 1] = chave;
    }
}


int main(void) {
    int qtd_centros = 0;
    scanf("%d", &qtd_centros);

    CentroAcademico *centros = malloc(qtd_centros * sizeof(CentroAcademico));
    for (int i = 0; i < qtd_centros; i++) {
        scanf("%19s", centros[i].sigla);
        centros[i].nota_acumulada = 0;
    }


    Trabalho *trabalhos = NULL;
    int qtd_trabalhos = 0;


    int qtd_planilhas = 0;
    scanf("%d", &qtd_planilhas);


    for (int i = 0; i < qtd_planilhas; i++) {
        char arq_txt[256];
        char arq_bin[256];
        scanf("%255s %255s", arq_txt, arq_bin);

        converter_txt_para_bin(arq_txt, arq_bin);
        processar_planilha_bin(arq_bin, centros, qtd_centros, &trabalhos, &qtd_trabalhos);

        printf("Processamento concluido: %s -> %s\n", arq_txt, arq_bin);
    }


    ordenar_centros(centros, qtd_centros);

    printf("=== RANKING INSTITUCIONAL (CENTROS) ===\n");

    for (int i = 0; i < qtd_centros; i++) {
        printf("%do Lugar: %s - %d pontos\n", i + 1, centros[i].sigla, centros[i].nota_acumulada);
    }

    ordenar_trabalhos(trabalhos, qtd_trabalhos);

    printf("=== RANKING INDIVIDUAL (TOP 3 TRABALHOS) ===\n");

    for (int i = 0; i < 3 && i < qtd_trabalhos; i++) {
        printf("%do Lugar: Trabalho %d (%s) - Nota %d\n", i + 1,
               trabalhos[i].id_trabalho, trabalhos[i].sigla_centro, trabalhos[i].nota);
    }


    free(trabalhos);
    free(centros);
    return 0;
}