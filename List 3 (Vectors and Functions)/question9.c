// Problem: Reverse consecutive non-zero elements (blocks) in-place in an array using a helper function, keeping zeros fixed.


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
