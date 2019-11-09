#include "tree.h"

huffNode* criarArvore(priorQueue* fila)
{
    int i = 0;
    huffNode* huffTree = (huffNode*)malloc(sizeof(huffNode));
    huffNode *huffNodeTree, *noEsq, *noDir;
    while(fila -> tamanho >= 2)
    {
        nodeQueue *no1 = remover(fila, 0), *no2 = remover(fila, 0);
        noEsq = no1 -> value;
        noDir = no2 -> value;
        free(no1);
        free(no2);
        huffNodeTree = criarHuffNode('A'+i, (noEsq -> frequency + noDir -> frequency));
        inserir(fila, huffNodeTree);
        huffNodeTree -> esq = noEsq;
        huffNodeTree -> dir = noDir;
        i++;
    }
    nodeQueue* aux = remover(fila,0);
    huffTree = aux -> value;
    free(aux);
    return huffTree;
}

boolean eFolha(huffNode* node)
{
    if(node -> esq == NULL && node -> dir == NULL)
        return true;
    return false;
}

void printarArvore(huffNode* root)
{
    if(eFolha(root) == true)
        printf("\n%d", root -> valueHuffNode);
    if(root -> esq != NULL)
        printarArvore(root -> esq);
    if(root -> dir != NULL)
        printarArvore(root -> dir);
}

int quantasFolhas(huffNode* root)
{
    if(root == NULL)
        return 0;
    if(eFolha(root) == true)
        return 1;
    else
        return quantasFolhas(root -> esq) + quantasFolhas(root -> dir);
}

int alturaArvore(huffNode* root)
{
    if(root == NULL)
        return 0;
    else
    {
       int altEsq = alturaArvore(root->esq);
       int altDir = alturaArvore(root->dir);

       if (altEsq > altDir)
           return(altEsq+1);
       return(altDir+1);
    }
}

nodeBit* criarNodeBit(int value, char* code)
{
    nodeBit* noAtual = (nodeBit*)malloc(sizeof(nodeBit));
    noAtual -> value = value;
    noAtual -> code = code;

    return noAtual;
}

char* vetorTeste(char* base, int tamanho)
{
    int i = 0;
    char* novaString = (char*)malloc(sizeof(char)*tamanho);
    //if(novaString == NULL)

    novaString[tamanho] = 0;
    for(i = 0; i < tamanho; i++)
        novaString[i] = base[i];

    return novaString;
}

void transformarEmBits(huffNode* root, char* codeAtual, char **vetor, int atual)
{
    if(eFolha(root) == true)
    {
        int i = atual;
        if(i < strlen(codeAtual))
            for(; i < strlen(codeAtual); i++)
                codeAtual[i] = 0;
        char* a = vetorTeste(codeAtual, atual);
        vetor[root -> valueHuffNode] = a;
        //printf("\nchar: %c code: %s",root -> valueHuffNode, codeAtual);
    }
    if(root -> esq != NULL)
    {
        codeAtual[atual] = '0';
        transformarEmBits(root -> esq, codeAtual, vetor, atual + 1);
    }
    if(root -> dir != NULL)
    {
        codeAtual[atual] = '1';
        transformarEmBits(root -> dir, codeAtual, vetor, atual + 1);
    }
}

void printarArq(huffNode* root, FILE* arq)
{
    if(root != NULL)
    {
        if(eFolha(root))
        {
            unsigned char v1 = root -> valueHuffNode;
            unsigned int v2 = root -> frequency;
            fwrite(&v1, sizeof(char), 1, arq);
            fwrite(&v2, sizeof(unsigned int), 1, arq);
        }
        printarArq(root -> esq, arq);
        printarArq(root -> dir, arq);
    }
}

huffNode* destransformarBits(FILE *saida, huffNode* atual, huffNode* tree, int instrucao)
{
    if(instrucao == '0' && atual -> esq != NULL)
    {
        atual -> valueHuffNode = atual -> esq -> valueHuffNode;
        atual -> frequency = atual -> esq -> frequency;
        atual -> dir = atual -> esq -> dir;
        atual -> esq = atual -> esq -> esq;
    }
    if(instrucao == '1' && atual -> dir != NULL)
    {
        atual -> valueHuffNode = atual -> dir -> valueHuffNode;
        atual -> frequency = atual -> dir -> frequency;
        atual -> esq = atual -> dir -> esq;
        atual -> dir = atual -> dir -> dir;
    }
    if(eFolha(atual))
    {
        fwrite(&(atual -> valueHuffNode), sizeof(char), 1, saida);
        free(atual);
        atual = criarHuffNode(tree -> valueHuffNode, tree -> frequency);
        atual -> esq = tree -> esq;
        atual -> dir = tree -> dir;
    }
    return atual;
}

void freeArvore(huffNode* root)
{
    if(root != NULL)
    {
        if(eFolha(root))
            free(root);
        else
        {
            freeArvore(root -> esq);
            freeArvore(root -> dir);
        }
    }
}
