#ifndef TREE_H
#define TREE_H

#include "priorQueue.h"
#include <string.h>

typedef struct
{
    int value;
    char* code;
}nodeBit;

huffNode* criarArvore(priorQueue* fila);
boolean eFolha(huffNode* node);
void printarArvore(huffNode* root);
int quantasFolhas(huffNode* root);
int alturaArvore(huffNode* root);
nodeBit* criarNodeBit(int value, char* code);
void transformarEmBits(huffNode* root, char* codeAtual, char **vetor, int atual);
void printarArq(huffNode* root, FILE* arq);
huffNode* destransformarBits(FILE *saida, huffNode* atual, huffNode* tree, int instrucao);
void freeArvore(huffNode* root);
#endif
