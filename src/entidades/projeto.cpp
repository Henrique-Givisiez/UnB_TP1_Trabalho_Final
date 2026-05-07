#include "entidades/projeto.hpp"

// ---------- Setters ----------

void Projeto::setCodigo(const std::string& codigo) {
    this->codigo.set(codigo);
}

void Projeto::setNome(const std::string& nome) {
    this->nome.set(nome);
}

void Projeto::setInicio(const std::string& inicio) {
    this->inicio.set(inicio);
}

void Projeto::setTermino(const std::string& termino) {
    this->termino.set(termino);
}

// ---------- Getters ----------

std::string Projeto::getCodigo() const {
    return codigo.get();
}

std::string Projeto::getNome() const {
    return nome.get();
}

std::string Projeto::getInicio() const {
    return inicio.get();
}

std::string Projeto::getTermino() const {
    return termino.get();
}