#include "GerenciadorTreino.hpp"
#include "Interface.hpp"

int main() {
    GerenciadorTreino gerenciador;
    Interface interface(gerenciador);
    interface.executar();
    return 0;
}
