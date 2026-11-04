#include <stdio.h>
#include <string.h>
#include <time.h>

#include "structs.h"
#include "pagamentos.h"
#include "caixa.h"
#include "vendas.h"
#include "cores.h"
#include "entrada.h"

#define DESCONTO_DEBITO 5.0f


void beepErro() {
    printf("\a");
}


void beepSucesso() {
    printf("\a\a");
}


void registrarLog(char mensagem[]) {
    FILE *arquivo;
    time_t tempoAtual;
    struct tm *infoTempo;
    char data[20];
    char hora[10];

    tempoAtual = time(NULL);
    infoTempo = localtime(&tempoAtual);

    strftime(data, 20, "%d/%m/%Y", infoTempo);
    strftime(hora, 10, "%H:%M", infoTempo);

    arquivo = fopen("logs.txt", "a");

    if(arquivo == NULL) {
        return;
    }

    fprintf(arquivo, "[%s %s] %s\n", data, hora, mensagem);

    fclose(arquivo);
}


static void iniciarPagamento(int idVenda, Pagamento *pagamento) {
    pagamento->idPagamento = idVenda;
    pagamento->idVenda = idVenda;
    pagamento->valorPago = 0;
    pagamento->valorDinheiro = 0;
    pagamento->valorCartao = 0;
    pagamento->desconto = 0;
    pagamento->troco = 0;
    strcpy(pagamento->tipoPagamento, "");
    strcpy(pagamento->tipoCartao, "");
}


static int confirmarCartao() {
    int aprovado;

    printf(COR_TITULO "\nPagamento na maquininha:\n" COR_FIM);
    printf(COR_MENU "[1] - Pagamento OK\n" COR_FIM);
    printf(COR_MENU "[0] - Pagamento nao OK\n" COR_FIM);
    printf(COR_ENTRADA "Opcao: " COR_FIM);
    aprovado = lerInteiro("");

    if(aprovado == 1) {
        return 1;
    }

    return 0;
}


static int processarCartao(float valorBase, float *valorCartao, float *desconto, char tipoCartao[]) {
    int tipo;
    int opcao;

    while(1) {
        printf(COR_TITULO "\nEscolha o tipo de cartao:\n" COR_FIM);
        printf(COR_MENU "[1] - Debito\n" COR_FIM);

        printf(COR_MENU "[2] - Credito\n" COR_FIM);
        printf(COR_MENU "[0] - Cancelar\n" COR_FIM);
        printf(COR_ENTRADA "Opcao: " COR_FIM);
        tipo = lerInteiro("");

        if(tipo == 0) {
            return 0;
        }

        if(tipo == 1) {
            printf(COR_MENU "\nDEBITO\n" COR_FIM);
            printf(COR_MENU "[1] - Pagar valor total no debito com desconto de pagamento a vista\n" COR_FIM);
            printf(COR_MENU "[2] - Cancelar\n" COR_FIM);
            printf(COR_ENTRADA "Opcao: " COR_FIM);
            opcao = lerInteiro("");

            if(opcao == 2) {
                return 0;
            }

            if(opcao == 1) {
                if(!confirmarCartao()) {
                    beepErro();
                    printf(COR_ERRO "\nPagamento recusado. Escolha a forma de pagamento novamente.\n" COR_FIM);
                    return -1;
                }

                *desconto = valorBase * (DESCONTO_DEBITO / 100);
                *valorCartao = valorBase - *desconto;
                strcpy(tipoCartao, "Debito");
                return 1;
            }

            beepErro();
            printf(COR_ERRO "\nOpcao invalida!\n" COR_FIM);
            continue;
        }
        else if(tipo == 2) {
            printf(COR_MENU "\nCREDITO\n" COR_FIM);
            printf(COR_MENU "[1] - Pagar valor total no credito\n" COR_FIM);
            printf(COR_MENU "[2] - Cancelar\n" COR_FIM);
            printf(COR_ENTRADA "Opcao: " COR_FIM);
            opcao = lerInteiro("");

            if(opcao == 2) {
                return 0;
            }

            if(opcao == 1) {
                if(!confirmarCartao()) {
                    beepErro();
                    printf(COR_ERRO "\nPagamento recusado. Escolha a forma de pagamento novamente.\n" COR_FIM);
                    return -1;
                }

                *desconto = 0;
                *valorCartao = valorBase;
                strcpy(tipoCartao, "Credito");
                return 1;
            }

            beepErro();
            printf(COR_ERRO "\nOpcao invalida!\n" COR_FIM);
            continue;
        }
        else {
            beepErro();
            printf(COR_ERRO "\nTipo de cartao invalido!\n" COR_FIM);
        }
    }
}


