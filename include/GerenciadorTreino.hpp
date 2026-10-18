#ifndef GERENCIADOR_TREINO_HPP
#define GERENCIADOR_TREINO_HPP

#include <set>
#include <map>
#include <vector>
#include <string>
#include "Exercicio.hpp"
#include "TreinoDia.hpp"

class GerenciadorTreino {
private:
    std::set<Exercicio> catalogo;
    std::map<std::string, std::string> rotinaSemanal;
    std::vector<TreinoDia> historico;

public:
    GerenciadorTreino();

    // Catálogo de Exercícios
    bool cadastrarExercicio(const Exercicio& ex);
    bool buscarExercicio(const std::string& nome, Exercicio& encontrado) const;
    const std::set<Exercicio>& getCatalogo() const;

    // Rotina Semanal
    void configurarRotina(const std::string& dia, const std::string& divisao);
    std::string getDivisaoDia(const std::string& dia) const;
    const std::map<std::string, std::string>& getRotinaSemanal() const;

    // Histórico de Treinos
    void registrarTreino(const TreinoDia& treino);
    const std::vector<TreinoDia>& getHistorico() const;
    std::vector<TreinoDia> buscarHistoricoPorDia(const std::string& dia) const;
};

#endif
