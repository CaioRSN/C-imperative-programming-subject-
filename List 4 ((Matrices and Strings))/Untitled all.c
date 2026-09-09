
#include <stdio.h>

void codificacao(int vetor_digitos[], int quant_dig, int deslocamento){
    
    for (int i = 0; i < quant_dig; i++){
        
        if ((vetor_digitos[i] + deslocamento) > 9){
            vetor_digitos[i] = vetor_digitos[i] + deslocamento - 10; //se passar de nove, zera e continua
      } else{
            vetor_digitos[i] += deslocamento;
        }
     
    }
     
}


void descodificacao(int vetor_digitos[], int quant_dig, int deslocamento){   

   for (int i = 0; i < quant_dig; i++){
       if ((vetor_digitos[i] - deslocamento) < 0){
           vetor_digitos[i] = (vetor_digitos[i] - deslocamento + 10); //se for menor que zero, deixa positivo e faz a divisao inteira
       } else{
           vetor_digitos[i] -= deslocamento;
       }
        
   }
  
}


int verificador(int vetor_digitos[], int quant_dig){

    int resultado_verificador = 0;

    for (int i = 0; i < quant_dig; i++){
    resultado_verificador += vetor_digitos[i];
    }
    resultado_verificador = resultado_verificador % 10;

    return resultado_verificador;
}



int main()
{

int quant_dig, deslocamento;
char caractere;
     
scanf ("%d", &quant_dig);
int vetor_digitos[quant_dig];


//=============================================================================

for (int i = 0; i < quant_dig; i++){
    scanf("%d", &vetor_digitos[i]);
}


scanf("%d", &deslocamento);
scanf(" %c", &caractere);



if (caractere == 'C'){
   codificacao(vetor_digitos, quant_dig, deslocamento);
} else {
    descodificacao(vetor_digitos, quant_dig, deslocamento);
}

int resultado = verificador(vetor_digitos, quant_dig);


printf("Código ");
if (caractere == 'C'){
    printf("codificado: ");
} else{
    printf("decodificado: ");
}

for (int i = 0; i < quant_dig; i++){
printf("%d ", vetor_digitos[i]);
}
printf("\n");

printf("Verificador: %d\n", resultado);


if (resultado >=0 && resultado <= 2){
    printf("Nível de segurança: BAIXO");
} else if (resultado >= 3 && resultado <= 6) {
    printf("Nível de segurança: MÉDIO");
}  else{
    printf("Nível de segurança: ALTO");
    }
 

    return 0;
}




//kkkk





#include <stdio.h>

void inveter(int vetor_elem[], int bloco[], int tam_bloco, int pos_inicio){

 for (int i = 0; i < tam_bloco; i++){
    vetor_elem[pos_inicio + i] = bloco[tam_bloco - 1 - i]; 
 }

  
}

int main(){

    int quant_elem;
    scanf("%d", &quant_elem);


    int vetor_elementos[quant_elem];
    int bloco[200];
    int tam_bloco = 0;

    for (int i = 0; i < quant_elem; i++){
     scanf("%d", &vetor_elementos[i]);
    }    

//==============================================================

    for(int i = 0; i < quant_elem; i++){
        if (vetor_elementos[i] != 0){
            bloco[tam_bloco] = vetor_elementos[i];
            tam_bloco++;}

        else {
            if (tam_bloco > 0){
                inveter(vetor_elementos, bloco, tam_bloco, i - tam_bloco );
                tam_bloco = 0; //zerar
            }
        }

     }

     if (tam_bloco > 0){ //só se nn terminar em 0
        inveter(vetor_elementos, bloco, tam_bloco, quant_elem - tam_bloco);
     }

    
     for (int i = 0; i < quant_elem; i++){
        printf("%d ", vetor_elementos[i]);
     }

    return 0;
} 



//kkkk



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



//kkkk




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




//kkkk






#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(){

    float nota = 10.0;
    int num_erros = 0;

    char texto[1001];


    fgets(texto, 1001, stdin);
    texto[strcspn(texto, "\n")] = '\0';
    
    int parte_frase = 0;
    int primeira_letra = 1;
    int total_palavras = 0;
    int palavras_minusculas = 0;


    if (texto[0] == '\0'){
        printf("Texto vazio! Nota: 0.0");
    }


   else {

    for (int i = 0; texto[i] != '\0'; i++){
      
        if (isalpha(texto[i])){

            if (parte_frase == 0){
              parte_frase = 1;  
              total_palavras++; }


            if (primeira_letra == 1){

              if (islower(texto[i])){
                num_erros++;
                palavras_minusculas++;
                texto[i] = toupper(texto[i]);}
            
              primeira_letra = 0;
            }

            else { //nn eh primeira letra e eh maiuscula

              if (isupper(texto[i])){
                num_erros++;
                texto[i] = tolower(texto[i]); // Corrige para min
            }
        } 

       } else {

         parte_frase = 0;
         if (texto[i] == '.' || texto[i] == '!'|| texto[i] == '?'){
             primeira_letra = 1;
            }

      }

    }


        
    
    
    nota = nota - (num_erros * 0.5);
    if (nota < 0.0){
        nota = 0;
    }

    printf("Texto corrigido:\n");
    printf("%s\n", texto);
    printf("Frases que iniciavam com letra minúscula: %d\n", palavras_minusculas);
    printf("Total de palavras: %d\n", total_palavras);
    printf("Total de erros: %d\n", num_erros);
    printf("Nota: %.1f\n", nota);

    
 }

    return 0;
}




