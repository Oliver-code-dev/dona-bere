#ifndef CAIXA_H
#define CAIXA_H

#include "structs.h"


extern int caixaAberto;


int caixaEstaAberto();


void abrirCaixa();


void fecharCaixa();


void realizarSangria();


float calcularDinheiroDisponivelCaixa();

#endif
