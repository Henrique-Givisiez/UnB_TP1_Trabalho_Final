/**
 * @file codigo.hpp
 * @brief Declaração do domínio Codigo.
 */
#ifndef CODIGO_HPP_INCLUDED
#define CODIGO_HPP_INCLUDED
#include <string>


/**
 * @brief Representa um código válido no sistema.
 *
 * Essa classe encapsula a validação e o armazenamento de um código composto
 * por 5 caracteres, sendo 2 letras maiúsculas seguidas de 3 dígitos.
 */
class Codigo {
private:
    std::string codigo;
    void validar(std::string);
    static const int TAMANHO = 5;
public:
    /**
     * @brief Define o código armazenado.
     *
     * @param codigo Novo código a ser armazenado.
     * @throws std::invalid_argument Caso o valor informado seja inválido.
     */
    void set(std::string codigo);

    /**
     * @brief Retorna o código armazenado.
     *
     * @return Código atual em formato textual.
     */
    std::string get() const;
};

inline std::string Codigo::get() const{
    return codigo;
}

#endif // CODIGO_HPP_INCLUDED