//kkkk




#include <stdio.h>
#include <string.h>

int main (){
    
    int linhas, colunas;
    int quant_palavras;

    scanf("%d %d", &linhas, &colunas);

    char matriz[linhas][colunas + 1];

    int dl[8] = { 0,  0,  1, -1,  1,  1, -1, -1};
    int dc[8] = { 1, -1,  0,  0,  1, -1,  1, -1};
    char *nomes_dir[8] = {
    "horizontal-direita",
    "horizontal-esquerda",
    "vertical-baixo",
    "vertical-cima",
    "diagonal-baixo-direita",
    "diagonal-baixo-esquerda",
    "diagonal-cima-direita",
    "diagonal-cima-esquerda"
};


    for (int i = 0; i < linhas; i++){
        scanf("%s", matriz[i]);
    }

    scanf("%d", &quant_palavras);


    for (int i = 0; i < quant_palavras; i++){
        char palavra[100];
        scanf("%s", palavra);
        
        int achou = 0;
        int tam_palavra = strlen(palavra);

        for (int l = 0; l < linhas && achou == 0; l++){

            for (int c = 0; c < colunas && achou == 0; c++){

                for (int p = 0; p < 8; p++){

                    int linha_fim = l + (tam_palavra - 1) * dl[p]; 
                    int coluna_fim = c + (tam_palavra - 1) * dc[p];

                    if (linha_fim >= 0 && linha_fim < linhas && coluna_fim >= 0 && coluna_fim < colunas){

                        int bateu = 1;

                        for (int z = 0; z < tam_palavra && bateu == 1; z++){

                            int linha_atual = l + z * dl[p];
                            int coluna_atual = c + z * dc[p];
                            
                            if (matriz[linha_atual][coluna_atual] != palavra[z]){
                                bateu = 0;
                            }

                        }

                        if (bateu == 1) {
                            printf("%s encontrada em (%d, %d), direcao: %s\n", palavra, l, c, nomes_dir[p]);
                            achou = 1;
                        }

                    }

                }

            }

        }

     if (achou == 0){
        printf("%s nao encontrada\n", palavra);
     }

    }


    return 0;
}



//kkkkk





#include <stdio.h>
#include <string.h>

int main (){


    int linhas, colunas;

    scanf("%d %d", &linhas, &colunas);
    char matriz[linhas][colunas + 1];


    for (int i = 0; i < linhas; i++){
        scanf("%s", matriz[i]);
    }


    int linha_inicial, coluna_inicial;
    scanf("%d %d", &linha_inicial, &coluna_inicial);

    char direcao[15];
    int dl = 0, dc = 0; 
    scanf ("%s", direcao);
 
    if (strcmp(direcao, "CIMA") == 0){
        dl = -1;
        dc = 0;
    } else if (strcmp(direcao, "BAIXO") == 0) {
       dl = 1;
       dc = 0;
    } else if (strcmp(direcao, "ESQUERDA") == 0){
        dl = 0;
        dc = -1;
    } else{
        dl = 0;
        dc = 1;
    }


//==========================================================================

    int l = linha_inicial;
    int c = coluna_inicial;
    while (l >= 0 && l < linhas && c >= 0 && c < colunas && matriz[l][c] != '#'){

        if (matriz[l][c] == '.'){
            matriz[l][c] = '*';


        } else if (matriz[l][c] == '/'){ //espelho 1 ========================

            if (dl == -1 && dc == 0){  //cima para direita
                dl = 0;
                dc = 1;
            } else if (dl == 1 && dc == 0){ //baixo para esquerda
               dl = 0;
               dc = -1;
            } else if (dl == 0 && dc == -1){ //esquerda para baixo
                dl = 1;
                dc = 0;
            }
            else { //direita pra cima 
                dl = -1;
                dc = 0;
            }

            
        } else if (matriz[l][c] == '\\'){

              if (dl == -1 && dc == 0){  //cima para esquerda
                dl = 0;
                dc = -1;
            } else if (dl == 1 && dc == 0){ //baixo para direita
               dl = 0;
               dc = 1;
            } else if (dl == 0 && dc == -1){ //esquerda para cima
                dl = -1;
                dc = 0;
            }
            else { //direita pra cima 
                dl = 1;
                dc = 0;
            }

        }

        l += dl;
        c += dc; 

    }

    for(int i = 0; i < linhas; i++){
        printf("%s\n", matriz[i]);
    }


    return 0;
}