#include <stdio.h>
#include <stdlib.h>

#include "menus.h"


#include "clientes.h"
#include "produtos.h"
#include "vendas.h"
#include "pagamentos.h"
#include "caixa.h"
#include "relatorios.h"
#include "usuarios.h"
#include "cores.h"
#include "entrada.h"


static void linhaMenu()
{
    printf(COR_MENU "+================================+\n" COR_FIM);
}


static void tituloMenu(char titulo[])
{
    linhaMenu();
    printf(COR_MENU "|%-32s|\n" COR_FIM, titulo);
    linhaMenu();
}


void menuPrincipal()
{
    int opcao = 0;
    char fecharSistema;

    do
    {
        printf("\n\n");
        tituloMenu("        MENU PRINCIPAL");
        printf(COR_MENU "| [1] - Cadastros                |\n" COR_FIM);
        printf(COR_MENU "| [2] - Vendas                   |\n" COR_FIM);
        printf(COR_MENU "| [3] - Abertura de Caixa        |\n" COR_FIM);
        printf(COR_MENU "| [4] - Fechamento de Caixa      |\n" COR_FIM);
        printf(COR_MENU "| [5] - Relatorios               |\n" COR_FIM);
        printf(COR_MENU "| [6] - Sair                     |\n" COR_FIM);
        linhaMenu();

        opcao = lerInteiro(COR_ENTRADA "Digite a opcao desejada: " COR_FIM);

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
                printf(COR_TITULO "\nDeseja realmente sair?\n" COR_FIM);
                printf(COR_MENU "[S] - Sim\n" COR_FIM);
                printf(COR_MENU "[N] - Nao\n" COR_FIM);
                fecharSistema = lerCharOpcao("");

                if(fecharSistema == 'S' || fecharSistema == 's')
                {
                    printf(COR_AVISO "\nEncerrando sistema...\n" COR_FIM);
                    opcao = 7;
                }
                else if(fecharSistema == 'N' || fecharSistema == 'n')
                {
                    printf(COR_AVISO "\nVoltando ao sistema...\n" COR_FIM);

                }
                else
                {
                    printf(COR_ERRO "\nOpcao invalida!\n" COR_FIM);
                }
                break;

            default:
                printf(COR_ERRO "\nEssa opcao nao existe!\n" COR_FIM);
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
        tituloMenu("        MENU CADASTROS");
        printf(COR_MENU "| [1] - Usuarios                 |\n" COR_FIM);
        printf(COR_MENU "| [2] - Clientes                 |\n" COR_FIM);
        printf(COR_MENU "| [3] - Produtos                 |\n" COR_FIM);
        printf(COR_MENU "| [4] - Voltar                   |\n" COR_FIM);
        linhaMenu();

        opcao = lerInteiro(COR_ENTRADA "Digite a opcao desejada: " COR_FIM);

        switch(opcao)
        {
            case 1:
                menuUsuarios();
                break;

            case 2:
                menuClientes();
                break;

            case 3:
                menuProdutos();
                break;

            case 4:
                printf(COR_AVISO "Voltando...\n" COR_FIM);
                break;

            default:
                printf(COR_ERRO "\nEssa opcao nao existe!\n" COR_FIM);
                break;
        }
    } while(opcao != 4);
}


void menuUsuarios()
{
    int opcao = 0;

    do
    {
        printf("\n\n");
        tituloMenu("         MENU USUARIOS");
        printf(COR_MENU "| [1] - Criar novo usuario       |\n" COR_FIM);
        printf(COR_MENU "| [2] - Editar usuario           |\n" COR_FIM);
        printf(COR_MENU "| [3] - Remover usuario          |\n" COR_FIM);
        printf(COR_MENU "| [4] - Voltar                   |\n" COR_FIM);
        linhaMenu();

        opcao = lerInteiro(COR_ENTRADA "Digite a opcao desejada: " COR_FIM);

        switch(opcao)
        {
            case 1:
                cadastrarUsuario();
                break;

            case 2:
                editarUsuario();
                break;

            case 3:
                removerUsuario();

                break;

            case 4:
                printf(COR_AVISO "Voltando...\n" COR_FIM);
                break;

            default:
                printf(COR_ERRO "\nEssa opcao nao existe!\n" COR_FIM);
                break;
        }
    } while(opcao != 4);
}


