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