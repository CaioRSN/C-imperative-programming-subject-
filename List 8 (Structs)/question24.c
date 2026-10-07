#include <stdio.h>
#include <string.h>

typedef struct {
    char titulo[101];
    char genero[101];
    char estudio[101];
    char console[101];
    int nota;
    int anoLancamento;
} Jogo;


int main(){


    int quantidade_jogos;
    scanf("%d", &quantidade_jogos);
    Jogo colecao[100];

    for (int i = 0; i < quantidade_jogos; i++) {
        scanf("%s %s %s %s %d %d", 
              colecao[i].titulo, 
              colecao[i].genero, 
              colecao[i].estudio, 
              colecao[i].console, 
              &colecao[i].nota, 
              &colecao[i].anoLancamento);
    

         if (colecao[i].nota > 7) {
            printf("AWESOME! Mais um GOTY pra minha coleção!\n");
      } else if (colecao[i].nota < 4) {
            printf("Era melhor jogar mais um jogo de Mahjong.\n");
        }
    }


    char funcao[50];

    while (scanf("%s", funcao) != EOF) {

        if (strcmp(funcao, "printAno") == 0) {
            int ano_busca;
            scanf("%d", &ano_busca);
            int jogos_encontrados = 0;

            for (int i = 0; i < quantidade_jogos; i++) {
                if (colecao[i].anoLancamento == ano_busca) {
                    printf("%s\n", colecao[i].titulo);
                    jogos_encontrados++;
                }
            }

            if (jogos_encontrados > 0) {
                printf("Tenho %d jogos || %d.\n", jogos_encontrados, ano_busca);
            } else {
                printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n", ano_busca);
            }

      } else if (strcmp(funcao, "printLetra") == 0) {
            char letra_busca;
            scanf(" %c", &letra_busca); 
            int jogos_encontrados = 0;

            for (int i = 0; i < quantidade_jogos; i++) {
                if (colecao[i].titulo[0] == letra_busca) {
                    printf("%s\n", colecao[i].titulo);
                    jogos_encontrados++;
                }
            }

            if (jogos_encontrados > 0) {
                printf("Tenho %d jogos || %c.\n", jogos_encontrados, letra_busca);
            } else {
                printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n", letra_busca);
            }

        } else if (strcmp(funcao, "printStudio") == 0) {
            char estudio_busca[101];
            scanf("%s", estudio_busca);
            int jogos_encontrados = 0;

            for (int i = 0; i < quantidade_jogos; i++) {
                if (strcmp(colecao[i].estudio, estudio_busca) == 0) {
                    printf("%s\n", colecao[i].titulo);
                    jogos_encontrados++;
                }
            }

            if (jogos_encontrados > 0) {
                printf("Tenho %d jogos || %s.\n", jogos_encontrados, estudio_busca);
            } else {
                printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n", estudio_busca);
            }

        } else if (strcmp(funcao, "printConsole") == 0) {
            char console_busca[101];
            scanf("%s", console_busca);
            int jogos_encontrados = 0;

            for (int i = 0; i < quantidade_jogos; i++) {
                if (strcmp(colecao[i].console, console_busca) == 0) {
                    printf("%s\n", colecao[i].titulo);
                    jogos_encontrados++;
                }
            }

            if (jogos_encontrados > 0) {
                printf("Tenho %d jogos || %s.\n", jogos_encontrados, console_busca);
            } else {
                printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n", console_busca);
            }

        } else if (strcmp(funcao, "printColecao") == 0) {
            for (int i = 0; i < quantidade_jogos; i++) {
                printf("%s %d\n", colecao[i].titulo, colecao[i].nota);
            }
        }
    }

    printf("Enjoei de jogar, agora vou ver TV.\n");


    return 0;
}
