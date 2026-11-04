#ifndef VENDAS_H
#define VENDAS_H

#include "structs.h"


void novaVenda();


void listagemVendas();


int gerarCodigoVenda();


int verificarEstoque(
    int codigoProduto,
    int quantidadeDesejada
);


void atualizarEstoque(
    int codigoProduto,
    int quantidadeVendida
);


void atualizarVendaSalva(Venda venda);


void atualizarStatusItensVenda(
    int idVenda,
    char novoStatus
);


void baixarEstoqueItensVenda(int idVenda);


void gerarDataHora(
    char data[],
    char hora[]
);

#endif
