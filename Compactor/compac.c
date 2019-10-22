#include <stdlib.h>
#include "compac.h"

void contar(FILE *arq)
{
    int qtdChars = 1;
    int c, freq2;
    caractere *objChar;

    while(!feof(arq))
        qtdChars++;
    rewind(arq);

    chars = (caractere*)malloc(sizeof(caractere)*qtdChars);
    //fazer a fila direto
    while(!feof(arq))
    {
        objChar = (caractere*)malloc(sizeof(caractere));
        c = fgetc(arq);
        freq2 = 1;
        objChar -> charac = c;
        objChar -> freq = freq2;
        if(fgetc(arq) != c)
        {

        }
        else
        {
            freq2++;
            objChar -> freq = freq2;
        }
    }
    free(chars);
}

void compactar(FILE *arq)
{

}

void descompactar(FILE *arq)
{

}
