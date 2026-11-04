#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "caixa.h"
#include "pagamentos.h"
#include "usuarios.h"
#include "cores.h"
#include "entrada.h"

#define ARQ_CAIXA "caixa.dat"
#define MIN_TROCO 50.0f


int caixaAberto = 0;


int caixaEstaAberto() {
    FILE *arquivo;
    Caixa caixa;

    arquivo = fopen(ARQ_CAIXA, "r");

    if(arquivo == NULL) {
        caixaAberto = 0;
        return caixaAberto;
    }

    if(fscanf(arquivo, "%f|%d\n", &caixa.valorInicial, &caixa.statusCaixa) == 2) {
        caixaAberto = caixa.statusCaixa;
    }

    fclose(arquivo);

    return caixaAberto;
}


static float lerValorAberturaCaixa() {
    FILE *arquivo;
    float valorInicial = 0;
    int statusCaixa = 0;

    arquivo = fopen(ARQ_CAIXA, "r");

    if(arquivo == NULL) {
        return 0;
    }

    fscanf(arquivo, "%f|%d\n", &valorInicial, &statusCaixa);
    fclose(arquivo);

    return valorInicial;
}


static float calcularTotalSangrias() {
    FILE *arquivo;
    float valorSangria;
    float totalSangrias = 0;

    arquivo = fopen("sangrias.dat", "r");

    if(arquivo == NULL) {
        return 0;
    }

    while(fscanf(arquivo, "%f\n", &valorSangria) != EOF) {
        totalSangrias += valorSangria;
    }

    fclose(arquivo);

    return totalSangrias;
}


static void somarPagamentos(
    float *dinheiro,
    float *cartao,
    float *mistoDinheiro,
    float *mistoCartao
) {
    FILE *arquivo;
    char linha[300];
    char tipoPagamento[40];

    char tipoCartao[20];
    int idVenda;
    float valorPago;
    float valorDinheiro;
    float valorCartao;
    float desconto;
    float troco;
    float valorAntigo;

    *dinheiro = 0;
    *cartao = 0;
    *mistoDinheiro = 0;
    *mistoCartao = 0;

    arquivo = fopen("pagamentos.dat", "r");

    if(arquivo == NULL) {
        return;
    }

    while(fgets(linha, sizeof(linha), arquivo)) {
        if(sscanf(
            linha,
            "%d|%f|%f|%f|%f|%f|%39[^|]|%19[^\n]",
            &idVenda,
            &valorPago,
            &valorDinheiro,
            &valorCartao,
            &desconto,
            &troco,
            tipoPagamento,
            tipoCartao
        ) == 8) {
            if(strcmp(tipoPagamento, "Dinheiro") == 0) {
                *dinheiro += valorDinheiro;
            }
            else if(strcmp(tipoPagamento, "Cartao") == 0) {
                *cartao += valorCartao;
            }
            else if(strcmp(tipoPagamento, "Misto") == 0) {
                *mistoDinheiro += valorDinheiro;
                *mistoCartao += valorCartao;
            }
        }
        else if(sscanf(linha, "%f|%39[^\n]", &valorAntigo, tipoPagamento) == 2) {
            if(strcmp(tipoPagamento, "Dinheiro") == 0) {
                *dinheiro += valorAntigo;
            }
            else if(strcmp(tipoPagamento, "Cartao") == 0) {
                *cartao += valorAntigo;
            }
            else if(strcmp(tipoPagamento, "Misto") == 0) {
                *mistoCartao += valorAntigo;
            }
        }
    }

    fclose(arquivo);
}


static void lerResumoVendas(
    int *qtdVendas,
    float *faturamento,
    float *maiorVenda
) {
    FILE *arquivo;
    Venda venda;

    *qtdVendas = 0;
    *faturamento = 0;
    *maiorVenda = 0;

    arquivo = fopen("vendas.dat", "r");

    if(arquivo == NULL) {
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
        (*qtdVendas)++;
        *faturamento += venda.totalFinal;

        if(venda.totalFinal > *maiorVenda) {
            *maiorVenda = venda.totalFinal;
        }
    }

    fclose(arquivo);
}


