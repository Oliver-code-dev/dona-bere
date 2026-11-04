#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "produtos.h"


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


float calcularPrecoVenda(
    float precoCompra,
    float margemLucro
)
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
    printf("+================================+\n");

    printf("|      CADASTRO DE PRODUTO       |\n");
    printf("+================================+\n");

    printf("Descricao do produto: ");
    scanf(" %[^\n]", produto.descricao);

    padronizarDescricao(produto.descricao);

    do
    {
        printf("\nEscolha a categoria:\n");
        printf("[1] - Alimento\n");
        printf("[2] - Limpeza\n");
        printf("[3] - Panificacao\n");

        printf("Opcao: ");
        scanf("%d", &categoria);

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
                printf("\nCategoria invalida!\n");
                break;
        }

    } while(categoria < 1 || categoria > 3);

    do
    {
        printf("Preco de compra: R$ ");
        scanf("%f", &produto.precoCompra);

        if(produto.precoCompra <= 0)
        {
            printf("\nO preco deve ser maior que zero!\n");
        }

    } while(produto.precoCompra <= 0);

    do
    {
        printf("Margem de lucro (%%): ");
        scanf("%f", &produto.margemLucro);

        if(produto.margemLucro <= 0)
        {
            printf("\nA margem deve ser maior que zero!\n");
        }

    } while(produto.margemLucro <= 0);

    produto.precoVenda = calcularPrecoVenda(
        produto.precoCompra,
        produto.margemLucro
    );

    do
    {
        printf("Quantidade em estoque: ");
        scanf("%d", &produto.estoqueAtual);

        if(produto.estoqueAtual < 0)
        {
            printf("\nO estoque nao pode ser negativo!\n");
        }

    } while(produto.estoqueAtual < 0);

    do
    {
        printf("Estoque minimo: ");
        scanf("%d", &produto.estoqueMinimo);

        if(produto.estoqueMinimo < 0)
        {

            printf("\nO estoque minimo nao pode ser negativo!\n");
        }

    } while(produto.estoqueMinimo < 0);

    do
    {
        printf("\n\n");
        printf("+================================+\n");
        printf("|       RESUMO DO PRODUTO        |\n");
        printf("+================================+\n");

        printf("Codigo...........: %03d\n", produto.codigoProduto);
        printf("Descricao........: %s\n", produto.descricao);
        printf("Categoria........: %s\n", produto.categoria);
        printf("Preco Compra.....: R$ %.2f\n", produto.precoCompra);
        printf("Margem Lucro.....: %.2f%%\n", produto.margemLucro);
        printf("Preco Venda......: R$ %.2f\n", produto.precoVenda);
        printf("Estoque Atual....: %d\n", produto.estoqueAtual);
        printf("Estoque Minimo...: %d\n", produto.estoqueMinimo);

        printf("\nOs dados estao corretos?\n");
        printf("[1] - Sim\n");
        printf("[2] - Corrigir\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        if(opcao == 2)
        {
            int campo;

            printf("\nQual campo deseja corrigir?\n");
            printf("[1] - Descricao\n");
            printf("[2] - Categoria\n");
            printf("[3] - Preco Compra\n");
            printf("[4] - Margem Lucro\n");
            printf("[5] - Estoque Atual\n");
            printf("[6] - Estoque Minimo\n");

            printf("Opcao: ");
            scanf("%d", &campo);

            switch(campo)
            {
                case 1:
                    printf("Nova descricao: ");
                    scanf(" %[^\n]", produto.descricao);
                    padronizarDescricao(produto.descricao);
                    break;

                case 2:
                    do
                    {
                        printf("\nEscolha a categoria:\n");
                        printf("[1] - Alimento\n");
                        printf("[2] - Limpeza\n");
                        printf("[3] - Panificacao\n");

                        printf("Opcao: ");
                        scanf("%d", &categoria);

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
                                printf("\nCategoria invalida!\n");
                                break;
                        }

                    } while(categoria < 1 || categoria > 3);
                    break;

                case 3:
                    printf("Novo preco de compra: ");
                    scanf("%f", &produto.precoCompra);

                    break;

                case 4:
                    printf("Nova margem de lucro: ");
                    scanf("%f", &produto.margemLucro);
                    break;

                case 5:
                    printf("Novo estoque atual: ");
                    scanf("%d", &produto.estoqueAtual);
                    break;

                case 6:
                    printf("Novo estoque minimo: ");
                    scanf("%d", &produto.estoqueMinimo);
                    break;

                default:
                    printf("\nCampo invalido!\n");
                    break;
            }

            produto.precoVenda = calcularPrecoVenda(
                produto.precoCompra,
                produto.margemLucro
            );
        }

    } while(opcao != 1);

    arquivo = fopen("produtos.dat", "a");

    if(arquivo == NULL)
    {
        printf("\nErro ao abrir arquivo!\n");
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

    printf("\nProduto cadastrado com sucesso!\n");
}


void listagemProdutos()
{
    FILE *arquivo;

    Produto produto;

    arquivo = fopen("produtos.dat", "r");

    if(arquivo == NULL)
    {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }

    printf("\n\n");
    printf("+================================================================================+\n");
    printf("|                           LISTAGEM DE PRODUTOS                                |\n");
    printf("+================================================================================+\n");

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
        printf("Codigo...........: %03d\n", produto.codigoProduto);
        printf("Descricao........: %s\n", produto.descricao);
        printf("Categoria........: %s\n", produto.categoria);
        printf("Preco Compra.....: R$ %.2f\n", produto.precoCompra);
        printf("Margem Lucro.....: %.2f%%\n", produto.margemLucro);
        printf("Preco Venda......: R$ %.2f\n", produto.precoVenda);
        printf("Estoque Atual....: %d\n", produto.estoqueAtual);
        printf("Estoque Minimo...: %d\n", produto.estoqueMinimo);

        if(produto.estoqueAtual <= produto.estoqueMinimo)
        {
            printf(">>> REPOR URGENTE <<<\n");
        }

        printf("+================================================================================+\n");
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
    printf("+================================+\n");
    printf("|        EXCLUIR PRODUTO         |\n");
    printf("+================================+\n");

    printf("Digite o codigo do produto: ");
    scanf("%d", &codigoBusca);

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
        if(produto.codigoProduto == codigoBusca)
        {
            encontrado = 1;

            printf("\n=================================\n");
            printf("PRODUTO EXCLUIDO COM SUCESSO!\n");
            printf("=================================\n");

            continue;
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

    if(!encontrado)
    {
        printf("\nProduto nao encontrado!\n");
    }
}


int buscarProduto(
    int codigoBusca,
    Produto *produto
)
{
    FILE *arquivo;

    arquivo = fopen("produtos.dat", "r");

    if(arquivo == NULL)
    {
        return 0;
    }

    while(
        fscanf(
            arquivo,
            "%d|%99[^|]|%49[^|]|%f|%f|%f|%d|%d\n",

            &produto->codigoProduto,
            produto->descricao,
            produto->categoria,
            &produto->precoCompra,
            &produto->margemLucro,
            &produto->precoVenda,
            &produto->estoqueAtual,
            &produto->estoqueMinimo
        ) != EOF
    )
    {
        if(produto->codigoProduto == codigoBusca)
        {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}
