#include <stdio.h>
#include <stdint.h>


typedef struct PureInstruction {
    char Command;
    int Reg1;
    int Destiny;
    int Reg2_Imm;     
    unsigned char FlagTipo: 1; 
} PureInstruction;


typedef union PCInstruction {
    uint32_t MachineCode; 

    struct {
        uint32_t opcode : 8;     
        uint32_t Reg1 : 5;    
        uint32_t Reg2 : 5;      
        uint32_t Destiny : 5;       
        uint32_t unused : 9;  
    } R;

   
    struct {
        uint32_t opcode : 8; 
        uint32_t Reg1 : 5;  
        uint32_t Destiny : 5;       
        int32_t Immediate : 14;    
    } I;

} PCInstruction;


PCInstruction Codificar(PureInstruction *instrucao_entrada) {
    PCInstruction instrucao_saida;
    instrucao_saida.MachineCode = 0;

    if (instrucao_entrada->FlagTipo == 0) {

        instrucao_saida.R.opcode = (uint32_t)instrucao_entrada->Command;

        instrucao_saida.R.Reg1 = instrucao_entrada->Reg1;

        instrucao_saida.R.Reg2 = instrucao_entrada->Reg2_Imm;

        instrucao_saida.R.Destiny = instrucao_entrada->Destiny;

        instrucao_saida.R.unused = 0;


    } else {
        
        instrucao_saida.I.opcode = (uint32_t)instrucao_entrada->Command;

        instrucao_saida.I.Reg1 = instrucao_entrada->Reg1;

        instrucao_saida.I.Destiny = instrucao_entrada->Destiny;

        instrucao_saida.I.Immediate = instrucao_entrada->Reg2_Imm;
    }

    return instrucao_saida;
}


void PrintInstruction(PCInstruction *instrucao_para_imprimir) { 
    printf("0x%08X\n", instrucao_para_imprimir->MachineCode);
}



int main() {
    int total_instrucoes;

    if (scanf("%d", &total_instrucoes) != 1) {
        return 0;
    }

    for (int indice = 0; indice < total_instrucoes; indice++) {
        PureInstruction dados_leitura;
        int tipo_flag_temp;

        scanf("%d %c %d %d %d", 
              &tipo_flag_temp, 
              &dados_leitura.Command, 
              &dados_leitura.Reg1, 
              &dados_leitura.Reg2_Imm, 
              &dados_leitura.Destiny);

        dados_leitura.FlagTipo = tipo_flag_temp;

       
        PCInstruction instrucao_convertida = Codificar(&dados_leitura);
        PrintInstruction(&instrucao_convertida);
    }

    return 0;
}

#include <stdio.h>


union Identificacao {
    unsigned int matricula;
    unsigned long long cpf;
    unsigned int temporario;
};


struct Permissoes {
    unsigned laboratorio : 1;
    unsigned biblioteca : 1;
    unsigned estacionamento : 1;
    unsigned servidores : 1;
    unsigned noturno : 1;
    unsigned bloqueado : 1;
};

struct Cartao {
    char tipo;
    union Identificacao id;
    struct Permissoes perm;
};

int main() {
    int total_cartoes;
    
    if (scanf("%d", &total_cartoes) != 1) return 0;
    
    struct Cartao cartoes[105];
    

    for (int i = 0; i < total_cartoes; i++) {
        char tipo_id;
        scanf(" %c", &tipo_id);
        cartoes[i].tipo = tipo_id;
        
       
        if (tipo_id == 'C') {
            scanf("%llu", &cartoes[i].id.cpf);
        } else if (tipo_id == 'M') {
            scanf("%u", &cartoes[i].id.matricula);
        } else if (tipo_id == 'T') {
            scanf("%u", &cartoes[i].id.temporario);
        }
        
        int lab, bib, est, srv, noturno, bloqueado;
        scanf("%d %d %d %d %d %d", &lab, &bib, &est, &srv, &noturno, &bloqueado);
        
        cartoes[i].perm.laboratorio = lab;
        cartoes[i].perm.biblioteca = bib;
        cartoes[i].perm.estacionamento = est;
        cartoes[i].perm.servidores = srv;
        cartoes[i].perm.noturno = noturno;
        cartoes[i].perm.bloqueado = bloqueado;
    }
    
    int total_solicitacoes;
    
    if (scanf("%d", &total_solicitacoes) != 1) return 0;
    
    for (int i = 0; i < total_solicitacoes; i++) {
        char req_tipo, req_area, req_periodo;
        unsigned long long req_cpf = 0;
        unsigned int req_id_uint = 0;
        
        scanf(" %c", &req_tipo);
        
        if (req_tipo == 'C') {
            scanf("%llu", &req_cpf);
        } else {
            scanf("%u", &req_id_uint);
        }
        
        scanf(" %c %c", &req_area, &req_periodo);
        
        int liberado = 0; 
        int encontrado = 0;
        
        for (int j = 0; j < total_cartoes && encontrado == 0; j++) {
            if (cartoes[j].tipo == req_tipo) {
                int id_confere = 0;
                
                if (req_tipo == 'C' && cartoes[j].id.cpf == req_cpf) {
                    id_confere = 1;
                } else if (req_tipo == 'M' && cartoes[j].id.matricula == req_id_uint) {
                    id_confere = 1;
                } else if (req_tipo == 'T' && cartoes[j].id.temporario == req_id_uint) {
                    id_confere = 1;
                }
                
                if (id_confere) {
                    encontrado = 1;
                    
                    if (cartoes[j].perm.bloqueado == 0) {
                        int tem_permissao_area = 0;
                        
                        if (req_area == 'L' && cartoes[j].perm.laboratorio) tem_permissao_area = 1;
                        if (req_area == 'B' && cartoes[j].perm.biblioteca) tem_permissao_area = 1;
                        if (req_area == 'E' && cartoes[j].perm.estacionamento) tem_permissao_area = 1;
                        if (req_area == 'S' && cartoes[j].perm.servidores) tem_permissao_area = 1;
                        
                        int tem_permissao_horario = 1;
                        if (req_periodo == 'N' && cartoes[j].perm.noturno == 0) {
                            tem_permissao_horario = 0;
                        }
                        
                        if (tem_permissao_area && tem_permissao_horario) {
                            liberado = 1;
                        }
                    }
                }
            }
        }
        
      if (encontrado == 0) {
            printf("CARTAO NAO ENCONTRADO\n");
        } else if (liberado) {
            printf("ACESSO LIBERADO\n");
        } else {
            printf("ACESSO NEGADO\n");
        }
    }
    return 0;
}

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