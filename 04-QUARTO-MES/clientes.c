#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clientes.h"
#include "cores.h"
#include "entrada.h"
#include "pagamentos.h"

#define ARQ_CLIENTES "clientes.dat"


static int lerTextoCliente(char mensagem[], char destino[], int tamanhoDestino)
{
    char texto[160];

    printf(COR_ENTRADA "%s" COR_FIM, mensagem);
    scanf(" %159[^\n]", texto);

    if(strcmp(texto, "0") == 0)
    {
        return 0;
    }

    strncpy(destino, texto, tamanhoDestino - 1);
    destino[tamanhoDestino - 1] = '\0';
    return 1;
}


static void gravarCliente(FILE *arquivo, Cliente cliente)
{
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
}


static int lerClienteArquivo(FILE *arquivo, Cliente *cliente)
{
    return fscanf(
        arquivo,
        "%d|%99[^|]|%99[^|]|%14[^|]|%99[^|]|%49[^|]|%19[^\n]\n",
        &cliente->codigoCliente,
        cliente->nomeCompleto,
        cliente->nomeSocial,
        cliente->cpf,
        cliente->ruaNumero,
        cliente->bairro,
        cliente->celular
    );
}


static int cpfExisteEmOutroCliente(char cpf[], int codigoIgnorado)
{
    FILE *arquivo;
    Cliente cliente;

    arquivo = fopen(ARQ_CLIENTES, "r");

    if(arquivo == NULL)
    {
        return 0;
    }

    while(lerClienteArquivo(arquivo, &cliente) != EOF)
    {
        if(strcmp(cliente.cpf, cpf) == 0 && cliente.codigoCliente != codigoIgnorado)
        {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;

}


static void mostrarResumoCliente(Cliente cliente)
{
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|        RESUMO DO CLIENTE       |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_TITULO "Codigo.......: %03d\n" COR_FIM, cliente.codigoCliente);
    printf(COR_TITULO "Nome.........: %s\n" COR_FIM, cliente.nomeCompleto);
    printf(COR_TITULO "Nome social..: %s\n" COR_FIM, cliente.nomeSocial);
    printf(COR_TITULO "CPF..........: %s\n" COR_FIM, cliente.cpf);
    printf(COR_TITULO "Endereco.....: %s\n" COR_FIM, cliente.ruaNumero);
    printf(COR_TITULO "Bairro.......: %s\n" COR_FIM, cliente.bairro);
    printf(COR_TITULO "Celular......: %s\n" COR_FIM, cliente.celular);
}


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
        else if(novaPalavra)
        {
            texto[i] = toupper((unsigned char)texto[i]);
            novaPalavra = 0;
        }
        else
        {
            texto[i] = tolower((unsigned char)texto[i]);
        }
    }
}


int gerarCodigoCliente()
{
    FILE *arquivo;
    Cliente cliente;
    int maiorCodigo = 0;

    arquivo = fopen(ARQ_CLIENTES, "r");

    if(arquivo == NULL)
    {
        return 1;
    }

    while(lerClienteArquivo(arquivo, &cliente) != EOF)
    {
        if(cliente.codigoCliente > maiorCodigo)
        {
            maiorCodigo = cliente.codigoCliente;
        }
    }

    fclose(arquivo);
    return maiorCodigo + 1;
}


int cpfExiste(char cpf[])
{
    return cpfExisteEmOutroCliente(cpf, 0);
}


