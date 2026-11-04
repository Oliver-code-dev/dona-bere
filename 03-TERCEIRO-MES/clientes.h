#ifndef CLIENTES_H
#define CLIENTES_H

#include "structs.h"


void cadastrarCliente();


void listagemClientes();


void padronizarNome(char *texto);

int gerarCodigoCliente();

int cpfExiste(char cpf[]);

void editarCliente();

#endif