void menuClientes()
{
    int opcao = 0;

    do
    {
        printf("\n\n");
        tituloMenu("         MENU CLIENTES");
        printf(COR_MENU "| [1] - Cadastrar cliente        |\n" COR_FIM);
        printf(COR_MENU "| [2] - Editar cliente           |\n" COR_FIM);
        printf(COR_MENU "| [3] - Remover cliente          |\n" COR_FIM);
        printf(COR_MENU "| [4] - Voltar                   |\n" COR_FIM);
        linhaMenu();

        opcao = lerInteiro(COR_ENTRADA "Digite a opcao desejada: " COR_FIM);

        switch(opcao)
        {
            case 1:
                cadastrarCliente();
                break;

            case 2:
                editarCliente();
                break;

            case 3:
                removerCliente();
                break;

            case 4:
                printf(COR_AVISO "Voltando...\n" COR_FIM);
                break;

            default:
                printf(COR_ERRO "\nEssa opcao nao existe!\n" COR_FIM);
                break;
        }
    } while(opcao != 4);
}


void menuProdutos()
{
    int opcao = 0;

    do
    {
        printf("\n\n");
        tituloMenu("         MENU PRODUTOS");
        printf(COR_MENU "| [1] - Cadastrar produto        |\n" COR_FIM);
        printf(COR_MENU "| [2] - Editar produto           |\n" COR_FIM);
        printf(COR_MENU "| [3] - Remover produto          |\n" COR_FIM);
        printf(COR_MENU "| [4] - Voltar                   |\n" COR_FIM);
        linhaMenu();

        opcao = lerInteiro(COR_ENTRADA "Digite a opcao desejada: " COR_FIM);

        switch(opcao)
        {
            case 1:
                cadastrarProduto();
                break;

            case 2:
                editarProduto();
                break;

            case 3:
                excluirProduto();
                break;

            case 4:
                printf(COR_AVISO "Voltando...\n" COR_FIM);
                break;

            default:
                printf(COR_ERRO "\nEssa opcao nao existe!\n" COR_FIM);
                break;
        }
    } while(opcao != 4);
}


void menuVendas()
{
    int opcao = 0;

    do
    {
        printf("\n\n");
        tituloMenu("          MENU VENDAS");
        printf(COR_MENU "| [1] - Nova Venda               |\n" COR_FIM);
        printf(COR_MENU "| [2] - Realizar Sangria         |\n" COR_FIM);
        printf(COR_MENU "| [3] - Pagamento Pendente       |\n" COR_FIM);
        printf(COR_MENU "| [4] - Voltar                   |\n" COR_FIM);
        linhaMenu();

        opcao = lerInteiro(COR_ENTRADA "Digite a opcao desejada: " COR_FIM);

        switch(opcao)
        {
            case 1:
                novaVenda();
                break;

            case 2:
                realizarSangria();
                break;

            case 3:
                realizarPagamentoPendente();
                break;

            case 4:
                printf(COR_AVISO "\nVoltando...\n" COR_FIM);
                break;

            default:
                printf(COR_ERRO "\nEssa opcao nao existe!\n" COR_FIM);
                break;
        }
    } while(opcao != 4);
}


