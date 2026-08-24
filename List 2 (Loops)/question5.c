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