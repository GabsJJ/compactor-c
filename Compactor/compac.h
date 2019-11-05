#ifndef COMPAC_H
#define COMPAC_H

#include "priorQueue.h"
#include "tree.h"

priorQueue* priQueue;

void contar(FILE *arq);
void transformarBytes(nodeBit** vetBits, FILE *saida, FILE *arq);
void compactar(FILE *arq, char dir[]);
char* destransformarBytes(FILE *arq, huffNode** vetCharFreq, int bitsLixo, int bytesCharFreq);
void criarFilaDec(huffNode** vetCharFreq, int sizeVetChar, priorQueue* queue2);
void descompactar(FILE *arq, char dir[]);
#endif
