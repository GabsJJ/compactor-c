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

nodeBit* criarNodeBit(int value, char* code)
{
    nodeBit* noAtual = (nodeBit*)malloc(sizeof(nodeBit));
    noAtual -> value = value;
    noAtual -> code = code;

    return noAtual;
}

void transformarEmBits(huffNode* root, char* codeAtual, nodeBit** vetor)
{
    if(eFolha(root) == true)
    {
        char* codeAux = (char*)malloc(sizeof(char)*strlen(codeAtual));
        int i = 0;
        for(i = 0; i < strlen(codeAtual); i++)
            codeAux[i] = 0;
        strcpy(codeAux, codeAtual);
        vetor[root -> valueHuffNode] -> value = root -> valueHuffNode;
        vetor[root -> valueHuffNode] -> code = codeAux;
    }
    if(root -> esq != NULL)
    {
        strcat(codeAtual, "0");
        transformarEmBits(root -> esq, codeAtual, vetor);
        codeAtual[strlen(codeAtual)-1] = 0;
    }
    if(root -> dir != NULL)
    {
        strcat(codeAtual, "1");
        transformarEmBits(root -> dir, codeAtual, vetor);
        codeAtual[strlen(codeAtual)-1] = 0;
    }
}

void printarArq(huffNode* root, FILE* arq)
{
    if(eFolha(root))
    {
        char v1 = root -> valueHuffNode;
        char v2 = root -> frequency;
        fputc(v1, arq);
        fputc(v2, arq);
    }
    if(root -> esq != NULL)
        printarArq(root -> esq, arq);
    if(root -> dir != NULL)
        printarArq(root -> dir, arq);
}
