#include "compac.h"

huffNode* procurarNoVetor(huffNode** vetor, int tamanho, char value)
{
    int i = 0;
    huffNode* noAt = NULL;
    for(i = 0; i < tamanho; i++)
    {
        if(vetor[i] != NULL && vetor[i] -> valueHuffNode == value)
            return vetor[i];
    }
    return noAt;
}

void contar(FILE *arq)
{
    int qtdChars = 0;
    int c, pAtual = 0, i = 0;
    huffNode* noAt;

    while((c = fgetc(arq) ) != EOF)
       qtdChars++;
    rewind(arq);

    huffNode** vetAux = (huffNode**)malloc(sizeof(huffNode)*qtdChars);
    for(i = 0; i < qtdChars; i++)
        vetAux[i] = NULL;

    while((c = fgetc(arq) ) != EOF)
    {
        noAt = procurarNoVetor(vetAux, qtdChars, c);
        if(noAt != NULL)
            noAt -> frequency += 1;
        else
        {
            huffNode* aux = criarHuffNode(c, 1);
            vetAux[pAtual] = aux;
            pAtual++;
        }
    }
    /*cria a fila de prioridade de acordo com o metodo de huffman*/
    priQueue = criarFila();
    for(i = 0; i < qtdChars; i++)
        if(vetAux[i] != NULL)
            inserir(priQueue, vetAux[i]);

    free(vetAux);
}

void compactar(FILE *arq)
{
    huffNode* huffTree = criarArvore(priQueue);
    int qtdFolhas = quantasFolhas(huffTree);

    int i = 0;
    nodeBit** vetBits = (nodeBit**)malloc(sizeof(nodeBit*)*qtdFolhas);
    char *codeAux = (char*)malloc(sizeof(char)*alturaArvore(huffTree));
    nodeBit* noAtual = criarNodeBit('\0',codeAux);
    transformarEmBits(huffTree, noAtual, vetBits, i);
    //printarArvore(huffTree -> root);
}

void descompactar(FILE *arq)
{

}
