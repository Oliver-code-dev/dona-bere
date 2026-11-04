#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "clientes.h"


void padronizarNome(char *texto)
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


int gerarCodigoCliente()
{
    FILE *arquivo;

    int contador = 0;
    char linha[300];

    arquivo = fopen("clientes.dat", "r");

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


void cadastrarCliente()
{
    Cliente cliente;

    FILE *arquivo;

    int opcao = 0;

    cliente.codigoCliente = gerarCodigoCliente();

    printf("\n\n");
    printf("+================================+\n");
    printf("|      CADASTRO DE CLIENTE       |\n");
    printf("+================================+\n");

    printf("Nome completo: ");
    scanf(" %[^\n]", cliente.nomeCompleto);

    padronizarNome(cliente.nomeCompleto);

    printf("Nome social: ");
    scanf(" %[^\n]", cliente.nomeSocial);

    padronizarNome(cliente.nomeSocial);

    printf("CPF: ");
    scanf(" %[^\n]", cliente.cpf);

    if(cpfExiste(cliente.cpf))
    {
        printf("\n=================================\n");
        printf("CPF JA CADASTRADO NO SISTEMA!\n");
        printf("=================================\n");
        return;
    }

    printf("Rua e numero: ");
    scanf(" %[^\n]", cliente.ruaNumero);

    printf("Bairro: ");
    scanf(" %[^\n]", cliente.bairro);

    padronizarNome(cliente.bairro);

    printf("Celular/WhatsApp: ");
    scanf(" %[^\n]", cliente.celular);

    do
    {
        printf("\n\n");
        printf("+================================+\n");
        printf("|       RESUMO DO CLIENTE        |\n");
        printf("+================================+\n");

        printf("Codigo........: %03d\n", cliente.codigoCliente);
        printf("Nome..........: %s\n", cliente.nomeCompleto);
        printf("Nome Social...: %s\n", cliente.nomeSocial);
        printf("CPF...........: %s\n", cliente.cpf);
        printf("Rua/Numero....: %s\n", cliente.ruaNumero);
        printf("Bairro........: %s\n", cliente.bairro);
        printf("Celular.......: %s\n", cliente.celular);

        printf("\nOs dados estao corretos?\n");
        printf("[1] - Sim\n");
        printf("[2] - Corrigir\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        if(opcao == 2)
        {
            int campo;

            printf("\nQual campo deseja corrigir?\n");

            printf("[1] - Nome Completo\n");
            printf("[2] - Nome Social\n");
            printf("[3] - CPF\n");
            printf("[4] - Rua e Numero\n");
            printf("[5] - Bairro\n");
            printf("[6] - Celular\n");

            printf("Opcao: ");
            scanf("%d", &campo);

            switch(campo)
            {
                case 1:
                    printf("Novo nome completo: ");
                    scanf(" %[^\n]", cliente.nomeCompleto);
                    padronizarNome(cliente.nomeCompleto);
                    break;

                case 2:
                    printf("Novo nome social: ");
                    scanf(" %[^\n]", cliente.nomeSocial);
                    padronizarNome(cliente.nomeSocial);
                    break;

                case 3:
                    printf("Novo CPF: ");
                    scanf(" %[^\n]", cliente.cpf);
                    break;

                case 4:
                    printf("Nova rua e numero: ");
                    scanf(" %[^\n]", cliente.ruaNumero);
                    break;

                case 5:
                    printf("Novo bairro: ");
                    scanf(" %[^\n]", cliente.bairro);
                    padronizarNome(cliente.bairro);
                    break;

                case 6:
                    printf("Novo celular: ");
                    scanf(" %[^\n]", cliente.celular);
                    break;

                default:
                    printf("\nCampo invalido!\n");
                    break;
            }
        }

    } while(opcao != 1);

    arquivo = fopen("clientes.dat", "a");

    if(arquivo == NULL)
    {
        printf("\nErro ao abrir arquivo!\n");
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

    printf("\nCliente cadastrado com sucesso!\n");
}


void listagemClientes()
{
    FILE *arquivo;
    Cliente cliente;

    arquivo = fopen("clientes.dat", "r");

    if(arquivo == NULL)
    {
        printf("\nNenhum cliente cadastrado!\n");
        return;
    }

    printf("\n\n");
    printf("+=========================================================================+\n");
    printf("|                         LISTAGEM DE CLIENTES                            |\n");
    printf("+=========================================================================+\n");

    while(
        fscanf(
            arquivo,
            "%d|%99[^|]|%99[^|]|%14[^|]|%99[^|]|%49[^|]|%19[^\n]\n",
            &cliente.codigoCliente,
            cliente.nomeCompleto,
            cliente.nomeSocial,
            cliente.cpf,
            cliente.ruaNumero,
            cliente.bairro,
            cliente.celular
        ) != EOF
    )
    {
        printf("Codigo.......: %03d\n", cliente.codigoCliente);
        printf("Nome.........: %s\n", cliente.nomeCompleto);
        printf("Nome Social..: %s\n", cliente.nomeSocial);
        printf("CPF..........: %s\n", cliente.cpf);
        printf("Rua/Numero...: %s\n", cliente.ruaNumero);
        printf("Bairro.......: %s\n", cliente.bairro);
        printf("Celular......: %s\n", cliente.celular);

        printf("+=========================================================================+\n");
    }

    fclose(arquivo);
}


void editarCliente()
{
    FILE *arquivo;
    FILE *temp;

    Cliente cliente;

    int codigoBusca;
    int encontrado = 0;
    int opcao;

    printf("\n\n");
    printf("+================================+\n");
    printf("|         EDITAR CLIENTE         |\n");
    printf("+================================+\n");

    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigoBusca);

    arquivo = fopen("clientes.dat", "r");

    if(arquivo == NULL)
    {
        printf("\nErro ao abrir clientes.dat\n");
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
            "%d|%99[^|]|%99[^|]|%14[^|]|%99[^|]|%49[^|]|%19[^\n]\n",
            &cliente.codigoCliente,
            cliente.nomeCompleto,
            cliente.nomeSocial,
            cliente.cpf,
            cliente.ruaNumero,
            cliente.bairro,
            cliente.celular
        ) != EOF
    )
    {
        if(cliente.codigoCliente == codigoBusca)
        {
            encontrado = 1;

            printf("\nCLIENTE ENCONTRADO!\n");
            printf("\nNome........: %s\n", cliente.nomeCompleto);
            printf("CPF.........: %s\n", cliente.cpf);

            printf("\nO que deseja editar?\n");
            printf("[1] Nome Completo\n");
            printf("[2] Nome Social\n");
            printf("[3] CPF\n");
            printf("[4] Rua\n");
            printf("[5] Bairro\n");
            printf("[6] Celular\n");

            printf("Opcao: ");
            scanf("%d", &opcao);

            switch(opcao)
            {
                case 1:
                    printf("Novo nome: ");
                    scanf(" %[^\n]", cliente.nomeCompleto);
                    break;

                case 2:
                    printf("Novo nome social: ");
                    scanf(" %[^\n]", cliente.nomeSocial);

                    break;

                case 3:
                    printf("Novo CPF: ");
                    scanf(" %[^\n]", cliente.cpf);
                    break;

                case 4:
                    printf("Nova rua: ");
                    scanf(" %[^\n]", cliente.ruaNumero);
                    break;

                case 5:
                    printf("Novo bairro: ");
                    scanf(" %[^\n]", cliente.bairro);
                    break;

                case 6:
                    printf("Novo celular: ");
                    scanf(" %[^\n]", cliente.celular);
                    break;

                default:
                    printf("\nOpcao invalida!\n");
                    break;
            }

            printf("\nCliente atualizado!\n");
        }

        fprintf(
            temp,
            "%d|%s|%s|%s|%s|%s|%s\n",
            cliente.codigoCliente,
            cliente.nomeCompleto,
            cliente.nomeSocial,
            cliente.cpf,
            cliente.ruaNumero,
            cliente.bairro,
            cliente.celular
        );
    }

    fclose(arquivo);
    fclose(temp);

    remove("clientes.dat");
    rename("temp.dat", "clientes.dat");

    if(!encontrado)
    {
        printf("\nCliente nao encontrado!\n");
    }
}


int cpfExiste(char cpf[])
{
    FILE *arquivo;
    Cliente cliente;

    arquivo = fopen("clientes.dat", "r");

    if(arquivo == NULL)
    {
        return 0;
    }

    while(
        fscanf(
            arquivo,
            "%d|%99[^|]|%99[^|]|%14[^|]|%99[^|]|%49[^|]|%19[^\n]\n",
            &cliente.codigoCliente,
            cliente.nomeCompleto,
            cliente.nomeSocial,
            cliente.cpf,
            cliente.ruaNumero,
            cliente.bairro,
            cliente.celular
        ) != EOF
    )
    {
        if(strcmp(cliente.cpf, cpf) == 0)
        {
            fclose(arquivo);
            return 1;

        }
    }

    fclose(arquivo);

    return 0;
}
