#include "compac.h"

int main()
{
    FILE *arq1;
    char caminho[255];
    int opcao;

    printf("Digite o caminho do arquivo: ");
    scanf("%s", caminho);

    if((arq1 = fopen(caminho, "rb")) == NULL)
        printf("Arquivo não encontrado");
    else
    {
        printf("\n---O que deseja fazer?---");
        printf("\n1-Compactar");
        printf("\n2-Descompactar");
        printf("\n-------------------------\n");
        scanf("%u", &opcao);
        if(opcao == 1)
            compactar(arq1, caminho);
        else
            descompactar(arq1, caminho);
    }
    fclose(arq1);
    printf("\nFinalizado !");
    return 0;
}
