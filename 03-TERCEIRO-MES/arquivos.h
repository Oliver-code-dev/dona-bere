#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include "structs.h"




void salvarCliente(Cliente cliente);


void salvarProduto(Produto produto);


void salvarVenda(Venda venda);


void salvarPagamento(Pagamento pagamento);


void salvarCaixa(Caixa caixa);


int arquivoExiste(const char *nomeArquivo);

#endif
