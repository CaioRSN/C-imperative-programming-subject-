// Problem: Laser Lab Simulation
// Simulate a light beam traversing a grid: mark visited paths with '*', bounce off mirrors ('/' and '\' - escaped in C), and terminate at boundaries or obstacles ('#').

#include <stdio.h>
#include <string.h>

int main (){
    
    int linhas, colunas;
    int quant_palavras;

    scanf("%d %d", &linhas, &colunas);

    char matriz[linhas][colunas + 1];

    int dl[8] = { 0,  0,  1, -1,  1,  1, -1, -1};
    int dc[8] = { 1, -1,  0,  0,  1, -1,  1, -1};
    char *nomes_dir[8] = {
    "horizontal-direita",
    "horizontal-esquerda",
    "vertical-baixo",
    "vertical-cima",
    "diagonal-baixo-direita",
    "diagonal-baixo-esquerda",
    "diagonal-cima-direita",
    "diagonal-cima-esquerda"
};


    for (int i = 0; i < linhas; i++){
        scanf("%s", matriz[i]);
    }

    scanf("%d", &quant_palavras);


    for (int i = 0; i < quant_palavras; i++){
        char palavra[100];
        scanf("%s", palavra);
        
        int achou = 0;
        int tam_palavra = strlen(palavra);

        for (int l = 0; l < linhas && achou == 0; l++){

            for (int c = 0; c < colunas && achou == 0; c++){

                for (int p = 0; p < 8; p++){

                    int linha_fim = l + (tam_palavra - 1) * dl[p]; 
                    int coluna_fim = c + (tam_palavra - 1) * dc[p];

                    if (linha_fim >= 0 && linha_fim < linhas && coluna_fim >= 0 && coluna_fim < colunas){

                        int bateu = 1;

                        for (int z = 0; z < tam_palavra && bateu == 1; z++){

                            int linha_atual = l + z * dl[p];
                            int coluna_atual = c + z * dc[p];
                            
                            if (matriz[linha_atual][coluna_atual] != palavra[z]){
                                bateu = 0;
                            }

                        }

                        if (bateu == 1) {
                            printf("%s encontrada em (%d, %d), direcao: %s\n", palavra, l, c, nomes_dir[p]);
                            achou = 1;
                        }

                    }

                }

            }

        }

     if (achou == 0){
        printf("%s nao encontrada\n", palavra);
     }

    }


    return 0;
}