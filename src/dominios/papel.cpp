#include "dominios/papel.hpp"
#include <string>
#include <stdexcept>

using namespace std;

// Metodo que altera o papel e recebe o endereco (&) da string como parametro
void Papel::setPapel(std::string& novoPapel) {
    if (novoPapel == "DESENVOLVEDOR") {
        papel = DESENVOLVEDOR;
    } else if (novoPapel == "MESTRE DE SCRUM") {
        papel = MESTRE_SCRUM;
    } else if (novoPapel == "PROPRIETARIO DE PRODUTO") {
        papel = PROPRIETARIO_PROD;
    } else {
        throw invalid_argument("Papel invalido");
    }
}

string Papel::getPapel() const {
    switch (papel) {
        case DESENVOLVEDOR: return "DESENVOLVEDOR";
        case MESTRE_SCRUM: return "MESTRE SCRUM";
        case PROPRIETARIO_PROD: return "PROPRIETARIO DE PRODUTO";
    }
    return "";
}

Papel::PapelEnum Papel::getPapelInterno() const {
    return papel;
}
