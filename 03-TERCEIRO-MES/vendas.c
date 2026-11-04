#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "caixa.h"
#include "produtos.h"
#include "vendas.h"
#include "pagamentos.h"

int gerarCodigoVenda()
{
    FILE *arquivo;

    int contador = 0;

    char linha[300];

    arquivo = fopen("vendas.dat", "r");

    if(arquivo == NULL)
    {
        return 1;
    }

    while(fgets(linha, sizeof(linha), arquivo))
    {
        contador++;
    }

    fclose(arquivo);

    return contador + 1;
}

int verificarEstoque(
    int codigoProduto,
    int quantidadeDesejada
)
{
    FILE *arquivo;

    Produto produto;

    arquivo = fopen("produtos.dat", "r");

    if(arquivo == NULL)
    {
        printf("\nErro ao abrir produtos.dat\n");

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

        if(produto.codigoProduto == codigoProduto)
        {

            fclose(arquivo);

            if(produto.estoqueAtual >= quantidadeDesejada)
            {
                return 1;
            }
            else
            {
                return 0;
            }

        }
    }

    fclose(arquivo);

    return 0;
}

void atualizarEstoque(
    int codigoProduto,
    int quantidadeVendida
)
{
    FILE *arquivo;
    FILE *temp;

    Produto produto;

    arquivo = fopen("produtos.dat", "r");

    if(arquivo == NULL)
    {
        printf("\nErro ao abrir produtos.dat\n");

        return;
    }

    temp = fopen("temp.dat", "w");

    if(temp == NULL)
    {
        printf("\nErro ao criar arquivo temporario\n");

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

        if(produto.codigoProduto == codigoProduto)
        {
            produto.estoqueAtual -= quantidadeVendida;
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

void gerarDataHora(
    char data[],

    char hora[]
)
{
    time_t tempoAtual;

    struct tm *infoTempo;

    tempoAtual = time(NULL);

    infoTempo = localtime(&tempoAtual);

    strftime(
        data,
        20,
        "%d/%m/%Y",
        infoTempo
    );

    strftime(
        hora,
        10,
        "%H:%M",
        infoTempo
    );
}

void novaVenda()
{
        if(caixaAberto == 0)
    {
        printf("\n");

        printf("=====================================\n");

        printf("CAIXA FECHADO!\n");

        printf("Abra o caixa antes de vender.\n");

        printf("=====================================\n");

        return;
    }

    FILE *arquivo;

    Venda venda;
    Produto produto;

    int continuar = 1;

    float totalVenda = 0;

    venda.idVenda = gerarCodigoVenda();

    gerarDataHora(
        venda.dataVenda,
        venda.horaVenda
    );

    printf("\n\n");
    printf("+================================+\n");
    printf("|          NOVA VENDA            |\n");
    printf("+================================+\n");

    do
    {

        printf("Codigo do produto: ");
        scanf("%d", &venda.codigoProduto);

        if(
            !buscarProduto(
                venda.codigoProduto,
                &produto
            )
        )
        {
            printf("\nPRODUTO NAO ENCONTRADO!\n");

            return;
        }

        strcpy(
            venda.descricaoProduto,
            produto.descricao
        );

    
        venda.precoUnitario =
            produto.precoVenda;

        printf("\n");

        printf("Produto: %s\n",
            venda.descricaoProduto);

        printf("Preco: %.2f\n",
            venda.precoUnitario);

        printf("Estoque: %d\n",
        produto.estoqueAtual);

        printf("Quantidade: ");
        scanf("%d", &venda.quantidade);

        if(
            !verificarEstoque(
                venda.codigoProduto,
                venda.quantidade
            )
        )
        {
            printf("\n=================================\n");
            printf("ESTOQUE INSUFICIENTE!\n");
            printf("=================================\n");

            continue;
        }

        venda.totalItem =
            venda.precoUnitario * venda.quantidade;

        totalVenda += venda.totalItem;

        printf("\nItem adicionado com sucesso!\n");

        printf("\nTotal do item: R$ %.2f\n",
            venda.totalItem);

        printf("Total parcial da venda: R$ %.2f\n",
            totalVenda);

            printf("=====================================\n");
            printf("[1] - Adicionar outro item\n");
            printf("[2] - Finalizar venda\n");
            printf("[0] - Cancelar venda\n");
            printf("=====================================\n");

        printf("Opcao: ");
        scanf("%d", &continuar);

        if(continuar == 0)
        {
            printf("\n");

            printf("=====================================\n");
            printf("VENDA CANCELADA!\n");
            printf("=====================================\n");

            return;
        }

        arquivo = fopen("vendas.dat", "a");

        if(arquivo == NULL)
        {
            printf("\nErro ao abrir arquivo!\n");

            return;
        }

        fprintf(
            arquivo,
            "%d|%d|%s|%.2f|%d|%.2f|%s|%s\n",

            venda.idVenda,
            venda.codigoProduto,
            venda.descricaoProduto,
            venda.precoUnitario,
            venda.quantidade,
            venda.totalItem,
            venda.dataVenda,
            venda.horaVenda
        );

        
        
        
        
        
        
        
        fclose(arquivo);

        

        atualizarEstoque(
            venda.codigoProduto,
            venda.quantidade
        );

    } while(continuar == 1);

    printf("\n=================================\n");
    printf("TOTAL FINAL DA VENDA: R$ %.2f\n",
        totalVenda);
    printf("=================================\n");

    realizarPagamento(totalVenda);
}

void listagemVendas()
{
    FILE *arquivo;

    Venda venda;

    arquivo = fopen("vendas.dat", "r");

    if(arquivo == NULL)
    {
        printf("\nNenhuma venda cadastrada!\n");
        return;
    }

    printf("\n\n");
    printf("+================================================================================+\n");
    printf("|                             LISTAGEM DE VENDAS                                |\n");
    printf("+================================================================================+\n");

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

        printf("ID Venda........: %03d\n", venda.idVenda);
        printf("Codigo Produto..: %03d\n",
            venda.codigoProduto);

        printf("Descricao.......: %s\n",
            venda.descricaoProduto);

        printf("Preco Unitario..: R$ %.2f\n",
            venda.precoUnitario);

        printf("Quantidade......: %d\n",
            venda.quantidade);

        printf("Total Item......: R$ %.2f\n",
            venda.totalItem);

        printf("Data............: %s\n",
            venda.dataVenda);

        printf("Hora............: %s\n",
            venda.horaVenda);

        printf("+================================================================================+\n");
    }

    fclose(arquivo);
}
