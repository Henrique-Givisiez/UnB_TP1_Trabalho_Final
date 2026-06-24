/**
 * @file pessoa.hpp
 * @brief Declaração da entidade Pessoa.
 */
#ifndef PESSOA_HPP
#define PESSOA_HPP

#include "dominios/email.hpp"
#include "dominios/nome.hpp"
#include "dominios/senha.hpp"
#include "dominios/papel.hpp"

/// @brief Entidade que representa um usuário do sistema.
///
/// Cada pessoa é identificada unicamente pelo seu email.
/// Possui nome, senha e papel no projeto.
class Pessoa {
private:
    Email  email;
    Nome   nome;
    Senha  senha;
    Papel  papel;

public:
    /// @brief Define o email da pessoa.
    /// @param email String no formato parte-local@dominio.
    /// @throws std::invalid_argument se o email for inválido.
    void setEmail(const std::string& email);

    /// @brief Define o nome da pessoa.
    /// @param nome String com até 10 caracteres.
    /// @throws std::invalid_argument se o nome for inválido.
    void setNome(const std::string& nome);

    /// @brief Define a senha da pessoa.
    /// @param senha String de exatamente 6 caracteres.
    /// @throws std::invalid_argument se a senha for inválida.
    void setSenha(const std::string& senha);

    /// @brief Define o papel da pessoa no projeto.
    /// @param papel String com o papel (DESENVOLVEDOR, MESTRE SCRUM, PROPRIETARIO DE PRODUTO).
    /// @throws std::invalid_argument se o papel for inválido.
    void setPapel(const std::string& papel);

    /// @brief Retorna o email da pessoa.
    std::string getEmail() const;

    /// @brief Retorna o nome da pessoa.
    std::string getNome()  const;

    /// @brief Retorna a senha da pessoa.
    std::string getSenha() const;

    /// @brief Retorna o papel da pessoa.
    std::string getPapel() const;
};

#endif