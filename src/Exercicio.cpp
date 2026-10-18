#include "Exercicio.hpp"

Exercicio::Exercicio(const std::string& nome, const std::string& grupoMuscular)
    : nome(nome), grupoMuscular(grupoMuscular) {}

std::string Exercicio::getNome() const {
    return nome;
}

std::string Exercicio::getGrupoMuscular() const {
    return grupoMuscular;
}

bool Exercicio::operator<(const Exercicio& outro) const {
    return nome < outro.nome;
}

bool Exercicio::operator==(const Exercicio& outro) const {
    return nome == outro.nome;
}
