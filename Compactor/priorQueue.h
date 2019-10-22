#ifndef PRIORQUEUE
#define PRIORQUEUE

#include <stdlib.h>

/*pode ser util*/
typedef enum
{
    false,
    true
}boolean;

typedef struct no
{
    char valueNodeTree;
    int frequency;
    struct no* esq;
    struct no* dir;
}node;

typedef struct noQ
{
    node value;
    struct noQ* prox;
}nodeQueue;

typedef struct queueP
{
    nodeQueue* inicio;
}priorQueue;

static priorQueue* criarFila();
static nodeQueue* criarNo(char value);
static nodeQueue* procurar(priorQueue* fila, nodeQueue procurado);
static void inserir(priorQueue* fila, nodeQueue* novo);
#endif
