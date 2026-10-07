#include <stdio.h>
#include <stdlib.h>


int main(){

    
    int capacidade = 1;
    int tamanho = 0;
    int *slimes = (int *)malloc(capacidade * sizeof(int));
    int nivel;


    while (scanf("%d", &nivel) == 1 && nivel != -1){
      
        if (tamanho == capacidade){
           capacidade *= 2;
           slimes = (int *)realloc(slimes, capacidade * sizeof(int));
        }

        slimes[tamanho] = nivel;
        tamanho++;
    }


     int i = 0;

     while (i < tamanho - 1){
      
        if (slimes[i] == slimes[i + 1]){
            slimes[i] += 1;

            for (int k = i + 1; k < tamanho - 1; k++){
                slimes[k] = slimes[k + 1];
            }
            tamanho--;

            if (i > 0){
                i--;
            }

        } else {
            i++;
        } 

     }

    printf("Slimes restantes:");
    for (int j = 0; j < tamanho; j++) {
        printf(" %d", slimes[j]);
    }
    printf("\n");

    free(slimes);


    return 0;
}