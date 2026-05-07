#include "entidades/historia.hpp"

// ------------------------------------------------------------------ //
//  Setters                                                             //
// ------------------------------------------------------------------ //

void Historia::setCodigo(const std::string& codigo) {
    this->codigo.set(codigo);
}

void Historia::setTitulo(const std::string& titulo) {
    this->titulo.set(titulo);
}

void Historia::setPapel(const std::string& papel) {
    this->papel.set(papel);
}

void Historia::setAcao(const std::string& acao) {
    this->acao.set(acao);
}

void Historia::setValor(const std::string& valor) {
    this->valor.set(valor);
}

void Historia::setEstimativa(int estimativa) {
    this->estimativa.set(estimativa);
}

void Historia::setPrioridade(const std::string& prioridade) {
    this->prioridade.set(prioridade);
}

void Historia::setEstado(const std::string& estado) {
    this->estado.set(estado);
}

// ------------------------------------------------------------------ //
//  Getters                                                             //
// ------------------------------------------------------------------ //

std::string Historia::getCodigo()     const { return codigo.get();     }
std::string Historia::getTitulo()     const { return titulo.get();     }
std::string Historia::getPapel()      const { return papel.get();      }
std::string Historia::getAcao()       const { return acao.get();       }
std::string Historia::getValor()      const { return valor.get();      }
int         Historia::getEstimativa() const { return estimativa.get(); }
std::string Historia::getPrioridade() const { return prioridade.get(); }
std::string Historia::getEstado()     const { return estado.get();     }