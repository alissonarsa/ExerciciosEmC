#include <stdio.h> // inclui stdio
#include <stdlib.h> // inclui stdlib
#include <string.h> // inclui string
#include <stdbool.h> // inclui bool

#define MAX 100 // define tamanho máximo

// ----------- Exercício 1: Fila de Atendimento -----------
typedef struct {
    char nome[50]; // nome do cliente
} Cliente;

typedef struct {
    Cliente clientes[MAX]; // vetor de clientes
    int front, rear; // índices da fila
} FilaAtendimento;

void initFilaAtendimento(FilaAtendimento *f) { f->front = f->rear = -1; } // inicializa fila
bool isEmptyAtendimento(FilaAtendimento *f) { return f->front == -1; } // verifica vazia
bool isFullAtendimento(FilaAtendimento *f) { return (f->rear + 1) % MAX == f->front; } // verifica cheia

void enfileirarCliente(FilaAtendimento *f, const char *nome) { // adiciona cliente
    if (isFullAtendimento(f)) {
        printf("Fila cheia!\n");
        return;
    }
    if (isEmptyAtendimento(f)) f->front = 0;
    f->rear = (f->rear + 1) % MAX;
    strcpy(f->clientes[f->rear].nome, nome);
}

void atenderCliente(FilaAtendimento *f) { // atende cliente
    if (isEmptyAtendimento(f)) {
        printf("Nenhum cliente para atender.\n");
        return;
    }
    printf("Atendendo: %s\n", f->clientes[f->front].nome);
    if (f->front == f->rear) f->front = f->rear = -1;
    else f->front = (f->front + 1) % MAX;
}

void teste_fila_atendimento() { // teste fila de atendimento
    FilaAtendimento f;
    initFilaAtendimento(&f);
    enfileirarCliente(&f, "Ana");
    enfileirarCliente(&f, "Bruno");
    enfileirarCliente(&f, "Carlos");
    atenderCliente(&f);
    atenderCliente(&f);
    atenderCliente(&f);
    atenderCliente(&f);
}

// ----------- Exercício 2: Palíndromo com Pilha e Fila -----------
typedef struct {
    char itens[MAX]; // pilha de char
    int topo;
} PilhaChar;

typedef struct {
    char itens[MAX]; // fila de char
    int front, rear;
} FilaChar;

void initPilha(PilhaChar *p) { p->topo = -1; } // inicializa pilha
void push(PilhaChar *p, char c) { if (p->topo < MAX-1) p->itens[++(p->topo)] = c; } // empilha
char pop(PilhaChar *p) { return p->topo >= 0 ? p->itens[(p->topo)--] : '\0'; } // desempilha

void initFila(FilaChar *f) { f->front = f->rear = -1; } // inicializa fila
void enfileirar(FilaChar *f, char c) { // enfileira char
    if ((f->rear + 1) % MAX == f->front) return;
    if (f->front == -1) f->front = 0;
    f->rear = (f->rear + 1) % MAX;
    f->itens[f->rear] = c;
}
char desenfileirar(FilaChar *f) { // desenfileira char
    if (f->front == -1) return '\0';
    char c = f->itens[f->front];
    if (f->front == f->rear) f->front = f->rear = -1;
    else f->front = (f->front + 1) % MAX;
    return c;
}

bool verifica_palindromo(const char *palavra) { // verifica palíndromo
    PilhaChar p; FilaChar f;
    initPilha(&p); initFila(&f);
    int len = strlen(palavra);
    for (int i = 0; i < len; i++) {
        push(&p, palavra[i]);
        enfileirar(&f, palavra[i]);
    }
    for (int i = 0; i < len; i++) {
        if (pop(&p) != desenfileirar(&f)) return false;
    }
    return true;
}

void teste_palindromo() { // teste palíndromo
    printf("arara: %s\n", verifica_palindromo("arara") ? "Palindromo" : "Nao eh palindromo");
    printf("banana: %s\n", verifica_palindromo("banana") ? "Palindromo" : "Nao eh palindromo");
}

