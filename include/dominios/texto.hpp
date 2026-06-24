/**
 * @file texto.hpp
 * @brief Declaração do domínio Texto.
 */
#ifndef TEXTO_HPP
#define TEXTO_HPP

#include <string>
#include <stdexcept>

/**
 * @brief Representa um texto válido usado nos campos textuais do sistema.
 *
 * Essa classe encapsula a validação e o armazenamento de textos curtos aceitos
 * pelas regras do domínio do trabalho.
 *
 * Formato válido:
 * - Até 40 caracteres.
 * - Caracteres permitidos: letras (a-z ou A-Z), dígitos (0-9),
 *   vírgula (,), ponto (.) ou espaço em branco.
 * - Vírgula não pode ser seguida por vírgula ou ponto.
 * - Ponto não pode ser seguido por vírgula ou ponto.
 * - Espaço em branco deve ser seguido por letra ou dígito.
 * - Primeiro e último caractere não podem ser vírgula, ponto ou espaço.
 */
class Texto {
private:
    std::string valor;

    void validar(const std::string& texto);

public:
    /**
     * @brief Define o texto armazenado.
     *
     * @param texto Novo texto a ser armazenado.
     * @throws std::invalid_argument Caso o valor informado seja inválido.
     */
    void set(const std::string& texto);

    /**
     * @brief Retorna o texto armazenado.
     *
     * @return Texto atual em formato textual.
     */
    std::string get() const { return valor; }
};

#endif
