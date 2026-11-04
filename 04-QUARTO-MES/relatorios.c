#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "relatorios.h"
#include "clientes.h"
#include "produtos.h"
#include "vendas.h"
#include "structs.h"
#include "cores.h"


static int dataParaNumero(char data[]) {
    int dia;
    int mes;
    int ano;

    if(sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        return 0;
    }

    return ano * 10000 + mes * 100 + dia;
}


static int dataNoPeriodo(char data[], char inicio[], char fim[]) {
    int dataVenda = dataParaNumero(data);
    int dataInicio = dataParaNumero(inicio);
    int dataFim = dataParaNumero(fim);

    return dataVenda >= dataInicio && dataVenda <= dataFim;
}


static void lerPeriodo(char inicio[], char fim[]) {
    printf(COR_ENTRADA "Data inicial (dd/mm/aaaa): " COR_FIM);
    scanf(" %19s", inicio);
    printf(COR_ENTRADA "Data final   (dd/mm/aaaa): " COR_FIM);
    scanf(" %19s", fim);
}


static int compararClientesNome(const void *a, const void *b) {
    const Cliente *clienteA = (const Cliente *)a;
    const Cliente *clienteB = (const Cliente *)b;

    return strcmp(clienteA->nomeCompleto, clienteB->nomeCompleto);
}


static int compararProdutosDescricao(const void *a, const void *b) {
    const Produto *produtoA = (const Produto *)a;
    const Produto *produtoB = (const Produto *)b;

    return strcmp(produtoA->descricao, produtoB->descricao);
}


static int carregarClientes(Cliente **clientes) {
    FILE *arquivo;
    Cliente cliente;
    int quantidade = 0;

    *clientes = NULL;
    arquivo = fopen("clientes.dat", "r");

    if(arquivo == NULL) {
        return 0;
    }

    while(fscanf(
        arquivo,
        "%d|%99[^|]|%99[^|]|%14[^|]|%99[^|]|%49[^|]|%19[^\n]\n",
        &cliente.codigoCliente,
        cliente.nomeCompleto,
        cliente.nomeSocial,
        cliente.cpf,
        cliente.ruaNumero,
        cliente.bairro,
        cliente.celular
    ) != EOF) {
        Cliente *temporario = realloc(*clientes, (quantidade + 1) * sizeof(Cliente));

        if(temporario == NULL) {
            free(*clientes);
            *clientes = NULL;

            fclose(arquivo);
            return 0;
        }

        *clientes = temporario;
        (*clientes)[quantidade] = cliente;
        quantidade++;
    }

    fclose(arquivo);
    return quantidade;
}


static int carregarProdutos(Produto **produtos) {
    FILE *arquivo;
    Produto produto;
    int quantidade = 0;

    *produtos = NULL;
    arquivo = fopen("produtos.dat", "r");

    if(arquivo == NULL) {
        return 0;
    }

    while(fscanf(
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
    ) != EOF) {
        Produto *temporario = realloc(*produtos, (quantidade + 1) * sizeof(Produto));

        if(temporario == NULL) {
            free(*produtos);
            *produtos = NULL;
            fclose(arquivo);
            return 0;
        }

        *produtos = temporario;
        (*produtos)[quantidade] = produto;
        quantidade++;
    }

    fclose(arquivo);
    return quantidade;
}


static int clienteJaImpresso(int codigos[], int quantidade, int codigo) {
    int i;

    for(i = 0; i < quantidade; i++) {
        if(codigos[i] == codigo) {
            return 1;
        }
    }

    return 0;
}


