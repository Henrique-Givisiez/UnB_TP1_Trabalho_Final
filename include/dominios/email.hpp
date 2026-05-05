#ifndef EMAIL_HPP
#define EMAIL_HPP

#include <string>
#include <stdexcept>

/// @brief Domínio que representa um endereço de email no formato parte-local@dominio.
///
/// Parte local:
/// - Pode conter letras (a-z), dígitos (0-9), ponto (.) ou hífen (-).
/// - Não pode iniciar ou terminar com ponto ou hífen.
/// - Ponto ou hífen deve ser seguido por letra(s) ou dígito(s).
/// - Comprimento máximo: 64 caracteres.
///
/// Domínio:
/// - Composto por uma ou mais partes separadas por ponto (.).
/// - Cada parte pode conter letra (a-z), dígito (0-9) ou hífen (-).
/// - Cada parte não pode iniciar ou terminar com hífen.
/// - Comprimento máximo: 255 caracteres.
class Email {
private:
    std::string valor;

    void validar(const std::string& email);
    void validarParteLocal(const std::string& local);
    void validarDominio(const std::string& dominio);

public:
    /// @brief Define o valor do email após validação.
    /// @param email String no formato parte-local@dominio.
    /// @throws std::invalid_argument se o formato ou valor for inválido.
    void set(const std::string& email);

    /// @brief Retorna o valor do email.
    /// @return String com o endereço de email.
    std::string get() const;
};


inline std::string Email::get() const {
    return valor;
}

#endif