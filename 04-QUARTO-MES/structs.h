#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct
{
    char login[13];
    char senha[9];
    int tipo;
} Usuario;


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
    int codCliente;
    char dataVenda[20];
    char horaVenda[10];
    float total;
    float desconto;
    float totalFinal;
} Venda;


typedef struct
{
    int idVenda;
    int numItem;
    int codigoProduto;
    char descricaoProduto[100];
    float precoUnitario;
    int quantidade;
    float totalItem;
    char statusPagamento;
} ItemVenda;


typedef struct
{
    int idPagamento;
    int idVenda;
    float valorPago;
    float valorDinheiro;
    float valorCartao;
    float desconto;
    float troco;
    char tipoPagamento[40];
    char tipoCartao[20];
} Pagamento;


typedef struct
{
    float valorInicial;
    int statusCaixa;
} Caixa;


typedef struct
{
    int numSangria;

    float valorRetirado;
} Sangria;

#endif
