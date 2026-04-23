#include "dominios/prioridade.hpp"
#include <string>
#include <stdexcept>


// Metodo init que define BAIXA como prioridade default
Prioridade::Prioridade() {
    prioridade = BAIXA;
}

// Metodo que altera o estado e recebe o endereco (&) da string como parametro
void Prioridade::setPrioridade(std::string& novaPrioridade) {
    if (novaPrioridade == "BAIXA") {
        prioridade = BAIXA;
    } else if (novaPrioridade == "MEDIA") {
        prioridade = MEDIA;
    } else if (novaPrioridade == "ALTA") {
        prioridade = ALTA;
    } else {
        throw invalid_argument("Prioridade invalida");
    }
}

std::string Prioridade::getPrioridade() const {
    switch (prioridade) {
        case BAIXA: return "BAIXA";
        case MEDIA: return "MEDIA";
        case ALTA: return "ALTA";
    }
    return "";
}

Prioridade::PrioridadeEnum Prioridade::getPrioridadeInterno() const {
    return prioridade;
}