static void salvarPagamento(Pagamento pagamento) {
    FILE *arquivo;

    arquivo = fopen("pagamentos.dat", "a");

    if(arquivo == NULL) {
        beepErro();
        printf(COR_ERRO "\nErro ao abrir pagamentos.dat!\n" COR_FIM);
        registrarLog("ERRO: nao foi possivel salvar pagamento");
        return;
    }

    fprintf(
        arquivo,

        "%d|%.2f|%.2f|%.2f|%.2f|%.2f|%s|%s\n",
        pagamento.idVenda,
        pagamento.valorPago,
        pagamento.valorDinheiro,
        pagamento.valorCartao,
        pagamento.desconto,
        pagamento.troco,
        pagamento.tipoPagamento,
        pagamento.tipoCartao
    );

    fclose(arquivo);
}


int realizarPagamento(int idVenda, float totalVenda, Pagamento *pagamento) {
    int opcao = 0;
    int pago = 0;
    int resultadoCartao = 0;
    float valorRecebido = 0;
    float valorCartaoInformado = 0;
    float restante = 0;
    char log[200];

    if(totalVenda <= 0) {
        beepErro();
        printf(COR_ERRO "\nValor da venda invalido para pagamento.\n" COR_FIM);
        registrarLog("ERRO: tentativa de pagamento com total menor ou igual a zero");
        return 0;
    }

    if(!caixaEstaAberto()) {
        beepErro();
        printf("\n");
        printf(COR_ERRO "=====================================\n" COR_FIM);
        printf(COR_ERRO "CAIXA FECHADO!\n" COR_FIM);
        printf(COR_ERRO "Abra o caixa antes do pagamento.\n" COR_FIM);
        printf(COR_ERRO "=====================================\n" COR_FIM);
        registrarLog("ERRO: tentativa de pagamento com caixa fechado");
        return 0;
    }

    iniciarPagamento(idVenda, pagamento);

    printf("\n\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|      REALIZAR PAGAMENTO        |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_TITULO "Valor total da venda: R$ %.2f\n" COR_FIM, totalVenda);

    do {
        printf(COR_TITULO "\nEscolha a forma de pagamento:\n" COR_FIM);
        printf(COR_MENU "[1] - Dinheiro\n" COR_FIM);
        printf(COR_MENU "[2] - Cartao\n" COR_FIM);
        printf(COR_MENU "[3] - Dinheiro + Cartao\n" COR_FIM);
        printf(COR_MENU "[0] - Cancelar\n" COR_FIM);
        printf(COR_ENTRADA "Opcao: " COR_FIM);
        opcao = lerInteiro("");

        pagamento->valorPago = 0;
        pagamento->valorDinheiro = 0;
        pagamento->valorCartao = 0;
        pagamento->desconto = 0;
        pagamento->troco = 0;
        strcpy(pagamento->tipoPagamento, "");
        strcpy(pagamento->tipoCartao, "");

        switch(opcao) {
            case 0:
                registrarLog("Pagamento cancelado pelo usuario");
                return 0;

            case 1:
                do {
                    printf(COR_ENTRADA "\nValor recebido em dinheiro: R$ " COR_FIM);
                    valorRecebido = lerFloat("");

                    if(valorRecebido <= 0) {
                        beepErro();
                        printf(COR_ERRO "\nValor invalido! Informe um valor maior que zero.\n" COR_FIM);
                        registrarLog("ERRO: valor invalido em pagamento em dinheiro");
                    }
                } while(valorRecebido <= 0);

                if(valorRecebido >= totalVenda) {
                    strcpy(pagamento->tipoPagamento, "Dinheiro");
                    strcpy(pagamento->tipoCartao, "Nenhum");

                    pagamento->valorDinheiro = totalVenda;
                    pagamento->valorCartao = 0;
                    pagamento->valorPago = totalVenda;
                    pagamento->troco = valorRecebido - totalVenda;
                    pago = 1;
                }
                else {
                    restante = totalVenda - valorRecebido;

                    printf(COR_AVISO "\nValor insuficiente. Faltam R$ %.2f\n" COR_FIM, restante);
                    printf(COR_AVISO "O restante sera pago no cartao.\n" COR_FIM);

                    resultadoCartao = processarCartao(
                        restante,
                        &pagamento->valorCartao,
                        &pagamento->desconto,
                        pagamento->tipoCartao
                    );

                    if(resultadoCartao == 1) {
                        strcpy(pagamento->tipoPagamento, "Misto");
                        pagamento->valorDinheiro = valorRecebido;
                        pagamento->valorPago =
                            pagamento->valorDinheiro + pagamento->valorCartao;
                        pagamento->troco = 0;
                        pago = 1;
                    }
                    else if(resultadoCartao == 0) {
                        registrarLog("Pagamento misto cancelado pelo usuario");
                        return 0;
                    }
                }
                break;

            case 2:
                do {
                    printf(COR_ENTRADA "\nValor que sera pago no cartao: R$ " COR_FIM);
                    valorCartaoInformado = lerFloat("");

                    if(valorCartaoInformado <= 0 || valorCartaoInformado > totalVenda) {
                        beepErro();
                    printf(COR_ERRO "\nValor invalido para cartao!\n" COR_FIM);
                    }

                } while(valorCartaoInformado <= 0 || valorCartaoInformado > totalVenda);

                resultadoCartao = processarCartao(
                    valorCartaoInformado,
                    &pagamento->valorCartao,
                    &pagamento->desconto,
                    pagamento->tipoCartao
                );

                if(resultadoCartao == 1) {
                    if(valorCartaoInformado < totalVenda) {
                        restante = totalVenda - valorCartaoInformado;

                        printf(COR_AVISO "\nRestante em dinheiro: R$ %.2f\n" COR_FIM, restante);
                        printf(COR_ENTRADA "Valor recebido em dinheiro: R$ " COR_FIM);
                        valorRecebido = lerFloat("");

                        if(valorRecebido < restante) {
                            beepErro();
                            printf(COR_ERRO "\nValor em dinheiro insuficiente!\n" COR_FIM);
                            registrarLog("ERRO: dinheiro insuficiente no misto cartao + dinheiro");
                            break;
                        }

                        strcpy(pagamento->tipoPagamento, "Misto");
                        pagamento->valorDinheiro = restante;
                        pagamento->valorPago =
                            pagamento->valorCartao + pagamento->valorDinheiro;
                        pagamento->troco = valorRecebido - restante;
                    }
                    else {
                        strcpy(pagamento->tipoPagamento, "Cartao");
                        pagamento->valorDinheiro = 0;
                        pagamento->valorPago = pagamento->valorCartao;
                        pagamento->troco = 0;
                    }

                    pago = 1;
                }
                else if(resultadoCartao == 0) {
                    registrarLog("Pagamento no cartao cancelado pelo usuario");
                    return 0;
                }

                break;

            case 3:
                do {
                    printf(COR_ENTRADA "\nValor em dinheiro: R$ " COR_FIM);
                    valorRecebido = lerFloat("");

                    if(valorRecebido <= 0) {
                        beepErro();
                        printf(COR_ERRO "\nValor em dinheiro invalido! Informe um valor maior que zero.\n" COR_FIM);
                        registrarLog("ERRO: valor invalido em pagamento misto");
                    }
                } while(valorRecebido <= 0);

                if(valorRecebido >= totalVenda) {
                    strcpy(pagamento->tipoPagamento, "Dinheiro");
                    strcpy(pagamento->tipoCartao, "Nenhum");
                    pagamento->valorDinheiro = totalVenda;
                    pagamento->valorCartao = 0;
                    pagamento->valorPago = totalVenda;
                    pagamento->troco = valorRecebido - totalVenda;
                    pago = 1;
                }
                else {
                    restante = totalVenda - valorRecebido;
                    printf(COR_AVISO "\nValor restante: R$ %.2f\n" COR_FIM, restante);

                    resultadoCartao = processarCartao(
                        restante,
                        &pagamento->valorCartao,
                        &pagamento->desconto,
                        pagamento->tipoCartao
                    );

                    if(resultadoCartao == 1) {
                        strcpy(pagamento->tipoPagamento, "Misto");
                        pagamento->valorDinheiro = valorRecebido;
                        pagamento->valorPago =
                            pagamento->valorDinheiro + pagamento->valorCartao;
                        pagamento->troco = 0;
                        pago = 1;
                    }
                    else if(resultadoCartao == 0) {
                        registrarLog("Pagamento misto cancelado pelo usuario");
                        return 0;
                    }
                }
                break;

            default:
                beepErro();
                printf(COR_ERRO "\nOpcao de pagamento invalida!\n" COR_FIM);
                registrarLog("ERRO: opcao de pagamento invalida");
                break;
        }

    } while(!pago);

    salvarPagamento(*pagamento);

    sprintf(
        log,
        "Pagamento realizado - venda %d - tipo %s - valor %.2f",
        pagamento->idVenda,
        pagamento->tipoPagamento,
        pagamento->valorPago
    );
    registrarLog(log);

    beepSucesso();
    printf(COR_SUCESSO "\nPagamento realizado com sucesso!\n" COR_FIM);

    return 1;
}


void gerarCupomFiscal(Venda venda, ItemVenda itens[], int qtdItens, Pagamento pagamento) {
    int i;

    printf("\n\n");
    printf(COR_MENU "============================================================\n" COR_FIM);
    printf(COR_MENU "                       MERCADO BERE                         \n" COR_FIM);
    printf(COR_MENU "                      CUPOM FISCAL                          \n" COR_FIM);
    printf(COR_MENU "============================================================\n" COR_FIM);
    printf(COR_TITULO "Venda: %03d\n" COR_FIM, venda.idVenda);
    printf(COR_TITULO "Data.: %s  Hora: %s\n" COR_FIM, venda.dataVenda, venda.horaVenda);
    printf(COR_MENU "------------------------------------------------------------\n" COR_FIM);

    printf(COR_MENU "COD  DESCRICAO                 QTD  VL.UNIT     TOTAL\n" COR_FIM);
    printf(COR_MENU "------------------------------------------------------------\n" COR_FIM);

    for(i = 0; i < qtdItens; i++) {
        printf(
            COR_TITULO "%03d  %-24s %3d  R$ %7.2f  R$ %7.2f\n" COR_FIM,
            itens[i].codigoProduto,
            itens[i].descricaoProduto,
            itens[i].quantidade,
            itens[i].precoUnitario,
            itens[i].totalItem
        );
    }

    printf(COR_MENU "------------------------------------------------------------\n" COR_FIM);
    printf(COR_TITULO "Subtotal..............: R$ %.2f\n" COR_FIM, venda.total);
    printf(COR_TITULO "Desconto..............: R$ %.2f\n" COR_FIM, venda.desconto);
    printf(COR_SUCESSO "Total final...........: R$ %.2f\n" COR_FIM, venda.totalFinal);
    printf(COR_TITULO "Forma de pagamento....: %s\n" COR_FIM, pagamento.tipoPagamento);

    if(strcmp(pagamento.tipoCartao, "Nenhum") != 0) {
        printf(COR_TITULO "Tipo de cartao........: %s\n" COR_FIM, pagamento.tipoCartao);
    }

    printf(COR_TITULO "Dinheiro..............: R$ %.2f\n" COR_FIM, pagamento.valorDinheiro);
    printf(COR_TITULO "Cartao................: R$ %.2f\n" COR_FIM, pagamento.valorCartao);
    printf(COR_SUCESSO "Troco.................: R$ %.2f\n" COR_FIM, pagamento.troco);
    printf(COR_MENU "============================================================\n" COR_FIM);
    printf(COR_SUCESSO "              OBRIGADO PELA PREFERENCIA!\n" COR_FIM);
    printf(COR_MENU "============================================================\n" COR_FIM);
}


static int pagamentoJaExiste(int idVendaBusca) {
    FILE *arquivo;
    char linha[300];
    int idVenda;
    float valorPago;
    float valorDinheiro;
    float valorCartao;
    float desconto;
    float troco;
    char tipoPagamento[40];
    char tipoCartao[20];

    arquivo = fopen("pagamentos.dat", "r");

    if(arquivo == NULL) {
        return 0;
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
            if(idVenda == idVendaBusca) {
                fclose(arquivo);
                return 1;
            }
        }
    }

    fclose(arquivo);
    return 0;
}


