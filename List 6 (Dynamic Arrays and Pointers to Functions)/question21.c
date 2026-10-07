#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int (*Acao_t)(int estado_atual, int *energia, void *payload, void *matriz, int *linhas, int *colunas);


int ignorar(int estado_atual, int *energia, void *payload, void *matriz, int *linhas, int *colunas) {
    return estado_atual;
}


int deslocar(int estado_atual, int *energia, void *payload, void *matriz, int *linhas, int *colunas) {
    int custo_deslocamento = *(int *)payload;
    *energia -= custo_deslocamento;

    if (*energia < 0) {
        *energia = 0;
        return 2;
    }
    return estado_atual;
}


int minerar(int estado_atual, int *energia, void *payload, void *matriz, int *linhas, int *colunas) {
    int ganho_mineracao = *(int *)payload;
    *energia += ganho_mineracao;
    return 1; 
}


int transmitir(int estado_atual, int *energia, void *payload, void *matriz, int *linhas, int *colunas) {
    char *mensagem_recebida = (char *)payload;
    printf("[TRANSMISSAO] %s\n", mensagem_recebida);

    *energia -= 5;
    if (*energia < 0) {
        *energia = 0;
    }
    return estado_atual;
}


int clonar(int estado_atual, int *energia, void *payload, void *matriz, int *linhas, int *colunas) {
    int quantidade_novos_eventos = *(int *)payload;

    if (*energia < 70) {
        printf("[SISTEMA] Falha na clonagem: energia insuficiente\n");
        return estado_atual;
    }

    *energia -= 70;
    Acao_t **matriz_de_acoes = (Acao_t **)matriz;
    int total_eventos_apos_expansao = *colunas + quantidade_novos_eventos;

    for (int indice_estado = 0; indice_estado < *linhas; indice_estado++) {
        matriz_de_acoes[indice_estado] = (Acao_t *)realloc(matriz_de_acoes[indice_estado], total_eventos_apos_expansao * sizeof(Acao_t));
        for (int indice_novo_evento = *colunas; indice_novo_evento < total_eventos_apos_expansao; indice_novo_evento++) {
            matriz_de_acoes[indice_estado][indice_novo_evento] = ignorar;
        }
    }

    *colunas = total_eventos_apos_expansao;
    printf("[SISTEMA] Sonda clonada e matriz expandida para %d eventos\n", *colunas);
    return 0; 
}


Acao_t obter_acao(char codigo_da_acao) {

    if (codigo_da_acao == 'D') {
        return deslocar;
    }
    if (codigo_da_acao == 'M'){ 
        return minerar;
    }
    if (codigo_da_acao == 'T'){
        return transmitir;
    }
        
    if (codigo_da_acao == 'C'){
        return clonar;
    }

    return ignorar;
}


int main() {
    int quantidade_estados, quantidade_eventos;
    if (scanf("%d %d", &quantidade_estados, &quantidade_eventos) != 2) return 0;

    Acao_t **matriz_transicao = (Acao_t **)malloc(quantidade_estados * sizeof(Acao_t *));

    for (int indice_estado = 0; indice_estado < quantidade_estados; indice_estado++) {
        matriz_transicao[indice_estado] = (Acao_t *)malloc(quantidade_eventos * sizeof(Acao_t));

        for (int indice_evento = 0; indice_evento < quantidade_eventos; indice_evento++) {
            matriz_transicao[indice_estado][indice_evento] = ignorar;
        }
    }

    int quantidade_regras_iniciais;
    scanf("%d", &quantidade_regras_iniciais);

    for (int indice_regra = 0; indice_regra < quantidade_regras_iniciais; indice_regra++) {
        int estado_regra, evento_regra;
        char codigo_acao_regra;
        scanf("%d %d %c", &estado_regra, &evento_regra, &codigo_acao_regra);
        matriz_transicao[estado_regra][evento_regra] = obter_acao(codigo_acao_regra);
    }

    int estado_atual_sonda, energia_atual_sonda;
    scanf("%d %d", &estado_atual_sonda, &energia_atual_sonda);


    int evento_recebido;
    char tipo_dado_evento;


    while (scanf("%d %c", &evento_recebido, &tipo_dado_evento) == 2) {

        void *dado_generico_evento;
        int valor_evento_inteiro;
        char texto_evento_recebido[1005];

        if (tipo_dado_evento == 'I') {
            scanf("%d", &valor_evento_inteiro);
            dado_generico_evento = &valor_evento_inteiro;
        } else {
            scanf("%s", texto_evento_recebido);
            dado_generico_evento = texto_evento_recebido;
        }

        Acao_t acao_despacho = ignorar;
         if (evento_recebido >= 0 && evento_recebido < quantidade_eventos) {
            acao_despacho = matriz_transicao[estado_atual_sonda][evento_recebido];
        }


        estado_atual_sonda = acao_despacho(

            estado_atual_sonda, 
            &energia_atual_sonda, 
            dado_generico_evento, 
            (void *)matriz_transicao, 
            &quantidade_estados, 
            &quantidade_eventos
        );


        printf("[CLONE] Evento: %d | Energia: %d | Novo Estado: %d\n", evento_recebido, energia_atual_sonda, estado_atual_sonda);
    }


    for (int indice_estado = 0; indice_estado < quantidade_estados; indice_estado++) {
        free(matriz_transicao[indice_estado]);
    }
    free(matriz_transicao);

    return 0;
}