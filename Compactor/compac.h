#ifndef COMPAC_H
#define COMPAC_H

#include "priorQueue.h"
#include "tree.h"

priorQueue* priQueue;

void contar(FILE *arq);
void transformarBytes(nodeBit** vetBits, FILE *saida, FILE *arq);
void compactar(FILE *arq, char dir[]);
void cuidarBitsLidos(char byte[], huffNode* atual, huffNode* tree, FILE *saida);
void destransformarBytes(FILE *arq, FILE *saida, huffNode** vetCharFreq, int bitsLixo, int bytesCharFreq, huffNode* tree);
void criarFilaDec(huffNode** vetCharFreq, int sizeVetChar, priorQueue* queue2);
void descompactar(FILE *arq, char dir[]);
#endif
