#ifndef USUARIOS_H
#define USUARIOS_H

#include "structs.h"

void loginSistema();
void cadastrarUsuario();
void editarUsuario();
void removerUsuario();
int validarAdministrador();
int usuarioLogadoEhAdmin();
Usuario obterUsuarioLogado();

#endif
