#ifndef COMPAC
#define COMPAC

#include <stdio.h>

struct cchar
{
    int c;
    int freq;
}caractere;

void contar(FILE *arq);
void compactar(FILE *arq);
void descompactar(FILE *arq);
#endif
