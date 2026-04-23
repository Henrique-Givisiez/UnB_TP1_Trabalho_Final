#include "dominios/estado.hpp"
#include <string>
#include <stdexcept>

using namespace std;

// Metodo init que define o A_FAZER como estado default
Estado::Estado() {
    estado = A_FAZER;
}

// Metodo que altera o estado e recebe o endereco (&) da string como parametro
void Estado::setEstado(std::string& novoEstado) {
    if (novoEstado == "A FAZER") {
        estado = A_FAZER;
    } else if (novoEstado == "FAZENDO") {
        estado = FAZENDO;
    } else if (novoEstado == "FEITO") {
        estado = FEITO;
    } else {
        throw invalid_argument("Estado invalido");
    }
}

string Estado::getEstado() const {
    switch (estado) {
        case A_FAZER: return "A FAZER";
        case FAZENDO: return "FAZENDO";
        case FEITO: return "FEITO";
    }
    return "";
}

Estado::EstadoEnum Estado::getEstadoInterno() const {
    return estado;
}
