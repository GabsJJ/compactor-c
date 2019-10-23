#include "priorQueue.h"

nodeQueue* criarNo(huffNode* value)
{
    nodeQueue* aux = (nodeQueue*)malloc(sizeof(nodeQueue));
    aux -> value = value;
    aux -> prox = NULL;

    return aux;
}

huffNode* criarHuffNode(char value, int freq)
{
    huffNode* aux = (huffNode*)malloc(sizeof(huffNode));
    aux -> valueHuffNode = value;
    aux -> frequency = freq;
    aux -> esq = aux -> dir = NULL;
    return aux;
}

priorQueue* criarFila()
{
    priorQueue* filaAux = (priorQueue*)malloc(sizeof(priorQueue));
    filaAux -> inicio = filaAux -> fim = NULL;

    return filaAux;
}

void inserir(priorQueue* fila, huffNode* novo)
{
    if(fila -> inicio == NULL)
        fila -> fim = fila -> inicio = criarNo(novo);
    else
    {
        if(novo -> frequency <= fila -> inicio -> value -> frequency)
        {
            nodeQueue* novoAux = criarNo(novo);
            novoAux -> prox = fila -> inicio;
            fila -> inicio = novoAux;
        }
        else if(novo -> frequency >= fila -> fim -> value -> frequency)
        {
            nodeQueue* novoAux = criarNo(novo);
            fila -> fim -> prox = novoAux;
            fila -> fim = novoAux;
        }
        else
        {
            nodeQueue* noAt = fila -> inicio;
            nodeQueue* noAnt = noAt;
            while(noAt != NULL)
            {
                if(novo -> frequency < noAt -> value -> frequency)
                {
                    nodeQueue* novoAux = criarNo(novo);
                    novoAux -> prox = noAt;
                    noAnt -> prox = novoAux;
                }
                noAnt = noAt;
                noAt = noAt -> prox;
            }
        }
    }
}

void printar(priorQueue* fila)
{
    if(fila -> inicio != NULL)
    {
        nodeQueue* noAt = fila -> inicio;
        while(noAt != NULL)
        {
            printf("\nchar: %c, freq: %d", noAt -> value -> valueHuffNode, noAt -> value -> frequency);
            noAt = noAt -> prox;
        }
    }
}
