// Problem: Validate a given calendar date (day, month, year) between 1900 and 2100,
// accounting for months with different days and leap year rules.

#include <stdio.h>


int main (){
    int dia, mes, ano;

    int valido; //variavel suporte pra verificar se eh valido ou nn (1 ou 0)
    int bissexto = 0; //variavel suporte pra verificar se eh bissexto ou nn (1 ou 0)
    int mes_30dias = 0; //var suporte pra verificar se eh mes de 30 dias (1 ou 0)
 
    scanf("%d" "%d" "%d", &dia, &mes, &ano);
    

    if ((ano % 4 == 0 && ano % 100 != 0) || ano == 2000){
        bissexto = 1;
    }
    
    if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
        mes_30dias = 1;
    }


    if (ano <1900 || ano>2100){
     valido = 0;
    }
    else if (mes <1 || mes>12){
     valido = 0;
    }
    else if (dia <1 || dia>31){
        valido = 0;
    }
    else if (mes_30dias && dia == 31){
        valido = 0;
    }
    else if (mes == 2 && dia > 29){
        valido = 0;
    }
    else if (mes == 2 && bissexto == 0 && dia == 29) {
        valido = 0;
    }
  
    else{
        valido = 1;
    }


    if (valido == 0){
        printf("Data invalida");
    }
    else{
        printf("Data valida");
    }

    return 0;
}

 