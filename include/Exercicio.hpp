#ifndef EXERCICIO_HPP
#define EXERCICIO_HPP

#include <string>

class Exercicio {
private:
    std::string nome;
    std::string grupoMuscular;

public:
    Exercicio(const std::string& nome, const std::string& grupoMuscular);

    std::string getNome() const;
    std::string getGrupoMuscular() const;

    bool operator<(const Exercicio& outro) const;
    bool operator==(const Exercicio& outro) const;
};

#endif
