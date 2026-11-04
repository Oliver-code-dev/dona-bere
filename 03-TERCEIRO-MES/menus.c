#include <stdio.h>
#include <stdlib.h>

#include "menus.h"


#include "clientes.h"
#include "produtos.h"
#include "vendas.h"
#include "pagamentos.h"
#include "caixa.h"
#include "relatorios.h"


void menuPrincipal()
{
    int opcao = 0;
    char fecharSistema;

    do
    {
        printf("\n\n");
        printf("+================================+\n");
        printf("|         MENU PRINCIPAL         |\n");
        printf("+================================+\n");
        printf("| [1] - Cadastros                |\n");
        printf("| [2] - Vendas                   |\n");
        printf("| [3] - Abertura de Caixa        |\n");
        printf("| [4] - Fechamento de Caixa      |\n");
        printf("| [5] - Relatorios              |\n");
        printf("| [6] - Sair                     |\n");
        printf("+================================+\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                menuCadastros();
                break;

            case 2:
                menuVendas();
                break;

            case 3:
                menuAberturaCaixa();
                break;

            case 4:
                menuFechamentoCaixa();
                break;

            case 5:
                menuRelatorios();
                break;

            case 6:
                printf("\nDeseja realmente sair?\n");
                printf("[S] - Sim\n");
                printf("[N] - Nao\n");
                scanf(" %c", &fecharSistema);

                if(fecharSistema == 'S' || fecharSistema == 's')
                {
                    printf("\nEncerrando sistema...\n");
                    opcao = 7;
                }
                else if(fecharSistema == 'N' || fecharSistema == 'n')
                {
                    printf("\nVoltando ao sistema...\n");
                }
                else
                {
                    printf("\nOpcao invalida!\n");
                }
                break;

            default:
                printf("\nEssa opcao nao existe!\n");
                break;
        }
    } while(opcao != 7);
}


void menuCadastros()
{
    int opcao = 0;

    do
    {
        printf("\n\n");
        printf("+================================+\n");
        printf("|        MENU CADASTROS          |\n");
        printf("+================================+\n");
        printf("| [1] - Clientes                 |\n");
        printf("| [2] - Produtos                 |\n");
        printf("| [3] - Editar Cliente           |\n");
        printf("| [4] - Excluir Produto          |\n");
        printf("| [5] - Voltar                   |\n");
        printf("+================================+\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                cadastrarCliente();
                break;

            case 2:
                cadastrarProduto();
                break;

            case 3:
                editarCliente();
                break;

            case 4:
                excluirProduto();
                break;

            case 5:
                printf("Voltando...\n");
                break;

            default:
                printf("\nEssa opcao nao existe!\n");
                break;
        }
    } while(opcao != 5);
}


void menuVendas()
{
    int opcao = 0;

    do
    {
        printf("\n\n");
        printf("+================================+\n");
        printf("|          MENU VENDAS           |\n");
        printf("+================================+\n");
        printf("| [1] - Nova Venda               |\n");
        printf("| [2] - Realizar Sangria         |\n");
        printf("| [3] - Voltar                   |\n");
        printf("+================================+\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                novaVenda();
                break;

            case 2:
                realizarSangria();
                break;

            case 3:
                printf("\nVoltando...\n");
                break;

            default:

                printf("\nEssa opcao nao existe!\n");
                break;
        }
    } while(opcao != 3);
}


void menuAberturaCaixa()
{
    int opcao = 0;

    do
    {
        printf("\n\n");
        printf("+================================+\n");
        printf("|       ABERTURA DE CAIXA        |\n");
        printf("+================================+\n");
        printf("| [1] - Abrir Caixa              |\n");
        printf("| [2] - Voltar                   |\n");
        printf("+================================+\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                abrirCaixa();
                break;

            case 2:
                printf("\nVoltando...\n");
                break;

            default:
                printf("\nEssa opcao nao existe!\n");
                break;
        }
    } while(opcao != 2);
}


void menuFechamentoCaixa()
{
    int opcao = 0;

    do
    {
        printf("\n\n");
        printf("+================================+\n");
        printf("|      FECHAMENTO DE CAIXA       |\n");
        printf("+================================+\n");
        printf("| [1] - Fechar Caixa             |\n");
        printf("| [2] - Voltar                   |\n");
        printf("+================================+\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                fecharCaixa();
                break;

            case 2:
                printf("\nVoltando...\n");
                break;

            default:
                printf("\nEssa opcao nao existe!\n");
                break;
        }
    } while(opcao != 2);
}


void menuRelatorios()
{
    int opcao = 0;

    do
    {
        printf("\n\n");

        printf("+================================+\n");
        printf("|        MENU RELATORIOS         |\n");
        printf("+================================+\n");
        printf("| [1] - Clientes                 |\n");
        printf("| [2] - Produtos                 |\n");
        printf("| [3] - Vendas                   |\n");
        printf("| [4] - Faturamento              |\n");
        printf("| [5] - Produtos Criticos        |\n");
        printf("| [6] - Voltar                   |\n");
        printf("+================================+\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                listagemClientes();
                break;

            case 2:
                listagemProdutos();
                break;

            case 3:
                listagemVendas();
                break;

            case 4:
                relatorioFaturamento();
                break;

            case 5:
                relatorioProdutosCriticos();
                break;

            case 6:
                printf("Voltando...\n");
                break;

            default:
                printf("\nEssa opcao nao existe!\n");
                break;
        }
    } while(opcao != 6);
}
