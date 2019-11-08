#include "compac.h"

void contar(FILE *arq)
{
    int i = 0, c = 0;
    huffNode** vetAux = (huffNode**)malloc(sizeof(huffNode)*256);
    for(i = 0; i < 256; i++)
        vetAux[i] = criarHuffNode(666, 1);

    while(fread(&c, sizeof(char), 1, arq) == 1)
    {
        if(vetAux[c] -> valueHuffNode == 666)
            vetAux[c] -> valueHuffNode = c;
        else
            vetAux[c] -> frequency += 1;
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
    int i = 0, indMenor = 0, indiceByte = 0, c = 0;
    char oitoAtual[9] = {0};
    unsigned char byteResultado = 0;
    boolean acabou = false;
    fread(&c, sizeof(char), 1, arq);
    while(!acabou)
    {
        if(vetBits[c] -> value == 666)
        {
            if(fread(&c, sizeof(char), 1, arq) != 1)
                acabou = true;
        }
        else
        {
            for(; i < 8 && indMenor < strlen(vetBits[c] -> code); i++, indMenor++)
                oitoAtual[i] = vetBits[c] -> code[indMenor];
            if(i < 8)
            {
                indMenor = 0;
                if(fread(&c, sizeof(char), 1, arq) != 1)
                    acabou = true;
            }
            else if (i == 8)
            {
                i = 0;
                indiceByte = 0;
                for(; indiceByte < 8; indiceByte++)
                    if(oitoAtual[indiceByte] == '1')            /**1 = 00000001*/
                        byteResultado |= 1 << (7 - indiceByte); /**coloca 1 na posicao (7 -indiceByte) e mescla com o anterior*/
                for(; i < strlen(oitoAtual); i++)
                    oitoAtual[i] = 0;
                i = 0;
                fwrite(&byteResultado, sizeof(char), 1, saida);
                byteResultado = 0;
                if(indMenor == strlen(vetBits[c] -> code)) /**percorreu todo o cod atual*/
                {
                    indMenor = 0;
                    if(fread(&c, sizeof(char), 1, arq) != 1)
                        acabou = true;
                }
            }
        }
    }
    if (i < 8 && i != 0)
    {
        indiceByte = 0;
        for(; indiceByte < 8; indiceByte++)
            if(oitoAtual[indiceByte] == '1')
                byteResultado |= 1 << (7 - indiceByte);
        fwrite(&byteResultado, sizeof(char), 1, saida);
        byteResultado = 0;
    }
    rewind(saida);
    rewind(arq);
}

void compactar(FILE *arq, char dir[])
{
    fseek(arq, 1, SEEK_END);
    int qtdBytes = ftell(arq);
    rewind(arq);
    if(qtdBytes != 1)
    {
        contar(arq);
        huffNode* huffTree = criarArvore(priQueue);
        int i = 0, qtdBits = 0, folhas = quantasFolhas(huffTree)*2, c = 0;
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
        while(fread(&c, sizeof(char), 1, arq) == 1)
            qtdBits += strlen(vetBits[c] -> code);
        if(qtdBits <= 8)
            bitsLixo = 8 - qtdBits;
        else
            bitsLixo = qtdBits % 8;
        rewind(arq);
        fwrite(&bitsLixo, sizeof(char), 1, saida);
        fwrite(&folhas, sizeof(int), 1, saida);
        printarArq(huffTree, saida);
        transformarBytes(vetBits, saida, arq);

        free(huffTree);
        free(vetCode);
        free(priQueue);
        free(vetBits);
        fclose(saida);
    }
    else
        printf("Arquivo vazio...");
}

huffNode* cuidarBitsLidos(char byte[], huffNode *atual, huffNode* tree, FILE *saida)
{
    int i = 0;
    for(; i < strlen(byte); i++)
        atual = destransformarBits(saida, atual, tree, byte[i]);
    return atual;
}

huffNode** criarFilaPrioridadeDec(FILE *arq, int tamanho)
{
    unsigned char c1 = 0;
    unsigned int c2 = 0;
    int i = 0;
    huffNode** vetAux = (huffNode**)malloc(sizeof(huffNode*)*tamanho);
    while(i < tamanho)
    {
        fread(&c1, sizeof(char), 1, arq);
        fread(&c2, sizeof(unsigned int), 1, arq);
        vetAux[i] = criarHuffNode(c1, c2);
        i++;
    }
    return vetAux;
}

void destransformarBytes(FILE *arq, FILE *saida, huffNode** vetCharFreq, int bitsLixo, int bytesCharFreq, huffNode* tree)
{
    fpos_t posAt;
    huffNode *atual = criarHuffNode(tree -> valueHuffNode, tree -> frequency);
    atual -> esq = tree -> esq;
    atual -> dir = tree -> dir;
    int i = 0, c1 = 0, des = 0, qtosBytes = 0, indiceByteAtual = 0;
    char byteAtual[9] = {0};
    /**pega a qtd de bytes compactados*/
    c1 = fgetc(arq);
    fgetpos(arq, &posAt);
    fseek(arq, 1, SEEK_END);
    qtosBytes = ftell(arq) - posAt;
    fsetpos(arq, &posAt);
    while(!feof(arq))
    {
        indiceByteAtual++;
        for(i = 7; i >= 0; i--)
        {
            des = c1 >> i;
            if(des & 1)
                strcat(byteAtual,"1");
            else
                strcat(byteAtual,"0");
        }
        if(indiceByteAtual != qtosBytes)
            atual = cuidarBitsLidos(byteAtual, atual, tree, saida);
        else
        {
            byteAtual[strlen(byteAtual) - bitsLixo] = 0;
            atual = cuidarBitsLidos(byteAtual, atual, tree, saida);
        }
        for(i = 0; i < strlen(byteAtual); i++)
            byteAtual[i] = 0;
        fread(&c1, sizeof(char), 1, arq);
    }
    rewind(arq);
    free(atual);
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
    fseek(arq, 1, SEEK_END);
    int qtdBytes = ftell(arq);
    rewind(arq);
    if(qtdBytes != 1 && strstr(dir, ".joojar") != NULL)
    {
        dir[strlen(dir) - 7] = 0; /**tira o .joojar*/
        FILE *saida = fopen(dir, "wb");
        int bitsLixo = 0, bytesCharFreq = 0;
        fread(&bitsLixo, sizeof(char), 1, arq);
        fread(&bytesCharFreq, sizeof(int), 1, arq);
        huffNode** vetCharFreq = criarFilaPrioridadeDec(arq, bytesCharFreq/2);
        priorQueue* queue2 = criarFila();
        criarFilaDec(vetCharFreq, bytesCharFreq/2, queue2);
        huffNode* huffTree = criarArvore(queue2);
        destransformarBytes(arq, saida, vetCharFreq, bitsLixo, bytesCharFreq, huffTree);

        free(huffTree);
        free(queue2);
        free(vetCharFreq);
        fclose(saida);
    }
    else
        printf("\nNão foi possivel descompactar o arquivo...");
}
