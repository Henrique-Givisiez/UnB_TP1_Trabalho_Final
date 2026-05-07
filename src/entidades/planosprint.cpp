#include "entidades/planosprint.hpp"

// ------------------------------------------------------------------ //
//  Setters                                                             //
// ------------------------------------------------------------------ //

void PlanoSprint::setCodigo(const std::string& codigo) {
    this->codigo.set(codigo);
}

void PlanoSprint::setObjetivo(const std::string& objetivo) {
    this->objetivo.set(objetivo);
}

void PlanoSprint::setCapacidade(int capacidade) {
    this->capacidade.set(capacidade);
}

// ------------------------------------------------------------------ //
//  Getters                                                             //
// ------------------------------------------------------------------ //

std::string PlanoSprint::getCodigo() const {
    return codigo.get();
}

std::string PlanoSprint::getObjetivo() const {
    return objetivo.get();
}

int PlanoSprint::getCapacidade() const {
    return capacidade.get();
}