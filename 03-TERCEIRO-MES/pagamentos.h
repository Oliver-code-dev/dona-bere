#ifndef PAGAMENTOS_H
#define PAGAMENTOS_H

#include "structs.h"


void realizarPagamento(float totalVenda);


void gerarCupomFiscal(
    float totalVenda,
    char tipoPagamento[]
);

#endif
