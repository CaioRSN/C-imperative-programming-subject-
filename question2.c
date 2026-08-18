#include <stdio.h>


int main (){
    
   int energia, v1, v2, v3, d; //declaracao das 5 variaveis
   scanf("%d %d %d %d", &v1, &v2, &v3, &d); //iinput dos 4 valores

    int primeiro_d = d / 10;
    int segundo_d = d % 10;
    int caminho; //variavel de suporte pra saber se foi direto ou nao (1 ou 0)


    int caminho_direto = v1 + v3;
    int caminho_v2 = v1 + v2 + v3;

    if (primeiro_d > segundo_d){
        int bonus = primeiro_d - segundo_d;
        caminho_direto += bonus;

    } else if (segundo_d > primeiro_d){
        int bonus = segundo_d - primeiro_d;
        caminho_v2 += bonus;

    } else {
        int bonus = primeiro_d + segundo_d;
        caminho_direto += bonus;
        caminho_v2 += bonus;
    }

    //escolha de caminho
    if (caminho_direto > caminho_v2){
        energia = caminho_direto;
        caminho = 0;

    } else {
        energia = caminho_v2;
        caminho = 1;
    }
    


    //classificacao do caminho
    if (caminho == 0){
        printf("Caminho: direto. ");

    } else {
        printf("Caminho: P2. ");
    }

   
    //classificao da energia
    if (energia > 30){
        printf("Xupenio aprova! Nível: ELITE.");

    } else if (energia >= 10 && energia <=30){
      printf ("Boa caminhada! Nível: SÓLIDO.");

    } else if (energia >= 0 && energia <=9) {
      printf("Passou por pouco. Nível: BÁSICO.");

    } else {
      printf("Xupenio reprova. Nível: CRÍTICO.");
    }

    return 0;
}
