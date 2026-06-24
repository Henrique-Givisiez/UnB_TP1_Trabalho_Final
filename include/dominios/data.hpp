/**
 * @file data.hpp
 * @brief Declaração do domínio Data.
 */
#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <stdexcept>

/**
 * @brief Representa uma data válida no sistema.
 *
 * Essa classe encapsula a validação e o armazenamento de uma data no formato
 * DIA/MES/ANO.
 *
 * Formato válido:
 * - DIA: 1 a 31.
 * - MES: 01, 02, ..., 12.
 * - ANO: 2000 a 2999.
 * - A data deve ser válida considerando anos bissextos.
 */
class Data {
private:
    std::string valor;

    void validar(const std::string& data);
    bool bissexto(int ano) const;
    int diasNoMes(int mes, int ano) const;

public:
    /**
     * @brief Define a data armazenada.
     *
     * @param data Nova data no formato DIA/MES/ANO.
     * @throws std::invalid_argument Caso o valor informado seja inválido.
     */
    void set(const std::string& data);

    /**
     * @brief Retorna a data armazenada.
     *
     * @return Data atual no formato DIA/MES/ANO.
     */
    std::string get() const { return valor; }
};

#endif
