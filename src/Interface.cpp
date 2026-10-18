#include "Interface.hpp"
#include <iostream>
#include <limits>
#include <algorithm>

Interface::Interface(GerenciadorTreino& gerenciador)
    : gerenciador(gerenciador) {}

int Interface::lerInteiro(const std::string& mensagem, int minValor) {
    int valor;
    while (true) {
        std::cout << mensagem;
        if (std::cin >> valor) {
            if (minValor == -1 || valor >= minValor) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return valor;
            } else {
                std::cout << "Erro: o valor deve ser maior ou igual a " << minValor << ".\n";
            }
        } else {
            std::cout << "Entrada invalida! Digite um numero inteiro valido.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

double Interface::lerDouble(const std::string& mensagem, double minValor) {
    double valor;
    while (true) {
        std::cout << mensagem;
        if (std::cin >> valor) {
            if (valor >= minValor) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return valor;
            } else {
                std::cout << "Erro: a carga deve ser maior ou igual a " << minValor << ".\n";
            }
        } else {
            std::cout << "Entrada invalida! Digite um numero valido.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::string Interface::lerLinha(const std::string& mensagem) {
    std::string entrada;
    while (true) {
        std::cout << mensagem;
        std::getline(std::cin, entrada);
        if (!entrada.empty()) {
            return entrada;
        }
    }
}

void Interface::menuCadastrarExercicio() {
    std::cout << "\n--- CADASTRAR EXERCICIO ---\n";
    std::string nome = lerLinha("Digite o nome do exercicio: ");
    std::string grupo = lerLinha("Digite o grupo muscular: ");

    Exercicio novoEx(nome, grupo);
    if (gerenciador.cadastrarExercicio(novoEx)) {
        std::cout << "Exercicio cadastrado com sucesso!\n";
    } else {
        std::cout << "Erro: Ja existe um exercicio cadastrado com este nome.\n";
    }
}

void Interface::menuConfigurarRotina() {
    std::cout << "\n--- CONFIGURAR ROTINA SEMANAL ---\n";
    std::string dia = lerLinha("Digite o dia da semana (ex: segunda, terca): ");
    std::string divisao = lerLinha("Digite o nome da divisao de treino (ex: Push, Pull, Legs): ");

    gerenciador.configurarRotina(dia, divisao);
    std::cout << "Rotina para " << dia << " configurada como " << divisao << " com sucesso!\n";
}

void Interface::menuRegistrarTreino() {
    std::cout << "\n--- REGISTRAR TREINO DO DIA ---\n";
    if (gerenciador.getCatalogo().empty()) {
        std::cout << "Nenhum exercicio cadastrado no catalogo! Cadastre exercicios primeiro.\n";
        return;
    }

    std::string dia = lerLinha("Digite o dia da semana (ex: terca): ");
    std::string divisao = gerenciador.getDivisaoDia(dia);

    if (divisao.empty()) {
        std::cout << "Nao ha divisao configurada para esse dia. Digite uma para este treino.\n";
        divisao = lerLinha("Divisao do treino: ");
    } else {
        std::cout << "Treino selecionado: " << divisao << "\n";
    }

    TreinoDia treino(dia, divisao);

    int qtdExercicios = lerInteiro("Quantos exercicios deseja registrar? ", 1);

    for (int i = 0; i < qtdExercicios; ++i) {
        std::cout << "\nExercicio #" << (i + 1) << ":\n";
        std::string nomeEx = lerLinha("Digite o exercicio: ");

        Exercicio exercicio("", "");
        if (!gerenciador.buscarExercicio(nomeEx, exercicio)) {
            std::cout << "Exercicio nao encontrado no catalogo!\n";
            --i;
            continue;
        }

        RegistroExercicio reg(exercicio);
        int qtdSeries = lerInteiro("Quantidade de series: ", 1);

        for (int s = 1; s <= qtdSeries; ++s) {
            double carga = lerDouble("Serie " + std::to_string(s) + " - Carga (kg): ", 0.0);
            int reps = lerInteiro("Serie " + std::to_string(s) + " - Repeticoes: ", 1);
            reg.adicionarSerie(Serie(s, carga, reps));
        }

        treino.adicionarRegistro(reg);
    }

    gerenciador.registrarTreino(treino);
    std::cout << "\nTreino registrado com sucesso!\n";
}

void Interface::menuConsultarHistorico() {
    std::cout << "\n--- CONSULTAR HISTORICO ---\n";
    if (gerenciador.getHistorico().empty()) {
        std::cout << "Nenhum treino registrado ate o momento.\n";
        return;
    }

    std::cout << "1. Ver todos os treinos\n";
    std::cout << "2. Filtrar por dia da semana\n";
    int op = lerInteiro("Escolha uma opcao: ", 1);

    std::vector<TreinoDia> treinos;
    if (op == 1) {
        treinos = gerenciador.getHistorico();
    } else {
        std::string dia = lerLinha("Digite o dia da semana: ");
        treinos = gerenciador.buscarHistoricoPorDia(dia);
        if (treinos.empty()) {
            std::cout << "Nenhum treino encontrado para o dia: " << dia << "\n";
            return;
        }
    }

    for (size_t t = 0; t < treinos.size(); ++t) {
        std::cout << "\n==============================\n";
        std::cout << "Dia: " << treinos[t].getDiaSemana() << " | Treino: " << treinos[t].getNomeTreino() << "\n";
        const std::vector<RegistroExercicio>& registros = treinos[t].getExerciciosRealizados();

        for (size_t r = 0; r < registros.size(); ++r) {
            std::cout << "  - " << registros[r].getExercicio().getNome()
                      << " (" << registros[r].getExercicio().getGrupoMuscular() << "):\n";
            const std::vector<Serie>& series = registros[r].getSeries();
            for (size_t s = 0; s < series.size(); ++s) {
                std::cout << "      Serie " << series[s].getNumero()
                          << ": " << series[s].getCarga() << " kg x "
                          << series[s].getRepeticoes() << " reps\n";
            }
        }
    }
}

void Interface::menuVerEvolucao() {
    std::cout << "\n--- EVOLUCAO E RANKING DE CARGAS ---\n";
    if (gerenciador.getHistorico().empty()) {
        std::cout << "Nenhum treino registrado para calcular evolucao.\n";
        return;
    }

    std::string nomeEx = lerLinha("Digite o nome do exercicio para consultar: ");
    Exercicio ex("", "");
    if (!gerenciador.buscarExercicio(nomeEx, ex)) {
        std::cout << "Exercicio nao encontrado no catalogo!\n";
        return;
    }

    std::vector<double> cargas;
    const std::vector<TreinoDia>& historico = gerenciador.getHistorico();
    for (size_t i = 0; i < historico.size(); ++i) {
        const std::vector<RegistroExercicio>& registros = historico[i].getExerciciosRealizados();
        for (size_t j = 0; j < registros.size(); ++j) {
            if (registros[j].getExercicio() == ex) {
                cargas.push_back(registros[j].getCargaMaxima());
            }
        }
    }

    if (cargas.empty()) {
        std::cout << "Nao ha registros de execucao para o exercicio " << nomeEx << ".\n";
        return;
    }

    // Ordenação com algoritmo da STL
    std::sort(cargas.begin(), cargas.end());

    std::cout << "Historico de cargas maximas registradas (ordenadas):\n";
    for (size_t i = 0; i < cargas.size(); ++i) {
        std::cout << " - " << cargas[i] << " kg\n";
    }
    std::cout << "Recorde pessoal (Carga Maxima): " << cargas.back() << " kg!\n";
}

void Interface::executar() {
    while (true) {
        std::cout << "\n=== MENU FITCONTROL ===\n";
        std::cout << "1. Cadastrar Exercicio\n";
        std::cout << "2. Configurar Rotina Semanal\n";
        std::cout << "3. Registrar Treino do Dia\n";
        std::cout << "4. Consultar Historico\n";
        std::cout << "5. Ver Evolucao / Carga Maxima\n";
        std::cout << "6. Sair\n";

        int opcao = lerInteiro("Escolha uma opcao: ", 1);

        switch (opcao) {
            case 1:
                menuCadastrarExercicio();
                break;
            case 2:
                menuConfigurarRotina();
                break;
            case 3:
                menuRegistrarTreino();
                break;
            case 4:
                menuConsultarHistorico();
                break;
            case 5:
                menuVerEvolucao();
                break;
            case 6:
                std::cout << "Saindo do FitControl. Bons treinos!\n";
                return;
            default:
                std::cout << "Opcao invalida! Tente novamente.\n";
                break;
        }
    }
}
