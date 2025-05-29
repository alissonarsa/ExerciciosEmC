#include <stdio.h>
#include <string.h>

// 3

void inverter_string_auxiliar(char *str, int inicio, int fim) { // char é um caracter, *str = inicio da string
    if (inicio >= fim){
        return; // se inicio for igual ao fim finaliza
    }
    char temp = str[inicio]; // primeiro caracter (usar função auxiliar)
    str[inicio] = str[fim]; // inicio é igual o fim (usar função auxiliar)
    str[fim] = temp; // fim é igual inicio (usar função auxiliar)
    inverter_string_auxiliar(str, inicio + 1, fim - 1);
} // importante: a função auxiliar que chama ela mesma

// Função para chamar somente a str, pois, C é ARCAICO
void inverter_string(char *str) {
    inverter_string_auxiliar(str, 0, strlen(str) - 1);
}

// teste 

int main() {
    char str[] = "Alisson";
    inverter_string(str);
    printf("%s\n", str); // use "%d\n", para imprimir string
    return 0; // Retorna 0 indicando que o programa encerrou
}