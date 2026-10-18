#ifndef SERIE_HPP
#define SERIE_HPP

class Serie {
private:
    int numero;
    double carga;
    int repeticoes;

public:
    Serie(int numero, double carga, int repeticoes);

    int getNumero() const;
    double getCarga() const;
    int getRepeticoes() const;

    static bool valoresValidos(double carga, int repeticoes);
};

#endif
