#ifndef TREE_H
#define TREE_H

#include "priorQueue.h"
#include <string.h>

typedef struct
{
    char value;
    char code[];
}nodeBit;

huffNode* criarArvore(priorQueue* fila);
boolean eFolha(huffNode* node);
void printarArvore(huffNode* root);
int quantasFolhas(huffNode* root);
int alturaArvore(huffNode* root);
nodeBit* criarNodeBit(char value, char code[]);
nodeBit* transformarEmBits(huffNode* root, nodeBit* noAtual);
#endif
