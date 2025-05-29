#include <stdio.h> // biblioteca padrão de entrada e saída
#include <string.h> // biblioteca de manipulação de strings

//1

int fatorial(int n) { // a identação em C se da por {} e o tipo de retorno deve ser inserido na assinatura
    if (n == 0) {
        return 1;
    }
    return n * fatorial(n - 1);
}

// teste

int main() {

    int num = 5;
    printf("%d\n", fatorial(num)); // use "%d\n", para imprimir inteiros

    return 0; // Retorna 0 indicando que o programa encerrou
}