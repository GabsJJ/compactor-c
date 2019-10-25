#include "tree.h"

huffNode* criarArvore(priorQueue* fila)
{
    huffNode* huffTree = (huffNode*)malloc(sizeof(huffNode));
    huffNode *huffNodeTree, *noEsq, *noDir;
    while(fila -> tamanho >= 2)
    {
        noEsq = remover(fila, 0) -> value;
        noDir = remover(fila, 0) -> value;
        huffNodeTree = criarHuffNode(32, (noEsq -> frequency + noDir -> frequency));
        huffNodeTree -> esq = noEsq;
        huffNodeTree -> dir = noDir;
        inserir(fila, huffNodeTree);
    }
    nodeQueue* aux = remover(fila,0);
    huffTree = aux -> value;
    return huffTree;
}

boolean eFolha(huffNode* node)
{
    if(node -> esq == NULL && node -> dir == NULL)
        return true;
    return false;
}

void printarArvore(huffNode* root)
{
    if(eFolha(root) == true)
        printf("\n%c", root -> valueHuffNode);
    if(root -> esq != NULL)
        printarArvore(root -> esq);
    if(root -> dir != NULL)
        printarArvore(root -> dir);
}

int quantasFolhas(huffNode* root)
{
    if(root == NULL)
        return 0;
    if(eFolha(root) == true)
        return 1;
    else
        return quantasFolhas(root -> esq) + quantasFolhas(root -> dir);
}

int alturaArvore(huffNode* root)
{
    if(root == NULL)
        return 0;
    else
    {
       int altEsq = alturaArvore(root->esq);
       int altDir = alturaArvore(root->dir);

       if (altEsq > altDir)
           return(altEsq+1);
       return(altDir+1);
    }
}

nodeBit* criarNodeBit(char value, char *code)
{
    nodeBit* noAtual = (nodeBit*)malloc(sizeof(nodeBit));
    noAtual -> value = value;
    noAtual -> code = code;

    return noAtual;
}

void transformarEmBits(huffNode* root, nodeBit* noAtual, nodeBit** vetor, int index)
{
    if(eFolha(root) == true)
    {
        noAtual -> value = root -> valueHuffNode;
        printf("\nchar: %c code: %s", noAtual -> value, noAtual -> code);
        vetor[index] = noAtual;
        index++;
    }
    if(root -> esq != NULL)
    {
        strcat(noAtual -> code, "0");
        transformarEmBits(root -> esq, noAtual, vetor, index);
        /*printf("\n%d", strlen(noAtual -> code));
        char *aux = (char*)malloc(sizeof(char)*strlen(noAtual -> code));
        aux = noAtual -> code;
        noAtual -> code = "";
        free(aux);*/
        char aux[strlen(noAtual -> code)];
        memmove(aux, noAtual -> code, strlen(noAtual -> code)-1);
        noAtual -> code = aux;
    }
    if(root -> dir != NULL)
    {
        strcat(noAtual -> code, "1");
        transformarEmBits(root -> dir, noAtual, vetor, index);
        //noAtual -> code = "";

        /*char *aux = (char*)malloc(sizeof(char)*strlen(noAtual -> code));
        aux = noAtual -> code;
        noAtual -> code = "";
        memmove(noAtual -> code, aux, strlen(noAtual -> code)-1);
        free(aux);*/
        char aux[strlen(noAtual -> code)];
        memmove(aux, noAtual -> code, strlen(noAtual -> code)-1);
        noAtual -> code = aux;
    }
}
