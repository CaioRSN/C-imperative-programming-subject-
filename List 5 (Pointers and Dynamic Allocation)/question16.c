#include <stdio.h>
#include <stdlib.h>

void operacao(int *valor1, int *valor2, char *comando, int *Resultados, int *pos){


int resposta = 0;

    if (*comando == '+') {
        resposta = *valor1 + *valor2;
    } 
    else if (*comando == '-') {
        resposta = *valor1 - *valor2;
    } 
    else if (*comando == '*') {
        resposta = *valor1 * *valor2;
    } 
    else if (*comando == '/') {
        resposta = *valor1 / *valor2;
    }

    Resultados[*pos] = resposta;

    printf("Operação %d: %d %c %d = %d\n", *pos + 1, *valor1, *comando, *valor2, resposta);
    (*pos)++;
}



int main(){

    int * Resultados = (int*) calloc(1, sizeof(int));

    int capacidade = 1;
    int pos = 0;


    int v1, v2;
    char sinal;

    printf("=Iniciando Cálculos=\n");


    while (scanf("%d %c %d", &v1, &sinal, &v2) != EOF) {

        int operador_valido = 0;
        int divisao_por_zero = 0;

        if (sinal == '+' || sinal == '-' || sinal == '*' || sinal == '/'){
            operador_valido = 1;
        }

        if(sinal == '/' && v2 == 0){
            divisao_por_zero = 1;
        }

        if (operador_valido != 1 || divisao_por_zero == 1) {
            printf("Operação Inválida! Próxima!\n");
        } 
        

        else {

            if (pos == capacidade) {
                capacidade = capacidade * 2;

                int *temp = (int*) realloc(Resultados, capacidade * sizeof(int));

                if (temp == NULL) {
                    free(Resultados);
                    return 1;
                }

                Resultados = temp;
            }
          
            operacao(&v1, &v2, &sinal, Resultados, &pos);

        }
    }

    printf("\nOperações concluídas:\n");
    for (int i = 0; i < pos; i++) {
        printf("Resultado Operação %d: %d\n", i + 1, Resultados[i]);
    }

   
    free(Resultados); 
    return 0;
}