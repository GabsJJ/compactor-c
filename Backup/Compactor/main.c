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
        fflush(stdout);
        scanf("%u", &opcao);
        fflush(stdin);
        contar(arq1);
        if(opcao == 1)
            compactar(arq1, caminho);
        else
            descompactar(arq1);
        fclose(arq1);
    }
    return 0;
}
