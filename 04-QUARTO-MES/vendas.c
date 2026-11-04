#include <stdio.h>
#include <string.h>
#include <time.h>

#include "caixa.h"
#include "produtos.h"
#include "vendas.h"
#include "pagamentos.h"
#include "cores.h"
#include "entrada.h"

#define MAX_ITENS_CARRINHO 50

void avisarEstoqueMinimo(Produto produto);


int gerarCodigoVenda() {
    FILE *arquivo;

    int contador = 0;

    char linha[300];

    arquivo = fopen("vendas.dat", "r");

    if(arquivo == NULL) {
        return 1;
    }

    while(fgets(linha, sizeof(linha), arquivo)) {
        contador++;
    }

    fclose(arquivo);

    return contador + 1;
}


int verificarEstoque(int codigoProduto, int quantidadeDesejada) {
    FILE *arquivo;
    Produto produto;

    if(quantidadeDesejada <= 0) {
        beepErro();
        printf(COR_ERRO "\nQuantidade invalida! Informe um valor maior que zero.\n" COR_FIM);
        registrarLog("ERRO: quantidade menor ou igual a zero na verificacao de estoque");
        return 0;
    }

    arquivo = fopen("produtos.dat", "r");

    if(arquivo == NULL) {
        printf(COR_ERRO "\nErro ao abrir produtos.dat\n" COR_FIM);
        return 0;
    }

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

        if(produto.codigoProduto == codigoProduto) {

            if(produto.estoqueAtual <= 0) {
                fclose(arquivo);
                beepErro();
                printf(COR_ERRO "\nProduto sem estoque!\n" COR_FIM);
                registrarLog("ERRO: tentativa de venda de produto sem estoque");
                return 0;
            }

            fclose(arquivo);

            if(produto.estoqueAtual >= quantidadeDesejada){
                return 1;
            }
            else {
                printf(COR_AVISO "\nVoce deseja vender %d produto(s).\n" COR_FIM, quantidadeDesejada);
                printf(COR_AVISO "Ha somente %d em estoque.\n" COR_FIM, produto.estoqueAtual);
                beepErro();
                registrarLog("ERRO: estoque insuficiente na venda");
                return 0;
            }
        }
    }

    fclose(arquivo);

    return 0;
}


void atualizarEstoque(int codigoProduto, int quantidadeVendida) {
    FILE *arquivo;
    FILE *temp;

    Produto produto;

    if(quantidadeVendida <= 0) {
        beepErro();
        printf(COR_ERRO "\nErro: quantidade vendida deve ser maior que zero.\n" COR_FIM);
        registrarLog("ERRO: tentativa de atualizar estoque com quantidade invalida");
        return;
    }

    arquivo = fopen("produtos.dat", "r");

    if(arquivo == NULL) {
        printf(COR_ERRO "\nErro ao abrir produtos.dat\n" COR_FIM);
        return;
    }

    temp = fopen("temp.dat", "w");

    if(temp == NULL){
        printf(COR_ERRO "\nErro ao criar arquivo temporario\n" COR_FIM);
        fclose(arquivo);
        return;
    }

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

        if(produto.codigoProduto == codigoProduto) {
            if(produto.estoqueAtual - quantidadeVendida < 0) {
                printf(COR_ERRO "\nErro: estoque nao pode ficar negativo.\n" COR_FIM);
                beepErro();
                registrarLog("ERRO: tentativa de deixar estoque negativo");
            }
            else {
                produto.estoqueAtual -= quantidadeVendida;
            }
        }

        fprintf(
            temp,
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
    }

    fclose(arquivo);
    fclose(temp);

    remove("produtos.dat");

    rename("temp.dat", "produtos.dat");
}


void gerarDataHora(char data[], char hora[]) {
    time_t tempoAtual;

    struct tm *infoTempo;

    tempoAtual = time(NULL);

    infoTempo = localtime(&tempoAtual);

    strftime(data, 20, "%d/%m/%Y", infoTempo);

    strftime(hora, 10, "%H:%M", infoTempo);
}


