#include <stdlib.h>
#include "compac.h"

void contar(FILE *arq)
{
    while(!feof(arq))
    {
        caractere* c1 = (caractere*)malloc(sizeof(caractere));
        c1 -> c = fgetc(arq);
        c1 -> freq = f;

        printf("%c",);
    }
}

void compactar(FILE *arq)
{

}

void descompactar(FILE *arq)
{

}
