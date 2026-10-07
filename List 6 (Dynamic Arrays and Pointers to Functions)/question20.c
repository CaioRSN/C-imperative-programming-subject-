#include <stdio.h>
#include <stdlib.h>


char* ler_item() {
    int capacidade = 16;
    int tamanho = 0;
    
    char* palavra = (char*) malloc(capacidade * sizeof(char));
    int c;

    if (palavra == NULL) return NULL;

    while ((c = getchar()) != EOF && (c == '\n' || c == '\r'));

    if (c == EOF) {
        free(palavra);
        return NULL;
    }

    do {
        palavra[tamanho++] = (char) c;
        
        if (tamanho == capacidade) {
            capacidade *= 2;
            palavra = (char*) realloc(palavra, capacidade * sizeof(char));
        }
        c = getchar();
    } while (c != EOF && c != '\n' && c != '\r');

    palavra[tamanho] = '\0';
    return palavra;
}


int main() {
    int capacidade_inventario = 5;
    int num_itens = 0;
    
    char** inventario = (char**) malloc(capacidade_inventario * sizeof(char*));
    char* novo_item;


    while ((novo_item = ler_item()) != NULL) {
        
        printf("Sucesso! Mais um item pra colecao: %s\n", novo_item);
        
        if (num_itens == capacidade_inventario) {
            capacidade_inventario *= 2;
            inventario = (char**) realloc(inventario, capacidade_inventario * sizeof(char*));
        }
        
        inventario[num_itens++] = novo_item;
    }


    for (int i = 0; i < num_itens; i++) {
        printf("%d. %s\n", i + 1, inventario[i]);
        
        free(inventario[i]);
    }


    printf("O que vou fazer com tudo isso?\n");

    free(inventario);

    return 0;
}