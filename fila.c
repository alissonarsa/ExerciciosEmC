#include <stdio.h> // Inclui biblioteca padrão de entrada e saída
#include <stdlib.h> // Inclui funções de alocação de memória e conversão
#include <string.h> // Inclui funções para manipulação de strings

#define MAX 100 // Define o tamanho máximo da fila

typedef struct {
    char documents[MAX][50]; // Vetor de strings para armazenar os nomes dos documentos
    int front;               // Índice do início da fila
    int rear;                // Índice do final da fila
} PrinterQueue;

// Inicializa a fila
void initQueue(PrinterQueue *q) {
    q->front = -1; // Define o início como -1 (fila vazia)
    q->rear = -1;  // Define o final como -1 (fila vazia)
}

// Verifica se a fila está cheia
int isFull(PrinterQueue *q) {
    return (q->rear + 1) % MAX == q->front; // Retorna verdadeiro se o próximo do rear for o front (fila cheia)
}

// Verifica se a fila está vazia
int isEmpty(PrinterQueue *q) {
    return q->front == -1; // Retorna verdadeiro se o início for -1 (fila vazia)
}

// Adiciona um documento na fila
void enqueue(PrinterQueue *q, const char *document) {
    if (isFull(q)) { // Se a fila está cheia
        printf("Fila cheia. Não é possível adicionar o documento: %s\n", document); // Mensagem de erro
        return;
    }
    if (isEmpty(q)) { // Se a fila está vazia
        q->front = 0; // Define o início como 0
    }
    q->rear = (q->rear + 1) % MAX; // Atualiza o final da fila (circular)
    strcpy(q->documents[q->rear], document); // Copia o nome do documento para a posição correta
}

// Remove um documento da fila (imprime)
void dequeue(PrinterQueue *q) {
    if (isEmpty(q)) { // Se a fila está vazia
        printf("Fila vazia. Nenhum documento para imprimir.\n"); // Mensagem de erro
        return;
    }
    printf("Imprimindo documento: %s\n", q->documents[q->front]); // Mostra o documento que está sendo impresso
    if (q->front == q->rear) { // Se só tem um elemento na fila
        q->front = -1; // Reseta o início
        q->rear = -1;  // Reseta o final
    } else {
        q->front = (q->front + 1) % MAX; // Avança o início da fila (circular)
    }
}

// Função para imprimir o próximo documento (chama o dequeue)
void printNext(PrinterQueue *q) {
    dequeue(q); // Remove e imprime o próximo documento da fila
}

int main() {
    PrinterQueue pq; // Declara uma fila de impressora
    initQueue(&pq);  // Inicializa a fila

    enqueue(&pq, "Documento1"); // Adiciona "Documento1" na fila
    enqueue(&pq, "Documento2"); // Adiciona "Documento2" na fila
    enqueue(&pq, "Documento3"); // Adiciona "Documento3" na fila

    printNext(&pq); // Imprime o próximo documento ("Documento1")
    printNext(&pq); // Imprime o próximo documento ("Documento2")
    printNext(&pq); // Imprime o próximo documento ("Documento3")
    printNext(&pq); // Tenta imprimir de uma fila vazia (mensagem de erro)

    return 0; // Retorna 0 indicando que o programa terminou com sucesso
}