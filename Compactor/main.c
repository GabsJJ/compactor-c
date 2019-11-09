#include "compac.h"

int main()
{
    FILE *arq1;
    char caminho[255];
    int opcao = 0;
    while(1)
    {
        printf("Digite o caminho do arquivo: ");
        scanf("%s", caminho);
        if((arq1 = fopen(caminho, "rb")) == NULL)
        {
            printf("\nArquivo nao encontrado... Deseja continuar ?");
            printf("\n1-Sim");
            printf("\n2-Nao\n");
            scanf("%u", &opcao);
            if(opcao != 1)
                break;
            system("cls");
        }
        else
        {
            printf("\n---O que deseja fazer?---");
            printf("\n1-Compactar");
            printf("\n2-Descompactar");
            printf("\n-------------------------\n");
            scanf("%u", &opcao);
            if(opcao == 1)
                compactar(arq1, caminho);
            else if (opcao == 2)
                descompactar(arq1, caminho);
            else
                break;
            printf("\nDeseja continuar ?");
            printf("\n1-Sim");
            printf("\n2-Nao\n");
            scanf("%u", &opcao);
            if(opcao != 1)
                break;
            system("cls");
        }
    }
    system("pause");
    return 0;
}
