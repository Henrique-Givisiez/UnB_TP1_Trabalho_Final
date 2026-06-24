#ifndef SENHA_HPP
#define SENHA_HPP

#include <string>
#include <stdexcept>

/**
 * @brief Representa uma senha válida para autenticação.
 *
 * Essa classe encapsula a validação e o armazenamento de uma senha de acesso
 * aceita pelas regras do domínio do trabalho.
 *
 * Formato válido:
 * - Exatamente 6 caracteres.
 * - Cada caractere pode ser letra (a-z ou A-Z) ou dígito (0-9).
 * - Letra não pode ser seguida por letra; dígito não pode ser seguido por dígito.
 * - Deve conter pelo menos uma letra minúscula (a-z).
 * - Deve conter pelo menos uma letra maiúscula (A-Z).
 * - Deve conter pelo menos um dígito (0-9).
 */
class Senha {
private:
    std::string valor;

    void validar(const std::string& senha);

public:
    /**
     * @brief Define a senha armazenada.
     *
     * @param senha Nova senha a ser armazenada.
     * @throws std::invalid_argument Caso o valor informado seja inválido.
     */
    void set(const std::string& senha);

    /**
     * @brief Retorna a senha armazenada.
     *
     * @return Senha atual em formato textual.
     */
    std::string get() const;
};

inline std::string Senha::get() const {
    return valor;
}

#endif
