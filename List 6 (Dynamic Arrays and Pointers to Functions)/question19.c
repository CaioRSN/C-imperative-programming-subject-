#include <stdio.h>
#include <stdlib.h>


void ataqueSequencial(char** tabuleiro, int tamanho_tabuleiro, int numero_tentativa, int* linha_alvo, int* coluna_alvo) {
    *linha_alvo = numero_tentativa / tamanho_tabuleiro;
    *coluna_alvo = numero_tentativa % tamanho_tabuleiro;
}


void ataqueReverso(char** tabuleiro, int tamanho_tabuleiro, int numero_tentativa, int* linha_alvo, int* coluna_alvo) {
    int indice_linear = (tamanho_tabuleiro * tamanho_tabuleiro) - 1 - numero_tentativa;
    *linha_alvo = indice_linear / tamanho_tabuleiro;
    *coluna_alvo = indice_linear % tamanho_tabuleiro;
}



int main() {
    int tamanho_tabuleiro, total_navios;

    if (scanf("%d %d", &tamanho_tabuleiro, &total_navios) != 2) {
        return 1;
    }

    char** tabuleiro = (char**) malloc(tamanho_tabuleiro * sizeof(char*));
    if (tabuleiro == NULL) {
        return 1; 
    }


    for (int linha = 0; linha < tamanho_tabuleiro; linha++) {
        tabuleiro[linha] = (char*) malloc(tamanho_tabuleiro * sizeof(char));
        if (tabuleiro[linha] == NULL) {
            

            for (int linha_alocada = 0; linha_alocada < linha; linha_alocada++) {
                free(tabuleiro[linha_alocada]);
            }

            free(tabuleiro);
            return 1; 
        }
        
        for (int coluna = 0; coluna < tamanho_tabuleiro; coluna++) {
            tabuleiro[linha][coluna] = '~';
        }
    }


    for (int i = 0; i < total_navios; i++) {
        int linha_navio, coluna_navio;
        scanf("%d %d", &linha_navio, &coluna_navio);
        tabuleiro[linha_navio][coluna_navio] = 'N';
    }


    int escolha_estrategia;
    scanf("%d", &escolha_estrategia);


    void (*estrategias_ataque[2])(char**, int, int, int*, int*) = {
        ataqueSequencial, 
        ataqueReverso
    };


    int tentativas_usadas = 0;
    int navios_restantes = total_navios;
    int limite_tentativas = tamanho_tabuleiro * tamanho_tabuleiro;
    int linha_ataque = 0, coluna_ataque = 0;


    for (int tentativa_atual = 0; tentativa_atual < limite_tentativas && (tentativa_atual == 0 || navios_restantes > 0); tentativa_atual++) {
        
        estrategias_ataque[escolha_estrategia - 1](tabuleiro, tamanho_tabuleiro, tentativa_atual, &linha_ataque, &coluna_ataque);
        tentativas_usadas++;
        
        if (tabuleiro[linha_ataque][coluna_ataque] == 'N') {
            tabuleiro[linha_ataque][coluna_ataque] = 'X';
            navios_restantes--;
        } else if (tabuleiro[linha_ataque][coluna_ataque] == '~') {
            tabuleiro[linha_ataque][coluna_ataque] = 'O';
        }
    }
    

    printf("Tentativas ate vencer: %d\n", tentativas_usadas);
    printf("Tabuleiro final:\n");
    for (int linha = 0; linha < tamanho_tabuleiro; linha++) {
        for (int coluna = 0; coluna < tamanho_tabuleiro; coluna++) {
            printf("%c", tabuleiro[linha][coluna]);
            if (coluna < tamanho_tabuleiro - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    for (int linha = 0; linha < tamanho_tabuleiro; linha++) {
        free(tabuleiro[linha]);
    }
    free(tabuleiro);

    return 0;
}