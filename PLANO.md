# Plano de Implementação - FitControl

Este documento detalha o planejamento das classes, containers da STL e etapas de desenvolvimento do sistema FitControl, conforme especificado em `DESCRICAO.md` e respeitando as restrições de `AGENTS.md`.

---

## 1. Classes Propostas e Containers da STL

### 1. Classe `Serie`
- **Arquivos:** `include/Serie.hpp` e `src/Serie.cpp`
- **O que guarda:**
  - `int numero`: número da série (1, 2, ...).
  - `double carga`: carga em kg (regra: >= 0).
  - `int repeticoes`: quantidade de repetições (regra: > 0).
- **Métodos principais:**
  - `Serie(int numero, double carga, int repeticoes)`: construtor que valida os valores.
  - `int getNumero() const`
  - `double getCarga() const`
  - `int getRepeticoes() const`
- **STL utilizada:** Nenhuma internamente; armazena apenas tipos primitivos.

---

### 2. Classe `Exercicio`
- **Arquivos:** `include/Exercicio.hpp` e `src/Exercicio.cpp`
- **O que guarda:**
  - `std::string nome`: nome único do exercício (ex: "Supino Reto").
  - `std::string grupoMuscular`: grupo muscular associado (ex: "Peito").
- **Métodos principais:**
  - `Exercicio(const std::string& nome, const std::string& grupoMuscular)`
  - `std::string getNome() const`
  - `std::string getGrupoMuscular() const`
  - `bool operator<(const Exercicio& outro) const`: ordenação alfabética pelo nome.
  - `bool operator==(const Exercicio& outro) const`: comparação de igualdade pelo nome.
- **Uso da STL e justificativa:**
  - `std::string`: texto seguro e dinâmico.
  - `operator<` e `operator==`: necessários para que o objeto possa ser inserido em `std::set` e ordenado com algoritmos da STL sem depender de ponteiros ou funções extras.

---

### 3. Classe `RegistroExercicio`
- **Arquivos:** `include/RegistroExercicio.hpp` e `src/RegistroExercicio.cpp`
- **O que guarda:**
  - `Exercicio exercicio`: objeto do exercício executado.
  - `std::vector<Serie> series`: lista das séries realizadas.
- **Métodos principais:**
  - `RegistroExercicio(const Exercicio& ex)`
  - `void adicionarSerie(const Serie& s)`
  - `const Exercicio& getExercicio() const`
  - `const std::vector<Serie>& getSeries() const`
  - `double getCargaMaxima() const`: calcula a maior carga atingida entre as séries realizadas.
- **Uso da STL e justificativa:**
  - `std::vector<Serie>`: séries ocorrem em sequência ordenada (série 1, série 2, etc.). O `vector` permite inserção rápida com `push_back` e acesso sequencial simples via iteradores ou índices.

---

### 4. Classe `TreinoDia`
- **Arquivos:** `include/TreinoDia.hpp` e `src/TreinoDia.cpp`
- **O que guarda:**
  - `std::string diaSemana`: dia em que ocorreu o treino (ex: "terca").
  - `std::string nomeTreino`: divisão executada (ex: "Push").
  - `std::vector<RegistroExercicio> exerciciosRealizados`: lista dos exercícios feitos com suas respectivas séries.
- **Métodos principais:**
  - `TreinoDia(const std::string& diaSemana, const std::string& nomeTreino)`
  - `void adicionarRegistro(const RegistroExercicio& reg)`
  - `std::string getDiaSemana() const`
  - `std::string getNomeTreino() const`
  - `const std::vector<RegistroExercicio>& getExerciciosRealizados() const`
- **Uso da STL e justificativa:**
  - `std::vector<RegistroExercicio>`: preserva a ordem cronológica em que cada exercício foi feito durante a sessão de treino.

---

### 5. Classe `GerenciadorTreino` (Regras de Negócio)
- **Arquivos:** `include/GerenciadorTreino.hpp` e `src/GerenciadorTreino.cpp`
- **O que guarda:**
  - `std::set<Exercicio> catalogo`: conjunto com todos os exercícios cadastrados no sistema.
  - `std::map<std::string, std::string> rotinaSemanal`: mapeamento de cada dia da semana para uma divisão de treino (ex: `"terca"` -> `"Push"`).
  - `std::vector<TreinoDia> historico`: lista de todas as sessões de treino registradas no sistema.
