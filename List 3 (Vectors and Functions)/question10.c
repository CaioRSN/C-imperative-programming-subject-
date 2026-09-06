// Problem: Implement a grid-based Snake game simulator in C.
// Handle direction updates (W/A/S/D), track head and body segments, handle food consumption/growth, and detect wall or self-collisions.

#include <stdio.h>

int distanciakk (int pos_cobrinha_x, int pos_cobrinha_y, int pos_fruta_x, int pos_fruta_y){
    int distancia_x = pos_cobrinha_x - pos_fruta_x;
    int distancia_y = pos_cobrinha_y - pos_fruta_y;

    if (distancia_x < 0){
        distancia_x = -distancia_x;
    }
    if (distancia_y < 0){
        distancia_y = -distancia_y;
    }

    return distancia_x + distancia_y;
}

int frutas_x[10];
int frutas_y[10];
int visitada[10];

int menor_caminho = 0;
int melhor_caminho[10];

void coletar_frutaskk (int posicao_cobrinha_x, int posicao_cobrinha_y, int total_frut){

    for (int passo = 0; passo < total_frut; passo++){
        
        int menor_dist = 999999;
        int fruta_escolhida = -1;

        for (int i = 0; i < total_frut; i++){ //a nn visitada que está mais perto
            if (visitada[i] == 0){
                int dist = distanciakk(posicao_cobrinha_x, posicao_cobrinha_y, frutas_x[i], frutas_y[i]);
                
                if (dist < menor_dist){
                    menor_dist = dist;
                    fruta_escolhida = i;
                }
            }
        }

        visitada[fruta_escolhida] = 1;
        melhor_caminho[passo] = fruta_escolhida;
        menor_caminho += menor_dist; 
        
        posicao_cobrinha_x = frutas_x[fruta_escolhida];
        posicao_cobrinha_y = frutas_y[fruta_escolhida];
    }
}

//======================================================================


int main(){

   int tam_tabuleiro, total_frut;
   int posic_inicial_x, posic_inicial_y;

   scanf("%d", &tam_tabuleiro);
   posic_inicial_x = tam_tabuleiro / 2;
   posic_inicial_y = tam_tabuleiro / 2;

   scanf("%d", &total_frut);


   for (int i = 0; i < total_frut; i++){
    scanf(" (%d , %d)", &frutas_x[i], &frutas_y[i]);
   }


   printf("Inicializando analise do movimento.\n");

    coletar_frutaskk(posic_inicial_x, posic_inicial_y, total_frut);

    int cobrinha_x = posic_inicial_x;
    int cobrinha_y = posic_inicial_y;
    int movimentos_acumulados = 0;

    for (int i = 0; i < total_frut; i++){
        int id_fruta = melhor_caminho[i];
        int dist = distanciakk(cobrinha_x, cobrinha_y, frutas_x[id_fruta], frutas_y[id_fruta]);
        
        movimentos_acumulados += dist;
        cobrinha_x = frutas_x[id_fruta];
        cobrinha_y = frutas_y[id_fruta];

        printf("Fruta coletada, tamanho atual: %d e %d movimentos ate o momento.\n", i + 2, movimentos_acumulados);
    }

    printf("Interessante o comportamento, foram %d movimentos para coletar tudo. Eu não podia ser mais craque, agora e bom eu voltar para os tickets.\n", menor_caminho);

    return 0;
}