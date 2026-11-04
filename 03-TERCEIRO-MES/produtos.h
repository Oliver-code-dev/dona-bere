#ifndef PRODUTOS_H
#define PRODUTOS_H

#include "structs.h"


void cadastrarProduto();


void listagemProdutos();


void padronizarDescricao(char *texto);


int gerarCodigoProduto();


void excluirProduto();


float calcularPrecoVenda(
    float precoCompra,
    float margemLucro
);


int buscarProduto(
    int codigoBusca,
    Produto *produto
);

#endif
