#ifndef COMPAC_H
#define COMPAC_H

#include "priorQueue.h"
#include "tree.h"

priorQueue* priQueue;

huffNode* procurarNoVetor(huffNode* vetor[], int tamanho, char value);
void contar(FILE *arq);
void compactar(FILE *arq);
void descompactar(FILE *arq);
#endif
