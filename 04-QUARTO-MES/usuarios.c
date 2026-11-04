#include <stdio.h>
#include <string.h>

#include "usuarios.h"
#include "pagamentos.h"
#include "cores.h"
#include "entrada.h"

#define ARQ_USUARIOS "usuarios.dat"

static Usuario usuarioLogado;
static int existeUsuarioLogado = 0;


static int tamanhoValido(char texto[], int minimo, int maximo) {
    int tamanho = strlen(texto);
    return tamanho >= minimo && tamanho <= maximo;
}


static void lerTextoLinha(char mensagem[], char destino[], int tamanhoDestino) {
    char texto[120];

    printf(COR_ENTRADA "%s" COR_FIM, mensagem);
    scanf(" %119[^\n]", texto);

    texto[tamanhoDestino - 1] = '\0';
    strncpy(destino, texto, tamanhoDestino - 1);
    destino[tamanhoDestino - 1] = '\0';
}


static int arquivoUsuariosExiste() {
    FILE *arquivo = fopen(ARQ_USUARIOS, "r");

    if(arquivo == NULL) {
        return 0;
    }

    fclose(arquivo);
    return 1;
}


static int buscarUsuario(char login[], char senha[], Usuario *usuario) {
    FILE *arquivo;
    Usuario atual;

    arquivo = fopen(ARQ_USUARIOS, "r");

    if(arquivo == NULL) {
        return 0;
    }

    while(fscanf(
        arquivo,
        "%12[^|]|%8[^|]|%d\n",
        atual.login,
        atual.senha,
        &atual.tipo
    ) != EOF) {
        if(strcmp(atual.login, login) == 0 && strcmp(atual.senha, senha) == 0) {
            *usuario = atual;
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}


static int loginJaExiste(char login[]) {
    FILE *arquivo;
    Usuario atual;

    arquivo = fopen(ARQ_USUARIOS, "r");

    if(arquivo == NULL) {
        return 0;
    }

    while(fscanf(
        arquivo,
        "%12[^|]|%8[^|]|%d\n",

        atual.login,
        atual.senha,
        &atual.tipo
    ) != EOF) {
        if(strcmp(atual.login, login) == 0) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}


static void lerLoginValido(char destino[], int permitirExistente) {
    char texto[120];

    do {
        printf(COR_ENTRADA "Login (8 a 12 caracteres ou 0 para voltar): " COR_FIM);
        scanf(" %119[^\n]", texto);

        if(strcmp(texto, "0") == 0) {
            strcpy(destino, "0");
            return;
        }

        if(!tamanhoValido(texto, 8, 12)) {
            beepErro();
            printf(COR_ERRO "Login invalido! Use de 8 a 12 caracteres.\n" COR_FIM);
            continue;
        }

        if(!permitirExistente && loginJaExiste(texto)) {
            beepErro();
            printf(COR_ERRO "Esse login ja existe. Escolha outro.\n" COR_FIM);
            continue;
        }

        strcpy(destino, texto);
        return;
    } while(1);
}


static void lerSenhaValida(char destino[]) {
    char texto[120];

    do {
        printf(COR_ENTRADA "Senha (6 a 8 caracteres ou 0 para voltar): " COR_FIM);
        scanf(" %119[^\n]", texto);

        if(strcmp(texto, "0") == 0) {
            strcpy(destino, "0");
            return;
        }

        if(!tamanhoValido(texto, 6, 8)) {
            beepErro();
            printf(COR_ERRO "Senha invalida! Use de 6 a 8 caracteres.\n" COR_FIM);
            continue;
        }

        strcpy(destino, texto);
        return;
    } while(1);
}


static void lerLoginInicial(char destino[]) {
    char texto[120];

    do {
        printf(COR_ENTRADA "Login (8 a 12 caracteres): " COR_FIM);
        scanf(" %119[^\n]", texto);

        if(!tamanhoValido(texto, 8, 12)) {
            beepErro();
            printf(COR_ERRO "Login invalido! Use de 8 a 12 caracteres.\n" COR_FIM);
            continue;
        }

        strcpy(destino, texto);
        return;
    } while(1);
}


static void lerSenhaInicial(char destino[]) {
    char texto[120];

    do {
        printf(COR_ENTRADA "Senha (6 a 8 caracteres): " COR_FIM);
        scanf(" %119[^\n]", texto);

        if(!tamanhoValido(texto, 6, 8)) {
            beepErro();
            printf(COR_ERRO "Senha invalida! Use de 6 a 8 caracteres.\n" COR_FIM);
            continue;
        }

        strcpy(destino, texto);
        return;
    } while(1);
}


static void criarAdministradorInicial() {
    FILE *arquivo;
    Usuario admin;

    printf("\n");
    printf(COR_TITULO "+================================+\n" COR_FIM);
    printf(COR_TITULO "|   PRIMEIRO ACESSO - ADMIN      |\n" COR_FIM);
    printf(COR_TITULO "+================================+\n" COR_FIM);
    printf(COR_TITULO "Crie o usuario administrador inicial.\n" COR_FIM);

    lerLoginInicial(admin.login);
    lerSenhaInicial(admin.senha);

    admin.tipo = 1;

    arquivo = fopen(ARQ_USUARIOS, "w");

    if(arquivo == NULL) {
        beepErro();
        printf(COR_ERRO "\nErro ao criar usuarios.dat!\n" COR_FIM);
        return;
    }

    fprintf(arquivo, "%s|%s|%d\n", admin.login, admin.senha, admin.tipo);
    fclose(arquivo);

    printf(COR_SUCESSO "\nAdministrador inicial criado com sucesso!\n" COR_FIM);
}


void loginSistema() {
    char login[120];
    char senha[120];
    Usuario usuario;

    if(!arquivoUsuariosExiste()) {
        criarAdministradorInicial();
    }

    do {
        printf("\n");
        printf(COR_MENU "+================================+\n" COR_FIM);
        printf(COR_MENU "|        LOGIN DO SISTEMA        |\n" COR_FIM);
        printf(COR_MENU "+================================+\n" COR_FIM);
        lerTextoLinha(COR_ENTRADA "Login: " COR_FIM, login, sizeof(login));
        lerTextoLinha(COR_ENTRADA "Senha: " COR_FIM, senha, sizeof(senha));

        if(buscarUsuario(login, senha, &usuario)) {
            usuarioLogado = usuario;
            existeUsuarioLogado = 1;
            beepSucesso();
            printf(COR_SUCESSO "\nBem-vinda(o), %s!\n" COR_FIM, usuarioLogado.login);
            registrarLog("Login realizado no sistema");
            return;
        }

        beepErro();
        printf(COR_ERRO "\nLogin ou senha invalidos. Tente novamente.\n" COR_FIM);
        registrarLog("ERRO: tentativa de login invalida");
    } while(1);
}


void cadastrarUsuario() {
    FILE *arquivo;
    Usuario usuario;

    if(!validarAdministrador()) {
        return;
    }

    printf("\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|      CADASTRO DE USUARIO       |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);

    lerLoginValido(usuario.login, 0);
    if(strcmp(usuario.login, "0") == 0) {
        printf(COR_AVISO "\nCadastro cancelado. Voltando...\n" COR_FIM);
        return;
    }

    lerSenhaValida(usuario.senha);
    if(strcmp(usuario.senha, "0") == 0) {
        printf(COR_AVISO "\nCadastro cancelado. Voltando...\n" COR_FIM);
        return;
    }

    do {
        printf(COR_ENTRADA "Tipo [1] Administrador [2] Usuario [0] Voltar: " COR_FIM);
        usuario.tipo = lerInteiro("");

        if(usuario.tipo == 0) {
            printf(COR_AVISO "\nCadastro cancelado. Voltando...\n" COR_FIM);
            return;
        }

        if(usuario.tipo != 1 && usuario.tipo != 2) {
            beepErro();
            printf(COR_ERRO "Tipo invalido! Digite 1, 2 ou 0 para voltar.\n" COR_FIM);
        }
    } while(usuario.tipo != 1 && usuario.tipo != 2);

    arquivo = fopen(ARQ_USUARIOS, "a");

    if(arquivo == NULL) {
        beepErro();
        printf(COR_ERRO "\nErro ao abrir usuarios.dat!\n" COR_FIM);
        return;
    }

    fprintf(arquivo, "%s|%s|%d\n", usuario.login, usuario.senha, usuario.tipo);
    fclose(arquivo);

    beepSucesso();
    printf(COR_SUCESSO "\nUsuario cadastrado com sucesso!\n" COR_FIM);
    registrarLog("Usuario cadastrado");
}


int validarAdministrador() {
    char login[120];
    char senha[120];
    Usuario usuario;

    if(existeUsuarioLogado && usuarioLogado.tipo == 1) {
        return 1;
    }

    beepErro();
    printf(COR_AVISO "\nOperacao restrita ao administrador.\n" COR_FIM);
    printf(COR_AVISO "Informe um login administrador para liberar.\n" COR_FIM);
    lerTextoLinha(COR_ENTRADA "Login admin: " COR_FIM, login, sizeof(login));
    lerTextoLinha(COR_ENTRADA "Senha admin: " COR_FIM, senha, sizeof(senha));

    if(buscarUsuario(login, senha, &usuario) && usuario.tipo == 1) {
        return 1;
    }

    beepErro();
    printf(COR_ERRO "\nAdministrador nao validado. Operacao cancelada.\n" COR_FIM);
    registrarLog("ERRO: permissao administrativa negada");
    return 0;
}


int usuarioLogadoEhAdmin() {
    return existeUsuarioLogado && usuarioLogado.tipo == 1;
}


Usuario obterUsuarioLogado() {
    return usuarioLogado;
}


void editarUsuario() {
    FILE *arquivo;
    FILE *temp;
    Usuario usuario;
    char loginBusca[120];
    int encontrado = 0;
    int opcao = 0;

    if(!validarAdministrador()) {
        return;
    }

    printf("\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|        EDITAR USUARIO          |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);
    lerTextoLinha(COR_ENTRADA "Login do usuario (ou 0 para voltar): " COR_FIM, loginBusca, sizeof(loginBusca));

    if(strcmp(loginBusca, "0") == 0) {
        printf(COR_AVISO "\nVoltando...\n" COR_FIM);
        return;
    }

    arquivo = fopen(ARQ_USUARIOS, "r");

    if(arquivo == NULL) {
        printf(COR_AVISO "\nNenhum usuario cadastrado.\n" COR_FIM);
        return;
    }

    temp = fopen("temp_usuarios.dat", "w");

    if(temp == NULL) {
        fclose(arquivo);
        printf(COR_ERRO "\nErro ao criar arquivo temporario.\n" COR_FIM);
        return;
    }

    while(fscanf(
        arquivo,
        "%12[^|]|%8[^|]|%d\n",
        usuario.login,
        usuario.senha,
        &usuario.tipo
    ) != EOF) {
        if(strcmp(usuario.login, loginBusca) == 0) {
            encontrado = 1;
            {
                char senhaOriginal[9];
                int tipoOriginal = usuario.tipo;
                strcpy(senhaOriginal, usuario.senha);

                do {
                    printf(COR_TITULO "\nO que deseja editar?\n" COR_FIM);
                    printf(COR_MENU "[1] - Senha\n" COR_FIM);
                    printf(COR_MENU "[2] - Tipo\n" COR_FIM);
                    printf(COR_MENU "[3] - Voltar\n" COR_FIM);
                    printf(COR_ENTRADA "Opcao: " COR_FIM);
                    opcao = lerInteiro("");

                    switch(opcao) {
                        case 1:
                            lerSenhaValida(usuario.senha);
                            if(strcmp(usuario.senha, "0") == 0) {
                                strcpy(usuario.senha, senhaOriginal);
                                printf(COR_AVISO "\nEdicao de senha cancelada.\n" COR_FIM);
                            }
                            break;

                        case 2:
                            do {
                                printf(COR_ENTRADA "Novo tipo [1] Administrador [2] Usuario [0] Cancelar: " COR_FIM);
                                usuario.tipo = lerInteiro("");

                                if(usuario.tipo == 0) {
                                    usuario.tipo = tipoOriginal;
                                    printf(COR_AVISO "\nEdicao de tipo cancelada.\n" COR_FIM);
                                    break;
                                }

                                if(usuario.tipo != 1 && usuario.tipo != 2) {
                                    beepErro();
                                    printf(COR_ERRO "Tipo invalido!\n" COR_FIM);
                                }
                            } while(usuario.tipo != 1 && usuario.tipo != 2);

                            break;

                        case 3:
                            break;

                        default:
                            beepErro();
                            printf(COR_ERRO "\nOpcao invalida!\n" COR_FIM);
                            break;
                    }
                } while(opcao < 1 || opcao > 3);
            }

            printf(COR_SUCESSO "\nUsuario atualizado!\n" COR_FIM);
        }

        fprintf(temp, "%s|%s|%d\n", usuario.login, usuario.senha, usuario.tipo);
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQ_USUARIOS);
    rename("temp_usuarios.dat", ARQ_USUARIOS);

    if(!encontrado) {
        printf(COR_AVISO "\nUsuario nao encontrado.\n" COR_FIM);
    }
}


void removerUsuario() {
    FILE *arquivo;
    FILE *temp;
    Usuario usuario;
    char loginBusca[120];
    char confirma;
    int encontrado = 0;
    int totalUsuarios = 0;

    if(!validarAdministrador()) {
        return;
    }

    printf("\n");
    printf(COR_MENU "+================================+\n" COR_FIM);
    printf(COR_MENU "|        REMOVER USUARIO         |\n" COR_FIM);
    printf(COR_MENU "+================================+\n" COR_FIM);
    lerTextoLinha(COR_ENTRADA "Login do usuario (ou 0 para voltar): " COR_FIM, loginBusca, sizeof(loginBusca));

    if(strcmp(loginBusca, "0") == 0) {
        printf(COR_AVISO "\nVoltando...\n" COR_FIM);
        return;
    }

    arquivo = fopen(ARQ_USUARIOS, "r");

    if(arquivo == NULL) {
        printf(COR_AVISO "\nNenhum usuario cadastrado.\n" COR_FIM);
        return;
    }

    while(fscanf(arquivo, "%12[^|]|%8[^|]|%d\n", usuario.login, usuario.senha, &usuario.tipo) != EOF) {
        totalUsuarios++;
    }

    if(totalUsuarios <= 1) {
        fclose(arquivo);
        printf(COR_ERRO "\nNao e permitido remover o unico usuario do sistema.\n" COR_FIM);
        return;
    }

    rewind(arquivo);

    printf(COR_ENTRADA "Tem certeza que deseja remover? [S/N]: " COR_FIM);
    confirma = lerCharOpcao("");

    if(confirma != 'S' && confirma != 's') {
        fclose(arquivo);
        printf(COR_AVISO "\nRemocao cancelada.\n" COR_FIM);
        return;
    }

    temp = fopen("temp_usuarios.dat", "w");

    if(temp == NULL) {
        fclose(arquivo);

        printf(COR_ERRO "\nErro ao criar arquivo temporario.\n" COR_FIM);
        return;
    }

    while(fscanf(
        arquivo,
        "%12[^|]|%8[^|]|%d\n",
        usuario.login,
        usuario.senha,
        &usuario.tipo
    ) != EOF) {
        if(strcmp(usuario.login, loginBusca) == 0) {
            encontrado = 1;
            continue;
        }

        fprintf(temp, "%s|%s|%d\n", usuario.login, usuario.senha, usuario.tipo);
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQ_USUARIOS);
    rename("temp_usuarios.dat", ARQ_USUARIOS);

    if(encontrado) {
        printf(COR_SUCESSO "\nUsuario removido com sucesso.\n" COR_FIM);
    }
    else {
        printf(COR_AVISO "\nUsuario nao encontrado.\n" COR_FIM);
    }
}