void menuAberturaCaixa()
{
    int opcao = 0;

    do
    {
        printf("\n\n");
        tituloMenu("       ABERTURA DE CAIXA");
        printf(COR_MENU "| [1] - Abrir Caixa              |\n" COR_FIM);
        printf(COR_MENU "| [2] - Voltar                   |\n" COR_FIM);
        linhaMenu();

        opcao = lerInteiro(COR_ENTRADA "Digite a opcao desejada: " COR_FIM);

        switch(opcao)
        {
            case 1:
                abrirCaixa();
                break;

            case 2:
                printf(COR_AVISO "\nVoltando...\n" COR_FIM);
                break;

            default:
                printf(COR_ERRO "\nEssa opcao nao existe!\n" COR_FIM);
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
        tituloMenu("      FECHAMENTO DE CAIXA");
        printf(COR_MENU "| [1] - Fechar Caixa             |\n" COR_FIM);
        printf(COR_MENU "| [2] - Voltar                   |\n" COR_FIM);
        linhaMenu();

        opcao = lerInteiro(COR_ENTRADA "Digite a opcao desejada: " COR_FIM);

        switch(opcao)
        {
            case 1:
                fecharCaixa();
                break;

            case 2:
                printf(COR_AVISO "\nVoltando...\n" COR_FIM);
                break;

            default:
                printf(COR_ERRO "\nEssa opcao nao existe!\n" COR_FIM);
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
        tituloMenu("        MENU RELATORIOS");
        printf(COR_MENU "| [1] - Clientes                 |\n" COR_FIM);
        printf(COR_MENU "| [2] - Produtos                 |\n" COR_FIM);
        printf(COR_MENU "| [3] - Vendas                   |\n" COR_FIM);
        printf(COR_MENU "| [4] - Faturamento              |\n" COR_FIM);
        printf(COR_MENU "| [5] - Voltar                   |\n" COR_FIM);
        linhaMenu();

        opcao = lerInteiro(COR_ENTRADA "Digite a opcao desejada: " COR_FIM);

        switch(opcao)
        {
            case 1:
                menuRelatorioClientes();
                break;

            case 2:
                menuRelatorioProdutos();
                break;

            case 3:
                menuRelatorioVendas();
                break;

            case 4:
                relatorioFaturamento();
                break;

            case 5:
                printf(COR_AVISO "Voltando...\n" COR_FIM);
                break;

            default:
                printf(COR_ERRO "\nEssa opcao nao existe!\n" COR_FIM);
                break;
        }
    } while(opcao != 5);
}


void menuRelatorioClientes()
{
    int opcao = 0;

    do
    {
        printf("\n\n");
        tituloMenu("      RELATORIOS CLIENTES");
        printf(COR_MENU "| [1] - Listagem de clientes     |\n" COR_FIM);
        printf(COR_MENU "| [2] - Clientes por periodo     |\n" COR_FIM);
        printf(COR_MENU "| [3] - Voltar                   |\n" COR_FIM);
        linhaMenu();

        opcao = lerInteiro(COR_ENTRADA "Digite a opcao desejada: " COR_FIM);

        switch(opcao)
        {
            case 1:
                listagemClientesOrdenada();
                break;

            case 2:
                relatorioClientesCompraramPeriodo();
                break;

            case 3:
                printf(COR_AVISO "Voltando...\n" COR_FIM);
                break;

            default:
                printf(COR_ERRO "\nEssa opcao nao existe!\n" COR_FIM);
                break;
        }
    } while(opcao != 3);
}


void menuRelatorioProdutos()
{
    int opcao = 0;

    do
    {
        printf("\n\n");
        tituloMenu("      RELATORIOS PRODUTOS");
        printf(COR_MENU "| [1] - Listagem de produtos     |\n" COR_FIM);
        printf(COR_MENU "| [2] - Estoque critico          |\n" COR_FIM);
        printf(COR_MENU "| [3] - Produtos mais vendidos   |\n" COR_FIM);
        printf(COR_MENU "| [4] - Voltar                   |\n" COR_FIM);
        linhaMenu();

        opcao = lerInteiro(COR_ENTRADA "Digite a opcao desejada: " COR_FIM);

        switch(opcao)
        {
            case 1:
                listagemProdutosOrdenada();
                break;

            case 2:
                relatorioProdutosCriticos();
                break;

            case 3:
                relatorioProdutosMaisVendidosPeriodo();
                break;

            case 4:
                printf(COR_AVISO "Voltando...\n" COR_FIM);
                break;

            default:
                printf(COR_ERRO "\nEssa opcao nao existe!\n" COR_FIM);
                break;
        }
    } while(opcao != 4);
}


void menuRelatorioVendas()
{
    int opcao = 0;

    do
    {
        printf("\n\n");
        tituloMenu("       RELATORIOS VENDAS");
        printf(COR_MENU "| [1] - Listagem de vendas       |\n" COR_FIM);

        printf(COR_MENU "| [2] - Vendas por periodo       |\n" COR_FIM);
        printf(COR_MENU "| [3] - Voltar                   |\n" COR_FIM);
        linhaMenu();

        opcao = lerInteiro(COR_ENTRADA "Digite a opcao desejada: " COR_FIM);

        switch(opcao)
        {
            case 1:
                listagemVendas();
                break;

            case 2:
                relatorioVendasPeriodo();
                break;

            case 3:
                printf(COR_AVISO "Voltando...\n" COR_FIM);
                break;

            default:
                printf(COR_ERRO "\nEssa opcao nao existe!\n" COR_FIM);
                break;
        }
    } while(opcao != 3);
}
