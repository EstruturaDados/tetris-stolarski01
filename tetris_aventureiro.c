#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca pecas[MAX_FILA];
    int frente, tras, tamanho;
} Fila;

typedef struct {
    Peca pecas[MAX_PILHA];
    int topo;
} Pilha;

// ---------- Funções da fila ----------
void inicializarFila(Fila *f) { f->frente = 0; f->tras = -1; f->tamanho = 0; }
int filaCheia(Fila *f) { return f->tamanho == MAX_FILA; }
int filaVazia(Fila *f) { return f->tamanho == 0; }

Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    Peca p; p.tipo = tipos[rand() % 7]; p.id = id; return p;
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

// ---------- Funções da pilha ----------
void inicializarPilha(Pilha *p) { p->topo = -1; }
int pilhaCheia(Pilha *p) { return p->topo == MAX_PILHA - 1; }
int pilhaVazia(Pilha *p) { return p->topo == -1; }

void push(Pilha *p, Peca pc) {
    if (pilhaCheia(p)) return;
    p->pecas[++p->topo] = pc;
}

Peca pop(Pilha *p) {
    Peca removida = {'-', -1};
    if (pilhaVazia(p)) return removida;
    return p->pecas[p->topo--];
}

// ---------- Mostrar estruturas ----------
void mostrarFila(Fila *f) {
    printf("\nFila: ");
    for (int i = 0; i < f->tamanho; i++) {
        int idx = (f->frente + i) % MAX_FILA;
        printf("[%c%d] ", f->pecas[idx].tipo, f->pecas[idx].id);
    }
    printf("\n");
}

void mostrarPilha(Pilha *p) {
    printf("Pilha: ");
    for (int i = 0; i <= p->topo; i++) {
        printf("[%c%d] ", p->pecas[i].tipo, p->pecas[i].id);
    }
    printf("\n");
}

// ---------- Programa principal ----------
int main() {
    srand(time(NULL));
    Fila fila; Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int idSeq = 1;
    for (int i = 0; i < MAX_FILA; i++) enqueue(&fila, gerarPeca(idSeq++));

    int opcao;
    do {
        mostrarFila(&fila);
        mostrarPilha(&pilha);
        printf("\n1 - Jogar peca\n2 - Enviar peca da fila para reserva\n3 - Usar peca da reserva\n0 - Sair\nOpcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada = dequeue(&fila);
            printf("Peca jogada: [%c%d]\n", jogada.tipo, jogada.id);
            enqueue(&fila, gerarPeca(idSeq++));
        } else if (opcao == 2 && !filaVazia(&fila) && !pilhaCheia(&pilha)) {
            Peca reservada = dequeue(&fila);
            push(&pilha, reservada);
            printf("Peca [%c%d] enviada para reserva.\n", reservada.tipo, reservada.id);
            enqueue(&fila, gerarPeca(idSeq++));
        } else if (opcao == 3 && !pilhaVazia(&pilha)) {
            Peca usada = pop(&pilha);
            printf("Peca [%c%d] usada da reserva.\n", usada.tipo, usada.id);
        }

    } while (opcao != 0);

    return 0;
}
