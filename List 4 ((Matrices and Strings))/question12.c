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