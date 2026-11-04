#include <stdio.h>

void menu_material_limpeza(char produto[7][30], float preco[7], int estoque[7], int carrinho[7], float *total);
void menu_venda_alimentos(char produto[7][30], float preco[7], int estoque[7], int carrinho[7], float *total);
void menu_padaria(char produto[7][30], float preco[7], int estoque[7], int carrinho[7], float *total);
float calcular_desconto(float valor_total);
void menu_pagamento(float *total_limpeza, float *total_alimentos, float *total_padaria, float *caixa, float *faturamento_dia, float *total_limpeza_dia, float *total_alimentos_dia, float *total_padaria_dia);
void menu_abertura(float caixa, float abertura_caixa);
void menu_fechamento(float abertura_caixa, float caixa, float faturamento_dia, float total_limpeza_dia, float total_alimentos_dia, float total_padaria_dia);

int main()
{
    float total_limpeza_dia = 0;
    float total_alimentos_dia = 0;
    float total_padaria_dia = 0;

    char produto_material_limpeza[7][30] = {
        "Detergente", "Sabao em po (1kg)", "Esponja", "Amaciante (1L)",
        "Bucha de Pia (kit c/3)", "Desinfetante (1L)", "Sabao em barra (un)"
    };
    float preco_material_limpeza[7] = {1.99f, 8.99f, 1.50f, 15.0f, 4.99f, 7.99f, 1.0f};
    int estoque_material_limpeza[7] = {50, 30, 0, 20, 100, 15, 60};
    int carrinho_limpeza[7] = {0};
    float total_limpeza = 0;

    char produto_venda_alimentos[7][30] = {
        "Cafe (500g)", "Leite (cx)", "Arroz (1kg)", "Feijao Preto (1kg)",
        "Acucar (1kg)", "Sal (1kg)", "Farinha de Trigo (1kg)"
    };
    float preco_venda_alimentos[7] = {19.99f, 5.90f, 4.50f, 8.0f, 5.0f, 2.0f, 5.0f};
    int estoque_venda_alimentos[7] = {10, 15, 10, 5, 20, 6, 15};
    int carrinho_venda_alimentos[7] = {0};
    float total_venda_alimentos = 0;

    char produto_padaria[7][30] = {
        "Pao de Forma (pct)", "Pao integral (pct)", "Pao Frances (un)", "Sonho (un)",
        "Biscoito (kg)", "Pao Doce (un)", "Salgado (un)"
    };
    float preco_padaria[7] = {9.50f, 12.50f, 1.90f, 8.50f, 12.50f, 2.50f, 17.50f};
    int estoque_padaria[7];
    int carrinho_padaria[7] = {0};
    float total_padaria = 0;

    float caixa = 0, faturamento_dia = 0, abertura_caixa = 0;
    int menu = 0;

    printf("\n\nATUALIZACAO DO ESTOQUE DIARIO DA PADARIA\n\n");
    printf("Por favor, va ate a padaria e coloque a quantidade de cada item abaixo!\n");
    for (int c = 0; c < 7; c++) {
        printf("%s: ", produto_padaria[c]);
        scanf("%d", &estoque_padaria[c]);
    }

    printf("\nABERTURA DO CAIXA!!!\n\n");
    printf("Digite quantos R$ voce tem para usar no troco:\n");
    scanf("%f", &abertura_caixa);
    caixa = abertura_caixa;

    while (menu != 7) {
        printf("\n\n+-------------------------+\n");
        printf("|           MENU          |\n");
        printf("+-------------------------+\n");
        printf("|%-25s|\n", "[1] Material de Limpeza");
        printf("|%-25s|\n", "[2] Venda de Alimentos");
        printf("|%-25s|\n", "[3] Padaria");
        printf("|%-25s|\n", "[4] Pagamento");
        printf("|%-25s|\n", "[5] Abertura do Caixa");
        printf("|%-25s|\n", "[6] Fechamento do Caixa");
        printf("|%-25s|\n", "[7] Sair");
        printf("+-------------------------+\n");

        printf("Digite o numero referente ao menu principal que voce deseja acessar: ");
        scanf("%d", &menu);

        switch (menu)
        {
            case 1:
                menu_material_limpeza(produto_material_limpeza, preco_material_limpeza, estoque_material_limpeza, carrinho_limpeza, &total_limpeza);
                break;
            case 2:
                menu_venda_alimentos(produto_venda_alimentos, preco_venda_alimentos, estoque_venda_alimentos, carrinho_venda_alimentos, &total_venda_alimentos);
                break;
            case 3:
                menu_padaria(produto_padaria, preco_padaria, estoque_padaria, carrinho_padaria, &total_padaria);
                break;
            case 4:
                menu_pagamento(&total_limpeza, &total_venda_alimentos, &total_padaria, &caixa, &faturamento_dia, &total_limpeza_dia, &total_alimentos_dia, &total_padaria_dia);
                break;
            case 5:
                menu_abertura(caixa, abertura_caixa);
                break;
            case 6:
                menu_fechamento(abertura_caixa, caixa, faturamento_dia, total_limpeza_dia, total_alimentos_dia, total_padaria_dia);
                break;
            case 7:
                printf("FINALIZANDO...\n");
                break;
            default:
                printf("Desculpe. Essa opcao nao existe!\n");
                break;
        }
    }

    return 0;
}

