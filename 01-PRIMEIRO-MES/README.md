# Dona Berê - Primeiro Mês

Primeira versão do sistema do Mercado Dona Berê, desenvolvida em C para rodar no terminal. Esta entrega representa o início do projeto e foi focada na construção do algoritmo principal de vendas.

---

## 1. Contexto da Entrega

O problema apresentado no Projeto Mensal 1 é o controle manual de uma mercearia com uma pequena padaria. Como os cálculos eram feitos manualmente, o objetivo foi criar uma primeira versão de sistema capaz de registrar escolhas de produtos e ajudar no momento do pagamento.

**PDF de orientação:** `2025 1 PM1 GAM1 (3).pdf`  
**Projeto Mensal 1:** Gerenciamento Automatizado de Mercearia (GAM), versão 1.

---

## 2. Objetivo

Criar um programa em C com um menu de vendas para três categorias: material de limpeza, alimentos e padaria. O programa deveria receber a quantidade escolhida, calcular o valor da compra e finalizar o pagamento em dinheiro ou cartão.

---

## 3. Funcionalidades Desenvolvidas

- Menu principal com as três categorias de produtos;
- Produtos identificados por códigos;
- Leitura da quantidade comprada;
- Acúmulo separado dos valores de limpeza, alimentos e padaria;
- Resumo da compra antes do pagamento;
- Pagamento em dinheiro com desconto e cálculo de troco;
- Simulação de pagamento por cartão;
- Exibição da quantidade de vendas e do faturamento ao encerrar o programa.

---

## 4. Conteúdos Praticados

- Variáveis dos tipos `int` e `float`;
- Entrada e saída com `scanf` e `printf`;
- Condicionais com `if` e `else`;
- Repetição com `while`;
- Organização do menu usando `switch`;
- Operações aritméticas para totais, desconto e troco.

---

## 5. Estrutura da Entrega

```text
01-PRIMEIRO-MES/
│
├── Bere.c
└── README.md
```

O programa ainda está em um único arquivo, pois esta foi a primeira etapa do projeto.

---

## 6. Como Compilar e Executar

```powershell
gcc Bere.c -o bere
.\bere.exe
```

---

## 7. Continuidade do Projeto

No segundo mês, o programa evolui para trabalhar com estoque, carrinho, funções e controle de caixa.