void salvarItemVenda(ItemVenda item) {
    FILE *arquivo;

    arquivo = fopen("itens.venda.dat", "a");

    if(arquivo == NULL) {
        printf(COR_ERRO "\nErro ao salvar item da venda!" COR_FIM);
        return;
    }

    fprintf(
        arquivo,
        "%d|%d|%d|%s|%.2f|%d|%.2f|%c\n",
        item.idVenda,
        item.numItem,
        item.codigoProduto,
        item.descricaoProduto,
        item.precoUnitario,
        item.quantidade,
        item.totalItem,
        item.statusPagamento
    );

    fclose(arquivo);
}


void atualizarVendaSalva(Venda vendaAtualizada) {
    FILE *arquivo;
    FILE *temp;
    Venda venda;
    char linha[300];

    arquivo = fopen("vendas.dat", "r");

    if(arquivo == NULL) {
        return;
    }

    temp = fopen("temp_vendas.dat", "w");

    if(temp == NULL) {
        fclose(arquivo);
        return;
    }

    while(fgets(linha, sizeof(linha), arquivo)) {
        if(sscanf(
            linha,
            "%d|%d|%19[^|]|%9[^|]|%f|%f|%f",
            &venda.idVenda,
            &venda.codCliente,
            venda.dataVenda,
            venda.horaVenda,
            &venda.total,
            &venda.desconto,
            &venda.totalFinal
        ) == 7) {
            if(venda.idVenda == vendaAtualizada.idVenda) {

                fprintf(
                    temp,
                    "%d|%d|%s|%s|%.2f|%.2f|%.2f\n",
                    vendaAtualizada.idVenda,
                    vendaAtualizada.codCliente,
                    vendaAtualizada.dataVenda,
                    vendaAtualizada.horaVenda,
                    vendaAtualizada.total,
                    vendaAtualizada.desconto,
                    vendaAtualizada.totalFinal
                );
            }
            else {
                fputs(linha, temp);
            }
        }
        else {
            fputs(linha, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("vendas.dat");
    rename("temp_vendas.dat", "vendas.dat");
}


void atualizarStatusItensVenda(int idVenda, char novoStatus) {
    FILE *arquivo;
    FILE *temp;
    ItemVenda item;
    char linha[300];
    char statusAtual = 'a';
    int camposLidos;

    arquivo = fopen("itens.venda.dat", "r");

    if(arquivo == NULL) {
        return;
    }

    temp = fopen("temp_itens_venda.dat", "w");

    if(temp == NULL) {
        fclose(arquivo);
        return;
    }

    while(fgets(linha, sizeof(linha), arquivo)) {
        statusAtual = 'a';

        camposLidos = sscanf(
            linha,
            "%d|%d|%d|%99[^|]|%f|%d|%f|%c",
            &item.idVenda,
            &item.numItem,
            &item.codigoProduto,
            item.descricaoProduto,
            &item.precoUnitario,
            &item.quantidade,
            &item.totalItem,
            &statusAtual
        );

        if(camposLidos >= 7) {
            item.statusPagamento = statusAtual;

            if(item.idVenda == idVenda) {
                item.statusPagamento = novoStatus;
            }

            fprintf(
                temp,
                "%d|%d|%d|%s|%.2f|%d|%.2f|%c\n",
                item.idVenda,
                item.numItem,
                item.codigoProduto,
                item.descricaoProduto,
                item.precoUnitario,
                item.quantidade,
                item.totalItem,
                item.statusPagamento
            );
        }
        else {

            fputs(linha, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("itens.venda.dat");
    rename("temp_itens_venda.dat", "itens.venda.dat");
}


void baixarEstoqueItensVenda(int idVenda) {
    FILE *arquivo;
    ItemVenda item;
    Produto produto;
    char linha[300];
    char statusPagamento = 'a';

    arquivo = fopen("itens.venda.dat", "r");

    if(arquivo == NULL) {
        return;
    }

    while(fgets(linha, sizeof(linha), arquivo)) {
        statusPagamento = 'a';

        if(sscanf(
            linha,
            "%d|%d|%d|%99[^|]|%f|%d|%f|%c",
            &item.idVenda,
            &item.numItem,
            &item.codigoProduto,
            item.descricaoProduto,
            &item.precoUnitario,
            &item.quantidade,
            &item.totalItem,
            &statusPagamento
        ) >= 7) {
            item.statusPagamento = statusPagamento;

            if(item.idVenda == idVenda && item.statusPagamento == 'p' && item.quantidade > 0) {
                atualizarEstoque(item.codigoProduto, item.quantidade);

                if(buscarProduto(item.codigoProduto, &produto)) {
                    avisarEstoqueMinimo(produto);
                }
            }
        }
    }

    fclose(arquivo);
}


void avisarEstoqueMinimo(Produto produto) {
    if(produto.estoqueAtual <= produto.estoqueMinimo) {
        printf(COR_ERRO "\nATENCAO: produto no vermelho! Necessario repor estoque.\n" COR_FIM);
        printf(COR_ERRO "Produto: %s\n" COR_FIM, produto.descricao);
        printf(COR_ERRO "Estoque atual: %d\n" COR_FIM, produto.estoqueAtual);
        printf(COR_ERRO "Estoque minimo: %d\n" COR_FIM, produto.estoqueMinimo);
    }
}


void novaVenda() {
    if(!caixaEstaAberto()) {
        beepErro();
        printf("\n");

        printf(COR_ERRO "=====================================\n" COR_FIM);
        printf(COR_ERRO "CAIXA FECHADO!\n" COR_FIM);
        printf(COR_ERRO "Abra o caixa antes de vender.\n" COR_FIM);
        printf(COR_ERRO "=====================================\n" COR_FIM);

        registrarLog("ERRO: tentativa de venda com caixa fechado");
        return;
    }

    FILE *arquivo;

    Venda venda;
    ItemVenda itens[MAX_ITENS_CARRINHO];
    Produto produto;
    Pagamento pagamento;

    
    int continuar = 1;
    int qtdItens = 0;
    int codigoProduto;
    int quantidade;
    int i;
    float percentualDesconto = 0;
    char log[200];

    venda.idVenda = gerarCodigoVenda();
    venda.codCliente = 0;
    venda.total = 0;
    venda.desconto = 0;
    venda.totalFinal = 0;

    gerarDataHora(venda.dataVenda, venda.horaVenda);

    printf("\n\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|          NOVA VENDA            |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_TITULO "\nProdutos cadastrados:\n" COR_FIM);
    listagemProdutos();

    do {
        if(qtdItens >= MAX_ITENS_CARRINHO) {
            printf(COR_AVISO "\nLimite de itens do carrinho atingido!\n" COR_FIM);
            break;
        }

        printf(COR_ENTRADA "Codigo do produto (0 para cancelar venda): " COR_FIM);
        codigoProduto = lerInteiro("");

        if(codigoProduto == 0) {
            printf(COR_AVISO "\n=====================================\n" COR_FIM);
            printf(COR_AVISO "VENDA CANCELADA!\n" COR_FIM);
            printf(COR_AVISO "=====================================\n" COR_FIM);
            registrarLog("Venda cancelada antes de adicionar item");
            return;
        }

        if(!buscarProduto(codigoProduto, &produto)) {
            beepErro();
            printf(COR_ERRO "\nPRODUTO NAO ENCONTRADO!\n" COR_FIM);
            registrarLog("ERRO: produto nao encontrado na venda");
            continue;
        }

        printf(COR_TITULO "\nProduto: %s\n" COR_FIM, produto.descricao);
        printf(COR_TITULO "Preco: %.2f\n" COR_FIM, produto.precoVenda);
        printf(COR_TITULO "Estoque: %d\n" COR_FIM, produto.estoqueAtual);

        printf(COR_ENTRADA "Quantidade: " COR_FIM);
        quantidade = lerInteiro("");

        if(quantidade <= 0) {
            beepErro();
            printf(COR_ERRO "\nQuantidade invalida! Nao e permitido adicionar 0 ou numero negativo no carrinho.\n" COR_FIM);
            registrarLog("ERRO: quantidade invalida no carrinho");
            continue;
        }

        if(!verificarEstoque(codigoProduto, quantidade)) {
            printf(COR_ERRO "\n=================================\n" COR_FIM);
            printf(COR_ERRO "ESTOQUE INSUFICIENTE!\n" COR_FIM);
            printf(COR_ERRO "=================================\n" COR_FIM);
            continue;
        }

        itens[qtdItens].idVenda = venda.idVenda;
        itens[qtdItens].numItem = qtdItens + 1;
        itens[qtdItens].codigoProduto = produto.codigoProduto;
        strcpy(itens[qtdItens].descricaoProduto, produto.descricao);
        itens[qtdItens].precoUnitario = produto.precoVenda;
        itens[qtdItens].quantidade = quantidade;
        itens[qtdItens].totalItem = produto.precoVenda * quantidade;
        itens[qtdItens].statusPagamento = 'a';

        venda.total += itens[qtdItens].totalItem;
        qtdItens++;

        printf(COR_SUCESSO "\nItem adicionado com sucesso!\n" COR_FIM);
        printf(COR_TITULO "Total parcial da venda: R$ %.2f\n" COR_FIM, venda.total);

        do {
            printf(COR_MENU "=====================================\n" COR_FIM);
            printf(COR_MENU "[1] - Adicionar outro item\n" COR_FIM);

        
            printf(COR_MENU "[2] - Finalizar venda\n" COR_FIM);
            printf(COR_MENU "[0] - Cancelar venda\n" COR_FIM);
            printf(COR_MENU "=====================================\n" COR_FIM);

            printf(COR_ENTRADA "Opcao: " COR_FIM);
            continuar = lerInteiro("");

            if(continuar < 0 || continuar > 2) {
                beepErro();
                printf(COR_ERRO "\nOpcao invalida! Escolha 0, 1 ou 2.\n" COR_FIM);
            }
        } while(continuar < 0 || continuar > 2);

        if(continuar == 0) {
            printf(COR_AVISO "\n=====================================\n" COR_FIM);
            printf(COR_AVISO "VENDA CANCELADA!\n" COR_FIM);
            printf(COR_AVISO "=====================================\n" COR_FIM);
            return;
        }

    } while(continuar == 1);

    if(qtdItens == 0) {
        beepErro();
        printf(COR_AVISO "\nVenda sem itens. Nada foi salvo.\n" COR_FIM);
        registrarLog("ERRO: tentativa de finalizar venda sem itens");
        return;
    }

    printf(COR_MENU "\n=================================\n" COR_FIM);
    printf(COR_MENU "RESUMO DO CARRINHO\n" COR_FIM);
    printf(COR_MENU "=================================\n" COR_FIM);

    for(i = 0; i < qtdItens; i++) {
        printf(
            COR_TITULO "%03d - %s | Qtd: %d | Unit: R$ %.2f | Total: R$ %.2f\n" COR_FIM,
            itens[i].codigoProduto,
            itens[i].descricaoProduto,
            itens[i].quantidade,
            itens[i].precoUnitario,
            itens[i].totalItem
        );
    }

    do {
        printf(COR_ENTRADA "\nHa desconto? Informe 0 para nao ou o percentual: " COR_FIM);
        percentualDesconto = lerFloat("");

        if(percentualDesconto < 0 || percentualDesconto >= 100) {
            beepErro();
            printf(COR_ERRO "\nPercentual invalido! Use de 0 ate 99.99 para a venda nao ficar zerada.\n" COR_FIM);
        }

    } while(percentualDesconto < 0 || percentualDesconto >= 100);

    venda.desconto = venda.total * (percentualDesconto / 100);
    venda.totalFinal = venda.total - venda.desconto;

    printf(COR_MENU "\n=================================\n" COR_FIM);
    printf(COR_TITULO "TOTAL DO CARRINHO...: R$ %.2f\n" COR_FIM, venda.total);
    printf(COR_TITULO "DESCONTO............: R$ %.2f\n" COR_FIM, venda.desconto);
    printf(COR_SUCESSO "TOTAL FINAL DA VENDA: R$ %.2f\n" COR_FIM, venda.totalFinal);
    printf(COR_MENU "=================================\n" COR_FIM);

    arquivo = fopen("vendas.dat", "a");

    if(arquivo == NULL) {
        printf(COR_ERRO "\nErro ao abrir vendas.dat!\n" COR_FIM);
        return;
    }

    fprintf(
        arquivo,
        "%d|%d|%s|%s|%.2f|%.2f|%.2f\n",
        venda.idVenda,
        venda.codCliente,
        venda.dataVenda,
        venda.horaVenda,
        venda.total,
        venda.desconto,
        venda.totalFinal
    );

    fclose(arquivo);

    for(i = 0; i < qtdItens; i++) {
        salvarItemVenda(itens[i]);

        
    }

    if(!realizarPagamento(venda.idVenda, venda.totalFinal, &pagamento)) {
        printf(COR_AVISO "\nPagamento nao aprovado. Venda ficou em aberto.\n" COR_FIM);
        registrarLog("Venda salva em aberto por falta de pagamento");
        return;
    }

    venda.desconto += pagamento.desconto;
    venda.totalFinal = venda.total - venda.desconto;

    atualizarVendaSalva(venda);
    atualizarStatusItensVenda(venda.idVenda, 'p');
    baixarEstoqueItensVenda(venda.idVenda);

    sprintf(
        log,
        "Venda realizada - venda %d - total %.2f",
        venda.idVenda,
        venda.totalFinal
    );
    registrarLog(log);

    gerarCupomFiscal(venda, itens, qtdItens, pagamento);

    beepSucesso();
    printf(COR_SUCESSO "\nVenda finalizada com sucesso!\n" COR_FIM);

}


void listagemVendas() {
    FILE *arquivo;

    Venda venda;

    arquivo = fopen("vendas.dat", "r");

    if(arquivo == NULL) {
        printf(COR_AVISO "\nNenhuma venda cadastrada!\n" COR_FIM);
        return;
    }

    printf("\n\n");
    printf(COR_MENU "+================================================================================+\n" COR_FIM);
    printf(COR_MENU "|                             LISTAGEM DE VENDAS                                |\n" COR_FIM);
    printf(COR_MENU "+================================================================================+\n" COR_FIM);

    while(
        fscanf(
            arquivo,
            "%d|%d|%19[^|]|%9[^|]|%f|%f|%f\n",

            &venda.idVenda,
            &venda.codCliente,
            venda.dataVenda,
            venda.horaVenda,
            &venda.total,
            &venda.desconto,
            &venda.totalFinal
        ) != EOF
    )
    {

        printf(COR_TITULO "ID Venda........: %03d\n" COR_FIM, venda.idVenda);
        printf(COR_TITULO "Cliente.........: %03d\n" COR_FIM, venda.codCliente);
        printf(COR_TITULO "Data............: %s\n" COR_FIM, venda.dataVenda);
        printf(COR_TITULO "Hora............: %s\n" COR_FIM, venda.horaVenda);
        printf(COR_TITULO "Total bruto.....: R$ %.2f\n" COR_FIM, venda.total);
        printf(COR_TITULO "Desconto........: R$ %.2f\n" COR_FIM, venda.desconto);
        printf(COR_SUCESSO "Total final.....: R$ %.2f\n" COR_FIM, venda.totalFinal);

        printf(COR_MENU "+================================================================================+\n" COR_FIM);
    }

    fclose(arquivo);
}