void relatorioClientes() {
    printf("\n\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|    RELATORIO DE CLIENTES       |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);

    listagemClientes();
}


void relatorioProdutos() {
    printf("\n\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|    RELATORIO DE PRODUTOS       |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);

    listagemProdutos();

}


void relatorioVendas() {
    printf("\n\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|     RELATORIO DE VENDAS        |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);

    listagemVendas();
}


void relatorioFaturamento() {
    FILE *arquivo;
    Venda venda;
    float faturamentoTotal = 0;
    int quantidadeVendas = 0;
    float maiorVenda = 0;

    arquivo = fopen("vendas.dat", "r");

    if(arquivo == NULL) {
        printf(COR_AVISO "\nNenhuma venda cadastrada!\n" COR_FIM);
        return;
    }

    while(fscanf(
        arquivo,
        "%d|%d|%19[^|]|%9[^|]|%f|%f|%f\n",
        &venda.idVenda,
        &venda.codCliente,
        venda.dataVenda,
        venda.horaVenda,
        &venda.total,
        &venda.desconto,
        &venda.totalFinal
    ) != EOF) {
        quantidadeVendas++;
        faturamentoTotal += venda.totalFinal;

        if(venda.totalFinal > maiorVenda) {
            maiorVenda = venda.totalFinal;
        }
    }

    fclose(arquivo);

    printf("\n\n");
    printf(COR_TITULO "+================================+\n" COR_FIM);
    printf(COR_TITULO "|     RELATORIO FATURAMENTO      |\n" COR_FIM);
    printf(COR_TITULO "+================================+\n" COR_FIM);
    printf(COR_TITULO "Vendas realizadas.: %d\n" COR_FIM, quantidadeVendas);
    printf(COR_SUCESSO "Total faturado....: R$ %.2f\n" COR_FIM, faturamentoTotal);
    printf(COR_TITULO "Ticket medio......: R$ %.2f\n" COR_FIM, quantidadeVendas > 0 ? faturamentoTotal / quantidadeVendas : 0);
    printf(COR_TITULO "Maior venda.......: R$ %.2f\n" COR_FIM, maiorVenda);
    printf(COR_TITULO "+================================+\n" COR_FIM);
}


void relatorioProdutosCriticos() {
    Produto *produtos;
    int quantidade;
    int i;
    int encontrou = 0;

    quantidade = carregarProdutos(&produtos);

    if(quantidade == 0) {
        printf(COR_AVISO "\nNenhum produto cadastrado!\n" COR_FIM);
        return;
    }

    qsort(produtos, quantidade, sizeof(Produto), compararProdutosDescricao);

    printf("\n\n");
    printf(COR_ERRO "+===========================================+\n" COR_FIM);
    printf(COR_ERRO "|      RELATORIO ESTOQUE CRITICO            |\n" COR_FIM);
    printf(COR_ERRO "+===========================================+\n" COR_FIM);

    for(i = 0; i < quantidade; i++) {
        if(produtos[i].estoqueAtual <= produtos[i].estoqueMinimo) {
            encontrou = 1;
            printf(COR_ERRO "COD %03d | %-25s | Atual: %3d | Minimo: %3d | PRODUTO NO VERMELHO - REPOR\n" COR_FIM,
                produtos[i].codigoProduto,
                produtos[i].descricao,
                produtos[i].estoqueAtual,

                produtos[i].estoqueMinimo
            );
        }
    }

    if(!encontrou) {
        printf(COR_AVISO "\nNenhum produto em estoque critico!\n" COR_FIM);
    }

    free(produtos);
}


void listagemClientesOrdenada() {
    Cliente *clientes;
    int quantidade;
    int i;

    quantidade = carregarClientes(&clientes);

    if(quantidade == 0) {
        printf(COR_AVISO "\nNenhum cliente cadastrado!\n" COR_FIM);
        return;
    }

    qsort(clientes, quantidade, sizeof(Cliente), compararClientesNome);

    printf("\n\n");
    printf(COR_MENU "+=========================================================================+\n" COR_FIM);
    printf(COR_MENU "|              LISTAGEM DE CLIENTES EM ORDEM ALFABETICA                  |\n" COR_FIM);
    printf(COR_MENU "+=========================================================================+\n" COR_FIM);

    for(i = 0; i < quantidade; i++) {
        printf(COR_TITULO "%03d | %-30s | CPF: %-14s | Whats: %s\n" COR_FIM,
            clientes[i].codigoCliente,
            clientes[i].nomeCompleto,
            clientes[i].cpf,
            clientes[i].celular
        );
    }

    free(clientes);
}


void listagemProdutosOrdenada() {
    Produto *produtos;
    int quantidade;
    int i;

    quantidade = carregarProdutos(&produtos);

    if(quantidade == 0) {
        printf(COR_AVISO "\nNenhum produto cadastrado!\n" COR_FIM);
        return;
    }

    qsort(produtos, quantidade, sizeof(Produto), compararProdutosDescricao);

    printf("\n\n");
    printf(COR_MENU "+================================================================================+\n" COR_FIM);
    printf(COR_MENU "|              LISTAGEM DE PRODUTOS EM ORDEM ALFABETICA                         |\n" COR_FIM);
    printf(COR_MENU "+================================================================================+\n" COR_FIM);

    for(i = 0; i < quantidade; i++) {
        printf(COR_TITULO "%03d | %-25s | %-12s | R$ %8.2f | Estoque: %3d\n" COR_FIM,
            produtos[i].codigoProduto,
            produtos[i].descricao,
            produtos[i].categoria,
            produtos[i].precoVenda,
            produtos[i].estoqueAtual
        );
    }

    free(produtos);
}


void relatorioClientesCompraramPeriodo() {
    FILE *arquivo;
    Venda venda;
    Cliente *clientes;
    int quantidadeClientes;
    int codigosImpressos[500];
    int qtdImpressos = 0;
    int i;
    char inicio[20];

    char fim[20];

    lerPeriodo(inicio, fim);
    quantidadeClientes = carregarClientes(&clientes);

    arquivo = fopen("vendas.dat", "r");

    if(arquivo == NULL || quantidadeClientes == 0) {
        printf(COR_AVISO "\nNao ha dados suficientes para este relatorio.\n" COR_FIM);
        free(clientes);
        if(arquivo != NULL) {
            fclose(arquivo);
        }
        return;
    }

    printf(COR_MENU "\nCLIENTES QUE COMPRARAM NO PERIODO\n" COR_FIM);
    printf(COR_MENU "----------------------------------------\n" COR_FIM);

    while(fscanf(
        arquivo,
        "%d|%d|%19[^|]|%9[^|]|%f|%f|%f\n",
        &venda.idVenda,
        &venda.codCliente,
        venda.dataVenda,
        venda.horaVenda,
        &venda.total,
        &venda.desconto,
        &venda.totalFinal
    ) != EOF) {
        if(dataNoPeriodo(venda.dataVenda, inicio, fim)
            && venda.codCliente > 0
            && !clienteJaImpresso(codigosImpressos, qtdImpressos, venda.codCliente)) {
            for(i = 0; i < quantidadeClientes; i++) {
                if(clientes[i].codigoCliente == venda.codCliente) {
                    printf(COR_TITULO "%03d | %-30s | Ultima compra listada: %s\n" COR_FIM,
                        clientes[i].codigoCliente,
                        clientes[i].nomeCompleto,
                        venda.dataVenda
                    );
                    codigosImpressos[qtdImpressos] = venda.codCliente;
                    qtdImpressos++;
                }
            }
        }
    }

    if(qtdImpressos == 0) {
        printf(COR_AVISO "Nenhum cliente identificado no periodo.\n" COR_FIM);
    }

    fclose(arquivo);
    free(clientes);
}


void relatorioProdutosMaisVendidosPeriodo() {
    FILE *arquivoItens;
    FILE *arquivoVendas;
    ItemVenda item;
    Venda venda;
    int codigos[500];
    int quantidades[500];
    char descricoes[500][100];
    int totalProdutos = 0;
    int i;
    int posicao;
    int vendaDentroPeriodo;
    char inicio[20];
    char fim[20];

    lerPeriodo(inicio, fim);

    arquivoItens = fopen("itens.venda.dat", "r");

    if(arquivoItens == NULL) {
        printf(COR_AVISO "\nNenhum item vendido cadastrado!\n" COR_FIM);
        return;
    }

    while(fscanf(
        arquivoItens,
        "%d|%d|%d|%99[^|]|%f|%d|%f|%c\n",
        &item.idVenda,
        &item.numItem,
        &item.codigoProduto,
        item.descricaoProduto,

        &item.precoUnitario,
        &item.quantidade,
        &item.totalItem,
        &item.statusPagamento
    ) != EOF) {
        vendaDentroPeriodo = 0;
        arquivoVendas = fopen("vendas.dat", "r");

        if(arquivoVendas != NULL) {
            while(fscanf(
                arquivoVendas,
                "%d|%d|%19[^|]|%9[^|]|%f|%f|%f\n",
                &venda.idVenda,
                &venda.codCliente,
                venda.dataVenda,
                venda.horaVenda,
                &venda.total,
                &venda.desconto,
                &venda.totalFinal
            ) != EOF) {
                if(venda.idVenda == item.idVenda && dataNoPeriodo(venda.dataVenda, inicio, fim)) {
                    vendaDentroPeriodo = 1;
                }
            }
            fclose(arquivoVendas);
        }

        if(vendaDentroPeriodo && item.statusPagamento == 'p') {
            posicao = -1;

            for(i = 0; i < totalProdutos; i++) {
                if(codigos[i] == item.codigoProduto) {
                    posicao = i;
                }
            }

            if(posicao == -1 && totalProdutos < 500) {
                codigos[totalProdutos] = item.codigoProduto;
                quantidades[totalProdutos] = item.quantidade;
                strcpy(descricoes[totalProdutos], item.descricaoProduto);
                totalProdutos++;
            }
            else if(posicao != -1) {
                quantidades[posicao] += item.quantidade;
            }
        }
    }

    fclose(arquivoItens);

    printf(COR_TITULO "\nPRODUTOS MAIS VENDIDOS NO PERIODO\n" COR_FIM);
    printf(COR_MENU "----------------------------------------\n" COR_FIM);

    if(totalProdutos == 0) {
        printf(COR_AVISO "Nenhum produto vendido no periodo.\n" COR_FIM);
        return;
    }

    for(i = 0; i < totalProdutos; i++) {
        printf(COR_TITULO "%03d | %-25s | %d unidade(s)\n" COR_FIM, codigos[i], descricoes[i], quantidades[i]);
    }
}


void relatorioVendasPeriodo() {
    FILE *arquivo;
    Venda venda;
    char inicio[20];
    char fim[20];
    int encontrou = 0;
    float totalPeriodo = 0;

    lerPeriodo(inicio, fim);
    arquivo = fopen("vendas.dat", "r");

    if(arquivo == NULL) {
        printf(COR_AVISO "\nNenhuma venda cadastrada!\n" COR_FIM);
        return;
    }

    printf(COR_MENU "\nVENDAS NO PERIODO\n" COR_FIM);
    printf(COR_MENU "----------------------------------------\n" COR_FIM);

    while(fscanf(
        arquivo,
        "%d|%d|%19[^|]|%9[^|]|%f|%f|%f\n",
        &venda.idVenda,

        &venda.codCliente,
        venda.dataVenda,
        venda.horaVenda,
        &venda.total,
        &venda.desconto,
        &venda.totalFinal
    ) != EOF) {
        if(dataNoPeriodo(venda.dataVenda, inicio, fim)) {
            encontrou = 1;
            totalPeriodo += venda.totalFinal;
            printf(COR_TITULO "Venda %03d | %s %s | Cliente %03d | R$ %.2f\n" COR_FIM,
                venda.idVenda,
                venda.dataVenda,
                venda.horaVenda,
                venda.codCliente,
                venda.totalFinal
            );
        }
    }

    fclose(arquivo);

    if(!encontrou) {
        printf(COR_AVISO "Nenhuma venda encontrada no periodo.\n" COR_FIM);
    }

    printf(COR_MENU "----------------------------------------\n" COR_FIM);
    printf(COR_SUCESSO "Total do periodo: R$ %.2f\n" COR_FIM, totalPeriodo);
}
