# Dona Berê - Segundo Mês

Segunda versão do sistema do Mercado Dona Berê. Nesta entrega, o projeto anterior foi mantido e ampliado com recursos para controlar produtos, estoque, carrinho e caixa.

---

## 1. Contexto da Entrega

O Projeto Mensal 2 propõe a manutenção da primeira versão do sistema. A mercearia passa a ter mais produtos, itens sem estoque, necessidade de atualizar os produtos da padaria diariamente e controles de abertura e fechamento de caixa.

**PDF de orientação:** `ProdutoMensal_II - MercadoDaDonaBerê (1).pdf`  
**Projeto Mensal 2:** Sistema da Berê - A Manutenção.

---

## 2. Objetivo

Evoluir o programa do primeiro mês, organizando os dados dos produtos em vetores e criando funções para os menus. O sistema também passa a verificar estoque, permitir cancelamento de itens e mostrar informações de caixa.

---

## 3. Evolução em Relação ao Primeiro Mês

- Produtos, preços e estoque passaram a ser armazenados em vetores;
- Foram adicionados mais itens para cada categoria;
- O estoque da padaria é informado antes de iniciar as vendas;
- O carrinho registra a quantidade comprada de cada produto;
- É possível cancelar itens do carrinho e devolver a quantidade ao estoque;
- O programa foi dividido em funções para cada menu;
- Foram incluídas abertura e fechamento de caixa.

---

## 4. Funcionalidades Desenvolvidas

- Venda de produtos de limpeza, alimentos e padaria;
- Controle de estoque disponível;
- Mensagem para produto sem estoque ou quantidade maior que a disponível;
- Cancelamento de produtos já adicionados ao carrinho;
- Pagamento em dinheiro ou cartão;
- Aplicação de desconto no pagamento em dinheiro;
- Cálculo de troco;
- Abertura e fechamento de caixa com totais por categoria.

---

## 5. Conteúdos Praticados

- Vetores e matrizes;
- Funções e parâmetros;
- Ponteiros para alterar totais dentro das funções;
- Laços `for` e `while`;
- Condicionais com `if`, `else` e `switch`;
- Organização de informações de produtos em memória.

---

## 6. Estrutura da Entrega

```text
02-SEGUNDO-MES/
│
├── SISBere2.c
└── README.md
```

Mesmo com a criação de funções, o programa ainda está concentrado em um arquivo `.c`.

---

## 7. Como Compilar e Executar

```powershell
gcc SISBere2.c -o sisbere2
.\sisbere2.exe
```

---

## 8. Continuidade do Projeto

No terceiro mês, o sistema passa a ser separado em vários arquivos e começa a salvar clientes, produtos e vendas em arquivos `.dat`.