static void mostrarProdutoMaisVendido() {
    FILE *arquivo;
    char linha[300];
    int codigos[200];
    int quantidades[200];
    char descricoes[200][100];
    int totalProdutos = 0;
    int i;
    int posicao = -1;
    int idVenda;
    int numItem;
    int codigoProduto;
    int quantidade;
    float precoUnitario;
    float totalItem;
    char descricaoProduto[100];
    char statusPagamento = 'p';

    arquivo = fopen("itens.venda.dat", "r");

    if(arquivo == NULL) {
        printf(COR_AVISO "Produto mais vendido: nenhum item vendido ainda.\n" COR_FIM);
        return;
    }

    while(fgets(linha, sizeof(linha), arquivo)) {
        if(sscanf(
            linha,
            "%d|%d|%d|%99[^|]|%f|%d|%f|%c",
            &idVenda,
            &numItem,
            &codigoProduto,
            descricaoProduto,
            &precoUnitario,
            &quantidade,
            &totalItem,
            &statusPagamento
        ) >= 7 && statusPagamento == 'p' && quantidade > 0) {
            posicao = -1;

            for(i = 0; i < totalProdutos; i++) {
                if(codigos[i] == codigoProduto) {
                    posicao = i;
                }
            }

            if(posicao == -1 && totalProdutos < 200) {
                codigos[totalProdutos] = codigoProduto;
                quantidades[totalProdutos] = quantidade;
                strcpy(descricoes[totalProdutos], descricaoProduto);
                totalProdutos++;
            }
            else if(posicao != -1) {
                quantidades[posicao] += quantidade;
            }
        }
    }

    fclose(arquivo);

    if(totalProdutos == 0) {
        printf(COR_AVISO "Produto mais vendido: nenhum item vendido ainda.\n" COR_FIM);
        return;
    }

    posicao = 0;

    for(i = 1; i < totalProdutos; i++) {
        if(quantidades[i] > quantidades[posicao]) {
            posicao = i;
        }
    }

    printf(
        "Produto mais vendido: %s (%d unidade(s))\n",
        descricoes[posicao],
        quantidades[posicao]
    );
}


float calcularDinheiroDisponivelCaixa() {
    float dinheiro;
    float cartao;
    float mistoDinheiro;
    float mistoCartao;
    float valorAbertura;
    float totalSangrias;

    somarPagamentos(&dinheiro, &cartao, &mistoDinheiro, &mistoCartao);

    valorAbertura = lerValorAberturaCaixa();
    totalSangrias = calcularTotalSangrias();

    return valorAbertura + dinheiro + mistoDinheiro - totalSangrias;
}