void realizarPagamentoPendente() {
    FILE *arquivo;
    Venda venda;
    Pagamento pagamento;
    int encontrou = 0;
    int idEscolhido;
    int vendaEncontrada = 0;

    if(!caixaEstaAberto()) {
        beepErro();
        printf(COR_ERRO "\nCAIXA FECHADO! Abra o caixa antes do pagamento.\n" COR_FIM);

        registrarLog("ERRO: tentativa de pagar venda pendente com caixa fechado");
        return;
    }

    arquivo = fopen("vendas.dat", "r");

    if(arquivo == NULL) {
        printf(COR_AVISO "\nNenhuma venda cadastrada.\n" COR_FIM);
        return;
    }

    printf(COR_MENU "\nVENDAS EM ABERTO\n" COR_FIM);
    printf(COR_MENU "-------------------------------------\n" COR_FIM);

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
        if(!pagamentoJaExiste(venda.idVenda)) {
            if(venda.totalFinal <= 0) {
                printf(
                    COR_ERRO "Venda %03d ignorada: total zerado nao pode ser pago.\n" COR_FIM,
                    venda.idVenda
                );
            }
            else {
                encontrou = 1;
                printf(
                    COR_TITULO "Venda %03d | Data %s | Total R$ %.2f\n" COR_FIM,
                    venda.idVenda,
                    venda.dataVenda,
                    venda.totalFinal
                );
            }
        }
    }

    fclose(arquivo);

    if(!encontrou) {
        printf(COR_AVISO "\nNao ha vendas em aberto.\n" COR_FIM);
        return;
    }

    printf(COR_MENU "-------------------------------------\n" COR_FIM);
    printf(COR_ENTRADA "Informe o numero da venda para pagar: " COR_FIM);
    idEscolhido = lerInteiro("");

    arquivo = fopen("vendas.dat", "r");

    if(arquivo == NULL) {
        printf(COR_ERRO "\nErro ao abrir vendas.dat.\n" COR_FIM);
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
        if(venda.idVenda == idEscolhido && !pagamentoJaExiste(venda.idVenda)) {
            vendaEncontrada = 1;

            if(venda.totalFinal <= 0) {
                beepErro();
                printf(COR_ERRO "\nEsta venda esta com total zerado e nao pode ser paga.\n" COR_FIM);
                printf(COR_ERRO "Ela provavelmente foi gerada antes da correcao do desconto de 100%%.\n" COR_FIM);
                continue;
            }

            if(realizarPagamento(venda.idVenda, venda.totalFinal, &pagamento)) {
                venda.desconto += pagamento.desconto;
                venda.totalFinal = venda.total - venda.desconto;

                atualizarVendaSalva(venda);
                atualizarStatusItensVenda(venda.idVenda, 'p');
                baixarEstoqueItensVenda(venda.idVenda);

                printf(COR_SUCESSO "\nVenda em aberto paga com sucesso!\n" COR_FIM);
                registrarLog("Venda em aberto paga pelo menu de pagamentos");
            }
            else {
                printf(COR_AVISO "\nVenda continua em aberto.\n" COR_FIM);
            }
        }
    }

    fclose(arquivo);

    if(!vendaEncontrada) {
        beepErro();
        printf(COR_ERRO "\nVenda nao encontrada ou ja paga.\n" COR_FIM);
    }
}
