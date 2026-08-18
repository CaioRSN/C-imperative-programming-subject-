#include <stdio.h>

main() {

    int total_dinheiro, porcent1, porcent2, porcent3;
    int parte1, parte2, parte3, investimento = -1, sobra, dinheiro_final;
    int dinheiro_rebeka = 3; //dinheiro inicial dela

    scanf("%d %d %d %d", &total_dinheiro, &porcent1, &porcent2, &porcent3);

    //case 1, sem investimento dela e com porcentagem inteiras---------------------
    //-----------------------------------------------------------------------------
    if ((porcent1 * total_dinheiro) % 100 == 0 &&
        (porcent2 * total_dinheiro) % 100 == 0 &&
        (porcent3 * total_dinheiro) % 100 == 0) {

        parte1 = (porcent1 * total_dinheiro) / 100;
        parte2 = (porcent2 * total_dinheiro) / 100;
        parte3 = (porcent3 * total_dinheiro) / 100;

        sobra = total_dinheiro - (parte1 + parte2 + parte3);
        investimento = 0;
        dinheiro_final = dinheiro_rebeka - investimento + sobra;
    }

    //case 2, com ela investindo 1 real-------------------------------------
    //----------------------------------------------------------------------
    else if ((porcent1 * (total_dinheiro + 1)) % 100 == 0 &&
             (porcent2 * (total_dinheiro + 1)) % 100 == 0 &&
             (porcent3 * (total_dinheiro + 1)) % 100 == 0 &&
             (total_dinheiro + 1) - (((porcent1 * (total_dinheiro + 1)) / 100) + 
                                     ((porcent2 * (total_dinheiro + 1)) / 100) + 
                                     ((porcent3 * (total_dinheiro + 1)) / 100)) >= 2) {

        //variaveis placeholders so pra testar se vai cair no if sobre >=2
        int t = total_dinheiro + 1;
        parte1 = (porcent1 * t) / 100;
        parte2 = (porcent2 * t) / 100;
        parte3 = (porcent3 * t) / 100;
        sobra = t - (parte1 + parte2 + parte3);
        investimento = 1;
        dinheiro_final = dinheiro_rebeka - investimento + sobra;
    }

    //case 3, com ela investindo 2 reais-----------------------------------------
    //---------------------------------------------------------------------------
    else if ((porcent1 * (total_dinheiro + 2)) % 100 == 0 &&
             (porcent2 * (total_dinheiro + 2)) % 100 == 0 &&
             (porcent3 * (total_dinheiro + 2)) % 100 == 0 &&
             (total_dinheiro + 2) - (((porcent1 * (total_dinheiro + 2)) / 100) + 
                                     ((porcent2 * (total_dinheiro + 2)) / 100) + 
                                     ((porcent3 * (total_dinheiro + 2)) / 100)) >= 3) {

        //variaveis placeholders so pra testar se vai cair no if sobre >=3
        int t = total_dinheiro + 2;
        parte1 = (porcent1 * t) / 100;
        parte2 = (porcent2 * t) / 100;
        parte3 = (porcent3 * t) / 100;
        sobra = t - (parte1 + parte2 + parte3);
        investimento = 2;
        dinheiro_final = dinheiro_rebeka - investimento + sobra;
    }

    //case 4, com ela investindo 3 reaias---------------------------------------
    //--------------------------------------------------------------------------
    else if ((porcent1 * (total_dinheiro + 3)) % 100 == 0 &&
             (porcent2 * (total_dinheiro + 3)) % 100 == 0 &&
             (porcent3 * (total_dinheiro + 3)) % 100 == 0 &&
             (total_dinheiro + 3) - (((porcent1 * (total_dinheiro + 3)) / 100) + 
                                     ((porcent2 * (total_dinheiro + 3)) / 100) + 
                                     ((porcent3 * (total_dinheiro + 3)) / 100)) >= 4) {

        //variaveis placeholders so pra testar se vai cair no if sobre >=3
        int t = total_dinheiro + 3;
        parte1 = (porcent1 * t) / 100;
        parte2 = (porcent2 * t) / 100;
        parte3 = (porcent3 * t) / 100;
        sobra = t - (parte1 + parte2 + parte3);
        investimento = 3;
        dinheiro_final = dinheiro_rebeka - investimento + sobra;
    }

//saidas -----------------------------------------------------------------------------
//------------------------------------------------------------------------------------

    if (investimento == 2) {
        char c1, c2, c3;
        scanf(" %c %c %c", &c1, &c2, &c3);
        int soma = (c1 - 'a' + 1) + (c2 - 'a' + 1) + (c3 - 'a' + 1);

        printf("Cada homem ficou com %d, %d e %d reais, respectivamente.\n", parte1, parte2, parte3);
        printf("%d\n", soma);

    } else if (investimento == 3) {
        int i1, i2, i3;
        scanf("%d %d %d", &i1, &i2, &i3);

        if (i1 % 3 != 0 && i2 % 3 != 0 && i3 % 3 != 0) {
            investimento = -1;
        } else {
            int soma = 0;
            if (i1 % 3 == 0) soma += i1 / 3;
            if (i2 % 3 == 0) soma += i2 / 3;
            if (i3 % 3 == 0) soma += i3 / 3;

            printf("Cada homem ficou com %d, %d e %d reais, respectivamente.\n", parte1, parte2, parte3);
            printf("%d\n", soma);
        }

    } else if (investimento == 0 || investimento == 1) {
        printf("Cada homem ficou com %d, %d e %d reais, respectivamente.\n", parte1, parte2, parte3);
    }

    if (investimento != -1) {
        if (dinheiro_final >= 7) {
            printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir na noite passada!\n");
        } else {
            printf("E parece que Rebeka vai ter que voltar andando...\n");
        }
    } else {
        printf("Nao foi dessa vez que Rebeka pode ajudar...\n"); 
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }

}