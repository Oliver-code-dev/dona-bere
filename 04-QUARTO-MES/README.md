# Dona Berê - Quarto Mês

Quarta e última versão do sistema do Mercado Dona Berê. Esta entrega continua a profissionalização iniciada no terceiro mês e reúne os recursos de cadastro, vendas, pagamento, caixa, usuários e relatórios.

---

## 1. Contexto da Entrega

O Projeto Mensal 3 foi organizado pelo professor em duas sprints. A Sprint 03 inicia a profissionalização do sistema e a Sprint 04 representa a continuação e finalização dessa evolução. Esta pasta registra a versão mais completa produzida para o projeto.

**PDF de orientação:** `ProdutoMensal (TRÊS) - MercadoBerê (4) (1).pdf`  
**Projeto Mensal 3:** Sistema da Berê - A Profissionalização.  
**Etapa da entrega:** Sprint 04 - Finalização e documentação.

---

## 2. Objetivo

Ampliar a versão do terceiro mês com recursos para controlar o acesso dos usuários, registrar operações do sistema e detalhar os processos de vendas, pagamentos, caixa e relatórios.

---

## 3. Evolução em Relação ao Terceiro Mês

- Inclusão de usuários, login e tipos de acesso;
- Cadastro, edição e remoção de usuários;
- Validação de entrada para números e opções do menu;
- Pagamentos em dinheiro, cartão e forma mista;
- Emissão de cupom fiscal no terminal;
- Controle de sangria com valor mínimo para troco;
- Relatórios ordenados e relatórios filtrados por período;
- Registro de eventos em `logs.txt`.

---

## 4. Funcionalidades Desenvolvidas

### Usuários e acesso

- Criação do primeiro usuário administrador;
- Login antes de liberar o uso do sistema;
- Usuários administradores e usuários comuns;
- Proteção de operações administrativas.

### Clientes e produtos

- Cadastro, edição e remoção de clientes;
- Cadastro, edição e remoção de produtos;
- Verificação de CPF já cadastrado;
- Controle de estoque mínimo;
- Busca de produto por código.

### Vendas e pagamentos

- Criação de venda com vários itens;
- Registro de itens da venda em arquivo;
- Desconto na venda;
- Pagamento em dinheiro, cartão ou pagamento misto;
- Troco e confirmação de pagamento na maquininha;
- Cupom fiscal exibido no terminal;
- Pagamento posterior de vendas que ficaram em aberto.

### Caixa e relatórios

- Abertura e fechamento de caixa;
- Sangria;
- Relatório de faturamento;
- Relatórios de clientes, produtos e vendas;
- Produtos com estoque crítico;
- Produtos mais vendidos e vendas por período.

---

## 5. Organização dos Arquivos

```text
04-QUARTO-MES/
│
├── main.c
├── menus.c / menus.h
├── usuarios.c / usuarios.h
├── clientes.c / clientes.h
├── produtos.c / produtos.h
├── vendas.c / vendas.h
├── pagamentos.c / pagamentos.h
├── caixa.c / caixa.h
├── relatorios.c / relatorios.h
├── entrada.c / entrada.h
├── structs.h
├── cores.h
├── Bere4.c
└── README.md
```

`Bere4.c` é a versão reunida que inclui os módulos do sistema. Os demais arquivos mantêm o projeto organizado por funcionalidade.

---

## 6. Conteúdos Praticados

- Modularização com arquivos `.c` e `.h`;
- `struct` e passagem de estruturas para funções;
- Ponteiros;
- Leitura e gravação em arquivos `.dat`;
- Validação de dados de entrada;
- Manipulação de textos;
- Data e hora com `time.h`;
- Ordenação e relatórios;
- Bibliotecas `stdio.h`, `stdlib.h`, `string.h`, `ctype.h` e `time.h`.

---

## 7. Como Compilar e Executar

```powershell
gcc -std=c11 -o bere main.c menus.c entrada.c clientes.c produtos.c pagamentos.c caixa.c vendas.c relatorios.c usuarios.c
.\bere.exe
```

Os arquivos de dados e o arquivo `logs.txt` são criados na mesma pasta quando necessários.

---

## 8. Resultado da Evolução

Esta versão reúne os conteúdos praticados ao longo do semestre: desde o menu de vendas criado no primeiro mês até a organização de um sistema com usuários, arquivos, caixa e relatórios.
