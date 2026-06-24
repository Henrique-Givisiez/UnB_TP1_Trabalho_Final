/**
 * @file prioridade.hpp
 * @brief Declaração do domínio Prioridade.
 */
#ifndef PRIORIDADE_HPP_INCLUDED
#define PRIORIDADE_HPP_INCLUDED
#include <string>

/**
 * @brief Representa uma prioridade válida de história de usuário no sistema.
 *
 * Essa classe encapsula o armazenamento da prioridade de uma história de
 * usuário, aceitando apenas os valores definidos pelas regras do domínio do
 * trabalho.
 */
class Prioridade {
public:
    /**
     * @brief Valores internos aceitos para a prioridade da história de usuário.
     */
    enum PrioridadeEnum {
        BAIXA, /**< História com baixa prioridade. */
        MEDIA, /**< História com prioridade média. */
        ALTA   /**< História com alta prioridade. */
    };
private:
    PrioridadeEnum prioridade;
public:
    /**
     * @brief Inicializa a prioridade com o valor padrão.
     *
     * O valor inicial do domínio é BAIXA.
     */
    Prioridade();

    /**
     * @brief Define a prioridade da história de usuário.
     *
     * @param novaPrioridade Nova prioridade a ser armazenada.
     * @throws std::invalid_argument Caso o valor informado seja inválido.
     */
    void set(const std::string& novaPrioridade);

    /**
     * @brief Retorna a prioridade armazenada.
     *
     * @return Prioridade atual em formato textual.
     */
    std::string get() const;

    /**
     * @brief Retorna o valor interno da prioridade.
     *
     * @return Valor atual da prioridade na enumeração PrioridadeEnum.
     */
    PrioridadeEnum getPrioridadeInterno() const;
};


#endif // PRIORIDADE_HPP_INCLUDED
