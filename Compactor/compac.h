#ifndef COMPAC_H
#define COMPAC_H

#include "priorQueue.h"
#include "tree.h"

priorQueue* priQueue;

void contar(FILE *arq);
void transformBytes(nodeBit** vetBits, FILE *saida, FILE *arq);
void compactar(FILE *arq, char dir[]);
void descompactar(FILE *arq);
#endif
