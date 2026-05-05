#ifndef SENHA_HPP
#define SENHA_HPP

#include <string>
#include <stdexcept>

/// @brief Domínio que representa uma senha de acesso.
///
/// Formato válido:
/// - Exatamente 6 caracteres.
/// - Cada caractere pode ser letra (a-z ou A-Z) ou dígito (0-9).
/// - Letra não pode ser seguida por letra; dígito não pode ser seguido por dígito.
/// - Deve conter pelo menos uma letra minúscula (a-z).
/// - Deve conter pelo menos uma letra maiúscula (A-Z).
/// - Deve conter pelo menos um dígito (0-9).
class Senha {
private:
    std::string valor;

    void validar(const std::string& senha);

public:
    /// @brief Define o valor da senha após validação.
    /// @param senha String de exatamente 6 caracteres.
    /// @throws std::invalid_argument se o formato ou valor for inválido.
    void set(const std::string& senha);

    /// @brief Retorna o valor da senha.
    /// @return String com a senha.
    std::string get() const;
};

inline std::string Senha::get() const {
    return valor;
}

#endif