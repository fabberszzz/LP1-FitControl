#include "RegistroExercicio.hpp"

RegistroExercicio::RegistroExercicio(const Exercicio& exercicio)
    : exercicio(exercicio) {}

void RegistroExercicio::adicionarSerie(const Serie& serie) {
    series.push_back(serie);
}

const Exercicio& RegistroExercicio::getExercicio() const {
    return exercicio;
}

const std::vector<Serie>& RegistroExercicio::getSeries() const {
    return series;
}

double RegistroExercicio::getCargaMaxima() const {
    if (series.empty()) {
        return 0.0;
    }
    double maxCarga = series[0].getCarga();
    for (size_t i = 1; i < series.size(); ++i) {
        if (series[i].getCarga() > maxCarga) {
            maxCarga = series[i].getCarga();
        }
    }
    return maxCarga;
}
