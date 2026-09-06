// Problem: Simulate energy management for Pou game, processing eating/playing actions until energy reaches zero or below.

#include <stdio.h>

int main() {
    char acao;
    int valor;
    int energia = 10;

    while (energia > 0) {
        scanf(" %c %d", &acao, &valor);

        if (acao == 'a') { // Alimentar
            if (energia >= 10) {
                printf("O Pou está muito gordinho... ele precisa brincar!\n");
            } else {
                for (int i = 1; i <= valor; i++) {
                    printf("Alimento %d foi consumido.\n", i);
                }
                
                energia += valor;
                printf("%d de energia recuperado! Meu total agora é %d.\n", valor, energia);
            }
        } else if (acao == 'b') { // Brincar
            energia -= valor;

            if (valor == 1) {
                printf("Queimei meus neurônios em Memory!\n");
            } else if (valor == 2) {
                printf("Novo recorde em Free Fall!\n");
            } else if (valor == 3) {
                printf("Cliff Jump é demais!\n");
            } else if (valor == 4) {
                printf("Sky Jump é o clássico!\n");
            }
        }
    }

    printf("CONGRATURATION. THIS STORY IS HAPPY END. THANK YOU.\n");

    return 0;
}