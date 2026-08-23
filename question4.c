// Problem: Generate a dynamic upward-pointing arrow ASCII art inside an N x N grid.
// The background is filled with '#' and the arrow with '.'.
// The arrow consists of a triangle head and a straight stem, aligned to the center
// (adjusted for odd/even N dimensions).

#include <stdio.h>

int main(){

int entradaN;
int par = 0;
int impar = 0;
int indice_central;

    scanf("%d", &entradaN);
    

    if (entradaN % 2 == 0){
      par = 1;
      indice_central = (entradaN / 2) - 1;
    }
    else{
        impar = 1;
        indice_central = entradaN / 2;
    }


     int direita = indice_central;
     int esquerda = indice_central;


    //laco de repeticao das linhas
    for (int l = 0; l < entradaN; l++, direita++, esquerda--){
      
       if (l <= indice_central){

        //laco de repeticao das colunas
        for (int c = 0; c < entradaN; c++){
          
            if (c >= esquerda && c <= direita){
            printf(".");
            }

            else{
                printf("#");
            }
        }

    }
    
         else{
 
          for (int c = 0; c < entradaN; c++){
          if (c == indice_central){
            printf(".");
          }
          else{
            printf("#");
          }
        }

            }

         printf("\n");
    }


    return 0;
}
