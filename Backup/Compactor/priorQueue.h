#ifndef PRIORQUEUE_H
#define PRIORQUEUE_H

#include <stdio.h>
#include <stdlib.h>

/*pode ser util*/
typedef enum
{
    false,
    true
}boolean;

typedef struct noH
{
    int valueHuffNode;
    int frequency;
    struct noH* esq;
    struct noH* dir;
}huffNode;

typedef struct noQ
{
    huffNode* value;
    struct noQ* prox;
}nodeQueue;

typedef struct
{
    nodeQueue* inicio;
    nodeQueue* fim;
    int tamanho;
}priorQueue;

priorQueue* criarFila();
nodeQueue* criarNo(huffNode* value);
huffNode* criarHuffNode(int value, int freq);
void inserir(priorQueue* fila, huffNode* novo);
void printar(priorQueue* fila);
nodeQueue* remover(priorQueue* fila, int posicao);
#endif
