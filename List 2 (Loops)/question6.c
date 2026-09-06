// Problem: Calculate total traffic fines and cars penalized with license points based on speed between consecutive check points.

#include <stdio.h>

int main() {
    int quant_carros, quant_pontos;
    int arrecadacao_total = 0;
    int carros_com_ponto = 0;

    scanf("%d %d", &quant_carros, &quant_pontos);

    for (int i = 0; i < quant_carros; i++) {
        int hora_ant = 0, minuto_ant = 0;
        float km_ant = 0;

        int hora_atual, minuto_atual;
        float km_atual;

        int infracoes = 0;
        int multa_carro = 0;

        for (int j = 0; j < quant_pontos; j++) {
            scanf("%d %d %f", &hora_atual, &minuto_atual, &km_atual);

            if (j > 0) {
                int tempo_ant_min = hora_ant * 60 + minuto_ant;
                int tempo_atual_min = hora_atual * 60 + minuto_atual;
                int delta_t = tempo_atual_min - tempo_ant_min;
                float delta_d = km_atual - km_ant;

                if (delta_d < 0) {
                    delta_d = delta_d * -1;
                }

                if (delta_t > 0) {
                    float velocidade = (delta_d * 60.0) / delta_t;

                    if (velocidade > 100.0) {
                        infracoes += 1;

                        if (infracoes == 1) {
                            multa_carro += 100;
                        } else if (infracoes == 2) {
                            multa_carro += 200;
                        } else if (infracoes == 3) {
                            multa_carro += 300;
                        } else if (infracoes == 4) {
                            multa_carro += 1000;
                        }
                    }
                }
            }

            hora_ant = hora_atual;
            minuto_ant = minuto_atual;
            km_ant = km_atual;
        }

        arrecadacao_total += multa_carro;

        if (infracoes >= 4) {
            carros_com_ponto += 1;
        }
    }

    printf("Arrecadacao Multas: %d\n", arrecadacao_total);
    printf("Carros com ponto na carteira: %d\n", carros_com_ponto);

    return 0;
}