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
        if(c != '\r')
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

void transformarBytes(nodeBit** vetBits, FILE *saida, FILE *arq)
{
    int i = 0, indMenor = 0, c = 0, indiceByte = 0;
    char oitoAtual[9] = {0};
    unsigned char byteResultado = 0;
    boolean acabou = false;
    while(!acabou)
    {
        if(vetBits[c] -> value == 666)
        {
            c = fgetc(arq);
            if(c == EOF)
                acabou = true;
        }
        else
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
            else if (i == 8)
            {
                i = 0;
                indiceByte = 0;
                for(; indiceByte < 8; indiceByte++)
                    if(oitoAtual[indiceByte] == '1')            /**1 = 00000001*/
                        byteResultado |= 1 << (7 - indiceByte); /**coloca 1 na posicao (7 -indiceByte) e mescla com o anterior*/
                for(; i < 9; i++)
                        oitoAtual[i] = 0;
                i = 0;
                fputc(byteResultado, saida);
                byteResultado = 0;
                if(indMenor == strlen(vetBits[c] -> code)) /**percorreu todo o cod atual*/
                {
                    indMenor = 0;
                    c = fgetc(arq);
                    if(c == EOF)
                        acabou = true;
                }
            }
        }
    }
    if (i < 8)
    {
        indiceByte = 0;
        for(; indiceByte < 8; indiceByte++)
            if(oitoAtual[indiceByte] == '1')
                byteResultado |= 1 << (7 - indiceByte);
        fputc(byteResultado, saida);
        byteResultado = 0;
    }
}

void compactar(FILE *arq, char dir[])
{
    contar(arq);
    huffNode* huffTree = criarArvore(priQueue);
    int i = 0, c = 0, qtdBits = 0;
    unsigned char bitsLixo = 0;
    strcat(dir, ".joojar");
    FILE *saida = fopen(dir, "wb");
    nodeBit** vetBits = (nodeBit**)malloc(sizeof(nodeBit*)*256);

    for(i = 0; i < 256; i++)
        vetBits[i] = criarNodeBit(666,"a");
    char* vetCode = (char*)malloc(sizeof(char)*alturaArvore(huffTree));
    for(i = 0; i < alturaArvore(huffTree); i++)
        vetCode[i] = 0;
    transformarEmBits(huffTree, vetCode, vetBits);

    while((c = fgetc(arq)) != EOF)
        qtdBits += strlen(vetBits[c] -> code);
    printf("%d", qtdBits);
    bitsLixo = qtdBits % 8;
    fputc(bitsLixo, saida);
    rewind(arq);
    fputc(quantasFolhas(huffTree)*2, saida);
    printarArq(huffTree, saida);
    transformarBytes(vetBits, saida, arq);

    free(huffTree);
    free(vetCode);
    free(vetBits);
    free(priQueue);
}

char* destransformarBytes(FILE *arq, huffNode** vetCharFreq, int bitsLixo, int bytesCharFreq)
{
    fpos_t posAt;
    boolean pode = true;
    int i = 0, ind2 = 0, qtosBytes = 0, c1 = 0, c2 = 0, des = 0;
    char* vetBytes = 0;
    char byteAtual[9] = {0};
    while((c1 = fgetc(arq)) != EOF)
    {
        if(ind2 < bytesCharFreq/2)
        {
            c2 = fgetc(arq);
            vetCharFreq[ind2] = criarHuffNode(c1, c2);
            ind2++;
        }
        else
        {
            if(pode)
            {
                /**pega a qtd de bytes compactados*/
                fgetpos(arq, &posAt);
                fseek(arq, 1, SEEK_END);
                qtosBytes = ftell(arq) - posAt;
                fsetpos(arq, &posAt);
                pode = false;
                vetBytes = (char*)malloc(sizeof(char)*(8*qtosBytes +1));
                for(i = 0; i < 8*qtosBytes +1; i++)
                    vetBytes[i] = 0;
            }
            for(i = 7; i >= 0; i--)
            {
                des = c1 >> i;
                if(des & 1)
                    strcat(byteAtual,"1");
                else
                    strcat(byteAtual,"0");
            }
            strcat(vetBytes, byteAtual);
            for(i = 0; i < 8; i++)
                byteAtual[i] = 0;
        }
    }
    vetBytes[strlen(vetBytes) - bitsLixo] = 0;
    rewind(arq);
    return vetBytes;
}

void criarFilaDec(huffNode** vetCharFreq, int sizeVetChar, priorQueue* queue2)
{
    int i = 0;
    huffNode** vetAux = (huffNode**)malloc(sizeof(huffNode)*256);
    for(; i < 256; i++)
        vetAux[i] = criarHuffNode(666, 1);

    for(i = 0; i < sizeVetChar; i++)
        vetAux[vetCharFreq[i] -> valueHuffNode] = vetCharFreq[i];

    for(i = 0; i < 256; i++)
        if(vetAux[i] -> valueHuffNode != 666)
            inserir(queue2, vetAux[i]);

    free(vetAux);
}

void descompactar(FILE *arq, char dir[])
{
    dir[strlen(dir) - 7] = 0; /**tira o .joojar*/
    FILE *saida = fopen(dir, "wb");
    int i = 0, c1 = 0, bitsLixo = 0, bytesCharFreq = 0, indExt = 0;
    c1 = fgetc(arq);
    bitsLixo = c1;
    c1 = fgetc(arq);
    bytesCharFreq = c1;
    huffNode** vetCharFreq = (huffNode**)malloc(sizeof(huffNode*)*(bytesCharFreq/2));
    char* vetBytes = destransformarBytes(arq, vetCharFreq, bitsLixo, bytesCharFreq);

    printf("%s", vetBytes);
    priorQueue* queue2 = criarFila();
    criarFilaDec(vetCharFreq, bytesCharFreq/2, queue2);
    huffNode* huffTree = criarArvore(queue2);
    printarArvore(huffTree);
    for(i = 0; i < bytesCharFreq/2; i++)
        printf("\n%d",vetCharFreq[i] -> valueHuffNode);
    /*for(i = 0; indExt < strlen(vetBytes); indExt++)
    {
        destransformarBits(saida, huffTree, vetBytes, &i);
        indExt = i;
    }*/
    free(huffTree);
    free(queue2);
    free(vetCharFreq);
    free(vetBytes);
}
