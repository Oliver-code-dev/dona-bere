#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "produtos.h"
#include "cores.h"
#include "entrada.h"


void padronizarDescricao(char *texto)
{
    int i;
    int novaPalavra = 1;
    for(i = 0; texto[i] != '\0'; i++)
    {
        if(texto[i] == ' ')
        {
            novaPalavra = 1;
        }
        else
        {
            if(novaPalavra)
            {
                texto[i] = toupper(texto[i]);
                novaPalavra = 0;
            }
            else
            {
                texto[i] = tolower(texto[i]);
            }
        }
    }
}


int gerarCodigoProduto()
{
    FILE *arquivo;

    int contador = 0;
    char linha[300];

    arquivo = fopen("produtos.dat", "r");

    if(arquivo == NULL){
        return 1;
    }

    while(fgets(linha, sizeof(linha), arquivo)){
        contador++;
    }

    fclose(arquivo);

    return contador + 1;
}


float calcularPrecoVenda(float precoCompra, float margemLucro)
{
    return precoCompra * (1 + (margemLucro / 100));
}


void cadastrarProduto()
{
    Produto produto;

    FILE *arquivo;

    int opcao = 0;
    int categoria = 0;

    produto.codigoProduto = gerarCodigoProduto();

    printf("\n\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|      CADASTRO DE PRODUTO       |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);

    printf(COR_ENTRADA "Descricao do produto: " COR_FIM);

    scanf(" %[^\n]", produto.descricao);

    padronizarDescricao(produto.descricao);

    do
    {
        printf(COR_TITULO "\nEscolha a categoria:\n" COR_FIM);
        printf(COR_MENU "[1] - Alimento\n" COR_FIM);
        printf(COR_MENU "[2] - Limpeza\n" COR_FIM);
        printf(COR_MENU "[3] - Panificacao\n" COR_FIM);

        printf(COR_ENTRADA "Opcao: " COR_FIM);
        categoria = lerInteiro("");

        switch(categoria){
            case 1:
                strcpy(produto.categoria, "Alimento");
                break;

            case 2:
                strcpy(produto.categoria, "Limpeza");
                break;

            case 3:
                strcpy(produto.categoria, "Panificacao");
                break;

            default:
            printf(COR_ERRO "\nCategoria invalida!\n" COR_FIM);
                break;
        }

    } while(categoria < 1 || categoria > 3);

    do{
        printf(COR_ENTRADA "Preco de compra: R$ " COR_FIM);
        produto.precoCompra = lerFloat("");

        if(produto.precoCompra <= 0)
        {
            printf(COR_ERRO "\nO preco deve ser maior que zero!\n" COR_FIM);
        }

    } while(produto.precoCompra <= 0);

    do
    {
        printf(COR_ENTRADA "Margem de lucro (%%): " COR_FIM);
        produto.margemLucro = lerFloat("");

        if(produto.margemLucro <= 0){
            printf(COR_ERRO "\nA margem deve ser maior que zero!\n" COR_FIM);
        }

    } while(produto.margemLucro <= 0);

    produto.precoVenda = calcularPrecoVenda(produto.precoCompra, produto.margemLucro);

    do
    {
        printf(COR_ENTRADA "Quantidade em estoque: " COR_FIM);
        produto.estoqueAtual = lerInteiro("");

        if(produto.estoqueAtual < 0){
            printf(COR_ERRO "\nO estoque nao pode ser negativo!\n" COR_FIM);
        }

    } while(produto.estoqueAtual < 0);

    do
    {
        printf(COR_ENTRADA "Estoque minimo: " COR_FIM);
        produto.estoqueMinimo = lerInteiro("");

        if(produto.estoqueMinimo < 0)
        {
            printf(COR_ERRO "\nO estoque minimo nao pode ser negativo!\n" COR_FIM);
        }

    } while(produto.estoqueMinimo < 0);

    do
    {
        printf("\n\n");
        printf(COR_MENU "+================================+\n" COR_FIM);
        printf(COR_MENU "|       RESUMO DO PRODUTO        |\n" COR_FIM);
        printf(COR_MENU "+================================+\n" COR_FIM);

        printf(COR_TITULO "Codigo...........: %03d\n" COR_FIM, produto.codigoProduto);
        printf(COR_TITULO "Descricao........: %s\n" COR_FIM, produto.descricao);
        printf(COR_TITULO "Categoria........: %s\n" COR_FIM, produto.categoria);
        printf(COR_TITULO "Preco Compra.....: R$ %.2f\n" COR_FIM, produto.precoCompra);
        printf(COR_TITULO "Margem Lucro.....: %.2f%%\n" COR_FIM, produto.margemLucro);
        printf(COR_SUCESSO "Preco Venda......: R$ %.2f\n" COR_FIM, produto.precoVenda);
        printf(COR_TITULO "Estoque Atual....: %d\n" COR_FIM, produto.estoqueAtual);
        printf(COR_TITULO "Estoque Minimo...: %d\n" COR_FIM, produto.estoqueMinimo);

        printf(COR_TITULO "\nOs dados estao corretos?\n" COR_FIM);
        printf(COR_MENU "[1] - Sim\n" COR_FIM);
        printf(COR_MENU "[2] - Corrigir\n" COR_FIM);

        printf(COR_ENTRADA "Opcao: " COR_FIM);
        opcao = lerInteiro("");

        if(opcao == 2)
        {
            int campo;

            printf(COR_TITULO "\nQual campo deseja corrigir?\n" COR_FIM);
            printf(COR_MENU "[1] - Descricao\n" COR_FIM);
            printf(COR_MENU "[2] - Categoria\n" COR_FIM);
            printf(COR_MENU "[3] - Preco Compra\n" COR_FIM);
            printf(COR_MENU "[4] - Margem Lucro\n" COR_FIM);
            printf(COR_MENU "[5] - Estoque Atual\n" COR_FIM);
            printf(COR_MENU "[6] - Estoque Minimo\n" COR_FIM);

            printf(COR_ENTRADA "Opcao: " COR_FIM);
            campo = lerInteiro("");

            switch(campo)
            {
                case 1:
                    printf(COR_ENTRADA "Nova descricao: " COR_FIM);
                    scanf(" %[^\n]", produto.descricao);
                    padronizarDescricao(produto.descricao);
                    break;

                case 2:
                    do
                    {
                        printf(COR_TITULO "\nEscolha a categoria:\n" COR_FIM);
                        printf(COR_MENU "[1] - Alimento\n" COR_FIM);
                        printf(COR_MENU "[2] - Limpeza\n" COR_FIM);
                        printf(COR_MENU "[3] - Panificacao\n" COR_FIM);

                        printf(COR_ENTRADA "Opcao: " COR_FIM);
                        categoria = lerInteiro("");

                        switch(categoria)
                        {
                            case 1:
                                strcpy(produto.categoria, "Alimento");
                                break;

                            case 2:
                                strcpy(produto.categoria, "Limpeza");
                                break;

                            case 3:
                                strcpy(produto.categoria, "Panificacao");
                                break;

                            default:
                                printf(COR_ERRO "\nCategoria invalida!\n" COR_FIM);
                                break;
                        }

                    } while(categoria < 1 || categoria > 3);
                    break;

                case 3:
                    do
                    {
                        printf(COR_ENTRADA "Novo preco de compra: " COR_FIM);
                        produto.precoCompra = lerFloat("");

                        if(produto.precoCompra <= 0)
                        {
                            printf(COR_ERRO "\nO preco deve ser maior que zero!\n" COR_FIM);
                        }
                    } while(produto.precoCompra <= 0);
                    break;

                case 4:

                    do
                    {
                        printf(COR_ENTRADA "Nova margem de lucro: " COR_FIM);
                        produto.margemLucro = lerFloat("");

                        if(produto.margemLucro <= 0)
                        {
                            printf(COR_ERRO "\nA margem deve ser maior que zero!\n" COR_FIM);
                        }
                    } while(produto.margemLucro <= 0);
                    break;

                case 5:
                    do
                    {
                        printf(COR_ENTRADA "Novo estoque atual: " COR_FIM);
                        produto.estoqueAtual = lerInteiro("");

                        if(produto.estoqueAtual < 0)
                        {
                            printf(COR_ERRO "\nO estoque nao pode ser negativo!\n" COR_FIM);
                        }
                    } while(produto.estoqueAtual < 0);
                    break;

                case 6:
                    do
                    {
                        printf(COR_ENTRADA "Novo estoque minimo: " COR_FIM);
                        produto.estoqueMinimo = lerInteiro("");

                        if(produto.estoqueMinimo < 0)
                        {
                            printf(COR_ERRO "\nO estoque minimo nao pode ser negativo!\n" COR_FIM);
                        }
                    } while(produto.estoqueMinimo < 0);
                    break;

                default:
                    printf(COR_ERRO "\nCampo invalido!\n" COR_FIM);
                    break;
            }

            produto.precoVenda = calcularPrecoVenda(produto.precoCompra, produto.margemLucro);
        }

    } while(opcao != 1);

    arquivo = fopen("produtos.dat", "a");

    if(arquivo == NULL)
    {
        printf(COR_ERRO "\nErro ao abrir arquivo!\n" COR_FIM);
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
        produto.estoqueMinimo);

    fclose(arquivo);

    printf(COR_SUCESSO "\nProduto cadastrado com sucesso!\n" COR_FIM);
}


void listagemProdutos()
{
    FILE *arquivo;

    Produto produto;

    arquivo = fopen("produtos.dat", "r");

    if(arquivo == NULL){
        printf(COR_AVISO "\nNenhum produto cadastrado!\n" COR_FIM);
        return;
    }

    printf("\n\n");
    printf(COR_MENU "+================================================================================+\n" COR_FIM);
    printf(COR_MENU "|                           LISTAGEM DE PRODUTOS                                |\n" COR_FIM);
    printf(COR_MENU "+================================================================================+\n" COR_FIM);

    while(fscanf(arquivo, "%d|%99[^|]|%49[^|]|%f|%f|%f|%d|%d\n",
            &produto.codigoProduto,
            produto.descricao,
            produto.categoria,
            &produto.precoCompra,
            &produto.margemLucro,
            &produto.precoVenda,
            &produto.estoqueAtual,
            &produto.estoqueMinimo
        ) != EOF){
        printf(COR_TITULO "Codigo...........: %03d\n" COR_FIM, produto.codigoProduto);
        printf(COR_TITULO "Descricao........: %s\n" COR_FIM, produto.descricao);
        printf(COR_TITULO "Categoria........: %s\n" COR_FIM, produto.categoria);
        printf(COR_TITULO "Preco Compra.....: R$ %.2f\n" COR_FIM, produto.precoCompra);
        printf(COR_TITULO "Margem Lucro.....: %.2f%%\n" COR_FIM, produto.margemLucro);
        printf(COR_SUCESSO "Preco Venda......: R$ %.2f\n" COR_FIM, produto.precoVenda);
        printf(COR_TITULO "Estoque Atual....: %d\n" COR_FIM, produto.estoqueAtual);
        printf(COR_TITULO "Estoque Minimo...: %d\n" COR_FIM, produto.estoqueMinimo);

        if(produto.estoqueAtual <= produto.estoqueMinimo){
            printf(COR_ERRO ">>> PRODUTO NO VERMELHO: REPOR URGENTE <<<\n" COR_FIM);
        }

        printf(COR_MENU "+================================================================================+\n" COR_FIM);
    }

    fclose(arquivo);
}


void excluirProduto()
{
    FILE *arquivo;
    FILE *temp;

    Produto produto;

    int codigoBusca;
    int encontrado = 0;

    printf("\n\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|        EXCLUIR PRODUTO         |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);

    printf(COR_ENTRADA "Digite o codigo do produto: " COR_FIM);
    codigoBusca = lerInteiro("");

    arquivo = fopen("produtos.dat", "r");

    if(arquivo == NULL){
        printf(COR_ERRO "\nErro ao abrir produtos.dat\n" COR_FIM);
        return;
    }

    temp = fopen("temp.dat", "w");

    if(temp == NULL){
        printf(COR_ERRO "\nErro ao criar arquivo temporario\n" COR_FIM);
        fclose(arquivo);
        return;
    }

    while(fscanf(arquivo,"%d|%99[^|]|%49[^|]|%f|%f|%f|%d|%d\n",
            &produto.codigoProduto,
            produto.descricao,
            produto.categoria,
            &produto.precoCompra,
            &produto.margemLucro,
            &produto.precoVenda,
            &produto.estoqueAtual,
            &produto.estoqueMinimo
        ) != EOF){
        if(produto.codigoProduto == codigoBusca){
            encontrado = 1;

            printf(COR_SUCESSO "\n=================================\n" COR_FIM);
            printf(COR_SUCESSO "PRODUTO EXCLUIDO COM SUCESSO!\n" COR_FIM);
            printf(COR_SUCESSO "=================================\n" COR_FIM);

            continue;
        }

        fprintf(temp,"%d|%s|%s|%.2f|%.2f|%.2f|%d|%d\n",
            produto.codigoProduto,
            produto.descricao,
            produto.categoria,
            produto.precoCompra,
            produto.margemLucro,
            produto.precoVenda,
            produto.estoqueAtual,
            produto.estoqueMinimo);
    }

    fclose(arquivo);
    fclose(temp);

    remove("produtos.dat");
    rename("temp.dat", "produtos.dat");

    if(!encontrado)
    {
        printf("\nProduto nao encontrado!\n");
    }
}


void editarProduto()
{
    FILE *arquivo;
    FILE *temp;
    Produto produto;
    int codigoBusca;
    int encontrado = 0;
    int opcao = 0;
    int categoria = 0;

    printf("\n\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|         EDITAR PRODUTO         |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);

    printf(COR_ENTRADA "Digite o codigo do produto (0 para voltar): " COR_FIM);
    codigoBusca = lerInteiro("");

    if(codigoBusca == 0)
    {
        printf(COR_AVISO "\nVoltando...\n" COR_FIM);
        return;
    }

    arquivo = fopen("produtos.dat", "r");

    if(arquivo == NULL)
    {
        printf(COR_AVISO "\nNenhum produto cadastrado.\n" COR_FIM);
        return;
    }

    temp = fopen("temp_produtos.dat", "w");

    if(temp == NULL)
    {
        fclose(arquivo);
        printf(COR_ERRO "\nErro ao criar arquivo temporario.\n" COR_FIM);
        return;
    }

    while(fscanf(arquivo,"%d|%99[^|]|%49[^|]|%f|%f|%f|%d|%d\n",
            &produto.codigoProduto,
            produto.descricao,
            produto.categoria,
            &produto.precoCompra,
            &produto.margemLucro,
            &produto.precoVenda,
            &produto.estoqueAtual,
            &produto.estoqueMinimo
        ) != EOF)
    {
        if(produto.codigoProduto == codigoBusca)
        {
            encontrado = 1;

            do
            {
                printf(COR_SUCESSO "\nProduto encontrado: %s\n" COR_FIM, produto.descricao);
                printf(COR_MENU "[1] - Descricao\n" COR_FIM);

                printf(COR_MENU "[2] - Categoria\n" COR_FIM);
                printf(COR_MENU "[3] - Preco de compra\n" COR_FIM);
                printf(COR_MENU "[4] - Margem de lucro\n" COR_FIM);
                printf(COR_MENU "[5] - Estoque atual\n" COR_FIM);
                printf(COR_MENU "[6] - Estoque minimo\n" COR_FIM);
                printf(COR_MENU "[7] - Voltar\n" COR_FIM);
                printf(COR_ENTRADA "Opcao: " COR_FIM);
                opcao = lerInteiro("");

                switch(opcao)
                {
                    case 1:
                        printf(COR_ENTRADA "Nova descricao: " COR_FIM);
                        scanf(" %[^\n]", produto.descricao);
                        padronizarDescricao(produto.descricao);
                        break;

                    case 2:
                        do
                        {
                            printf(COR_MENU "[1] - Alimento\n" COR_FIM);
                            printf(COR_MENU "[2] - Limpeza\n" COR_FIM);
                            printf(COR_MENU "[3] - Panificacao\n" COR_FIM);
                            printf(COR_MENU "[0] - Cancelar\n" COR_FIM);
                            printf(COR_ENTRADA "Opcao: " COR_FIM);
                            categoria = lerInteiro("");

                            if(categoria == 0)
                            {
                                break;
                            }
                            else if(categoria == 1)
                            {
                                strcpy(produto.categoria, "Alimento");
                            }
                            else if(categoria == 2)
                            {
                                strcpy(produto.categoria, "Limpeza");
                            }
                            else if(categoria == 3)
                            {
                                strcpy(produto.categoria, "Panificacao");
                            }
                            else
                            {
                                printf(COR_ERRO "\nCategoria invalida!\n" COR_FIM);
                            }
                        } while(categoria < 0 || categoria > 3);
                        break;

                    case 3:
                        do
                        {
                            printf(COR_ENTRADA "Novo preco de compra: " COR_FIM);
                            produto.precoCompra = lerFloat("");

                            if(produto.precoCompra <= 0)
                            {
                                printf(COR_ERRO "\nO preco deve ser maior que zero!\n" COR_FIM);
                            }
                        } while(produto.precoCompra <= 0);
                        break;

                    case 4:
                        do
                        {
                            printf(COR_ENTRADA "Nova margem de lucro: " COR_FIM);
                            produto.margemLucro = lerFloat("");

                            if(produto.margemLucro <= 0)
                            {
                                printf(COR_ERRO "\nA margem deve ser maior que zero!\n" COR_FIM);
                            }
                        } while(produto.margemLucro <= 0);
                        break;

                    case 5:
                        do
                        {
                            printf(COR_ENTRADA "Novo estoque atual: " COR_FIM);
                            produto.estoqueAtual = lerInteiro("");

                            if(produto.estoqueAtual < 0)
                            {
                                printf(COR_ERRO "\nO estoque nao pode ser negativo!\n" COR_FIM);
                            }
                        } while(produto.estoqueAtual < 0);

                        break;

                    case 6:
                        do
                        {
                            printf(COR_ENTRADA "Novo estoque minimo: " COR_FIM);
                            produto.estoqueMinimo = lerInteiro("");

                            if(produto.estoqueMinimo < 0)
                            {
                                printf(COR_ERRO "\nO estoque minimo nao pode ser negativo!\n" COR_FIM);
                            }
                        } while(produto.estoqueMinimo < 0);
                        break;

                    case 7:
                        break;

                    default:
                        printf(COR_ERRO "\nOpcao invalida!\n" COR_FIM);
                        break;
                }
            } while(opcao < 1 || opcao > 7);

            produto.precoVenda = calcularPrecoVenda(produto.precoCompra, produto.margemLucro);
            printf(COR_SUCESSO "\nProduto atualizado!\n" COR_FIM);
        }

        fprintf(temp,"%d|%s|%s|%.2f|%.2f|%.2f|%d|%d\n",
            produto.codigoProduto,
            produto.descricao,
            produto.categoria,
            produto.precoCompra,
            produto.margemLucro,
            produto.precoVenda,
            produto.estoqueAtual,
            produto.estoqueMinimo);
    }

    fclose(arquivo);
    fclose(temp);

    remove("produtos.dat");
    rename("temp_produtos.dat", "produtos.dat");

    if(!encontrado)
    {
        printf(COR_AVISO "\nProduto nao encontrado!\n" COR_FIM);
    }
}


int buscarProduto(int codigoBusca, Produto *produto)
{
    FILE *arquivo;

    arquivo = fopen("produtos.dat", "r");

    if(arquivo == NULL){
        return 0;
    }

    while(fscanf(arquivo,"%d|%99[^|]|%49[^|]|%f|%f|%f|%d|%d\n",
            &produto->codigoProduto,
            produto->descricao,
            produto->categoria,
            &produto->precoCompra,
            &produto->margemLucro,
            &produto->precoVenda,
            &produto->estoqueAtual,
            &produto->estoqueMinimo
        ) != EOF){
        if(produto->codigoProduto == codigoBusca){
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}
