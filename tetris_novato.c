#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5

typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca pecas[MAX_FILA];
    int frente, tras, tamanho;
} Fila;

void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

int filaCheia(Fila *f) {
    return f->tamanho == MAX_FILA;
}

int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    Peca p;
    p.tipo = tipos[rand() % 7];
    p.id = id;
    return p;
}

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) return;
    f->tras = (f->tras + 1) % MAX_FILA;
    f->pecas[f->tras] = p;
    f->tamanho++;
}

Peca dequeue(Fila *f) {
    Peca removida = {'-', -1};
    if (filaVazia(f)) return removida;
    removida = f->pecas[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--;
    return removida;
}

void mostrarFila(Fila *f) {
    printf("\nFila de pecas: ");
    for (int i = 0; i < f->tamanho; i++) {
        int idx = (f->frente + i) % MAX_FILA;
        printf("[%c%d] ", f->pecas[idx].tipo, f->pecas[idx].id);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    Fila fila;
    inicializarFila(&fila);

    int idSeq = 1;
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca(idSeq++));
    }

    int opcao;
    do {
        mostrarFila(&fila);
        printf("\n1 - Jogar peca (remover da frente)\n0 - Sair\nOpcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada = dequeue(&fila);
            printf("Peca jogada: [%c%d]\n", jogada.tipo, jogada.id);
            enqueue(&fila, gerarPeca(idSeq++));
        }

    } while (opcao != 0);

    return 0;
}
