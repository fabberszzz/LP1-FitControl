#include "GerenciadorTreino.hpp"

GerenciadorTreino::GerenciadorTreino() {}

bool GerenciadorTreino::cadastrarExercicio(const Exercicio& ex) {
    std::pair<std::set<Exercicio>::iterator, bool> resultado = catalogo.insert(ex);
    return resultado.second;
}

bool GerenciadorTreino::buscarExercicio(const std::string& nome, Exercicio& encontrado) const {
    Exercicio chave(nome, "");
    std::set<Exercicio>::const_iterator it = catalogo.find(chave);
    if (it != catalogo.end()) {
        encontrado = *it;
        return true;
    }
    return false;
}

const std::set<Exercicio>& GerenciadorTreino::getCatalogo() const {
    return catalogo;
}

void GerenciadorTreino::configurarRotina(const std::string& dia, const std::string& divisao) {
    rotinaSemanal[dia] = divisao;
}

std::string GerenciadorTreino::getDivisaoDia(const std::string& dia) const {
    std::map<std::string, std::string>::const_iterator it = rotinaSemanal.find(dia);
    if (it != rotinaSemanal.end()) {
        return it->second;
    }
    return "";
}

const std::map<std::string, std::string>& GerenciadorTreino::getRotinaSemanal() const {
    return rotinaSemanal;
}

void GerenciadorTreino::registrarTreino(const TreinoDia& treino) {
    historico.push_back(treino);
}

const std::vector<TreinoDia>& GerenciadorTreino::getHistorico() const {
    return historico;
}

std::vector<TreinoDia> GerenciadorTreino::buscarHistoricoPorDia(const std::string& dia) const {
    std::vector<TreinoDia> filtrados;
    for (size_t i = 0; i < historico.size(); ++i) {
        if (historico[i].getDiaSemana() == dia) {
            filtrados.push_back(historico[i]);
        }
    }
    return filtrados;
}
