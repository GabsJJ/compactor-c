#include "tree.h"

tree* criarArvore(priorQueue* fila)
{
    tree* huffTree = (tree*)malloc(sizeof(tree));
    huffNode *huffNodeTree, *noEsq, *noDir;
    while(fila -> tamanho >= 2)
    {
        noEsq = remover(fila, 0) -> value;
        noDir = remover(fila, 0) -> value;
        huffNodeTree = criarHuffNode(32, (noEsq -> frequency + noDir -> frequency));
        huffNodeTree -> esq = noEsq;
        huffNodeTree -> dir = noDir;
        inserir(fila, huffNodeTree);
    }
    nodeQueue* aux = remover(fila,0);
    huffTree -> root = aux -> value;
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
        printf("\n%c", root -> valueHuffNode);
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

void transformarEmBits(tree* treeH, nodeBit* vetBits[])
{

}
