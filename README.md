# Amazon Engineering Challenge: Árvores Balanceadas (AVL e Rubro-Negra)

Este repositório contém a solução desenvolvida para o **Amazon Engineering Challenge**, proposto no componente curricular **IMD0039 - Estruturas de Dados Básicas II** do Instituto Metrópole Digital (IMD/UFRN).

---

## 📋 Sobre o Projeto

Durante o evento da Black Friday, o sistema de logística da Amazon recebe volumes massivos de pacotes que exigem registro, busca e remoção em tempo real com alta eficiência. Uma Árvore Binária de Busca (BST) convencional pode degenerar para complexidade $\mathcal{O}(n)$ caso os dados cheguem ordenados ou parcialmente ordenados.

Para contornar essa limitação, este projeto implementa e compara duas estruturas auto-balanceadas:
* **Árvore AVL:** Mantém uma garantia estrita de balanceamento baseada na diferença de altura das subárvores ($\le 1$).
* **Árvore Rubro-Negra (Red-Black Tree):** Mantém o balanceamento através de coloração dos nós (Vermelho/Preto) e rotações pontuais.

O programa permite a execução interativa de ambas as estruturas, contabiliza o total de rotações e a altura final, além de tratar adequadamente exceções como duplicatas e remoção de nós inexistentes.

---

## 🛠️ Funcionalidades Implementadas

- [x] **Inserção de elementos:** Inserção dinâmica com rebalanceamento automático em tempo real.
- [x] **Remoção de elementos:** Suporte a remoção de nós sem filhos, com um filho ou com dois filhos.
- [x] **Busca eficiente:** Pesquisa em tempo logarítmico $\mathcal{O}(\log n)$.
- [x] **Percurso Em-Ordem (In-Order):** Exibição dos identificadores das encomendas em ordem crescente.
- [x] **Visualização Estrutural da Árvore:** Representação textual da hierarquia da árvore no terminal, incluindo indicação explícita da **cor dos nós** na Rubro-Negra (`[VERMELHO]` / `[PRETO]`).
- [x] **Tratamento de Exceções:** Notificação amigável para busca/remoção de elementos inexistentes e bloqueio de inserção de chaves duplicadas.
- [x] **Métricas de Desempenho:** Contagem de rotações acumuladas e monitoramento de altura final da árvore.

---

## 📁 Estrutura do Repositório

```text
.
├── main.cpp                 # Código-fonte completo (AVL + Rubro-Negra + Menu CLI)
├── README.md                # Documentação do projeto e instruções de uso
└── Apresentacao_Tecnica.pdf # Apresentação da solução em formato de slides
```

---

## 🚀 Como Compilar e Executar

### Pré-requisitos
* Compilador C++ com suporte ao padrão C++11 ou superior (`g++`, `clang++`, `MSVC`).

### Instruções

1. **Compilar o código:**

     ```bash
     g++ -O3 main.cpp -o amazon_logistics.exe
     ```

2. **Executar a aplicação:**

     ```bash
     .\amazon_logistics.exe
     ```

---

## 📖 Exemplo de Uso Interativo

Ao iniciar o programa, escolha o tipo de árvore inicial:
```text
=================================================
  AMAZON ENGINEERING CHALLENGE - LOGISTICS SYSTEM
=================================================
Selecione a estrutura de dados inicial:
1. Arvore AVL
2. Arvore Rubro-Negra
Escolha: 1
```

Em seguida, utilize o menu de opções para interagir com a estrutura selecionada:
```text
--- MENU AVL ---
1. Inserir Pacote
2. Remover Pacote
3. Buscar Pacote
4. Em-Ordem
5. Imprimir Arvore
6. Altura e Rotacoes
0. Sair
Opcao: 1
ID: 50
```

---

## 📊 Resultados e Análise Comparativa Resumida

| Cenário de Teste | Métrica Analisada | Árvore AVL | Árvore Rubro-Negra |
| :--- | :--- | :---: | :---: |
| **Inserção Ordenada** ($n=100$) | Altura Final | **Menor** ($\approx \log_2 n$) | Ligeiramente Maior ($\le 2\log_2 n$) |
| **Inserção Ordenada** ($n=100$) | Número de Rotações | Maior | **Menor** (Uso de recolorismo) |
| **Consultas / Buscas Frequentes** | Latência de Leitura | **Mais Rápida** | Rápida |
| **Operações Escrita / Modificação**| Latência de Modificação | Rebalanceamento rígido | **Mais Rápida** |

* **Conclusão Técnica:** Para cenários com alto volume de gravação/remoção contínua (como o fluxo da Black Friday da Amazon), a **Árvore Rubro-Negra** é recomendada por rebalancear mais rápido via recoloração com poucas rotações.

---

## 👤 Autor

* **Nome:** Lyan Kelvin Benicio Silva
* **Matrícula:** 20250031871
