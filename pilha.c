#include <stdio.h> // inclui stdio
#include <stdlib.h> // inclui stdlib
#include <string.h> // inclui string
#include <stdbool.h> // inclui bool

#define MAX 100 // define tamanho máximo

// ----------- Exercício 1: Inversão de String com Pilha -----------
typedef struct {
    char itens[MAX]; // pilha de char
    int topo;
} PilhaChar;

void initPilha(PilhaChar *p) { p->topo = -1; } // inicializa pilha
void push(PilhaChar *p, char c) { if (p->topo < MAX-1) p->itens[++(p->topo)] = c; } // empilha
char pop(PilhaChar *p) { return p->topo >= 0 ? p->itens[(p->topo)--] : '\0'; } // desempilha

void inverter_string(const char *str, char *saida) { // inverte string usando pilha
    PilhaChar p;
    initPilha(&p);
    int len = strlen(str);
    for (int i = 0; i < len; i++) push(&p, str[i]);
    for (int i = 0; i < len; i++) saida[i] = pop(&p);
    saida[len] = '\0';
}

void teste_inverter_string() { // teste inversão de string
    char palavra[] = "Python";
    char invertida[MAX];
    inverter_string(palavra, invertida);
    printf("Invertida: %s\n", invertida); // deve mostrar "nohtyP"
}

// ----------- Exercício 2: Verificação de Parênteses Balanceados -----------
typedef struct {
    char itens[MAX];
    int topo;
} PilhaPar;

void initPilhaPar(PilhaPar *p) { p->topo = -1; }
void pushPar(PilhaPar *p, char c) { if (p->topo < MAX-1) p->itens[++(p->topo)] = c; }
char popPar(PilhaPar *p) { return p->topo >= 0 ? p->itens[(p->topo)--] : '\0'; }
char topoPar(PilhaPar *p) { return p->topo >= 0 ? p->itens[p->topo] : '\0'; }

bool verifica_balanceamento(const char *expr) { // verifica parênteses, colchetes e chaves
    PilhaPar p;
    initPilhaPar(&p);
    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];
        if (c == '(' || c == '[' || c == '{') pushPar(&p, c);
        else if (c == ')' || c == ']' || c == '}') {
            if (p.topo == -1) return false;
            char topo = popPar(&p);
            if ((c == ')' && topo != '(') ||
                (c == ']' && topo != '[') ||
                (c == '}' && topo != '{')) return false;
        }
    }
    return p.topo == -1;
}

void teste_balanceamento() { // teste balanceamento
    printf("{[()]}: %s\n", verifica_balanceamento("{[()]}") ? "Balanceado" : "Nao balanceado");
    printf("{[(])}: %s\n", verifica_balanceamento("{[(])}") ? "Balanceado" : "Nao balanceado");
}

// ----------- Exercício 3: Conversão Decimal para Binário -----------
typedef struct {
    char itens[MAX];
    int topo;
} PilhaBin;

void initPilhaBin(PilhaBin *p) { p->topo = -1; }
void pushBin(PilhaBin *p, char c) { if (p->topo < MAX-1) p->itens[++(p->topo)] = c; }
char popBin(PilhaBin *p) { return p->topo >= 0 ? p->itens[(p->topo)--] : '\0'; }

void decimal_para_binario(int n, char *saida) { // converte decimal para binário
    PilhaBin p;
    initPilhaBin(&p);
    if (n == 0) {
        saida[0] = '0';
        saida[1] = '\0';
        return;
    }
    while (n > 0) {
        pushBin(&p, (n % 2) + '0');
        n /= 2;
    }
    int i = 0;
    while (p.topo != -1) saida[i++] = popBin(&p);
    saida[i] = '\0';
}

void teste_decimal_para_binario() { // teste binário
    char bin[MAX];
    decimal_para_binario(10, bin);
    printf("Binario de 10: %s\n", bin); // deve mostrar "1010"
}

// ----------- Exercício 4: Desfazer Operações (Undo) -----------
typedef struct {
    char acoes[MAX][50];
    int topo;
} PilhaUndo;

void initPilhaUndo(PilhaUndo *p) { p->topo = -1; }
void pushUndo(PilhaUndo *p, const char *acao) { if (p->topo < MAX-1) strcpy(p->acoes[++(p->topo)], acao); }
void desfazer(PilhaUndo *p) {
    if (p->topo == -1) {
        printf("Nada para desfazer.\n");
        return;
    }
    printf("Desfeito: %s\n", p->acoes[p->topo--]);
}

void teste_undo() { // teste undo
    PilhaUndo p;
    initPilhaUndo(&p);
    pushUndo(&p, "Escreveu A");
    pushUndo(&p, "Escreveu B");
    pushUndo(&p, "Apagou C");
    desfazer(&p);
    desfazer(&p);
    desfazer(&p);
    desfazer(&p);
}

// ----------- Exercício 5: Avaliação de Expressão Pós-fixa -----------
typedef struct {
    int itens[MAX];
    int topo;
} PilhaInt;

void initPilhaInt(PilhaInt *p) { p->topo = -1; }
void pushInt(PilhaInt *p, int v) { if (p->topo < MAX-1) p->itens[++(p->topo)] = v; }
int popInt(PilhaInt *p) { return p->topo >= 0 ? p->itens[(p->topo)--] : 0; }

int avaliar_posfixa(const char *expr) { // avalia expressão pós-fixa
    PilhaInt p;
    initPilhaInt(&p);
    char copia[200];
    strcpy(copia, expr);
    char *token = strtok(copia, " ");
    while (token) {
        if (token[0] >= '0' && token[0] <= '9') {
            pushInt(&p, atoi(token));
        } else {
            int b = popInt(&p);
            int a = popInt(&p);
            switch (token[0]) {
                case '+': pushInt(&p, a + b); break;
                case '-': pushInt(&p, a - b); break;
                case '*': pushInt(&p, a * b); break;
                case '/': pushInt(&p, a / b); break;
            }
        }
        token = strtok(NULL, " ");
    }
    return popInt(&p);
}

void teste_posfixa() { // teste pós-fixa
    printf("2 3 + = %d\n", avaliar_posfixa("2 3 +")); // 5
    printf("2 3 + 4 * = %d\n", avaliar_posfixa("2 3 + 4 *")); // 20
}

int main() {
    // Exercício 1
    printf("Inversão de String:\n");
    teste_inverter_string();

    // Exercício 2
    printf("\nBalanceamento de Parênteses:\n");
    teste_balanceamento();

    // Exercício 3
    printf("\nDecimal para Binário:\n");
    teste_decimal_para_binario();

    // Exercício 4
    printf("\nDesfazer Operações:\n");
    teste_undo();

    // Exercício 5
    printf("\nExpressão Pós-fixa:\n");
    teste_posfixa();

    return 0;
}