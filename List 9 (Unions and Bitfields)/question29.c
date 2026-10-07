#include <stdio.h>


typedef union {
    int valor;
    struct { unsigned int resto : 30; unsigned int msb : 2; } e1;
    struct { unsigned int resto : 28; unsigned int msb : 2; unsigned int : 2; } e2;
    struct { unsigned int resto : 26; unsigned int msb : 2; unsigned int : 4; } e3;
} Senha;


int main() {
    int habilidade, hora, minuto;
    int dificuldade, senha_correta;
    int tentativa_inicial;

    scanf("%d | %d | %d", &habilidade, &hora, &minuto);
    scanf("%d | %d", &dificuldade, &senha_correta);
    scanf("%d", &tentativa_inicial);

    int dif_relativa = (dificuldade - habilidade) - 5;

    int nivel;
    if (dif_relativa <= 5) {
        nivel = 1;
    } else if (dif_relativa <= 10) {
        nivel = 2;
    } else {
        nivel = 3;
    }

    int tempo_por_etapa = 120 / habilidade;
    int tempo_total_minutos = tempo_por_etapa * nivel;

    int total_minutos_absolutos = minuto + tempo_total_minutos;
    int h_final = (hora + total_minutos_absolutos / 60) % 24;
    int m_final = total_minutos_absolutos % 60;

    int minutos_inicio;
    if (hora < 12) {
        minutos_inicio = (hora + 24) * 60 + minuto;
    } else {
        minutos_inicio = hora * 60 + minuto;
    }

    int minutos_fim = minutos_inicio + tempo_total_minutos;
    
    int no_prazo = 0;
    if (minutos_inicio >= 18 * 60) {
        if (minutos_fim <= 28 * 60) {
            no_prazo = 1;
        }
    }


    Senha senha;
    senha.valor = tentativa_inicial;


    for (int i = 0; i < nivel; i++) {

        unsigned int msb, resto;

        if (i == 0){
         msb = senha.e1.msb; resto = senha.e1.resto; 
        }

        else if (i == 1){
            msb = senha.e2.msb; resto = senha.e2.resto; 
        }

        else{
            msb = senha.e3.msb; resto = senha.e3.resto;
         }


         unsigned int r;
         if (msb == 0){
            r = resto + (dificuldade * 10 / 100);
         }

         else if (msb == 1){
          r = resto - (habilidade * 5 / 100);
         }

         else if (msb == 2){ 
            r = resto * (habilidade * 2);
         }

         else{
             r = resto / (dificuldade / 5);
         }


    senha.valor = r & ((1u << (30 - 2 * i)) - 1); 
    
        }

    printf("(%d) horario inicial: (%02d:%02d) | resultado encontrado: (%d)   horario final:(%02d:%02d)\n",
           tentativa_inicial, hora, minuto, senha.valor, h_final, m_final);

    if (senha.valor == senha_correta && no_prazo == 1) {
        printf("Beep sabia, Beep sempre sabe, BEEEEEEPPPPP\n");
    } else {
        printf("beepp, NA PROXIMA BEEP ABRIRAAAAAA\n");
    }

    return 0;
}