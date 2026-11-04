#include <stdio.h>
#include <stdlib.h>

#include "arquivos.h"

int arquivoExiste(const char *nomeArquivo)
{
    FILE *arquivo;

    arquivo = fopen(nomeArquivo, "r");

    if(arquivo == NULL)
    {
        return 0;
    }

    fclose(arquivo);

    return 1;
}

void salvarCliente(Cliente cliente)
{
    FILE *arquivo;

    arquivo = fopen("clientes.dat", "a");

    if(arquivo == NULL)
    {
        printf("\nErro ao salvar cliente!\n");
        return;
    }

    fprintf(
        arquivo,
        "%d|%s|%s|%s|%s|%s|%s\n",

        cliente.codigoCliente,
        cliente.nomeCompleto,
        cliente.nomeSocial,
        cliente.cpf,
        cliente.ruaNumero,
        cliente.bairro,
        cliente.celular
    );

    fclose(arquivo);
}

void salvarProduto(Produto produto)
{
    FILE *arquivo;

    arquivo = fopen("produtos.dat", "a");

    if(arquivo == NULL)
    {
        printf("\nErro ao salvar produto!\n");
        return;
    }

    fprintf(
        arquivo,
        "%d|%s|%s|%.2f|%.2f|%.2f|%d|%d\n",

        produto.codigoProduto,
        produto.descricao,
        produto.categoria,
        produto.precoCompra,
        produto.margemLucro,
        produto.precoVenda,
        produto.estoqueAtual,
        produto.estoqueMinimo
    );

    fclose(arquivo);
}

void salvarVenda(Venda venda)
{
    FILE *arquivo;

    arquivo = fopen("vendas.dat", "a");

    if(arquivo == NULL)
    {
        printf("\nErro ao salvar venda!\n");
        return;
    }

    fprintf(
        arquivo,
        "%d|%d|%s|%.2f|%d|%.2f\n",

        venda.idVenda,
        venda.codigoProduto,
        venda.descricaoProduto,
        venda.precoUnitario,
        venda.quantidade,
        venda.totalItem
    );

    fclose(arquivo);
}

void salvarPagamento(Pagamento pagamento)
{
    FILE *arquivo;

    arquivo = fopen("pagamentos.dat", "a");

    if(arquivo == NULL)
    {
        printf("\nErro ao salvar pagamento!\n");
        return;
    }

    fprintf(
        arquivo,
        "%.2f|%s\n",

        pagamento.valorPago,
        pagamento.tipoPagamento
    );

    fclose(arquivo);
}

void salvarCaixa(Caixa caixa)
{
    FILE *arquivo;

    arquivo = fopen("caixa.dat", "w");

    if(arquivo == NULL)
    {
        printf("\nErro ao salvar caixa!\n");
        return;
    }

    fprintf(
        arquivo,
        "%.2f|%d\n",

        caixa.valorInicial,
        caixa.statusCaixa
    );

    fclose(arquivo);
}
