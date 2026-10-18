#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "GerenciadorTreino.hpp"

class Interface {
private:
    GerenciadorTreino& gerenciador;

    // Métodos auxiliares de entrada e validação
    int lerInteiro(const std::string& mensagem, int minValor = -1);
    double lerDouble(const std::string& mensagem, double minValor = 0.0);
    std::string lerLinha(const std::string& mensagem);

    // Fluxos do menu
    void menuCadastrarExercicio();
    void menuConfigurarRotina();
    void menuRegistrarTreino();
    void menuConsultarHistorico();
    void menuVerEvolucao();

public:
    Interface(GerenciadorTreino& gerenciador);
    void executar();
};

#endif