void cadastrarCliente()
{
    FILE *arquivo;
    Cliente cliente;
    int opcao = 0;

    cliente.codigoCliente = gerarCodigoCliente();
    strcpy(cliente.nomeSocial, "Nao informado");

    printf("\n\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|      CADASTRO DE CLIENTE       |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);

    if(!lerTextoCliente("Nome completo (ou 0 para voltar): ", cliente.nomeCompleto, sizeof(cliente.nomeCompleto)))
    {
        printf(COR_AVISO "\nCadastro cancelado. Voltando...\n" COR_FIM);
        return;
    }
    padronizarNome(cliente.nomeCompleto);

    if(!lerTextoCliente("Nome social (ou 0 para nao informar): ", cliente.nomeSocial, sizeof(cliente.nomeSocial)))
    {
        strcpy(cliente.nomeSocial, "Nao informado");
    }
    else
    {
        padronizarNome(cliente.nomeSocial);
    }

    do
    {
        if(!lerTextoCliente("CPF (ou 0 para voltar): ", cliente.cpf, sizeof(cliente.cpf)))
        {
            printf(COR_AVISO "\nCadastro cancelado. Voltando...\n" COR_FIM);
            return;
        }

        if(cpfExiste(cliente.cpf))
        {
            beepErro();
            printf(COR_ERRO "CPF ja cadastrado. Informe outro CPF.\n" COR_FIM);
        }
    } while(cpfExiste(cliente.cpf));

    if(!lerTextoCliente("Rua e numero (ou 0 para voltar): ", cliente.ruaNumero, sizeof(cliente.ruaNumero)))
    {
        printf(COR_AVISO "\nCadastro cancelado. Voltando...\n" COR_FIM);
        return;
    }

    if(!lerTextoCliente("Bairro (ou 0 para voltar): ", cliente.bairro, sizeof(cliente.bairro)))
    {
        printf(COR_AVISO "\nCadastro cancelado. Voltando...\n" COR_FIM);
        return;
    }
    padronizarNome(cliente.bairro);

    if(!lerTextoCliente("Celular/WhatsApp (ou 0 para voltar): ", cliente.celular, sizeof(cliente.celular)))
    {
        printf(COR_AVISO "\nCadastro cancelado. Voltando...\n" COR_FIM);
        return;
    }

    do
    {
        printf("\n");
        mostrarResumoCliente(cliente);
        printf(COR_MENU "[1] - Confirmar cadastro\n" COR_FIM);
        printf(COR_MENU "[2] - Corrigir nome completo\n" COR_FIM);
        printf(COR_MENU "[3] - Corrigir nome social\n" COR_FIM);
        printf(COR_MENU "[4] - Corrigir CPF\n" COR_FIM);
        printf(COR_MENU "[5] - Corrigir endereco\n" COR_FIM);
        printf(COR_MENU "[6] - Corrigir bairro\n" COR_FIM);
        printf(COR_MENU "[7] - Corrigir celular\n" COR_FIM);
        printf(COR_MENU "[0] - Cancelar\n" COR_FIM);
        opcao = lerInteiro(COR_ENTRADA "Opcao: " COR_FIM);

        switch(opcao)
        {
            case 1:
                break;

            case 2:
                if(lerTextoCliente("Novo nome completo (ou 0 para cancelar): ", cliente.nomeCompleto, sizeof(cliente.nomeCompleto)))
                {
                    padronizarNome(cliente.nomeCompleto);
                }
                break;

            case 3:
                if(lerTextoCliente("Novo nome social (ou 0 para nao informar): ", cliente.nomeSocial, sizeof(cliente.nomeSocial)))
                {
                    padronizarNome(cliente.nomeSocial);
                }
                else
                {
                    strcpy(cliente.nomeSocial, "Nao informado");
                }
                break;

            case 4:
                do
                {
                    if(!lerTextoCliente("Novo CPF (ou 0 para cancelar): ", cliente.cpf, sizeof(cliente.cpf)))
                    {
                        break;
                    }

                    if(cpfExiste(cliente.cpf))
                    {
                        beepErro();
                        printf(COR_ERRO "CPF ja cadastrado. Informe outro CPF.\n" COR_FIM);
                    }
                } while(cpfExiste(cliente.cpf));
                break;

            case 5:
                lerTextoCliente("Novo endereco (ou 0 para cancelar): ", cliente.ruaNumero, sizeof(cliente.ruaNumero));
                break;

            case 6:
                if(lerTextoCliente("Novo bairro (ou 0 para cancelar): ", cliente.bairro, sizeof(cliente.bairro)))
                {
                    padronizarNome(cliente.bairro);
                }
                break;

            case 7:
                lerTextoCliente("Novo celular (ou 0 para cancelar): ", cliente.celular, sizeof(cliente.celular));
                break;

            case 0:
                printf(COR_AVISO "\nCadastro cancelado. Voltando...\n" COR_FIM);
                return;

            default:
                beepErro();
                printf(COR_ERRO "\nOpcao invalida!\n" COR_FIM);
                break;
        }
    } while(opcao != 1);

    arquivo = fopen(ARQ_CLIENTES, "a");

    if(arquivo == NULL)
    {
        beepErro();
        printf(COR_ERRO "\nErro ao abrir clientes.dat!\n" COR_FIM);
        return;
    }

    gravarCliente(arquivo, cliente);
    fclose(arquivo);

    beepSucesso();
    printf(COR_SUCESSO "\nCliente cadastrado com sucesso!\n" COR_FIM);
    registrarLog("Cliente cadastrado");
}


void listagemClientes()
{
    FILE *arquivo;
    Cliente cliente;
    int encontrou = 0;

    arquivo = fopen(ARQ_CLIENTES, "r");

    if(arquivo == NULL)
    {
        printf(COR_AVISO "\nNenhum cliente cadastrado!\n" COR_FIM);
        return;
    }

    printf("\n\n");
    printf(COR_MENU "+=========================================================================+\n" COR_FIM);
    printf(COR_MENU "|                         LISTAGEM DE CLIENTES                            |\n" COR_FIM);
    printf(COR_MENU "+=========================================================================+\n" COR_FIM);

    while(lerClienteArquivo(arquivo, &cliente) != EOF)
    {
        encontrou = 1;
        printf(COR_TITULO "%03d | %-30s | CPF: %-14s | Whats: %s\n" COR_FIM,
            cliente.codigoCliente,
            cliente.nomeCompleto,
            cliente.cpf,

            cliente.celular
        );
    }

    fclose(arquivo);

    if(!encontrou)
    {
        printf(COR_AVISO "\nNenhum cliente cadastrado!\n" COR_FIM);
    }
}


void editarCliente()
{
    FILE *arquivo;
    FILE *temp;
    Cliente cliente;
    int codigoBusca;
    int encontrado = 0;
    int opcao = 0;

    printf("\n\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|        EDITAR CLIENTE          |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);

    codigoBusca = lerInteiro("Codigo do cliente (ou 0 para voltar): ");

    if(codigoBusca == 0)
    {
        printf(COR_AVISO "\nVoltando...\n" COR_FIM);
        return;
    }

    arquivo = fopen(ARQ_CLIENTES, "r");

    if(arquivo == NULL)
    {
        printf(COR_AVISO "\nNenhum cliente cadastrado.\n" COR_FIM);
        return;
    }

    temp = fopen("temp_clientes.dat", "w");

    if(temp == NULL)
    {
        fclose(arquivo);
        printf(COR_ERRO "\nErro ao criar arquivo temporario.\n" COR_FIM);
        return;
    }

    while(lerClienteArquivo(arquivo, &cliente) != EOF)
    {
        if(cliente.codigoCliente == codigoBusca)
        {
            encontrado = 1;

            do
            {
                printf(COR_SUCESSO "\nCliente encontrado:\n" COR_FIM);
                mostrarResumoCliente(cliente);
                printf(COR_MENU "[1] - Nome completo\n" COR_FIM);
                printf(COR_MENU "[2] - Nome social\n" COR_FIM);
                printf(COR_MENU "[3] - CPF\n" COR_FIM);
                printf(COR_MENU "[4] - Endereco\n" COR_FIM);
                printf(COR_MENU "[5] - Bairro\n" COR_FIM);
                printf(COR_MENU "[6] - Celular\n" COR_FIM);
                printf(COR_MENU "[7] - Voltar\n" COR_FIM);
                opcao = lerInteiro(COR_ENTRADA "Opcao: " COR_FIM);

                switch(opcao)
                {
                    case 1:
                        if(lerTextoCliente("Novo nome completo (ou 0 para cancelar): ", cliente.nomeCompleto, sizeof(cliente.nomeCompleto)))
                        {
                            padronizarNome(cliente.nomeCompleto);
                        }
                        break;

                    case 2:
                        if(lerTextoCliente("Novo nome social (ou 0 para nao informar): ", cliente.nomeSocial, sizeof(cliente.nomeSocial)))
                        {
                            padronizarNome(cliente.nomeSocial);
                        }
                        else
                        {

                            strcpy(cliente.nomeSocial, "Nao informado");
                        }
                        break;

                    case 3:
                        do
                        {
                            if(!lerTextoCliente("Novo CPF (ou 0 para cancelar): ", cliente.cpf, sizeof(cliente.cpf)))
                            {
                                break;
                            }

                            if(cpfExisteEmOutroCliente(cliente.cpf, cliente.codigoCliente))
                            {
                                beepErro();
                                printf(COR_ERRO "CPF ja cadastrado para outro cliente.\n" COR_FIM);
                            }
                        } while(cpfExisteEmOutroCliente(cliente.cpf, cliente.codigoCliente));
                        break;

                    case 4:
                        lerTextoCliente("Novo endereco (ou 0 para cancelar): ", cliente.ruaNumero, sizeof(cliente.ruaNumero));
                        break;

                    case 5:
                        if(lerTextoCliente("Novo bairro (ou 0 para cancelar): ", cliente.bairro, sizeof(cliente.bairro)))
                        {
                            padronizarNome(cliente.bairro);
                        }
                        break;

                    case 6:
                        lerTextoCliente("Novo celular (ou 0 para cancelar): ", cliente.celular, sizeof(cliente.celular));
                        break;

                    case 7:
                        break;

                    default:
                        beepErro();
                        printf(COR_ERRO "\nOpcao invalida!\n" COR_FIM);
                        break;
                }
            } while(opcao < 1 || opcao > 7);

            printf(COR_SUCESSO "\nCliente atualizado!\n" COR_FIM);
        }

        gravarCliente(temp, cliente);
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQ_CLIENTES);
    rename("temp_clientes.dat", ARQ_CLIENTES);

    if(!encontrado)
    {
        printf(COR_AVISO "\nCliente nao encontrado.\n" COR_FIM);
    }
    else
    {
        registrarLog("Cliente atualizado");
    }
}


void removerCliente()
{
    FILE *arquivo;
    FILE *temp;
    Cliente cliente;
    int codigoBusca;
    int encontrado = 0;
    char confirma;

    printf("\n\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|        REMOVER CLIENTE         |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);

    codigoBusca = lerInteiro("Codigo do cliente (ou 0 para voltar): ");

    if(codigoBusca == 0)
    {
        printf(COR_AVISO "\nVoltando...\n" COR_FIM);

        return;
    }

    arquivo = fopen(ARQ_CLIENTES, "r");

    if(arquivo == NULL)
    {
        printf(COR_AVISO "\nNenhum cliente cadastrado.\n" COR_FIM);
        return;
    }

    temp = fopen("temp_clientes.dat", "w");

    if(temp == NULL)
    {
        fclose(arquivo);
        printf(COR_ERRO "\nErro ao criar arquivo temporario.\n" COR_FIM);
        return;
    }

    while(lerClienteArquivo(arquivo, &cliente) != EOF)
    {
        if(cliente.codigoCliente == codigoBusca)
        {
            encontrado = 1;
            mostrarResumoCliente(cliente);
            printf(COR_ENTRADA "Tem certeza que deseja remover? [S/N]: " COR_FIM);
            confirma = lerCharOpcao("");

            if(confirma == 'S' || confirma == 's')
            {
                printf(COR_SUCESSO "\nCliente removido com sucesso.\n" COR_FIM);
                continue;
            }

            printf(COR_AVISO "\nRemocao cancelada.\n" COR_FIM);
        }

        gravarCliente(temp, cliente);
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQ_CLIENTES);
    rename("temp_clientes.dat", ARQ_CLIENTES);

    if(!encontrado)
    {
        printf(COR_AVISO "\nCliente nao encontrado.\n" COR_FIM);
    }
    else
    {
        registrarLog("Cliente removido ou remocao cancelada");
    }
}
