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
    {
        fila -> fim = fila -> inicio = criarNo(novo);
    }
    else
    {
        if(novo -> valueHuffNode > fila -> inicio -> value -> valueHuffNode)
        {
            ///insere no fim
        }
        else
        {
            ///insere antes do inicio

        }

    }
}

void inserirNoFim(priorQueue* fila, huffNode* novo)
{

}

void printar(priorQueue* fila)
{
    if(fila -> inicio != NULL)
    {
        nodeQueue* noAt = fila -> inicio;
        while(noAt != NULL)
        {
            printf("%c", noAt -> value -> valueHuffNode);
            noAt = noAt -> prox;
        }
    }
}
