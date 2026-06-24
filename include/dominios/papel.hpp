#ifndef PAPEL_HPP_INCLUDED
#define PAPEL_HPP_INCLUDED
#include <string>

/**
 * @brief Representa um papel válido de pessoa no sistema.
 *
 * Essa classe encapsula o armazenamento do papel associado a uma pessoa,
 * aceitando apenas os valores definidos pelas regras do domínio do trabalho.
 */
class Papel {
public:
    /**
     * @brief Valores internos aceitos para o papel da pessoa.
     */
    enum PapelEnum {
        DESENVOLVEDOR,     /**< Pessoa com papel de desenvolvedor. */
        MESTRE_SCRUM,      /**< Pessoa com papel de mestre Scrum. */
        PROPRIETARIO_PROD  /**< Pessoa com papel de proprietário de produto. */
    };
private:
    PapelEnum papel;
public:
    /**
     * @brief Define o papel da pessoa.
     *
     * @param novoPapel Novo papel a ser armazenado.
     * @throws std::invalid_argument Caso o valor informado seja inválido.
     */
    void set(const std::string& novoPapel);

    /**
     * @brief Retorna o papel armazenado.
     *
     * @return Papel atual em formato textual.
     */
    std::string get() const;

    /**
     * @brief Retorna o valor interno do papel.
     *
     * @return Valor atual do papel na enumeração PapelEnum.
     */
    PapelEnum getPapelInterno() const;
};

#endif // PAPEL_HPP_INCLUDED
