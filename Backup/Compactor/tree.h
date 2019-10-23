#ifndef TREE_H
#define TREE_H

#include "priorQueue.h"

typedef struct
{
    huffNode* root;
}tree;

typedef struct
{
    char value;
    int code;
}nodeBit;

tree* criarArvore(priorQueue* fila);
boolean eFolha(huffNode* node);
void printarArvore(huffNode* root);
int quantasFolhas(huffNode* root);
void transformarEmBits(tree* treeH, nodeBit* vetBits[]);
#endif
