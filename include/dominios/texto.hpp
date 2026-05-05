#ifndef TEXTO_HPP
#define TEXTO_HPP

#include <string>
#include <stdexcept>

/// @brief Domínio que representa um texto genérico.
///
/// Formato válido:
/// - Até 40 caracteres.
/// - Caracteres permitidos: letras (a-z ou A-Z), dígitos (0-9),
///   vírgula (,), ponto (.) ou espaço em branco.
/// - Vírgula não pode ser seguida por vírgula ou ponto.
/// - Ponto não pode ser seguido por vírgula ou ponto.
/// - Espaço em branco é seguido por letra ou dígito.
/// - Primeiro e último caractere não podem ser vírgula, ponto ou espaço.
class Texto {
private:
    std::string valor;

    void validar(const std::string& texto);

public:
    /// @brief Define o valor do texto após validação.
    /// @param texto String com até 40 caracteres.
    /// @throws std::invalid_argument se o formato ou valor for inválido.
    void set(const std::string& texto);

    /// @brief Retorna o valor do texto.
    /// @return String com o texto.
    std::string get() const { return valor; }
};

#endif