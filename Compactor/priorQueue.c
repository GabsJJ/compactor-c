#include "priorQueue.h"

static nodeQueue* criarNo(char value)
{
    nodeQueue* aux = (nodeQueue*)malloc(sizeof(nodeQueue));
    aux -> value = value;
    aux -> prox = NULL;
}

priorQueue* criarFila()
{
    priorQueue* filaAux = (priorQueue*)malloc(sizeof(priorQueue));
    filaAux -> inicio = NULL;

    return filaAux;
}

static nodeQueue* procurar(priorQueue* fila, char valueS)
{
    nodeQueue* aux = NULL;
    if(fila -> inicio != NULL)
    {
        aux = fila -> inicio;
        while(aux -> value -> valueNodeTree != valueS || aux != NULL)
        {
            if(aux -> value -> valueNodeTree == valueS)
                return aux;
            else
                aux = aux -> prox;
        }
    }
    return aux;
}

static void inserir(priorQueue* fila, nodeQueue* novo)
{
    if(fila -> inicio == NULL)
    {
        //inserir no inicio
    }
    else
    {
        ///procura o item e insere

    }
}
