#ifndef COMPAC
#define COMPAC

#include <stdio.h>

typedef struct
{
    char charac;
    int freq;
}caractere;

static caractere *chars;
void contar(FILE *arq);
void compactar(FILE *arq);
void descompactar(FILE *arq);
#endif
