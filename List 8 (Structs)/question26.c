#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Mecha Mecha;


typedef struct {
    char nome[30];
    int atrib1;
    int atrib2;
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;
    SubSistema sistemas[]; 
};


void rotina_defesa(Mecha *mecha_alvo, int indice_slot, int dano_wintermute, int *resultado_saida) {
    
    int dano_base = mecha_alvo->sistemas[indice_slot].atrib1;
    int bonus_slot = mecha_alvo->sistemas[indice_slot].atrib2;

    int dano_final_sofrido = dano_wintermute - dano_base - (indice_slot * bonus_slot);
    
    if (dano_final_sofrido < 0) {
        dano_final_sofrido = 0;
    }
    
    *resultado_saida = dano_final_sofrido;
}

void rotina_utilidade(Mecha *mecha_alvo, int indice_slot, int dano_wintermute, int *resultado_saida) {
   
    int recuperacao_base = mecha_alvo->sistemas[indice_slot].atrib1;
    int multiplicador_slot = mecha_alvo->sistemas[indice_slot].atrib2;

    int energia_recuperada = recuperacao_base + (indice_slot * multiplicador_slot);
    
    mecha_alvo->energia_atual += energia_recuperada;
    
    *resultado_saida = energia_recuperada; 
}

void rotina_ataque(Mecha *mecha_alvo, int indice_slot, int dano_wintermute, int *resultado_saida) {
    int dano_base = mecha_alvo->sistemas[indice_slot].atrib1;
    int custo_energia = mecha_alvo->sistemas[indice_slot].atrib2;

    if (mecha_alvo->energia_atual < custo_energia) {
        *resultado_saida = 0;
    } else {
    
        int dano_causado = dano_base + mecha_alvo->energia_atual + indice_slot - dano_wintermute;
        
        mecha_alvo->energia_atual -= custo_energia;
        
        *resultado_saida = dano_causado;
    }
}

int comparar_mechas_por_id(const void *ponteiro_a, const void *ponteiro_b) {

    Mecha *mecha_a = *(Mecha **)ponteiro_a;
    Mecha *mecha_b = *(Mecha **)ponteiro_b;

    return (mecha_a->id - mecha_b->id);
}



int main() {


    int total_mechas;
    if (scanf("%d", &total_mechas) != 1) return 0;

    Mecha **esquadrao = malloc(total_mechas * sizeof(Mecha*));

    for (int i = 0; i < total_mechas; i++) {
        int id_temp, energia_temp, qtd_sistemas_temp;
        char modelo_temp[50];

        scanf("%d %49s %d %d", &id_temp, modelo_temp, &energia_temp, &qtd_sistemas_temp);

        Mecha *novo_mecha = malloc(sizeof(Mecha) + (qtd_sistemas_temp * sizeof(SubSistema)));

        novo_mecha->id = id_temp;
        strcpy(novo_mecha->modelo, modelo_temp);
        novo_mecha->energia_atual = energia_temp;
        novo_mecha->num_sistemas = qtd_sistemas_temp;

    

        for (int j = 0; j < qtd_sistemas_temp; j++) {
            char tipo_sistema;
            scanf(" %c %29s %d %d", 
                  &tipo_sistema, 
                  novo_mecha->sistemas[j].nome, 
                  &novo_mecha->sistemas[j].atrib1, 
                  &novo_mecha->sistemas[j].atrib2);

            if (tipo_sistema == 'D') {
                novo_mecha->sistemas[j].subrotina = rotina_defesa;
            } else if (tipo_sistema == 'U') {
                novo_mecha->sistemas[j].subrotina = rotina_utilidade;
            } else if (tipo_sistema == 'A') {
                novo_mecha->sistemas[j].subrotina = rotina_ataque;
            }
        }

        
        scanf("%d", &novo_mecha->valor_wintermute);

       
        esquadrao[i] = novo_mecha;
    }

    qsort(esquadrao, total_mechas, sizeof(Mecha*), comparar_mechas_por_id);


//KKKKKKKKKKKKKKKKKKKKKKSKAKDKAKEDWAFKCEAFCNEKJFDBVKFDVDKBVKDBVKDBKRDURDGIUDB


    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");

    for (int i = 0; i < total_mechas; i++) {
        Mecha *mecha_atual = esquadrao[i];
        int energia_inicial = mecha_atual->energia_atual;

        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", 
               mecha_atual->id, 
               mecha_atual->modelo, 
               energia_inicial);

       
        for (int slot = 0; slot < mecha_atual->num_sistemas; slot++) {
            
            if (mecha_atual->sistemas[slot].subrotina == rotina_defesa) {
                int dano_sofrido = 0;    
                mecha_atual->sistemas[slot].subrotina(mecha_atual, slot, mecha_atual->valor_wintermute, &dano_sofrido);
                
                printf("-> [DEFESA] %s | Dano final sofrido: %d\n", 
                       mecha_atual->sistemas[slot].nome, 
                       dano_sofrido);
            }
        }


        for (int slot = 0; slot < mecha_atual->num_sistemas; slot++) {
            if (mecha_atual->sistemas[slot].subrotina == rotina_utilidade) {
                int energia_recuperada = 0;
                
                mecha_atual->sistemas[slot].subrotina(mecha_atual, slot, mecha_atual->valor_wintermute, &energia_recuperada);
                
                printf("-> [UTILIDADE] %s | Energia atual: %d\n", 
                       mecha_atual->sistemas[slot].nome, 
                       mecha_atual->energia_atual);
            }
        }

        for (int slot = 0; slot < mecha_atual->num_sistemas; slot++) {
            if (mecha_atual->sistemas[slot].subrotina == rotina_ataque) {
                int custo_energia = mecha_atual->sistemas[slot].atrib2;
                int dano_causado = 0;


                if (mecha_atual->energia_atual < custo_energia) {
                    mecha_atual->sistemas[slot].subrotina(mecha_atual, slot, mecha_atual->valor_wintermute, &dano_causado);
                    
                    printf("-> [ATAQUE] %s | Energia insuficiente!\n", 
                           mecha_atual->sistemas[slot].nome);
                } else {
                    mecha_atual->sistemas[slot].subrotina(mecha_atual, slot, mecha_atual->valor_wintermute, &dano_causado);
                    
                    printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", 
                           mecha_atual->sistemas[slot].nome, 
                           dano_causado, 
                           mecha_atual->energia_atual);
                }
            }
        }

        printf("ENERGIA FINAL: %d\n", mecha_atual->energia_atual);
        printf("-----------------------------------------\n");
    }

    printf("Esquadrao pronto para o combate.\n");


    for (int i = 0; i < total_mechas; i++) {
        free(esquadrao[i]);
    }
    free(esquadrao);

    return 0;
}