void menu_material_limpeza(char produto[7][30], float preco[7], int estoque[7], int carrinho[7], float *total)
{
    int codigo, quantidade, cancelar_codigo, cancelar_quantidade;

    printf("\n\n+-----------------------------------------------------+\n");
    printf("|                   Material Limpeza                  |\n");
    printf("+-----------------------------------------------------+\n");

    for (int i = 0; i < 7; i++) {
        printf("|[%d] %-25s R$%05.2f [%3d unidades]|\n", i + 11, produto[i], preco[i], estoque[i]);
    }

    printf("|[18] Cancelar item                                   |\n");
    printf("|[19] Sair                                            |\n");
    printf("+-----------------------------------------------------+\n");

    printf("Digite o numero do produto que o cliente escolheu:\n");
    scanf("%d", &codigo);

    if (codigo == 19) {
        printf("Saindo do menu de material de limpeza...\n");
        return;
    }

    if (codigo == 18) {
        printf("Digite o codigo do produto que deseja cancelar: ");
        scanf("%d", &cancelar_codigo);

        int j = cancelar_codigo - 11;

        if (j < 0 || j >= 7) {
            printf("Codigo invalido!\n");
            return;
        }

        if (carrinho[j] == 0) {
            printf("Voce nao possui esse item no carrinho!\n");
            return;
        }

        printf("Digite a quantidade que deseja cancelar: ");
        scanf("%d", &cancelar_quantidade);

        if (cancelar_quantidade <= 0) {
            printf("Quantidade invalida!\n");
            return;
        }

        if (cancelar_quantidade > carrinho[j]) {
            printf("Voce nao tem essa quantidade no carrinho!\n");
            return;
        }

        carrinho[j] -= cancelar_quantidade;
        estoque[j] += cancelar_quantidade;
        *total -= (preco[j] * cancelar_quantidade);

        printf("Item cancelado com sucesso!\n");
        return;
    }

    int i = codigo - 11;

    if (i < 0 || i >= 7) {
        printf("Codigo invalido!\n");
        return;
    }

    if (estoque[i] == 0) {
        printf("Desculpe! Estamos sem estoque desse item no momento.\n");
        return;
    }

    printf("\nVoce escolheu %s!\nAgora, digite a quantidade do item:\n", produto[i]);
    scanf("%d", &quantidade);

    if (quantidade <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }

    if (quantidade > estoque[i]) {
        printf("Infelizmente nao temos estoque o suficiente!\n");
        return;
    }

    estoque[i] -= quantidade;
    carrinho[i] += quantidade;
    *total += (preco[i] * quantidade);
}

