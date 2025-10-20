#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PECA 5
#define MAX_JOGADORES 3

typedef struct {
    int valor;
    char naipe[10];
} Peca;

typedef struct {
    int jogadores[MAX_JOGADORES];
    int frente;
    int tras;
} FilaCircular;

typedef struct {
    Peca pecas[MAX_PECA];
    int topo;
} Pilha;

void inicializarFila(FilaCircular *f) {
    f->frente = -1;
    f->frente = -1;
}

int filaVazia(FilaCircular *f) {
    return f->frente == -1;
}

int filaCheia(FilaCircular *f) {
    return (f->tras + 1) % MAX_JOGADORES == f->frente;
}

void enfileirar(FilaCircular *f, int jogador) {
    if (filaCheia(f)) {
        printf("Fila cheia!\n");
    } else {
        if (filaVazia(f)) {
            f->frente = 0;
        }
        f->tras = (f->tras + 1) % MAX_JOGADORES;
        f->jogadores[f->tras] = jogador;
        printf("Jogador %d enfileirado.\n", jogador);
    }
}

int desenfileirar(FilaCircular *f) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return -1;
    } else {
        int jogador = f->jogadores[f->frente];
        if (f->frente == f->tras) {
            inicializarFila(f);
        } else {
            f->frente = (f->frente + 1) % MAX_JOGADORES;
        }
        return jogador;
    }
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PECA - 1;
}

void empilhar(Pilha *p, Peca peca) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia!\n");
    } else {
        p->topo++;
        p->pecas[p->topo] = peca;
        printf("Peça (valor %d, naipe %s) empilhada.\n", peca.valor, peca.naipe);
    }
}

Peca desempilhar(Pilha *p) {
    Peca pecaVazia = {-1, "Nulo"};
    if (pilhaVazia(p)) {
        printf("Pilha vazia!\n");
        return pecaVazia;
    } else {
        Peca peca = p->pecas[p->topo];
        p->topo--;
        return peca;
    }
}
void exibirEstado(FilaCircular *f, Pilha *p) {
    printf("\n--- Estado Atual ---\n");

    printf("Fila de Jogadores: ");
    if (filaVazia(f)) {
        printf("Vazia.\n");
    } else {
        int i = f->frente;
        while (i != f->tras) {
            printf("Jogador %d -> ", f->jogadores[i]);
            i = (i + 1) % MAX_JOGADORES;
        }
        printf("Jogador %d\n", f->jogadores[f->tras]);
    }

    printf("Pilha de Peças: ");
    if (pilhaVazia(p)) {
        printf("Vazia.\n");
    } else {
        for (int i = 0; i <= p->topo; i++) {
            printf("(%d, %s) ", p->pecas[i].valor, p->pecas[i].naipe);
        }
        printf("\n");
    }
    printf("--------------------\n");
}

void trocarPecas(Peca *peca1, Peca *peca2) {
    Peca temp = *peca1;
    *peca1 = *peca2;
    *peca2 = temp;
    printf("Peças trocadas com sucesso!\n");
}

int main() {
    FilaCircular filaJogadores;
    Pilha pilhaPecas;

    inicializarFila(&filaJogadores);
    inicializarPilha(&pilhaPecas);

    printf("Simulação de Jogo \n");

    enfileirar(&filaJogadores, 1);
    enfileirar(&filaJogadores, 2);
    enfileirar(&filaJogadores, 3);
    enfileirar(&filaJogadores, 4);
    
    Peca p1 = {10, "Copas"};
    Peca p2 = {5, "Ouros"};
    Peca p3 = {1, "Espadas"};

    empilhar(&pilhaPecas, p1);
    empilhar(&pilhaPecas, p2);
    empilhar(&pilhaPecas, p3);

    exibirEstado(&filaJogadores, &pilhaPecas);

    int jogadorDaVez = desenfileirar(&filaJogadores);
    if (jogadorDaVez != -1) {
        printf("\nVez do Jogador %d jogar.\n", jogadorDaVez);
    }
    enfileirar(&filaJogadores, jogadorDaVez);

    Peca ultimaPeca = desempilhar(&pilhaPecas);
    if (ultimaPeca.valor != -1) {
        printf("Última peça jogada: valor %d, naipe %s.\n", ultimaPeca.valor, ultimaPeca.naipe);
    }

    exibirEstado(&filaJogadores, &pilhaPecas);

    printf("\nTroca de valores entre duas pecas...\n");
    Peca pecaA = {8, "Paus"};
    Peca pecaB = {2, "Copas"};
    printf("Antes da troca: Peça A=(%d, %s), Peça B=(%d, %s)\n", pecaA.valor, pecaA.naipe, pecaB.valor, pecaB.naipe);
    trocarPecas(&pecaA, &pecaB);
    printf("Depois da troca: Peça A=(%d, %s), Peça B=(%d, %s)\n", pecaA.valor, pecaA.naipe, pecaB.valor, pecaB.naipe);

    return 0;
}
