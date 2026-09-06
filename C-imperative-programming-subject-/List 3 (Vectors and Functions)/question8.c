// Problem: Caesar cipher for numeric digits (encode/decode) with a checksum calculation and secur


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