void menu_venda_alimentos(char produto[7][30], float preco[7], int estoque[7], int carrinho[7], float *total)
{
    int codigo, quantidade, cancelar_codigo, cancelar_quantidade;

    printf("\n\n+---------------------------------------------------+\n");
    printf("|                Venda de Alimentos                 |\n");
    printf("+---------------------------------------------------+\n");

    for (int i = 0; i < 7; i++) {
        printf("|[%d] %-25s R$%05.2f [%3d unidades]|\n", i + 21, produto[i], preco[i], estoque[i]);
    }

    printf("|[28] Cancelar item                                 |\n");
    printf("|[29] Sair                                          |\n");
    printf("+---------------------------------------------------+\n");

    printf("Digite o numero do produto que o cliente escolheu:\n");
    scanf("%d", &codigo);

    if (codigo == 29) {
        printf("Saindo do menu de alimentos...\n");
        return;
    }

    if (codigo == 28) {
        printf("Digite o codigo do produto que deseja cancelar: ");
        scanf("%d", &cancelar_codigo);

        int b = cancelar_codigo - 21;

        if (b < 0 || b >= 7) {
            printf("Codigo invalido!\n");
            return;
        }

        if (carrinho[b] == 0) {
            printf("Voce nao possui esse item no carrinho!\n");
            return;
        }

        printf("Digite a quantidade que deseja cancelar: ");
        scanf("%d", &cancelar_quantidade);

        if (cancelar_quantidade <= 0) {
            printf("Quantidade invalida!\n");
            return;
        }

        if (cancelar_quantidade > carrinho[b]) {
            printf("Voce nao tem essa quantidade no carrinho!\n");
            return;
        }

        carrinho[b] -= cancelar_quantidade;
        estoque[b] += cancelar_quantidade;
        *total -= (preco[b] * cancelar_quantidade);

        printf("Item cancelado com sucesso!\n");
        return;
    }

    int a = codigo - 21;

    if (a < 0 || a >= 7) {
        printf("Codigo invalido!\n");
        return;
    }

    if (estoque[a] == 0) {
        printf("Desculpe! Estamos sem estoque desse item no momento.\n");
        return;
    }

    printf("\nVoce escolheu %s!\nAgora, digite a quantidade do item:\n", produto[a]);
    scanf("%d", &quantidade);

    if (quantidade <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }

    if (quantidade > estoque[a]) {
        printf("Infelizmente nao temos estoque o suficiente!\n");
        return;
    }

    estoque[a] -= quantidade;
    carrinho[a] += quantidade;
    *total += (preco[a] * quantidade);
}

void menu_padaria(char produto[7][30], float preco[7], int estoque[7], int carrinho[7], float *total)
{
    int codigo, quantidade, cancelar_codigo, cancelar_quantidade;

    printf("\n\n+-----------------------------------------------------+\n");
    printf("|                        Padaria                      |\n");
    printf("+-----------------------------------------------------+\n");

    for (int i = 0; i < 7; i++) {
        printf("|[%d] %-25s R$%05.2f [%3d unidades]|\n", i + 31, produto[i], preco[i], estoque[i]);
    }

    printf("|[38] Cancelar item                                   |\n");
    printf("|[39] Sair                                            |\n");
    printf("+-----------------------------------------------------+\n");

    printf("Digite o numero do produto que o cliente escolheu:\n");
    scanf("%d", &codigo);

    if (codigo == 39) {
        printf("Saindo do menu da padaria...\n");
        return;
    }

    if (codigo == 38) {
        printf("Digite o codigo do produto que deseja cancelar: ");
        scanf("%d", &cancelar_codigo);

        int c = cancelar_codigo - 31;

        if (c < 0 || c >= 7) {
            printf("Codigo invalido!\n");
            return;
        }

        if (carrinho[c] == 0) {
            printf("Voce nao possui esse item no carrinho!\n");
            return;
        }

        printf("Digite a quantidade que deseja cancelar: ");
        scanf("%d", &cancelar_quantidade);

        if (cancelar_quantidade <= 0) {
            printf("Quantidade invalida!\n");
            return;
        }

        if (cancelar_quantidade > carrinho[c]) {
            printf("Voce nao tem essa quantidade no carrinho!\n");
            return;
        }

        carrinho[c] -= cancelar_quantidade;
        estoque[c] += cancelar_quantidade;
        *total -= (preco[c] * cancelar_quantidade);

        printf("Item cancelado com sucesso!\n");
        return;
    }

    int b = codigo - 31;

    if (b < 0 || b >= 7) {
        printf("Codigo invalido!\n");
        return;
    }

    if (estoque[b] == 0) {
        printf("Desculpe! Estamos sem estoque desse item no momento.\n");
        return;
    }

    printf("\nVoce escolheu %s!\nAgora, digite a quantidade do item:\n", produto[b]);
    scanf("%d", &quantidade);

    if (quantidade <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }

    if (quantidade > estoque[b]) {
        printf("Infelizmente nao temos estoque o suficiente!\n");
        return;
    }

    estoque[b] -= quantidade;
    carrinho[b] += quantidade;
    *total += (preco[b] * quantidade);
}

float calcular_desconto(float valor_total)
{
    float pagamento = 0, valor_desconto = 0;

    if (valor_total <= 50) {
        pagamento = valor_total * 0.95f;
    }
    else if (valor_total > 50 && valor_total < 200) {
        pagamento = valor_total * 0.90f;
    }
    else {
        printf("Valor total: %.2f\nQual sera o valor de desconto em porcentagem?\n", valor_total);
        scanf("%f", &valor_desconto);
        pagamento = valor_total - (valor_total * valor_desconto / 100.0f);
    }

    return pagamento;
}

