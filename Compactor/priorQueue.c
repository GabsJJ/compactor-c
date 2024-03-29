#include "priorQueue.h"

nodeQueue* criarNo(huffNode* value)
{
    nodeQueue* aux = (nodeQueue*)malloc(sizeof(nodeQueue));
    aux -> value = value;
    aux -> prox = NULL;

    return aux;
}

huffNode* criarHuffNode(int value, int freq)
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
    filaAux -> tamanho = 0;

    return filaAux;
}

void inserir(priorQueue* fila, huffNode* novo)
{
    if(fila -> inicio == NULL)
        fila -> fim = fila -> inicio = criarNo(novo);
    else
    {
        if(novo -> frequency < fila -> inicio -> value -> frequency)
        {
            nodeQueue* novoAux = criarNo(novo);
            novoAux -> prox = fila -> inicio;
            fila -> inicio = novoAux;
        }
        else if(novo -> frequency > fila -> fim -> value -> frequency)
        {
            nodeQueue* novoAux = criarNo(novo);
            fila -> fim -> prox = novoAux;
            fila -> fim = novoAux;
        }
        else
        {
            nodeQueue* noAt = fila -> inicio;
            nodeQueue* noAnt = NULL;
            while(noAt != NULL)
            {
                if(novo -> frequency < noAt -> value -> frequency)
                {
                    nodeQueue* novoAux = criarNo(novo);
                    novoAux -> prox = noAt;
                    noAnt -> prox = novoAux;
                    break;
                }
                if(novo -> frequency == fila -> fim -> value -> frequency && noAt == fila -> fim)
                {
                    nodeQueue* novoAux = criarNo(novo);
                    novoAux -> prox = noAt;
                    if(noAnt != NULL)
                        noAnt -> prox = novoAux;
                    else
                        fila -> inicio = novoAux;
                    break;
                }
                noAnt = noAt;
                noAt = noAt -> prox;
            }
        }
    }
    fila -> tamanho += 1;
}

nodeQueue* remover(priorQueue* fila, int posicao)
{
    nodeQueue* noAremover = NULL;
    if(fila -> inicio != NULL && posicao < fila -> tamanho)
    {
        int i = 0;
        noAremover = fila -> inicio;
        nodeQueue* noAnt = NULL;
        while(i < posicao)
        {
            noAnt = noAremover;
            noAremover = noAremover -> prox;
            i++;
        }
        if(noAnt == NULL) /*tem um unico elemento ou o elemento a remover � o primeiro*/
        {
            fila -> inicio = fila -> inicio -> prox;
            if(fila -> inicio == NULL) /*ficou vazia*/
                fila -> fim = NULL;
        }
        else if(noAremover == fila -> fim)
            noAnt -> prox = NULL;
        else
        {
            noAnt -> prox = noAremover -> prox;
            noAremover -> prox = NULL;
        }
        fila -> tamanho -= 1;
    }
    return noAremover;
}

void freeFila(priorQueue* fila)
{
    if(fila -> tamanho != 0)
    {
        nodeQueue* rem = NULL;
        while(fila -> tamanho != 0)
            rem = remover(fila, 0);
        free(rem);
    }
}

void printar(priorQueue* fila)
{
    if(fila -> inicio != NULL)
    {
        nodeQueue* noAt = fila -> inicio;
        while(noAt != NULL)
        {
            printf("\nchar: %c freq: %d", noAt -> value -> valueHuffNode, noAt -> value -> frequency);
            noAt = noAt -> prox;
        }
    }
}
