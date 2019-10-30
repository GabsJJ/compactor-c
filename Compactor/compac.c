#include "compac.h"

void contar(FILE *arq)
{
    int c, i = 0;
    huffNode** vetAux = (huffNode**)malloc(sizeof(huffNode)*256);
    for(i = 0; i < 256; i++)
        vetAux[i] = criarHuffNode(666, 1);

    while((c = fgetc(arq) ) != EOF)
    {
        if(vetAux[c] -> valueHuffNode == 666)
            vetAux[c] -> valueHuffNode = c;
        else
            vetAux[c] -> frequency += 1;
    }
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
    int qtdFolhas = quantasFolhas(huffTree), i = 0;

    nodeBit** vetBits = (nodeBit**)malloc(sizeof(nodeBit*)*qtdFolhas);
    char* vetCode = (char*)malloc(sizeof(char)*alturaArvore(huffTree));
    for(i = 0; i < alturaArvore(huffTree); i++)
        vetCode[i] = 0;
    i = 0;
    transformarEmBits(huffTree, vetCode, vetBits, &i);

    ///colocar no arq
    for(i=0; i< qtdFolhas; i++)
    {
        printf("\n val: %c code: %s", vetBits[i] -> value, vetBits[i] -> code);
    }



    //freeArvore(huffTree);
    free(huffTree);
    free(vetCode);
    free(vetBits);
    free(priQueue);
}

void descompactar(FILE *arq)
{

}
