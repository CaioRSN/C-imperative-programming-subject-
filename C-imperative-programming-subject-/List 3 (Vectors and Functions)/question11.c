#include <stdio.h>

void ler_dataset(float caule[], float folha[], float raiz[], float broto[], int rotulos[], int n){
    for (int i = 0; i < n; i++){
        scanf("%f %f %f %f %d", &caule[i], &folha[i], &raiz[i], &broto[i], &rotulos[i]);
    }
}

void calcular_centroides(float caule[], float folha[], float raiz[], float broto[], int rotulos[], int n,
                         float centroide_caule[], float centroide_folha[], float centroide_raiz[], float centroide_broto[]){
    

    int quantidade[3] = {0, 0, 0};

    for (int i = 0; i < 3; i++){ //soh pra zerar
        centroide_caule[i] = 0;
        centroide_folha[i] = 0;
        centroide_raiz[i] = 0;
        centroide_broto[i] = 0;
    }

    for (int i = 0; i < n; i++){
        centroide_caule[rotulos[i]] += caule[i];
        centroide_folha[rotulos[i]] += folha[i];
        centroide_raiz[rotulos[i]] += raiz[i];
        centroide_broto[rotulos[i]] += broto[i];
        quantidade[rotulos[i]]++;
    }

    for (int i = 0; i < 3; i++){
        if (quantidade[i] > 0){
            centroide_caule[i] = centroide_caule[i] / quantidade[i];
            centroide_folha[i] = centroide_folha[i] / quantidade[i];
            centroide_raiz[i] = centroide_raiz[i] / quantidade[i];
            centroide_broto[i] = centroide_broto[i] / quantidade[i];
        }
    }
}

float distancia_quadrados(float caule, float folha, float raiz, float broto,
                         float centroide_caule, float centroide_folha, float centroide_raiz, float centroide_broto){
    

    float diferen_caule = caule - centroide_caule;
    float diferen_folha = folha - centroide_folha;
    float diferen_raiz = raiz - centroide_raiz;
    float diferen_broto = broto - centroide_broto;



    return (diferen_caule * diferen_caule) + (diferen_folha * diferen_folha) + (diferen_raiz * diferen_raiz) + (diferen_broto * diferen_broto);
}


int classificar(float caule, float folha, float raiz, float broto,
                float centroide_caule[], float centroide_folha[], float centroide_raiz[], float centroide_broto[]){
    

    float menor_distancia = 999999.0;
    int classe_ate_entao = 0;


    for (int i = 0; i < 3; i++){
        float dkk = distancia_quadrados(caule, folha, raiz, broto,
                                      centroide_caule[i], centroide_folha[i], centroide_raiz[i], centroide_broto[i]);
        if (dkk < menor_distancia){
            menor_distancia = dkk;
            classe_ate_entao = i;
        }
    }

    return classe_ate_entao;
}


void classificar_conjunto(float caule[], float folha[], float raiz[], float broto[], int n,
                         float centroide_caule[], float centroide_folha[], float centroide_raiz[], float centroide_broto[],
                         int previstos[]){

    for (int i = 0; i < n; i++){
        previstos[i] = classificar(caule[i], folha[i], raiz[i], broto[i],
                                   centroide_caule, centroide_folha, centroide_raiz, centroide_broto);
    }
}

void imprimir_especie(int classe){
    
    if (classe == 0){
        printf("Lunaria");
    } else if (classe == 1){
        printf("Ignea");
    } else if (classe == 2){
        printf("Bruma");
    }
}

void imprimir_previsoes(int previstos[], int n){

    for (int i = 0; i < n; i++){
        printf("Amostra %d: ", i + 1);
        imprimir_especie(previstos[i]);
        printf("\n");
    }
}

float calcular_acuracia(int previstos[], int reais[], int n){
    int acertos = 0;
    for (int i = 0; i < n; i++){
        if (previstos[i] == reais[i]){
            acertos++;
        }
    }
    return ((float)acertos / n) * 100.0;
}

int main(){
    int n_treino, n_teste;

    scanf("%d", &n_treino);

    float caule_tr[n_treino], folha_tr[n_treino], raiz_tr[n_treino], broto_tr[n_treino];
    int rotulos_tr[n_treino];
 

    ler_dataset(caule_tr, folha_tr, raiz_tr, broto_tr, rotulos_tr, n_treino); //primeira kk

    float c_caule[3], c_folha[3], c_raiz[3], c_broto[3];
    calcular_centroides(caule_tr, folha_tr, raiz_tr, broto_tr, rotulos_tr, n_treino, c_caule, c_folha, c_raiz, c_broto); //segunda kk

    scanf("%d", &n_teste);

    float caule_te[n_teste], folha_te[n_teste], raiz_te[n_teste], broto_te[n_teste];
    int rotulos_te[n_teste];

    ler_dataset(caule_te, folha_te, raiz_te, broto_te, rotulos_te, n_teste); //terceira kk (do teste)

    int previstos[n_teste];

    classificar_conjunto(caule_te, folha_te, raiz_te, broto_te, n_teste, c_caule, c_folha, c_raiz, c_broto, previstos); //quarta kk

    imprimir_previsoes(previstos, n_teste); //quinta kk

    float acuracia = calcular_acuracia(previstos, rotulos_te, n_teste); //sexta kk
    printf("Acuracia: %.2f%%\n", acuracia);



    return 0;
}