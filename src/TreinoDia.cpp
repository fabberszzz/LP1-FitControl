#include "TreinoDia.hpp"

TreinoDia::TreinoDia(const std::string& diaSemana, const std::string& nomeTreino)
    : diaSemana(diaSemana), nomeTreino(nomeTreino) {}

void TreinoDia::adicionarRegistro(const RegistroExercicio& reg) {
    exerciciosRealizados.push_back(reg);
}

std::string TreinoDia::getDiaSemana() const {
    return diaSemana;
}

std::string TreinoDia::getNomeTreino() const {
    return nomeTreino;
}

const std::vector<RegistroExercicio>& TreinoDia::getExerciciosRealizados() const {
    return exerciciosRealizados;
}
