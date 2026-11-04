#include <stdio.h>
#include <stdlib.h>

#include "cores.h"
#include "menus.h"
#include "usuarios.h"


int main()
{
    loginSistema();

    printf("\n");
    printf(COR_MENU "=========================================\n" COR_FIM);
    printf(COR_TITULO "ORDEM RECOMENDADA DE USO\n" COR_FIM);
    printf(COR_MENU "1. Abra o caixa antes de vender.\n" COR_FIM);
    printf(COR_MENU "2. Cadastre clientes e produtos, se precisar.\n" COR_FIM);
    printf(COR_MENU "3. Registre vendas e pagamentos.\n" COR_FIM);
    printf(COR_MENU "4. Emita relatorios e feche o caixa.\n" COR_FIM);
    printf(COR_MENU "=========================================\n" COR_FIM);

    menuPrincipal();

    return 0;
}