- **Métodos principais:**
  - `bool cadastrarExercicio(const Exercicio& ex)`: adiciona ao catálogo; retorna `false` caso já exista (evita duplicidade).
  - `bool buscarExercicio(const std::string& nome, Exercicio& encontrado) const`: busca no catálogo por nome.
  - `void configurarRotina(const std::string& dia, const std::string& divisao)`: define a divisão de um dia no mapa.
  - `std::string getDivisaoDia(const std::string& dia) const`: retorna a divisão associada ao dia ou string vazia.
  - `void registrarTreino(const TreinoDia& treino)`: adiciona sessão ao histórico.
  - `const std::set<Exercicio>& getCatalogo() const`
  - `std::vector<TreinoDia> buscarHistoricoPorDia(const std::string& dia) const`: filtra sessões do dia solicitado.
  - `const std::vector<TreinoDia>& getHistorico() const`
- **Uso da STL e justificativa:**
  - `std::set<Exercicio>`: não aceita elementos duplicados (atende à regra de exercícios únicos) e mantém os itens ordenados automaticamente usando `operator<`.
  - `std::map<std::string, std::string>`: associa de forma natural uma chave única (dia da semana) ao seu valor (divisão de treino), permitindo busca direta `O(log N)`.
  - `std::vector<TreinoDia>`: histórico cumulativo dos treinos realizados.
  - *Separação de responsabilidades:* esta classe não faz `cin` nem `cout`; recebe dados por valor/referência constante e retorna valores ou códigos de status.

---

### 6. Interface em Modo Texto
- **Arquivos:** `include/Interface.hpp` e `src/Interface.cpp` (acionados a partir de `src/main.cpp`)
- **O que faz:**
  - Exibe menus e mensagens na tela com `std::cout`.
  - Lê opções e entradas do usuário com `std::cin`.
  - Valida falhas de leitura numérica (`std::cin.fail()`), limpando o buffer com `std::cin.clear()` e descartando caracteres inválidos com `std::cin.ignore()`.
  - Invoca os métodos da classe `GerenciadorTreino` e exibe os resultados ao usuário.

---

## 2. Etapas de Implementação

Todas as etapas mantêm o projeto compilável via `g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o fit_control`.

### Etapa 1: Modelos Básicos (`Serie` e `Exercicio`)
- **Arquivos:** `include/Serie.hpp`, `src/Serie.cpp`, `include/Exercicio.hpp`, `src/Exercicio.cpp`, `src/main.cpp`.
- **Objetivo:** Implementar atributos, validações de valores (carga >= 0, repetições > 0) e os operadores `<` e `==` de `Exercicio`.
- **Como testar:** Um teste simples na `main.cpp` cria instâncias de `Exercicio` e `Serie`, valida regras e testa comparações entre exercícios.

### Etapa 2: Composição de Treinos (`RegistroExercicio` e `TreinoDia`)
- **Arquivos:** `include/RegistroExercicio.hpp`, `src/RegistroExercicio.cpp`, `include/TreinoDia.hpp`, `src/TreinoDia.cpp`.
- **Objetivo:** Agrupar séries com `std::vector<Serie>` e compor o treino do dia com `std::vector<RegistroExercicio>`.
- **Como testar:** Na `main.cpp`, criar um `TreinoDia`, inserir séries em exercícios e calcular a carga máxima de um exercício.

### Etapa 3: Lógica do Sistema (`GerenciadorTreino`)
- **Arquivos:** `include/GerenciadorTreino.hpp`, `src/GerenciadorTreino.cpp`.
- **Objetivo:** Integrar os containers associativos `std::set` (para catálogo único) e `std::map` (para rotina semanal), além do histórico geral.
- **Como testar:** Na `main.cpp`, tentar cadastrar exercícios repetidos (verificar retorno `false`), configurar rotinas por dia e recuperar treinos filtrados.

### Etapa 4: Interface de Linha de Comando e Menus (`Interface`)
- **Arquivos:** `include/Interface.hpp`, `src/Interface.cpp`, atualização de `src/main.cpp`.
- **Objetivo:** Implementar o menu interativo em texto, a captura de dados com validação contra entradas inválidas (ex: letras onde se espera número) e mensagens de erro amigáveis.
- **Como testar:** Executar o binário interativamente e simular o fluxo de uso descrito em `DESCRICAO.md`, inserindo dados corretos e inválidos.
