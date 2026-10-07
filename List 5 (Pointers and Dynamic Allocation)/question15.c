#include <stdio.h>
#include <stdlib.h>


int *insere(int *vetor, int *quantidade, int *capacidade, int valor){
    
    if (*quantidade == *capacidade){
        (*capacidade) = (*capacidade) * 2;
    
    
    int *temporario = (int *) realloc(vetor, (*capacidade) * sizeof(int));
    
    if (temporario == NULL) {
     free(vetor);
     return NULL;
    }
    vetor = temporario;
    }
    
    *(vetor + *quantidade) = valor;
    (*quantidade)++;
    
    return vetor;
   }



void imprime_invertido(int *vetor, int quantidade){

   for(int i = 0; i < quantidade; i++){
     int *ultimo_termo = vetor + (quantidade - 1 - i);
   
     printf("%d ", *ultimo_termo);
   }
    
  printf("\n");
}



int main(){

   int quantidade = 0;
   int *pont_quantidade = &quantidade;
   
   int capacidade = 1;
   int *pont_capacidade = &capacidade;
  
   int *vetor = (int *) malloc(capacidade * sizeof(int));
   if (vetor == NULL) {
     return 1;
}
   
   int numerokk = 0;
   scanf("%d", &numerokk);
   
   while (numerokk != -1){
     
     vetor = insere(vetor, &quantidade, &capacidade, numerokk);
     
     if (vetor == NULL) {
            return 1;
        }
     
     
     scanf("%d", &numerokk);
     
     }


   
   imprime_invertido(vetor, quantidade);
   
   
   
    free(vetor);
    return 0;
}