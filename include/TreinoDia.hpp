#ifndef TREINO_DIA_HPP
#define TREINO_DIA_HPP

#include <string>
#include <vector>
#include "RegistroExercicio.hpp"

class TreinoDia {
private:
    std::string diaSemana;
    std::string nomeTreino;
    std::vector<RegistroExercicio> exerciciosRealizados;

public:
    TreinoDia(const std::string& diaSemana, const std::string& nomeTreino);

    void adicionarRegistro(const RegistroExercicio& reg);

    std::string getDiaSemana() const;
    std::string getNomeTreino() const;
    const std::vector<RegistroExercicio>& getExerciciosRealizados() const;
};

#endif
