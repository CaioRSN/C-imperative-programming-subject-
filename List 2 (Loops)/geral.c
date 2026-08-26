// Problem: Generate a dynamic upward-pointing arrow ASCII art inside an N x N grid.
// The background is filled with '#' and the arrow with '.'.
// The arrow consists of a triangle head and a straight stem, aligned to the center
// (adjusted for odd/even N dimensions).

#include <stdio.h>

int main(){

int entradaN;
int par = 0;
int impar = 0;
int indice_central;

    scanf("%d", &entradaN);
    

    if (entradaN % 2 == 0){
      par = 1;
      indice_central = (entradaN / 2) - 1;
    }
    else{
        impar = 1;
        indice_central = entradaN / 2;
    }


     int direita = indice_central;
     int esquerda = indice_central;


    //laco de repeticao das linhas
    for (int l = 0; l < entradaN; l++, direita++, esquerda--){
      
       if (l <= indice_central){

        //laco de repeticao das colunas
        for (int c = 0; c < entradaN; c++){
          
            if (c >= esquerda && c <= direita){
            printf(".");
            }

            else{
                printf("#");
            }
        }

    }
    
         else{
 
          for (int c = 0; c < entradaN; c++){
          if (c == indice_central){
            printf(".");
          }
          else{
            printf("#");
          }
        }

            }

         printf("\n");
    }


    return 0;
}


// Problem: Calculate coupon scores based on even/odd digits (with point multipliers and bonus rules), classify each as PREMIADO or COMUM, and output overall promotion results.

#include <stdio.h>

int main(){

    int quant_cupom, cupom, digito;
    int par = 0;
    int impar = 0;
    int pontuacao_cupom, quant_premiado = 0, quant_normal = 0, quant_impar, quant_par; 

    scanf ("%d", &quant_cupom);
    

    for (int i = 0; i < quant_cupom; i++){
 
     pontuacao_cupom = 0; //reset da pontuacao de cada cupom
     quant_impar = 0; //reset
     quant_par = 0; //reset

     scanf("%d", &cupom);


     //loop pra verificar todos os digitos do cupom
     while(cupom > 0){
        par = 0; impar = 0;
        digito = cupom % 10;
        

        if (digito % 2 == 0){
            par = 1;
            quant_par += 1;
        } else{
            impar = 1;
            quant_impar += 1;
        }


        if (par == 1){
          pontuacao_cupom += digito * 2;
        } else{
          pontuacao_cupom += digito * 3;
        }

        cupom = cupom / 10;
     }

     if (quant_par > quant_impar){
        pontuacao_cupom += 5;
     } else if(quant_impar > quant_par) {
        pontuacao_cupom += 3;
     } else{
        pontuacao_cupom += 1;
     }

     if (pontuacao_cupom % 10 == 0){
        printf("%d PREMIADO\n", pontuacao_cupom);
        quant_premiado += 1;
     } else {
        printf("%d COMUM\n", pontuacao_cupom);
        quant_normal += 1;
     }
    }


    printf("Premiados: %d\n", quant_premiado);
    printf("Comuns: %d\n", quant_normal);
    
    if (quant_premiado > quant_normal){
        printf("Resultado: PROMOCAO");
    } else if (quant_normal > quant_premiado) {
        printf("Resultado: NORMAL");
    } else {
        printf("Resultado: EMPATE");
    }

    return 0;
}


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

