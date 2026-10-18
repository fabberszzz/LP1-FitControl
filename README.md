# Sistema de Registro de Treinos (FitControl)

## Como Compilar
Para compilar o projeto em C++11, utilize o seguinte comando no terminal:
```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o fit_control
```

## Como Executar os Exemplos
Você pode rodar os cenários de teste presentes na pasta `exemplos/` usando o redirecionamento de entrada padrão (`<`):

- **Linux / macOS:**
  ```bash
  ./fit_control < exemplos/cenario1.txt
  ```

- **PowerShell (Windows):**
  ```powershell
  Get-Content exemplos\cenario1.txt | .\fit_control
  ```

- **Prompt de Comando (CMD - Windows):**
  ```cmd
  fit_control.exe < exemplos\cenario1.txt
  ```

### Cenários disponíveis:
- **`cenario1.txt`:** Fluxo introdutório — cadastro simples de exercício ("Supino Reto"), definição de rotina ("Push"), registro de 2 séries, consulta de histórico e evolução.
- **`cenario2.txt`:** Treino completo de pernas ("Legs") — cadastro de 5 exercícios, registro de treino com 3 exercícios simultâneos (8 séries no total), histórico e recorde no agachamento.
- **`cenario3.txt`:** Progressão de cargas na mesma semana — múltiplos treinos de "Push" registrando aumento de carga no Supino Inclinado com halteres e verificação do histórico e ordenação das cargas.
- **`cenario4.txt`:** Teste de robustez e tratamento de erros — tenta cadastrar exercício repetido, buscar exercício inexistente, digita texto ("abc", "xyz") e números negativos onde o programa exige números válidos, verificando a recuperação do buffer.
- **`cenario5.txt`:** Semana completa de treinos ("Pull") — configuração de rotina para segunda, quarta e sexta com múltiplos exercícios, volume de séries, filtros de histórico por dia específico e recordes pessoais.

---

## Onde uso a STL

O projeto faz uso direto de vários containers e algoritmos da biblioteca padrão do C++ (STL), com escolhas alinhadas às necessidades de cada entidade:

1. **`std::set<Exercicio>` (em `GerenciadorTreino`)**:
   - **Onde é usado:** No atributo `catalogo` da classe `GerenciadorTreino`.
   - **Por que foi usado:** O catálogo de exercícios exige que não haja nomes duplicados e mantém uma ordenação alfabética natural. O `std::set` garante unicidade na inserção (`insert().second`) e busca em tempo logarítmico `O(log N)` utilizando o `operator<` implementado na classe `Exercicio`.

2. **`std::map<std::string, std::string>` (em `GerenciadorTreino`)**:
   - **Onde é usado:** No atributo `rotinaSemanal` da classe `GerenciadorTreino`.
   - **Por que foi usado:** Associa uma chave única (o dia da semana, como `"segunda"`, `"terca"`) ao seu respectivo valor (a divisão de treino, como `"Pull"`, `"Push"`). Isso permite consultar de forma imediata e flexível qual treino está planejado para determinado dia.

3. **`std::vector` (em `RegistroExercicio`, `TreinoDia` e `GerenciadorTreino`)**:
   - **`std::vector<Serie>` em `RegistroExercicio`:** Armazena a sequência cronológica de séries realizadas dentro de um exercício. O vetor é ideal aqui por garantir acesso contíguo em memória e inserção eficiente ao final com `push_back`.
   - **`std::vector<RegistroExercicio>` em `TreinoDia`:** Guarda a lista ordenada de exercícios praticados no dia.
   - **`std::vector<TreinoDia>` em `GerenciadorTreino`:** Guarda o histórico geral de todas as sessões de treino registradas no sistema.
   - **`std::vector<double>` em `Interface::menuVerEvolucao`:** Coleta todas as cargas máximas registradas de um exercício para que possam ser ordenadas.

4. **Algoritmos da STL (`<algorithm>`)**:
   - **`std::sort` (em `Interface::menuVerEvolucao`):** Utilizado para ordenar a lista de cargas máximas registradas de um exercício específico, facilitando a visualização da progressão e a obtenção do recorde pessoal (`cargas.back()`).

---

## Como usei a IA

O desenvolvimento do FitControl com auxílio da IA foi conduzido de forma modular e incremental, dividindo o projeto em etapas bem delimitadas:

1. **Planejamento Inicial (`PLANO.md`):**
   - Antes de iniciar a codificação, foram analisados os requisitos de `DESCRICAO.md` e as diretrizes de desenvolvimento.
   - A IA propôs o detalhamento das classes, quais containers da STL seriam utilizados e justificou cada escolha, dividindo a implementação em 4 etapas testáveis.

2. **Etapa 1 - Modelos Básicos (`Serie` e `Exercicio`):**
   - Implementação das classes fundamentais em `include/` e `src/`.
   - Criação de testes unitários na `main.cpp` para validar carga $\ge 0$, repetições $> 0$ e os operadores de comparação (`operator<` e `operator==`).

3. **Etapa 2 - Composição de Séries e Treinos (`RegistroExercicio` e `TreinoDia`):**
   - Criação das classes que usam `std::vector` para agrupar séries e exercícios de um treino.
   - Validação via asserções na `main.cpp` do cálculo de carga máxima e integridade dos vetores.

4. **Etapa 3 - Lógica de Negócio (`GerenciadorTreino`):**
   - Implementação do catálogo com `std::set` (garantindo unicidade e rejeitando duplicatas) e da rotina semanal com `std::map`.
   - Isolamento completo das regras de negócio, sem uso de `std::cin` ou `std::cout` nas classes internas.

5. **Etapa 4 - Interface em Linha de Comando (`Interface`):**
   - Implementação da classe `Interface` centralizando toda a interação em texto, menus e validação de falhas de buffer (`cin.clear()` e `cin.ignore()`).
   - Simulação completa do fluxo do programa para confirmar o funcionamento ponta a ponta.
