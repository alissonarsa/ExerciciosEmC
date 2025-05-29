#include <stdio.h> 
#include <string.h> 

// 2

int soma_lista(int lista[], int tamanho) {
    if (tamanho == 0) {
        return 0;
    }      // ultimo elem. + 
    return lista[tamanho - 1] + soma_lista(lista, tamanho - 1); // Soma o último elemento com a soma do restante da lista
}

// teste

int main() { // importante: ao dividir tamnho por vetor em byte temos o tamnho da lista
    
    int lista[] = {5, 5, 5};
    int tamanho = sizeof(lista) / sizeof(lista[0]); // sizeof retorna o tamanho da lista e o tamanhdo do vetor em byte
    printf("%d\n", soma_lista(lista, tamanho)); // use "%d\n", para imprimir inteiros

    return 0; // Retorna 0 indicando que o programa encerrou
}