void menu_pagamento(
    float *total_limpeza, float *total_alimentos, float *total_padaria,
    float *caixa, float *faturamento_dia,
    float *total_limpeza_dia, float *total_alimentos_dia, float *total_padaria_dia)
{
    float valor_total = *total_limpeza + *total_padaria + *total_alimentos;

    int opcao;
    float pagamento = 0, valor_desconto = 0, dinheiro_cliente = 0;
    int cartao = 0;

    if (valor_total <= 0) {
        printf("Ops... parece que o carrinho esta vazio...\n");
        return;
    }

    printf("\n\n+---------------------------------+\n");
    printf("|             PAGAMENTO           |\n");
    printf("+---------------------------------+\n");
    printf("|%-25s R$%05.2f|\n", "Material de Limpeza", *total_limpeza);
    printf("|%-25s R$%05.2f|\n", "Venda de Alimentos", *total_alimentos);
    printf("|%-25s R$%05.2f|\n", "Padaria", *total_padaria);
    printf("|%-25s R$%05.2f|\n", "Valor Total", valor_total);
    printf("+---------------------------------+\n");

    printf("|%-25s %8s\n", "[1] Dinheiro", "|");
    printf("|%-25s %8s\n", "[2] Cartao", "|");
    printf("|%-25s %8s\n", "[3] Voltar", "|");
    printf("+---------------------------------+\n\n");

    printf("Digite a forma de pagamento:\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            pagamento = calcular_desconto(valor_total);

            printf("O valor total com desconto deu: %.2f\n", pagamento);
            printf("Agora vamos calcular o troco!\nDigite o valor pago pelo cliente:\n");
            scanf("%f", &dinheiro_cliente);

            if (dinheiro_cliente < pagamento) {
                printf("Desculpe, esta faltando R$%.2f no valor total!\n", pagamento - dinheiro_cliente);
                return;
            }

            if (dinheiro_cliente > pagamento) {
                float troco = dinheiro_cliente - pagamento;
                printf("Troco: R$%.2f\n", troco);
            }

            *caixa += pagamento;
            *faturamento_dia += pagamento;

            *total_limpeza_dia += *total_limpeza;
            *total_alimentos_dia += *total_alimentos;
            *total_padaria_dia += *total_padaria;

            *total_limpeza = 0;
            *total_alimentos = 0;
            *total_padaria = 0;

            printf("Pagamento finalizado!\n");
            break;

        case 2:
            printf("Pagamento na maquininha foi aprovado?\n[1] SIM\n[2] NAO\n");
            scanf("%d", &cartao);

            if (cartao == 1) {
                printf("Pagamento finalizado!\n");
                *caixa += valor_total;
                *faturamento_dia += valor_total;
                *total_limpeza_dia += *total_limpeza;
                *total_alimentos_dia += *total_alimentos;
                *total_padaria_dia += *total_padaria;
                *total_limpeza = 0;
                *total_alimentos = 0;
                *total_padaria = 0;
            }
            else if (cartao == 2) {
                printf("Escolha outra opcao de pagamento!\n");
            }
            else {
                printf("Nao temos essa opcao!\n");
            }
            break;

        case 3:
            printf("\nVoltando...");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
    }
}

void menu_abertura(float caixa, float abertura_caixa)
{
    float abertura_caixa_atual = caixa;

    printf("\n\n+---------------------------------+\n");
    printf("|        ABERTURA DE CAIXA        |\n");
    printf("+---------------------------------+\n");
    printf("|%-25s R$%05.2f|\n", "Quantia Inicial:", abertura_caixa);
    printf("|%-25s R$%05.2f|\n", "Quantia Atual:", abertura_caixa_atual);
    printf("+---------------------------------+\n");
}

void menu_fechamento(float abertura_caixa, float caixa, float faturamento_dia, float total_limpeza_dia, float total_alimentos_dia, float total_padaria_dia)
{
    float faturamento_total = faturamento_dia;

    printf("\n\n+---------------------------------+\n");
    printf("|       FECHAMENTO DE CAIXA       |\n");
    printf("+---------------------------------+\n");
    printf("|%-25s R$%05.2f|\n", "Abertura do Caixa:", abertura_caixa);
    printf("|%-25s R$%05.2f|\n", "Caixa Atual:", caixa);
    printf("+---------------------------------+\n");
    printf("|%-25s R$%05.2f|\n", "Total Limpeza:", total_limpeza_dia);
    printf("|%-25s R$%05.2f|\n", "Total Alimentos:", total_alimentos_dia);
    printf("|%-25s R$%05.2f|\n", "Total Padaria:", total_padaria_dia);
    printf("|%-25s R$%05.2f|\n", "Faturamento Total:", faturamento_total);
    printf("+---------------------------------+\n");
}
