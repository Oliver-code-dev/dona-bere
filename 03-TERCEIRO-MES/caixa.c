#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "caixa.h"


int caixaAberto = 0;


void abrirCaixa()
{
    if(caixaAberto == 1)
    {
        printf("\n");
        printf("=====================================\n");
        printf("O CAIXA JA ESTA ABERTO!\n");
        printf("=====================================\n");
        return;
    }

    FILE *arquivo;
    Caixa caixa;

    printf("\n\n");
    printf("+================================+\n");
    printf("|         ABRIR CAIXA            |\n");
    printf("+================================+\n");

    printf("Digite o valor inicial do caixa: R$ ");
    scanf("%f", &caixa.valorInicial);

    caixa.statusCaixa = 1;

    arquivo = fopen("caixa.dat", "w");

    if(arquivo == NULL)
    {
        printf("\nErro ao abrir arquivo!\n");
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

    printf("\nCaixa aberto com sucesso!\n");
}


void realizarSangria()
{
    if(caixaAberto == 0)
    {
        printf("\n");
        printf("=====================================\n");
        printf("CAIXA FECHADO!\n");
        printf("Nao e possivel fazer sangria.\n");
        printf("=====================================\n");
        return;
    }

    FILE *arquivo;
    float valorSangria;

    printf("\n\n");
    printf("+================================+\n");
    printf("|       REALIZAR SANGRIA         |\n");
    printf("+================================+\n");

    printf("Digite o valor da sangria: R$ ");
    scanf("%f", &valorSangria);

    if(valorSangria <= 0)
    {
        printf("\nValor invalido!\n");
        return;

    }

    arquivo = fopen("sangrias.dat", "a");

    if(arquivo == NULL)
    {
        printf("\nErro ao abrir arquivo!\n");
        return;
    }

    fprintf(
        arquivo,
        "%.2f\n",
        valorSangria
    );

    fclose(arquivo);

    printf("\nSangria realizada com sucesso!\n");
}


void fecharCaixa()
{
    if(caixaAberto == 0)
    {
        printf("\n");
        printf("=====================================\n");
        printf("O CAIXA JA ESTA FECHADO!\n");
        printf("=====================================\n");
        return;
    }

    FILE *arquivoPagamentos;
    FILE *arquivoSangrias;

    float valorPagamento;
    float totalPagamentos = 0;

    float valorSangria;
    float totalSangrias = 0;

    float valorFinal = 0;

    char tipoPagamento[30];

    printf("\n\n");
    printf("+================================+\n");
    printf("|         FECHAR CAIXA           |\n");
    printf("+================================+\n");

    arquivoPagamentos = fopen("pagamentos.dat", "r");

    if(arquivoPagamentos != NULL)
    {
        while(
            fscanf(
                arquivoPagamentos,
                "%f|%29[^\n]\n",
                &valorPagamento,
                tipoPagamento
            ) != EOF
        )
        {
            totalPagamentos += valorPagamento;
        }

        fclose(arquivoPagamentos);
    }

    arquivoSangrias = fopen("sangrias.dat", "r");

    if(arquivoSangrias != NULL)
    {
        while(
            fscanf(
                arquivoSangrias,
                "%f\n",
                &valorSangria
            ) != EOF
        )
        {
            totalSangrias += valorSangria;
        }

        fclose(arquivoSangrias);

    }

    valorFinal = totalPagamentos - totalSangrias;

    printf("\n+================================+\n");
    printf("TOTAL DE PAGAMENTOS: R$ %.2f\n", totalPagamentos);
    printf("TOTAL DE SANGRIAS..: R$ %.2f\n", totalSangrias);
    printf("VALOR FINAL CAIXA..: R$ %.2f\n", valorFinal);
    printf("+================================+\n");

    caixaAberto = 0;

    printf("\nCaixa fechado com sucesso!\n");
}
