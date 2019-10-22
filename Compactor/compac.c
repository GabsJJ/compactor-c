#include <stdlib.h>
#include "compac.h"
#include "priorQueue.h"

node* criarNo(char val, int freq)
{
    node* aux = (node*)malloc(sizeof(node));
    aux -> value = val;
    aux -> frequency = freq;
    aux -> esq = NULL;
    aux -> dir = NULL;

    return aux;
}

void contar(FILE *arq)
{
    int qtdChars = 1;
    int c, freq2;
    noCaracter *objChar;

    while(!feof(arq))
        qtdChars++;
    rewind(arq);

    noCaracter vetAux[qtdChars];

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
