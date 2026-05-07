#ifndef PLANOSPRINT_HPP
#define PLANOSPRINT_HPP

#include "dominios/codigo.hpp"
#include "dominios/texto.hpp"
#include "dominios/tempo.hpp"

/**
 * @brief Entidade que representa um Plano de Sprint no sistema Scrum.
 *
 * Agrega os domínios Codigo (PK), Texto (objetivo) e Tempo (capacidade).
 * Toda validação é delegada aos respectivos domínios; nenhuma regra de
 * negócio vive nesta classe.
 */
class PlanoSprint {
private:
    Codigo codigo;     ///< Chave primária do plano de sprint.
    Texto  objetivo;   ///< Objetivo do sprint.
    Tempo  capacidade; ///< Capacidade total do sprint (em horas ou dias).

public:
    // ------------------------------------------------------------------ //
    //  Setters                                                             //
    // ------------------------------------------------------------------ //

    /**
     * @brief Define o código (PK) do plano de sprint.
     * @param codigo Valor a ser validado e armazenado pelo domínio Codigo.
     * @throws std::invalid_argument se o valor for inválido.
     */
    void setCodigo(const std::string& codigo);

    /**
     * @brief Define o objetivo do plano de sprint.
     * @param objetivo Valor a ser validado e armazenado pelo domínio Texto.
     * @throws std::invalid_argument se o valor for inválido.
     */
    void setObjetivo(const std::string& objetivo);

    /**
     * @brief Define a capacidade do plano de sprint.
     * @param capacidade Inteiro entre 1 e 365.
     * @throws std::invalid_argument se o valor estiver fora do intervalo.
     */
    void setCapacidade(int capacidade);
    void setCapacidade(double) = delete; // Impede atribuição de valores decimais

    // ------------------------------------------------------------------ //
    //  Getters                                                             //
    // ------------------------------------------------------------------ //

    /**
     * @brief Retorna o código do plano de sprint.
     * @return Representação em string do domínio Codigo.
     */
    std::string getCodigo()    const;

    /**
     * @brief Retorna o objetivo do plano de sprint.
     * @return Representação em string do domínio Texto.
     */
    std::string getObjetivo()  const;

    /**
     * @brief Retorna a capacidade do plano de sprint.
     * @return Inteiro entre 1 e 365.
     */
    int getCapacidade() const;
};

#endif // PLANOSPRINT_HPP