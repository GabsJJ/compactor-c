#include "tree.h"

huffNode* criarArvore(priorQueue* fila)
{
    int i = 0;
    huffNode* huffTree = (huffNode*)malloc(sizeof(huffNode));
    huffNode *huffNodeTree, *noEsq, *noDir;
    while(fila -> tamanho >= 2)
    {
        noEsq = remover(fila, 0) -> value;
        noDir = remover(fila, 0) -> value;
        huffNodeTree = criarHuffNode('A'+i, (noEsq -> frequency + noDir -> frequency));
        huffNodeTree -> esq = noEsq;
        huffNodeTree -> dir = noDir;
        inserir(fila, huffNodeTree);
        i++;
    }
    nodeQueue* aux = remover(fila,0);
    huffTree = aux -> value;
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

void transformarEmBits(huffNode* root, char* codeAtual, nodeBit** vetor)
{
    if(eFolha(root) == true)
    {
        char* codeAux = (char*)malloc(sizeof(char)*strlen(codeAtual));
        int i = 0;
        for(; i <= strlen(codeAtual); i++)
            codeAux[i] = codeAtual[i];
        vetor[root -> valueHuffNode] -> value = root -> valueHuffNode;
        vetor[root -> valueHuffNode] -> code = codeAux;
    }
    if(root -> esq != NULL)
    {
        strcat(codeAtual, "0");
        transformarEmBits(root -> esq, codeAtual, vetor);
        codeAtual[strlen(codeAtual)-1] = 0;
    }
    if(root -> dir != NULL)
    {
        strcat(codeAtual, "1");
        transformarEmBits(root -> dir, codeAtual, vetor);
        codeAtual[strlen(codeAtual)-1] = 0;
    }
}

void printarArq(huffNode* root, FILE* arq)
{
    if(eFolha(root))
    {
        unsigned char v1 = root -> valueHuffNode;
        unsigned int v2 = root -> frequency;
        fwrite(&v1, sizeof(char), 1, arq);
        fwrite(&v2, sizeof(unsigned int), 1, arq);
    }
    if(root -> esq != NULL)
        printarArq(root -> esq, arq);
    if(root -> dir != NULL)
        printarArq(root -> dir, arq);
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
