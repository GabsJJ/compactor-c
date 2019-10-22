#ifndef COMPAC
#define COMPAC

#include "priorQueue.h"

huffNode* procurarNoVetor(huffNode* vetor[], int tamanho, char value);
void contar(FILE *arq);
void compactar(FILE *arq);
void descompactar(FILE *arq);
#endif
