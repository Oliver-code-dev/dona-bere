#include <stdio.h>

#include "entrada.h"
#include "cores.h"


void limparEntrada()
{

    int caractere;



    while((caractere = getchar()) != '\n' && caractere != EOF)
    {
        
    }
}


int lerInteiro(char mensagem[])
{

    int valor;


    int leitura;


    do
    {

        printf(COR_ENTRADA "%s" COR_FIM, mensagem);




        leitura = scanf("%d", &valor);


        limparEntrada();


        if(leitura == 1)
        {

            return valor;
        }


        printf(COR_ERRO "Digite apenas numeros para escolher a opcao.\n" COR_FIM);

    } while(1);
}


float lerFloat(char mensagem[])
{

    float valor;


    int leitura;


    do
    {

        printf(COR_ENTRADA "%s" COR_FIM, mensagem);



        leitura = scanf("%f", &valor);


        limparEntrada();


        if(leitura == 1)
        {

            return valor;
        }


        printf(COR_ERRO "Digite um valor numerico valido.\n" COR_FIM);

    } while(1);
}


char lerCharOpcao(char mensagem[])
{

    char valor;


    printf(COR_ENTRADA "%s" COR_FIM, mensagem);



    scanf(" %c", &valor);


    limparEntrada();


    return valor;
}
