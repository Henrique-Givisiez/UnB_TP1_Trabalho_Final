#ifndef EMAIL_HPP
#define EMAIL_HPP

#include <string>
#include <stdexcept>

/**
 * @brief Representa um endereço de email válido.
 *
 * Essa classe encapsula a validação e o armazenamento de um endereço de email
 * no formato parte-local@dominio.
 *
 * Parte local:
 * - Pode conter letras (a-z), dígitos (0-9), ponto (.) ou hífen (-).
 * - Não pode iniciar ou terminar com ponto ou hífen.
 * - Ponto ou hífen deve ser seguido por letra(s) ou dígito(s).
 * - Comprimento máximo: 64 caracteres.
 *
 * Domínio:
 * - Composto por uma ou mais partes separadas por ponto (.).
 * - Cada parte pode conter letra (a-z), dígito (0-9) ou hífen (-).
 * - Cada parte não pode iniciar ou terminar com hífen.
 * - Comprimento máximo: 255 caracteres.
 */
class Email {
private:
    std::string valor;

    void validar(const std::string& email);
    void validarParteLocal(const std::string& local);
    void validarDominio(const std::string& dominio);

public:
    /**
     * @brief Define o endereço de email armazenado.
     *
     * @param email Novo endereço de email no formato parte-local@dominio.
     * @throws std::invalid_argument Caso o valor informado seja inválido.
     */
    void set(const std::string& email);

    /**
     * @brief Retorna o endereço de email armazenado.
     *
     * @return Endereço de email atual em formato textual.
     */
    std::string get() const;
};


inline std::string Email::get() const {
    return valor;
}

#endif
