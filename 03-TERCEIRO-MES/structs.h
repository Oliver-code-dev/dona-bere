#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct
{
    int codigoCliente;
    char nomeCompleto[100];
    char nomeSocial[100];
    char cpf[15];
    char ruaNumero[100];
    char bairro[50];
    char celular[20];
} Cliente;

typedef struct
{
    int codigoProduto;
    char descricao[100];
    char categoria[50];
    float precoCompra;
    float margemLucro;
    float precoVenda;
    int estoqueAtual;
    int estoqueMinimo;
} Produto;

typedef struct
{
    int idVenda;
    int codigoProduto;
    char descricaoProduto[100];
    float precoUnitario;
    int quantidade;
    float totalItem;
    char dataVenda[20];
    char horaVenda[10];
} Venda;

typedef struct
{
    float valorPago;
    char tipoPagamento[30];
} Pagamento;

typedef struct
{
    float valorInicial;
    int statusCaixa;
} Caixa;

#endif
