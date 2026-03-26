#include "dominios/estado.hpp"
#include <string>


Estado::Estado() {
    valor = A_FAZER;
}

bool Estado::setEstado(std::string& estado) {
    if (estado == "A FAZER") {
        valor = A_FAZER;
        return true;
    }
    if (estado == "FAZENDO") {
        valor = FAZENDO;
        return true;
    }
    if (estado == "FEITO") {
        valor = FEITO;
        return true;
    }
    return false;
}

std::string Estado::getEstado() const {
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
