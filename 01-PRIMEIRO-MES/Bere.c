#include <stdio.h>

int main() {

    int menu = 0;
    int codigo = 0;
    int quantidade = 0;
    int contVendas = 0;

    float faturamentoTotal = 0;
    float valorUnitario = 0;

    float totalLimpeza = 0;
    float totalAlimentos = 0;
    float totalPadaria = 0;

    while(menu != 5){

        printf("\n\n+-----------------------+\n");
        printf("|         MENU          |\n");
        printf("+-----------------------+\n");
        printf("| [1] Material Limpeza  |\n");
        printf("| [2] Venda Alimentos   |\n");
        printf("| [3] Padaria           |\n");
        printf("| [4] Pagamento         |\n");
        printf("| [5] Sair              |\n");
        printf("+-----------------------+\n");
        printf("Digite a opcao: ");
        scanf("%d",&menu);

        switch(menu){

        case 1:

            printf("\n+-----------------------------+\n");
            printf("|      Material de Limpeza    |\n");
            printf("+-----------------------------+\n");
            printf("| [11] Detergente      R$01.99|\n");
            printf("| [12] Sabao em po     R$08.99|\n");
            printf("| [13] Esponja         R$01.50|\n");
            printf("| [14] Amaciante       R$15.00|\n");
            printf("| [15] Voltar ao Menu         |\n");
            printf("+-----------------------------+\n");

            printf("Codigo do item: ");
            scanf("%d",&codigo);

            while(codigo < 11 || codigo > 15){
                printf("Opcao invalida!\n");
                scanf("%d",&codigo);
            }

            if(codigo == 15){
                break;
            }

            if(codigo == 11) valorUnitario = 1.99;
            else if(codigo == 12) valorUnitario = 8.99;
            else if(codigo == 13) valorUnitario = 1.50;
            else if(codigo == 14) valorUnitario = 15.00;

            printf("Quantidade: ");
            scanf("%d",&quantidade);

            while(quantidade <= 0){
                printf("Quantidade invalida!\n");
                scanf("%d",&quantidade);
            }

            totalLimpeza += valorUnitario * quantidade;
            printf("Adicionado ao carrinho!\n");

        break;

        case 2:

            printf("+-------------------------------+\n");
            printf("|       Venda de Alimentos      |\n");
            printf("+-------------------------------+\n");
            printf("| [21] Cafe              R$19.99|\n");
            printf("| [22] Leite (cx)        R$05.90|\n");
            printf("| [23] Arroz (1kg)       R$04.50|\n");
            printf("| [24] Feijao Preto      R$08.00|\n");
            printf("| [25] Acucar (1kg)      R$05.00|\n");
            printf("| [26] Voltar ao Menu           |\n");
            printf("+-------------------------------+\n");

            printf("Codigo do item: ");
            scanf("%d",&codigo);

            while(codigo < 21 || codigo > 26){
                printf("Opcao invalida!\n");
                scanf("%d",&codigo);
            }

            if(codigo == 26){
                break;
            }

            if(codigo == 21) valorUnitario = 19.99;
            else if(codigo == 22) valorUnitario = 5.90;
            else if(codigo == 23) valorUnitario = 4.50;
            else if(codigo == 24) valorUnitario = 8.00;
            else if(codigo == 25) valorUnitario = 5.00;

            printf("Quantidade: ");
            scanf("%d",&quantidade);

            while(quantidade <= 0){
                printf("Quantidade invalida!\n");
                scanf("%d",&quantidade);
            }

            totalAlimentos += valorUnitario * quantidade;

        break;

        case 3:

            printf("+--------------------------------+\n");
            printf("|            Padaria             |\n");
            printf("+--------------------------------+\n");
            printf("| [31] Pao de Forma      R$09.50 |\n");
            printf("| [32] Pao Integral      R$12.50 |\n");
            printf("| [33] Pao Frances       R$01.90 |\n");
            printf("| [34] Sonho             R$08.50 |\n");
            printf("| [35] Voltar ao Menu           |\n");
            printf("+--------------------------------+\n");

            printf("Codigo do item: ");
            scanf("%d",&codigo);

            while(codigo < 31 || codigo > 35){
                printf("Opcao invalida!\n");
                scanf("%d",&codigo);
            }

            if(codigo == 35){
                break;
            }

            if(codigo == 31) valorUnitario = 9.50;
            else if(codigo == 32) valorUnitario = 12.50;
            else if(codigo == 33) valorUnitario = 1.90;
            else if(codigo == 34) valorUnitario = 8.50;

            printf("Quantidade: ");
            scanf("%d",&quantidade);

            while(quantidade <= 0){
                printf("Quantidade invalida!\n");
                scanf("%d",&quantidade);
            }

            totalPadaria += valorUnitario * quantidade;

        break;

        case 4:

        {

            int metodoPago,confirmacao,pagoFinalizado=0;

            float totalVenda = totalLimpeza + totalAlimentos + totalPadaria;
            float valorRecebido;

            if(totalVenda == 0){
                printf("\nCarrinho vazio!\n");
                break;

            }

            while(pagoFinalizado == 0){

                printf("\n--- RESUMO DA COMPRA ---\n");
                printf("Limpeza: R$ %.2f | Alimentos: R$ %.2f | Padaria: R$ %.2f\n",totalLimpeza,totalAlimentos,totalPadaria);
                printf("TOTAL: R$ %.2f\n",totalVenda);

                printf("Forma pagamento (1-Dinheiro 2-Cartao 3-Cancelar): ");
                scanf("%d",&metodoPago);

                while(metodoPago < 1 || metodoPago > 3){
                    printf("Opcao invalida!\n");
                    scanf("%d",&metodoPago);
                }

                if(metodoPago == 1){

                    float totalComDesconto;

                    if(totalVenda <= 50) totalComDesconto = totalVenda * 0.95;
                    else if(totalVenda < 100) totalComDesconto = totalVenda * 0.90;
                    else totalComDesconto = totalVenda * 0.82;

                    printf("Total com desconto: %.2f\n",totalComDesconto);

                    printf("Valor recebido: ");
                    scanf("%f",&valorRecebido);

                    while(valorRecebido < totalComDesconto){

                        float pagoExtra;

                        printf("Faltam %.2f: ",totalComDesconto - valorRecebido);
                        scanf("%f",&pagoExtra);

                        valorRecebido += pagoExtra;
                    }

                    printf("Troco: %.2f\n",valorRecebido - totalComDesconto);

                    faturamentoTotal += totalComDesconto;
                    pagoFinalizado = 1;
                }

                else if(metodoPago == 2){

                    printf("Processando cartao...\n");

                    printf("Pagamento aprovado? (1-Sim / 2-Nao): ");
                    scanf("%d",&confirmacao);

                    if(confirmacao == 1){

                        faturamentoTotal += totalVenda;
                        pagoFinalizado = 1;

                        printf("Pagamento aprovado!\n");
                    }

                    else{

                        printf("Erro na transacao.\n");
                    }
                }

                else{

                    break;
                }
            }

            if(pagoFinalizado == 1){

                contVendas++;

                printf("Compra finalizada!\n");

                totalLimpeza = 0;
                totalAlimentos = 0;
                totalPadaria = 0;
            }

        }

        break;

        case 5:

            printf("Encerrando sistema...\n");

        break;

        default:

            printf("Opcao invalida!\n");

        }

    }

    printf("\n==================================\n");
    printf("        FATURAMENTO DO DIA        \n");
    printf("==================================\n");
    printf("Total clientes: %d\n",contVendas);
    printf("Faturamento total: R$ %.2f\n",faturamentoTotal);
    printf("==================================\n");

    return 0;
}
