# Sistema Dona Berê

Projeto acadêmico desenvolvido em linguagem C durante o primeiro semestre. O sistema foi construído em entregas mensais, sempre a partir do mesmo problema: apoiar o funcionamento de uma pequena mercearia pelo terminal.

O repositório mantém as quatro versões do projeto para registrar a evolução do aprendizado, desde um menu simples de vendas até uma versão organizada em módulos, com arquivos, usuários, caixa e relatórios.

---

## 1. Contexto do Projeto

O cenário apresentado nos projetos mensais é o da Dona Berê, dona de uma mercearia que fazia os controles de produtos, vendas e pagamentos manualmente. A proposta da disciplina foi desenvolver, aos poucos, um sistema em C para diminuir erros de cálculo e organizar essas operações.

A cada mês, uma nova entrega foi criada a partir da anterior. Por isso, as pastas deste repositório não são cópias iguais: elas mostram as mudanças feitas no programa conforme os conteúdos eram estudados.

---

## 2. Objetivos

Os objetivos do projeto foram:

- Praticar lógica de programação e linguagem C;
- Criar menus e interações pelo terminal;
- Trabalhar com produtos, quantidades, vendas e pagamentos;
- Utilizar vetores, matrizes, funções, ponteiros e `struct`;
- Organizar o código em arquivos `.c` e `.h`;
- Gravar dados de clientes, produtos e vendas em arquivos `.dat`;
- Criar recursos de caixa, sangria e relatórios.

---

## 3. Evolução do Projeto

### Primeiro mês - Algoritmo e menu

A primeira versão concentra os conceitos básicos de C. O sistema possui as categorias de limpeza, alimentos e padaria, recebe a quantidade de produtos e permite finalizar a compra em dinheiro ou cartão.

Principais conteúdos usados:

- Variáveis `int` e `float`;
- `printf` e `scanf`;
- `if`, `else`, `while` e `switch`;
- Cálculo de totais, desconto e troco.

### Segundo mês - Manutenção e ampliação

Na segunda entrega, o sistema recebe mais produtos e passa a trabalhar com estoque e carrinho. Também entram funções, vetores, matrizes e o controle de abertura e fechamento de caixa.

Principais mudanças:

- Produtos, preços e estoque organizados em vetores;
- Atualização diária do estoque da padaria;
- Cancelamento de itens do carrinho;
- Funções para os menus de cada categoria;
- Abertura e fechamento de caixa.

### Terceiro mês - Profissionalização: início

O programa passa a ser dividido em arquivos `.c` e `.h`. Nesta etapa, os dados deixam de existir somente enquanto o programa está aberto e passam a ser gravados em arquivos `.dat`.

Principais mudanças:

- Uso de `struct` para cliente, produto, venda, pagamento e caixa;
- Cadastro, edição e exclusão de clientes e produtos;
- Registros de vendas, itens e pagamentos;
- Relatórios de clientes, produtos, vendas e faturamento;
- Organização em módulos.

### Quarto mês - Profissionalização: finalização

A quarta versão reúne e amplia as funcionalidades anteriores. O sistema recebe controle de usuários, login, mais opções de pagamento e relatórios mais detalhados.

Principais mudanças:

- Cadastro de usuários e login;
- Tipos de acesso para usuários;
- Pagamento em dinheiro, cartão ou forma mista;
- Emissão de cupom fiscal no terminal;
- Sangria e fechamento de caixa;
- Relatórios por período, estoque crítico e produtos mais vendidos;
- Registro de eventos em `logs.txt`.

---

## 4. Organização do Repositório

```text
DONA BERE/
│
├── README.md
├── .gitignore
│
├── 01-PRIMEIRO-MES/
│   ├── Bere.c
│   └── README.md
│
├── 02-SEGUNDO-MES/
│   ├── SISBere2.c
│   └── README.md
│
├── 03-TERCEIRO-MES/
│   ├── main.c
│   ├── menus.c / menus.h
│   ├── clientes.c / clientes.h
│   ├── produtos.c / produtos.h
│   ├── vendas.c / vendas.h
│   ├── pagamentos.c / pagamentos.h
│   ├── caixa.c / caixa.h
│   ├── relatorios.c / relatorios.h
│   ├── arquivos.c / arquivos.h
│   ├── structs.h
│   └── README.md
│
└── 04-QUARTO-MES/
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
    └── README.md
```

Cada pasta possui um README com os detalhes da respectiva entrega e o comando de compilação.

---

## 5. Tecnologias e Conteúdos Praticados

### Linguagem e bibliotecas

- **C** - linguagem utilizada no desenvolvimento;
- **`stdio.h`** - entrada, saída e arquivos;
- **`stdlib.h`** - funções auxiliares e memória dinâmica;
- **`string.h`** - manipulação de textos;
- **`ctype.h`** - tratamento de caracteres;
- **`time.h`** - data e hora das vendas e registros.

### Conceitos trabalhados

- Estruturas condicionais e de repetição;
- Funções e passagem de parâmetros;
- Vetores e matrizes;
- Ponteiros;
- `struct`;
- Modularização em arquivos `.c` e `.h`;
- Leitura e gravação em arquivos `.dat`;
- Organização de dados e geração de relatórios.

---

## 6. Documentos de Orientação

Os projetos foram desenvolvidos a partir dos enunciados enviados pelo professor. Os PDFs estão identificados abaixo e servem como referência para cada entrega.

| Entrega | Documento de orientação |
| --- | --- |
| Primeiro mês | `2025 1 PM1 GAM1 (3).pdf` - Projeto Mensal 1: Gerenciamento Automatizado de Mercearia (GAM), versão 1. |
| Segundo mês | `ProdutoMensal_II - MercadoDaDonaBerê (1).pdf` - Projeto Mensal 2: Sistema da Berê - A Manutenção. |
| Terceiro mês | `ProdutoMensal (TRÊS) - MercadoBerê (4) (1).pdf` - Projeto Mensal 3: Sistema da Berê - A Profissionalização, Sprint 03. |
| Quarto mês | `ProdutoMensal (TRÊS) - MercadoBerê (4) (1).pdf` - continuação do Projeto Mensal 3, Sprint 04: finalização e documentação. |

Os PDFs não foram adicionados ao repositório; os nomes foram mantidos para registrar a origem e o contexto acadêmico de cada etapa.

---

## 7. Como Compilar

Cada versão possui seu próprio comando de compilação, pois o número de arquivos aumenta ao longo do projeto.

### Primeiro mês

```powershell
cd 01-PRIMEIRO-MES
gcc Bere.c -o bere
.\bere.exe
```

### Segundo mês

```powershell
cd 02-SEGUNDO-MES
gcc SISBere2.c -o sisbere2
.\sisbere2.exe
```

Para o terceiro e quarto mês, consulte o README da pasta correspondente.

---

## 8. Status do Projeto

**Entregas acadêmicas concluídas.**

Este repositório preserva as versões desenvolvidas durante o semestre e mostra o processo de evolução do sistema Dona Berê em C.
