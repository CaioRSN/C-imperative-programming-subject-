#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct Cidadela {
    char nome[256];
    int populacao;
    int periculosidade;
    char funcao[256];
};


int comparacao(const void *a, const void *b) {
    struct Cidadela *c1 = (struct Cidadela *)a;
    struct Cidadela *c2 = (struct Cidadela *)b;

    if ((*c1).populacao != (*c2).populacao) {
        return (*c2).populacao - (*c1).populacao;
    }
    if ((*c1).periculosidade != (*c2).periculosidade) {
        return (*c2).periculosidade - (*c1).periculosidade;
    }
    return strcmp((*c1).nome, (*c2).nome);
}

int main() {
    struct Cidadela cidadelas[1000];
    int total_cidadelas = 0;
    int chave_recebida = 0;
    int chave = -1;

    char linha[500];

    
    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        
        linha[strcspn(linha, "\n")] = '\0';
        
        if (strlen(linha) > 0) {

            if (strchr(linha, '!') != NULL) {
                chave_recebida = 1;
                int valor_chave = 0;

                for (int i = 0; linha[i] != '\0'; i++) {
                    if (isdigit(linha[i])) {
                        valor_chave = valor_chave * 10 + (linha[i] - '0');
                    }
                }
                chave = valor_chave;

            } else {
                struct Cidadela c;
                c.populacao = 0;
                c.periculosidade = 0;
                c.nome[0] = '\0';
                c.funcao[0] = '\0';

                int tam_nome = 0;
                int tam_funcao = 0;
                int espacos_consecutivos = 0;
                int valor_populacao = 0;
                int tem_digito = 0;

                for (int i = 0; linha[i] != '\0'; i++) {
                    if (isupper(linha[i])) {
                        c.nome[tam_nome] = linha[i];
                        tam_nome++;
                    }

                    if (linha[i] == '*') {
                        c.periculosidade++;
                    }

                    if (isdigit(linha[i])) {
                        valor_populacao = valor_populacao * 10 + (linha[i] - '0');
                        tem_digito = 1;
                    }

                    if (linha[i] == ' ') {
                        espacos_consecutivos++;
                    } else {
                        if (espacos_consecutivos == 2 && isalpha(linha[i])) {
                            c.funcao[tam_funcao] = linha[i];
                            tam_funcao++;
                        }
                        espacos_consecutivos = 0;
                    }
                }

                c.nome[tam_nome] = '\0';
                c.funcao[tam_funcao] = '\0';

                if (tem_digito == 1) {
                    c.populacao = valor_populacao;
                } else {
                    c.populacao = 0;
                }

                if (tam_nome > 0) {
                    c.nome[0] = toupper(c.nome[0]);
                    for (int i = 1; i < tam_nome; i++) {
                        c.nome[i] = tolower(c.nome[i]);
                    }
                }

                if (tam_funcao > 0) {
                    c.funcao[0] = toupper(c.funcao[0]);
                    for (int i = 1; i < tam_funcao; i++) {
                        c.funcao[i] = tolower(c.funcao[i]);
                    }
                }

                cidadelas[total_cidadelas] = c;
                total_cidadelas++;
            }
        }
    }

    if (chave_recebida == 0) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");

    } else {
        qsort(cidadelas, total_cidadelas, sizeof(struct Cidadela), comparacao);

        if (chave > 0 && chave <= total_cidadelas) {
            struct Cidadela alvo = cidadelas[chave - 1];

            printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade ", alvo.nome, alvo.populacao, alvo.funcao);

            for (int i = 0; i < alvo.periculosidade; i++) {
                printf("*");
            }
            printf(".");

            if (alvo.populacao >= 1000 && alvo.periculosidade > 3) {
                printf(" Talvez seja melhor desistir...\n");
            } else if (alvo.populacao >= 1000) {
                printf(" Um lugar denso, vai ser difícil achar ela.\n");
            } else if (alvo.periculosidade > 3) {
                printf(" Vai ser complicado entrar lá.\n");
            } else {
                printf("\n");
            }
        }
    }



    return 0;
}
