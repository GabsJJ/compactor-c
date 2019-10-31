#include "compac.h"

void contar(FILE *arq)
{
    int c, i = 0;
    huffNode** vetAux = (huffNode**)malloc(sizeof(huffNode)*256);
    for(i = 0; i < 256; i++)
        vetAux[i] = criarHuffNode(666, 1);

    while((c = fgetc(arq)) != EOF)
    {
        /*pode ter quebras de linha, tabulações, carriage return etc*/
        if(c != '\r' && c != '\n' && c != '\t' && c != '\v' && c != '\f')
        {
            if(vetAux[c] -> valueHuffNode == 666)
                vetAux[c] -> valueHuffNode = c;
            else
                vetAux[c] -> frequency += 1;
        }
    }
    rewind(arq);
    /*cria a fila de prioridade de acordo com o metodo de huffman*/
    priQueue = criarFila();
    for(i = 0; i < 256; i++)
        if(vetAux[i] -> valueHuffNode != 666)
            inserir(priQueue, vetAux[i]);
    free(vetAux);
}

void compactar(FILE *arq, char dir[])
{
    huffNode* huffTree = criarArvore(priQueue);
    int i = 0, indMenor = 0, c = 0;

    nodeBit** vetBits = (nodeBit**)malloc(sizeof(nodeBit*)*256);
    for(i = 0; i < 256; i++)
        vetBits[i] = criarNodeBit(666,"a");
    char* vetCode = (char*)malloc(sizeof(char)*alturaArvore(huffTree));
    for(i = 0; i < alturaArvore(huffTree); i++)
        vetCode[i] = 0;
    transformarEmBits(huffTree, vetCode, vetBits);

    FILE *saida = fopen("C:/Users/u18196/Desktop/t.joojar", "wb");

    char oitoAtual[9];
    unsigned char byteResultado = 0;
    i = 0;
    boolean acabou = false;
    while(!acabou)
    {
        for(; i < 8 && indMenor < strlen(vetBits[c] -> code); i++, indMenor++)
            oitoAtual[i] = vetBits[c] -> code[indMenor];
        if(i < 8)
        {
            indMenor = 0;
            c = fgetc(arq);
            if(c == EOF)
                acabou = true;
        }
        else
        {
            i = 0;
            int indiceByte = 0;
            for(; indiceByte < 8; indiceByte++)
                if(oitoAtual[indiceByte] == '1')            /**1 = 00000001*/
                    byteResultado |= 1 << (7 - indiceByte); /**coloca 1 na posicao (7 -indiceByte)*/
            if(strlen(vetBits[c] -> code) <= 8)
            {
                indMenor = 0;
                c = fgetc(arq);
                if(c == EOF)
                    acabou = true;
                fputc(byteResultado, saida);
                byteResultado = 0;
            }
        }
        /**falta => quando acabar e os bytes n estiverem todos completos -> botar lixo de memória ou algo do tipo*/
    }
    /*for(i=0; i< 256; i++)
    {
        if(vetBits[i] -> value != 666)
            printf("\n val: %c code: %s", vetBits[i] -> value, vetBits[i] -> code);
    }*/

    /*freeArvore(huffTree);*/
    free(huffTree);
    free(vetCode);
    free(vetBits);
    free(priQueue);
}

void descompactar(FILE *arq)
{

}
