#include <stdio.h>
#include <stdlib.h>

#include "relatorios.h"


#include "clientes.h"
#include "produtos.h"
#include "vendas.h"


void relatorioClientes()
{
    printf("\n\n");
    printf("+================================+\n");
    printf("|    RELATORIO DE CLIENTES       |\n");
    printf("+================================+\n");

    listagemClientes();
}


void relatorioProdutos()
{
    printf("\n\n");
    printf("+================================+\n");
    printf("|    RELATORIO DE PRODUTOS       |\n");
    printf("+================================+\n");

    listagemProdutos();
}


void relatorioVendas()
{
    printf("\n\n");
    printf("+================================+\n");
    printf("|     RELATORIO DE VENDAS        |\n");
    printf("+================================+\n");

    listagemVendas();
}


void relatorioFaturamento()
{
    FILE *arquivo;

    Venda venda;

    float faturamentoTotal = 0;

    arquivo = fopen("vendas.dat", "r");

    if(arquivo == NULL)
    {
        printf("\nErro ao abrir vendas.dat\n");
        return;
    }

    while(
        fscanf(
            arquivo,
            "%d|%d|%99[^|]|%f|%d|%f|%19[^|]|%9[^\n]\n",

            &venda.idVenda,
            &venda.codigoProduto,
            venda.descricaoProduto,
            &venda.precoUnitario,
            &venda.quantidade,
            &venda.totalItem,
            venda.dataVenda,
            venda.horaVenda
        ) != EOF
    )
    {
        faturamentoTotal += venda.totalItem;
    }

    fclose(arquivo);

    printf("\n\n");

    printf("+================================+\n");
    printf("|     RELATORIO FATURAMENTO     |\n");
    printf("+================================+\n");

    printf("TOTAL FATURADO: R$ %.2f\n", faturamentoTotal);

    printf("+================================+\n");
}


void relatorioProdutosCriticos()
{
    FILE *arquivo;

    Produto produto;

    int encontrou = 0;

    arquivo = fopen("produtos.dat", "r");

    if(arquivo == NULL)
    {
        printf("\nErro ao abrir produtos.dat\n");
        return;
    }

    printf("\n\n");
    printf("+===========================================+\n");
    printf("|      RELATORIO ESTOQUE CRITICO            |\n");
    printf("+===========================================+\n");

    while(
        fscanf(
            arquivo,
            "%d|%99[^|]|%49[^|]|%f|%f|%f|%d|%d\n",

            &produto.codigoProduto,
            produto.descricao,
            produto.categoria,
            &produto.precoCompra,
            &produto.margemLucro,
            &produto.precoVenda,
            &produto.estoqueAtual,
            &produto.estoqueMinimo
        ) != EOF
    )
    {
        if(produto.estoqueAtual <= produto.estoqueMinimo)
        {
            encontrou = 1;

            printf("\n");
            printf("CODIGO...........: %d\n", produto.codigoProduto);
            printf("PRODUTO..........: %s\n", produto.descricao);
            printf("ESTOQUE ATUAL....: %d\n", produto.estoqueAtual);
            printf("ESTOQUE MINIMO...: %d\n", produto.estoqueMinimo);
            printf("STATUS...........: REPOR URGENTE\n");
            printf("--------------------------------------\n");
        }
    }

    fclose(arquivo);

    if(!encontrou)
    {
        printf("\nNenhum produto em estoque critico!\n");
    }
}
