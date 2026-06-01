#include "../../include/servico/servicos.hpp"

#include <algorithm>

PessoaServico::PessoaServico(BancoDadosMemoria* banco) {
    this->banco = banco;
}

bool PessoaServico::criar(const Pessoa& pessoa) {
    if (banco == nullptr) {
        return false;
    }

    const std::string email = pessoa.getEmail();

    if (banco->pessoas.find(email) != banco->pessoas.end()) {
        return false;
    }

    banco->pessoas[email] = pessoa;
    return true;
}

bool PessoaServico::ler(const std::string& email, Pessoa* pessoa) {
    if (banco == nullptr || pessoa == nullptr) {
        return false;
    }

    std::map<std::string, Pessoa>::iterator it = banco->pessoas.find(email);

    if (it == banco->pessoas.end()) {
        return false;
    }

    *pessoa = it->second;
    return true;
}

bool PessoaServico::atualizar(const Pessoa& pessoa) {
    if (banco == nullptr) {
        return false;
    }

    const std::string email = pessoa.getEmail();

    std::map<std::string, Pessoa>::iterator it = banco->pessoas.find(email);

    if (it == banco->pessoas.end()) {
        return false;
    }

    /*
     * A chave primária não é editada porque o email usado como chave no map
     * permanece o mesmo. A apresentação também não deve oferecer edição da PK.
     */
    it->second = pessoa;
    return true;
}

bool PessoaServico::excluir(const std::string& email) {
    if (banco == nullptr) {
        return false;
    }

    std::map<std::string, Pessoa>::iterator it = banco->pessoas.find(email);

    if (it == banco->pessoas.end()) {
        return false;
    }

    if (possuiAssociacaoImpeditiva(email)) {
        return false;
    }

    banco->pessoas.erase(it);
    return true;
}

bool PessoaServico::possuiAssociacaoImpeditiva(const std::string& email) const {
    if (banco == nullptr) {
        return true;
    }

    /*
     * Impede excluir uma pessoa que esteja associada a algum projeto.
     */
    std::map<std::string, std::vector<std::string> >::const_iterator itProjetos;
    itProjetos = banco->pessoaParaProjetos.find(email);

    if (itProjetos != banco->pessoaParaProjetos.end() &&
        !itProjetos->second.empty()) {
        return true;
    }

    /*
     * Impede excluir uma pessoa que seja Mestre Scrum de algum projeto.
     */
    std::map<std::string, std::string>::const_iterator itMestre;

    for (itMestre = banco->projetoParaMestreScrum.begin();
         itMestre != banco->projetoParaMestreScrum.end();
         ++itMestre) {
        if (itMestre->second == email) {
            return true;
        }
    }

    /*
     * Impede excluir uma pessoa associada a alguma história.
     */
    std::map<std::string, std::vector<std::string> >::const_iterator itHistorias;

    for (itHistorias = banco->historiaParaPessoas.begin();
         itHistorias != banco->historiaParaPessoas.end();
         ++itHistorias) {
        const std::vector<std::string>& emails = itHistorias->second;

        if (std::find(emails.begin(), emails.end(), email) != emails.end()) {
            return true;
        }
    }

    return false;
}

AuthServico::AuthServico(BancoDadosMemoria* banco) {
    this->banco = banco;
}

bool AuthServico::autenticar(const std::string& email,
                             const std::string& senha,
                             Pessoa* pessoaAutenticada) {
    if (banco == nullptr) {
        return false;
    }

    std::map<std::string, Pessoa>::iterator it = banco->pessoas.find(email);

    if (it == banco->pessoas.end()) {
        return false;
    }

    if (it->second.getSenha() != senha) {
        return false;
    }

    *pessoaAutenticada = it->second;
    return true;
}