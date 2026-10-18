# Sistema de Registro de Treinos (FitControl)

## Nome e ideia
O FitControl é um sistema em modo texto desenvolvido em C++ para gerenciar rotinas de musculação e registrar o progresso de cargas e repetições. Ele serve para praticantes de academia organizarem suas divisões de treino semanais (como PPL + UL) e detalharem o desempenho exato de cada exercício por série.

## O que o sistema guarda
- **Rotinas de Treino:** Divisões associadas aos dias da semana (ex: Segunda - Pull, Terça - Push).
- **Exercícios:** Nome do exercício e grupo muscular correspondente.
- **Séries:** Número da série, carga utilizada (em kg) e quantidade de repetições executadas em um exercício.

## O que dá para fazer
1. **Cadastrar Exercício:** Adiciona um novo exercício informando seu nome e grupo muscular.
2. **Configurar Rotina Semanal:** Associa um tipo de treino (ex: Push, Pull, Legs) a um dia da semana.
3. **Registrar Treino / Séries:** Seleciona o dia/treino e cadastra detalhadamente as séries de cada exercício (ex: Supino Reto com 5 séries, especificando a carga e as repetições de cada uma).
4. **Consultar Histórico:** Mostra os treinos realizados em uma data ou dia da semana específico, listando os exercícios e o detalhamento de cada série.
5. **Ver Evolução / Ranking:** Ordena os exercícios ou exibe a carga máxima atingida em um exercício utilizando algoritmos de ordenação da STL.

## Regras
- Não podem existir dois exercícios cadastrados com exatamente o mesmo nome.
- A carga de uma série deve ser maior ou igual a 0, e as repetições devem ser estritamente maiores que 0.
- Dias da semana e nomes de treinos devem ser identificados de forma padronizada.
- A ordenação de exercícios deve respeitar o operador de menor (`operator<`) definido na classe.

## Quando algo dá errado
- **Item não encontrado:** Se o usuário tentar buscar ou registrar um exercício que não está cadastrado, o sistema avisa que o exercício não existe e retorna ao menu.
- **Cadastro duplicado:** Se tentar cadastrar um exercício com um nome já existente, o sistema recusa e exibe uma mensagem de erro.
- **Lista vazia:** Se o usuário tentar consultar histórico ou gerar relatórios sem nenhum treino cadastrado, o sistema informa que não há dados registrados.
- **Entrada inválida:** Se o usuário digitar letras onde o programa espera um número (como na carga ou repetições), o sistema limpa o buffer de entrada, exibe um aviso de formato inválido e pede o dado novamente.

## Classes que eu imagino
- `Exercicio`: Guarda as informações básicas do exercício (nome e grupo muscular), contendo os operadores de comparação (`operator==` e `operator<`).
- `Serie`: Guarda os dados de uma única execução (número da série, carga e repetições).
- `RotinaTreino`: Gerencia a divisão de um dia específico, contendo uma coleção de exercícios e suas respectivas séries.
- `GerenciadorTreino`: Classe de controle principal que armazena os dados utilizando containers da STL (`std::map`, `std::set`, etc.) e gerencia a lógica de negócio separada da interface.

## Exemplo de uso

> ./sistema
> 
> === MENU FITCONTROL ===
> 1. Cadastrar Exercicio
> 2. Registrar Treino do Dia
> 3. Consultar Historico
> 4. Sair
> Escolha uma opcao: 2
> 
> Digite o dia da semana (ex: terca): terca
> Treino selecionado: Push
> Digite o exercicio: Supino Reto
> Quantidade de series: 2
> Serie 1 - Carga (kg): 50
> Serie 1 - Repeticoes: 12
> Serie 2 - Carga (kg): 60
> Serie 2 - Repeticoes: 10
> Treino registrado com sucesso!