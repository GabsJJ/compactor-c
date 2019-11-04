#ifndef COMPAC_H
#define COMPAC_H

#include "priorQueue.h"
#include "tree.h"

priorQueue* priQueue;

void contar(FILE *arq);
void transformarBytes(nodeBit** vetBits, FILE *saida, FILE *arq);
void compactar(FILE *arq, char dir[]);
void descompactar(FILE *arq, char dir[]);
#endif
