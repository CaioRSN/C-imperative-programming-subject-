#include <stdio.h>
#include <string.h>

int main (){


    int linhas, colunas;

    scanf("%d %d", &linhas, &colunas);
    char matriz[linhas][colunas + 1];


    for (int i = 0; i < linhas; i++){
        scanf("%s", matriz[i]);
    }


    int linha_inicial, coluna_inicial;
    scanf("%d %d", &linha_inicial, &coluna_inicial);

    char direcao[15];
    int dl = 0, dc = 0; 
    scanf ("%s", direcao);
 
    if (strcmp(direcao, "CIMA") == 0){
        dl = -1;
        dc = 0;
    } else if (strcmp(direcao, "BAIXO") == 0) {
       dl = 1;
       dc = 0;
    } else if (strcmp(direcao, "ESQUERDA") == 0){
        dl = 0;
        dc = -1;
    } else{
        dl = 0;
        dc = 1;
    }


//==========================================================================

    int l = linha_inicial;
    int c = coluna_inicial;
    while (l >= 0 && l < linhas && c >= 0 && c < colunas && matriz[l][c] != '#'){

        if (matriz[l][c] == '.'){
            matriz[l][c] = '*';


        } else if (matriz[l][c] == '/'){ //espelho 1 ========================

            if (dl == -1 && dc == 0){  //cima para direita
                dl = 0;
                dc = 1;
            } else if (dl == 1 && dc == 0){ //baixo para esquerda
               dl = 0;
               dc = -1;
            } else if (dl == 0 && dc == -1){ //esquerda para baixo
                dl = 1;
                dc = 0;
            }
            else { //direita pra cima 
                dl = -1;
                dc = 0;
            }

            
        } else if (matriz[l][c] == '\\'){

              if (dl == -1 && dc == 0){  //cima para esquerda
                dl = 0;
                dc = -1;
            } else if (dl == 1 && dc == 0){ //baixo para direita
               dl = 0;
               dc = 1;
            } else if (dl == 0 && dc == -1){ //esquerda para cima
                dl = -1;
                dc = 0;
            }
            else { //direita pra cima 
                dl = 1;
                dc = 0;
            }

        }

        l += dl;
        c += dc; 

    }

    for(int i = 0; i < linhas; i++){
        printf("%s\n", matriz[i]);
    }


    return 0;
}