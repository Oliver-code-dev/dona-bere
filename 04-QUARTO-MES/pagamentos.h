#ifndef PAGAMENTOS_H
#define PAGAMENTOS_H

#include "structs.h"


int realizarPagamento(int idVenda, float totalVenda, Pagamento *pagamento
);


void realizarPagamentoPendente();


void gerarCupomFiscal(Venda venda, ItemVenda itens[], int qtdItens, Pagamento pagamento);


void registrarLog(char mensagem[]);


void beepErro();
void beepSucesso();

#endif