void abrirCaixa() {
    FILE *arquivo;
    Caixa caixa;

    if(!validarAdministrador()) {
        return;
    }

    if(caixaEstaAberto()) {
        printf("\n");
        printf(COR_AVISO "=====================================\n" COR_FIM);
        printf(COR_AVISO "O CAIXA JA ESTA ABERTO!\n" COR_FIM);
        printf(COR_AVISO "=====================================\n" COR_FIM);
        return;
    }

    printf("\n\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|         ABRIR CAIXA            |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);

    do {
        printf(COR_ENTRADA "Digite o valor inicial do caixa: R$ " COR_FIM);
        caixa.valorInicial = lerFloat("");

        if(caixa.valorInicial < 0) {
            beepErro();
            printf(COR_ERRO "\nO valor de abertura deve ser maior ou igual a zero.\n" COR_FIM);
            registrarLog("ERRO: abertura de caixa com valor negativo");
        }

    } while(caixa.valorInicial < 0);

    caixa.statusCaixa = 1;

    arquivo = fopen(ARQ_CAIXA, "w");

    if(arquivo == NULL) {
        beepErro();
        printf(COR_ERRO "\nErro ao abrir arquivo!\n" COR_FIM);
        registrarLog("ERRO: nao foi possivel abrir caixa.dat");
        return;
    }

    fprintf(
        arquivo,
        "%.2f|%d\n",
        caixa.valorInicial,
        caixa.statusCaixa
    );

    fclose(arquivo);

    caixaAberto = 1;

    beepSucesso();
    printf(COR_SUCESSO "\nCaixa aberto com sucesso!\n" COR_FIM);
    registrarLog("Caixa aberto");
}



void realizarSangria() {
    FILE *arquivo;
    float valorSangria;
    float dinheiroDisponivel;
    char log[200];

    if(!validarAdministrador()) {
        return;
    }

    if(!caixaEstaAberto()) {
        beepErro();
        printf("\n");
        printf(COR_ERRO "=====================================\n" COR_FIM);
        printf(COR_ERRO "CAIXA FECHADO!\n" COR_FIM);
        printf(COR_ERRO "Nao e possivel fazer sangria.\n" COR_FIM);
        printf(COR_ERRO "=====================================\n" COR_FIM);
        registrarLog("ERRO: tentativa de sangria com caixa fechado");
        return;
    }

    dinheiroDisponivel = calcularDinheiroDisponivelCaixa();

    printf("\n\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|       REALIZAR SANGRIA         |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_TITULO "Dinheiro disponivel no caixa: R$ %.2f\n" COR_FIM, dinheiroDisponivel);
    printf(COR_TITULO "Valor minimo para troco.....: R$ %.2f\n" COR_FIM, MIN_TROCO);

    printf(COR_ENTRADA "Digite o valor da sangria: R$ " COR_FIM);
    valorSangria = lerFloat("");

    if(valorSangria <= 0) {
        beepErro();
        printf(COR_ERRO "\nValor invalido!\n" COR_FIM);
        registrarLog("ERRO: valor invalido em sangria");
        return;
    }

    if(valorSangria > dinheiroDisponivel - MIN_TROCO) {
        beepErro();
        printf(COR_ERRO "\nSangria nao permitida!\n" COR_FIM);
        printf(COR_ERRO "Deve sobrar pelo menos R$ %.2f para troco.\n" COR_FIM, MIN_TROCO);
        registrarLog("ERRO: sangria maior que dinheiro permitido");
        return;
    }

    arquivo = fopen("sangrias.dat", "a");

    if(arquivo == NULL) {
        beepErro();
        printf(COR_ERRO "\nErro ao abrir arquivo!\n" COR_FIM);
        registrarLog("ERRO: nao foi possivel salvar sangria");
        return;
    }

    fprintf(arquivo, "%.2f\n", valorSangria);

    fclose(arquivo);

    sprintf(log, "Sangria realizada - valor %.2f", valorSangria);
    registrarLog(log);

    beepSucesso();
    printf(COR_SUCESSO "\nSangria realizada com sucesso!\n" COR_FIM);
}


void fecharCaixa() {
    FILE *arquivo;
    float dinheiro;
    float cartao;
    float mistoDinheiro;
    float mistoCartao;
    float totalSangrias;
    float valorAbertura;
    float faturamento;
    float maiorVenda;
    float totalPagamentos;
    float saldoDinheiro;
    float ajuste;
    int qtdVendas;
    Caixa caixa;
    char log[200];

    if(!validarAdministrador()) {

        return;
    }

    if(!caixaEstaAberto()) {
        printf("\n");
        printf(COR_AVISO "=====================================\n" COR_FIM);
        printf(COR_AVISO "O CAIXA JA ESTA FECHADO!\n" COR_FIM);
        printf(COR_AVISO "=====================================\n" COR_FIM);
        return;
    }

    somarPagamentos(&dinheiro, &cartao, &mistoDinheiro, &mistoCartao);
    lerResumoVendas(&qtdVendas, &faturamento, &maiorVenda);

    valorAbertura = lerValorAberturaCaixa();
    totalSangrias = calcularTotalSangrias();
    totalPagamentos = dinheiro + cartao + mistoDinheiro + mistoCartao;
    saldoDinheiro = valorAbertura + dinheiro + mistoDinheiro - totalSangrias;
    ajuste = faturamento - totalPagamentos;

    printf("\n\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|         FECHAR CAIXA           |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_TITULO "Quantidade de vendas.............: %d\n" COR_FIM, qtdVendas);
    printf(COR_SUCESSO "Total vendido / faturamento......: R$ %.2f\n" COR_FIM, faturamento);
    printf(COR_TITULO "Valor de abertura................: R$ %.2f\n" COR_FIM, valorAbertura);
    printf(COR_TITULO "Dinheiro.........................: R$ %.2f\n" COR_FIM, dinheiro);
    printf(COR_TITULO "Cartao...........................: R$ %.2f\n" COR_FIM, cartao);
    printf(COR_TITULO "Misto - parte em dinheiro........: R$ %.2f\n" COR_FIM, mistoDinheiro);
    printf(COR_TITULO "Misto - parte em cartao..........: R$ %.2f\n" COR_FIM, mistoCartao);
    printf(COR_AVISO "Sangrias.........................: R$ %.2f\n" COR_FIM, totalSangrias);
    printf(COR_TITULO "Saldo em dinheiro no caixa.......: R$ %.2f\n" COR_FIM, saldoDinheiro);
    printf(COR_TITULO "Ajuste...........................: R$ %.2f\n" COR_FIM, ajuste);
    printf(COR_TITULO "Maior venda......................: R$ %.2f\n" COR_FIM, maiorVenda);
    mostrarProdutoMaisVendido();
    printf(COR_MENU "+================================+\n" COR_FIM);

    if(ajuste > 0.01f || ajuste < -0.01f) {
        beepErro();
        printf(COR_ERRO "\nATENCAO: O caixa nao podera ser fechado porque ha divergencia de valores.\n" COR_FIM);
        printf(COR_ERRO "Confira os pagamentos e ajuste os valores antes de finalizar.\n" COR_FIM);
        registrarLog("ATENCAO: fechamento de caixa com divergencia");
        return;
    }

    caixa.valorInicial = valorAbertura;
    caixa.statusCaixa = 0;

    arquivo = fopen(ARQ_CAIXA, "w");

    if(arquivo != NULL) {
        fprintf(
            arquivo,
            "%.2f|%d\n",
            caixa.valorInicial,
            caixa.statusCaixa
        );
        fclose(arquivo);
    }

    caixaAberto = 0;

    sprintf(log, "Fechamento de caixa - faturamento %.2f", faturamento);
    registrarLog(log);

    beepSucesso();
    printf(COR_SUCESSO "\nCaixa fechado com sucesso!\n" COR_FIM);
}
