# Dona Berê - Terceiro Mês

Terceira versão do sistema do Mercado Dona Berê. Esta etapa marca o começo da profissionalização do projeto: o código passa a ser separado em módulos e os dados são gravados em arquivos.

---

## 1. Contexto da Entrega

Depois das versões anteriores, o projeto precisava permitir que clientes, produtos e vendas fossem cadastrados e mantidos mesmo depois de fechar o programa. O enunciado também propõe um menu mais organizado, cadastros, relatórios e recursos de caixa.

**PDF de orientação:** `ProdutoMensal (TRÊS) - MercadoBerê (4) (1).pdf`  
**Projeto Mensal 3:** Sistema da Berê - A Profissionalização.  
**Etapa da entrega:** Sprint 03 - Profissionalização - Start.

---

## 2. Objetivo

Transformar o programa das entregas anteriores em um sistema organizado em arquivos `.c` e `.h`, com estruturas para os dados da mercearia e persistência em arquivos `.dat`.

---

## 3. Evolução em Relação ao Segundo Mês

- O programa foi separado em vários arquivos por funcionalidade;
- Foram criadas estruturas para cliente, produto, venda, item de venda, pagamento e caixa;
- Clientes e produtos podem ser cadastrados, editados e removidos;
- Vendas e pagamentos passaram a ser gravados em arquivos;
- O estoque é atualizado durante o processo de venda;
- Foram incluídos relatórios para consultar os dados do sistema;
- O caixa ganhou a opção de sangria.

---

## 4. Funcionalidades Desenvolvidas

### Cadastros

- Cadastro de clientes;
- Cadastro de produtos;
- Edição e remoção de clientes e produtos;
- Geração de códigos para clientes, produtos e vendas.

### Vendas e pagamentos

- Criação de venda com itens;
- Verificação de estoque;
- Cálculo de descontos e total final;
- Registro de pagamentos;
- Atualização do estoque após a venda.

### Caixa e relatórios

- Abertura e fechamento de caixa;
- Sangria;
- Listagem de clientes, produtos e vendas;
- Relatório de faturamento;
- Relatório de produtos com estoque crítico.

---

## 5. Organização dos Arquivos

```text
03-TERCEIRO-MES/
│
├── main.c
├── menus.c / menus.h
├── clientes.c / clientes.h
├── produtos.c / produtos.h
├── vendas.c / vendas.h
├── pagamentos.c / pagamentos.h
├── caixa.c / caixa.h
├── relatorios.c / relatorios.h
├── arquivos.c / arquivos.h
├── structs.h
└── README.md
```

Os arquivos `.h` concentram as declarações e os arquivos `.c` guardam a implementação das funções de cada parte do sistema.

---

## 6. Conteúdos Praticados

- Modularização com arquivos `.c` e `.h`;
- `struct` para organizar dados relacionados;
- Funções e ponteiros;
- Manipulação de arquivos com `fopen`, `fscanf`, `fprintf` e `fclose`;
- Uso de arquivos `.dat` para guardar informações;
- Vetores e matrizes;
- Bibliotecas `stdio.h`, `stdlib.h`, `string.h`, `ctype.h` e `time.h`.

---

## 7. Como Compilar e Executar

```powershell
gcc -std=c11 -o bere main.c menus.c clientes.c produtos.c vendas.c pagamentos.c caixa.c relatorios.c arquivos.c
.\bere.exe
```

Os arquivos `.dat` são criados na mesma pasta quando o sistema precisa salvar os dados.

---

## 8. Continuidade do Projeto

No quarto mês, a versão profissionalizada recebe usuários, login, mais opções de pagamento e relatórios por período.
