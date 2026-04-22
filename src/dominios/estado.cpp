#include "dominios/estado.hpp"
#include <string>
#include <stdexcept>

using namespace std;

// Metodo init que define o A_FAZER como valor default
Estado::Estado() {
    valor = A_FAZER;
}

// Metodo que altera o estado e recebe o endereco (&) da string como parametro
void Estado::setEstado(std::string& estado) {
    if (estado == "A FAZER") {
        valor = A_FAZER;
    } else if (estado == "FAZENDO") {
        valor = FAZENDO;
    } else if (estado == "FEITO") {
        valor = FEITO;
    } else {
        throw invalid_argument("Estado invalido");
    }
}

string Estado::getEstado() const {
    switch (valor) {
        case A_FAZER: return "A FAZER";
        case FAZENDO: return "FAZENDO";
        case FEITO: return "FEITO";
    }
    return "";
}

Estado::Valor Estado::getValorInterno() const {
    return valor;
}
