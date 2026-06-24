/**
 * @file tempo.hpp
 * @brief Declaração do domínio Tempo.
 */
#ifndef TEMPO_HPP
#define TEMPO_HPP

#include <string>
#include <stdexcept>

/**
 * @brief Representa um valor de tempo válido em dias.
 *
 * Essa classe encapsula a validação e o armazenamento de um tempo inteiro,
 * aceitando valores de 1 a 365 dias, inclusive.
 */
class Tempo {
private:
    int valor;

    void validar(int tempo);

public:
    /**
     * @brief Define o tempo armazenado.
     *
     * @param tempo Novo valor inteiro entre 1 e 365.
     * @throws std::invalid_argument Caso o valor informado seja inválido.
     */
    void set(int tempo);

    /**
     * @brief Impede a definição de tempo com valor decimal.
     *
     * Este método é removido da interface utilizável para evitar valores não
     * inteiros.
     *
     * @param tempo Valor decimal rejeitado pela interface.
     */
    void set(double tempo) = delete;

    /**
     * @brief Retorna o tempo armazenado.
     *
     * @return Tempo atual em dias.
     */
    int get() const;
};


inline int Tempo::get() const {
    return valor;
}

#endif
