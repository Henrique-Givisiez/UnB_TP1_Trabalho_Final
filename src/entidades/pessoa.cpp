#include "entidades/pessoa.hpp"

// ---------------------------------------------------------------------
// Setters — delegam validação ao domínio correspondente
// ---------------------------------------------------------------------

void Pessoa::setEmail(const std::string& email) {
    this->email.set(email);
}

void Pessoa::setNome(const std::string& nome) {
    this->nome.set(nome);
}

void Pessoa::setSenha(const std::string& senha) {
    this->senha.set(senha);
}

void Pessoa::setPapel(const std::string& papel) {
    this->papel.set(papel);
}

// ---------------------------------------------------------------------
// Getters — delegam ao domínio correspondente
// ---------------------------------------------------------------------

std::string Pessoa::getEmail() const {
    return email.get();
}

std::string Pessoa::getNome() const {
    return nome.get();
}

std::string Pessoa::getSenha() const {
    return senha.get();
}

std::string Pessoa::getPapel() const {
    return papel.get();
}