// ----------- Exercício 3: Fila Circular -----------
typedef struct {
    int dados[MAX]; // fila circular de int
    int front, rear;
} FilaCircular;

void initFilaCircular(FilaCircular *f) { f->front = f->rear = -1; } // inicializa fila circular
bool isEmptyCircular(FilaCircular *f) { return f->front == -1; } // verifica vazia
bool isFullCircular(FilaCircular *f) { return (f->rear + 1) % MAX == f->front; } // verifica cheia

void enfileirarCircular(FilaCircular *f, int valor) { // enfileira circular
    if (isFullCircular(f)) {
        printf("Fila circular cheia!\n");
        return;
    }
    if (isEmptyCircular(f)) f->front = 0;
    f->rear = (f->rear + 1) % MAX;
    f->dados[f->rear] = valor;
}

int desenfileirarCircular(FilaCircular *f) { // desenfileira circular
    if (isEmptyCircular(f)) {
        printf("Fila circular vazia!\n");
        return -1;
    }
    int valor = f->dados[f->front];
    if (f->front == f->rear) f->front = f->rear = -1;
    else f->front = (f->front + 1) % MAX;
    return valor;
}

void teste_fila_circular() { // teste fila circular
    FilaCircular f;
    initFilaCircular(&f);
    enfileirarCircular(&f, 10);
    enfileirarCircular(&f, 20);
    enfileirarCircular(&f, 30);
    printf("Saiu: %d\n", desenfileirarCircular(&f));
    printf("Saiu: %d\n", desenfileirarCircular(&f));
    enfileirarCircular(&f, 40);
    printf("Saiu: %d\n", desenfileirarCircular(&f));
    printf("Saiu: %d\n", desenfileirarCircular(&f));
}

// ----------- Exercício 4: Simulação de Impressora -----------
typedef struct {
    char nome[50]; // nome do documento
    int paginas;   // número de páginas
} Documento;

typedef struct {
    Documento docs[MAX]; // fila de documentos
    int front, rear;
} FilaImpressora;

void initFilaImpressora(FilaImpressora *f) { f->front = f->rear = -1; } // inicializa impressora
bool isEmptyImpressora(FilaImpressora *f) { return f->front == -1; } // verifica vazia
bool isFullImpressora(FilaImpressora *f) { return (f->rear + 1) % MAX == f->front; } // verifica cheia

void adicionarDocumento(FilaImpressora *f, const char *nome, int paginas) { // adiciona doc
    if (isFullImpressora(f)) {
        printf("Fila de impressao cheia!\n");
        return;
    }
    if (isEmptyImpressora(f)) f->front = 0;
    f->rear = (f->rear + 1) % MAX;
    strcpy(f->docs[f->rear].nome, nome);
    f->docs[f->rear].paginas = paginas;
}

void imprimirProximo(FilaImpressora *f) { // imprime doc
    if (isEmptyImpressora(f)) {
        printf("Nenhum documento para imprimir.\n");
        return;
    }
    printf("Imprimindo: %s (%d paginas)\n", f->docs[f->front].nome, f->docs[f->front].paginas);
    if (f->front == f->rear) f->front = f->rear = -1;
    else f->front = (f->front + 1) % MAX;
}

void teste_impressora() { // teste impressora
    FilaImpressora f;
    initFilaImpressora(&f);
    adicionarDocumento(&f, "Trabalho1.pdf", 5);
    adicionarDocumento(&f, "Relatorio.docx", 2);
    imprimirProximo(&f);
    imprimirProximo(&f);
    imprimirProximo(&f);
}

int main() { // main com testes
    // Exercício 1
    printf("Fila de Atendimento:\n");
    teste_fila_atendimento();

    // Exercício 2
    printf("\nVerificacao de Palindromo:\n");
    teste_palindromo();

    // Exercício 3
    printf("\nFila Circular:\n");
    teste_fila_circular();

    // Exercício 4
    printf("\nSimulacao de Impressora:\n");
    teste_impressora();

    return 0;
}