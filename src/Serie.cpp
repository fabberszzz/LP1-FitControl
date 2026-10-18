#include "Serie.hpp"
#include <stdexcept>

Serie::Serie(int numero, double carga, int repeticoes)
    : numero(numero), carga(carga), repeticoes(repeticoes) {
    if (!valoresValidos(carga, repeticoes)) {
        throw std::invalid_argument("Carga deve ser >= 0 e repeticoes devem ser > 0.");
    }
}

int Serie::getNumero() const {
    return numero;
}

double Serie::getCarga() const {
    return carga;
}

int Serie::getRepeticoes() const {
    return repeticoes;
}

bool Serie::valoresValidos(double carga, int repeticoes) {
    return carga >= 0.0 && repeticoes > 0;
}
