#ifndef REGISTRO_EXERCICIO_HPP
#define REGISTRO_EXERCICIO_HPP

#include <vector>
#include "Exercicio.hpp"
#include "Serie.hpp"

class RegistroExercicio {
private:
    Exercicio exercicio;
    std::vector<Serie> series;

public:
    RegistroExercicio(const Exercicio& exercicio);

    void adicionarSerie(const Serie& serie);

    const Exercicio& getExercicio() const;
    const std::vector<Serie>& getSeries() const;

    double getCargaMaxima() const;
};

#endif
