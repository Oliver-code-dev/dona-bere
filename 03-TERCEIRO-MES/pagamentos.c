#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pagamentos.h"
#include "caixa.h"


void gerarCupomFiscal(
    float totalVenda,
    char tipoPagamento[]
)
{
    printf("\n\n");

    printf("=====================================\n");
    printf("           MERCADO BERE             \n");
    printf("=====================================\n");

    printf("CUPOM FISCAL SIMULADO\n");

    printf("-------------------------------------\n");

    printf("TOTAL DA VENDA: R$ %.2f\n", totalVenda);

    printf("FORMA PAGAMENTO: %s\n", tipoPagamento);

    printf("-------------------------------------\n");

    printf("OBRIGADO PELA PREFERENCIA!\n");

    printf("VOLTE SEMPRE!\n");

    printf("=====================================\n");
}


void realizarPagamento(float totalVenda)
{
    if(caixaAberto == 0)
    {
        printf("\n");
        printf("=====================================\n");
        printf("CAIXA FECHADO!\n");
        printf("Abra o caixa antes do pagamento.\n");
        printf("=====================================\n");
        return;
    }

    FILE *arquivo;

    Pagamento pagamento;

    int opcao = 0;
    int aprovado = 0;

    float valorDinheiro = 0;
    float valorCartao = 0;
    float troco = 0;
    float restante = 0;

    printf("\n\n");
    printf("+================================+\n");
    printf("|      REALIZAR PAGAMENTO       \n");
    printf("+================================+\n");

    printf("Valor total da venda: R$ %.2f\n", totalVenda);

    do
    {
        printf("\nEscolha a forma de pagamento:\n");
        printf("[1] - Dinheiro\n");
        printf("[2] - Cartao\n");
        printf("[3] - Dinheiro + Cartao\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:

                strcpy(pagamento.tipoPagamento, "Dinheiro");

                printf("\nValor recebido: R$ ");
                scanf("%f", &valorDinheiro);

                if(valorDinheiro < totalVenda)
                {
                    restante = totalVenda - valorDinheiro;

                    printf("\nValor insuficiente!\n");
                    printf("Faltam R$ %.2f\n", restante);

                    printf("\nDeseja completar no cartao?\n");
                    printf("[1] - Sim\n");
                    printf("[0] - Nao\n");

                    printf("Opcao: ");
                    scanf("%d", &aprovado);

                    if(aprovado == 1)
                    {
                        valorCartao = restante;

                        pagamento.valorPago =
                            valorDinheiro + valorCartao;

                        strcpy(pagamento.tipoPagamento, "Misto");

                        printf("\nProcessando cartao...\n");
                        printf("Pagamento aprovado!\n");

                        printf("\nPagamento realizado!\n");

                        printf("Dinheiro: R$ %.2f\n", valorDinheiro);
                        printf("Cartao: R$ %.2f\n", valorCartao);
                    }
                    else
                    {
                        printf("\nPagamento cancelado!\n");
                        return;
                    }
                }
                else
                {
                    troco = valorDinheiro - totalVenda;

                    pagamento.valorPago = valorDinheiro;

                    printf("\nPagamento realizado!\n");
                    printf("Troco: R$ %.2f\n", troco);
                }

                break;

            case 2:

                strcpy(pagamento.tipoPagamento, "Cartao");

                printf("\nProcessando pagamento...\n");

                printf("[1] - Aprovado\n");
                printf("[0] - Recusado\n");

                printf("Opcao: ");
                scanf("%d", &aprovado);

                if(aprovado == 1)
                {
                    pagamento.valorPago = totalVenda;

                    printf("\nPagamento aprovado!\n");
                    printf("Venda finalizada!\n");
                }
                else
                {
                    printf("\nPagamento recusado!\n");
                    printf("Escolha outra forma.\n");
                    return;
                }

                break;

            case 3:

                strcpy(pagamento.tipoPagamento, "Misto");

                printf("\nValor em dinheiro: R$ ");

                scanf("%f", &valorDinheiro);

                if(valorDinheiro > totalVenda)
                {
                    troco = valorDinheiro - totalVenda;

                    pagamento.valorPago = valorDinheiro;

                    printf("\nTroco: R$ %.2f\n", troco);
                    printf("\nPagamento realizado!\n");
                }
                else
                {
                    restante = totalVenda - valorDinheiro;

                    printf("\nValor restante no cartao: R$ %.2f\n", restante);

                    printf("\n[1] - Aprovado\n");
                    printf("[0] - Recusado\n");

                    printf("Opcao: ");
                    scanf("%d", &aprovado);

                    if(aprovado == 1)
                    {
                        valorCartao = restante;

                        pagamento.valorPago =
                            valorDinheiro + valorCartao;

                        printf("\nPagamento aprovado!\n");

                        printf("Dinheiro: R$ %.2f\n", valorDinheiro);
                        printf("Cartao: R$ %.2f\n", valorCartao);
                    }
                    else
                    {
                        printf("\nPagamento recusado!\n");
                        return;
                    }
                }

                break;

            default:
                printf("\nOpcao invalida!\n");
                break;
        }

    } while(opcao < 1 || opcao > 3);

    arquivo = fopen("pagamentos.dat", "a");

    if(arquivo == NULL)
    {
        printf("\nErro ao abrir arquivo!\n");
        return;
    }

    fprintf(
        arquivo,
        "%.2f|%s\n",

        pagamento.valorPago,
        pagamento.tipoPagamento
    );

    fclose(arquivo);

    printf("\nPagamento salvo com sucesso!\n");

    gerarCupomFiscal(
        totalVenda,
        pagamento.tipoPagamento
    );
}

