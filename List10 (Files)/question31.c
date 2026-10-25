#include <stdio.h>
#include <string.h>


typedef struct {
    char titular[51];
    float saldo;
    int ativa;
} Conta;



int main(void) {
    FILE *arq = fopen("contas.bin", "wb+");

    int n = 0;
    scanf("%d", &n);


    for (int i = 0; i < n; i++) {
        Conta conta = {"", 0.0, 1};
        scanf("%f %50[^\n]", &conta.saldo, conta.titular);
        fwrite(&conta, sizeof(Conta), 1, arq);
    }

    int k = 0;
    scanf("%d", &k);


    for (int i = 0; i < k; i++) {
        char operacao[20];
        int numero = 0;
        float valor = 0.0;


        scanf("%19s %d", operacao, &numero);


        if (strcmp(operacao, "DEPOSITAR") == 0 || strcmp(operacao, "SACAR") == 0) {
            scanf("%f", &valor);
        }

        if (numero < 1 || numero > n) {
            printf("Conta inexistente\n");
        }
        else {
            long posicao = (numero - 1) * sizeof(Conta);
            Conta conta;
            fseek(arq, posicao, SEEK_SET);
            fread(&conta, sizeof(Conta), 1, arq);


            if (conta.ativa == 0) {
                printf("Conta encerrada\n");
            }

            else if (strcmp(operacao, "CONSULTAR") == 0) {
                printf("%s - saldo: %.2f\n", conta.titular, conta.saldo);
            }

            else if (strcmp(operacao, "DEPOSITAR") == 0) {
                conta.saldo += valor;
                fseek(arq, posicao, SEEK_SET);
                fwrite(&conta, sizeof(Conta), 1, arq);
                printf("Saldo atual: %.2f\n", conta.saldo);
            }

            else if (strcmp(operacao, "SACAR") == 0) {
                if (valor > conta.saldo) {
                    printf("Saldo insuficiente\n");
                }
                else {
                    conta.saldo -= valor;
                    fseek(arq, posicao, SEEK_SET);
                    fwrite(&conta, sizeof(Conta), 1, arq);
                    printf("Saldo atual: %.2f\n", conta.saldo);
                }
            }

            else if (strcmp(operacao, "ENCERRAR") == 0) {
                conta.ativa = 0;
                fseek(arq, posicao, SEEK_SET);
                fwrite(&conta, sizeof(Conta), 1, arq);
                printf("Conta encerrada com sucesso\n");
            }
        }
    }


    printf("Contas ativas:\n");
    fseek(arq, 0, SEEK_SET);


    Conta conta;
    int numero = 0;

    while (fread(&conta, sizeof(Conta), 1, arq) == 1) {
        numero++;
        if (conta.ativa == 1) {
            printf("%d %s %.2f\n", numero, conta.titular, conta.saldo);
        }
    }

    
    fclose(arq);
    return 0;
}