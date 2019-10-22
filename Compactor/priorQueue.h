#ifndef PRIORQUEUE
#define PRIORQUEUE

#include <stdio.h>
#include <stdlib.h>

/*pode ser util*/
typedef enum
{
    false,
    true
}boolean;

typedef struct no
{
    char valueHuffNode;
    int frequency;
    struct no* esq;
    struct no* dir;
}huffNode;

typedef struct noQ
{
    huffNode* value;
    struct noQ* prox;
}nodeQueue;

typedef struct queueP
{
    nodeQueue* inicio;
    nodeQueue* fim;
}priorQueue;

priorQueue* criarFila();
nodeQueue* criarNo(huffNode* value);
huffNode* criarHuffNode(char value, int freq);
void inserir(priorQueue* fila, huffNode* novo);
void printar(priorQueue* fila);
#endif
