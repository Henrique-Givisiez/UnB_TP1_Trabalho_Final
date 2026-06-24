/**
 * @file historia.hpp
 * @brief Declaração da entidade Historia.
 */
#ifndef HISTORIA_HPP
#define HISTORIA_HPP

#include "dominios/codigo.hpp"
#include "dominios/texto.hpp"
#include "dominios/papel.hpp"
#include "dominios/tempo.hpp"
#include "dominios/prioridade.hpp"
#include "dominios/estado.hpp"

/**
 * @brief Entidade que representa uma História de Usuário no sistema Scrum.
 *
 * Agrega os domínios Codigo (PK), Texto (titulo, acao, valor), Papel,
 * Tempo (estimativa), Prioridade e Estado. Toda validação é delegada
 * aos respectivos domínios; nenhuma regra de negócio vive nesta classe.
 *
 * Uma história pertence exclusivamente a um Projeto ou a um Plano de
 * Sprint — nunca aos dois simultaneamente (restrição {OU} do diagrama).
 * Essa restrição é controlada pela camada de serviço.
 */
class Historia {
private:
    Codigo     codigo;     ///< Chave primária da história de usuário.
    Texto      titulo;     ///< Título da história de usuário.
    Papel      papel;      ///< Papel do usuário (como...).
    Texto      acao;       ///< Ação desejada (eu quero...).
    Texto      valor;      ///< Valor esperado (para...).
    Tempo      estimativa; ///< Estimativa de esforço (1 a 365).
    Prioridade prioridade; ///< Prioridade da história (ALTA, MEDIA, BAIXA).
    Estado     estado;     ///< Estado atual (A FAZER, FAZENDO, FEITO).

public:
    // ------------------------------------------------------------------ //
    //  Setters                                                             //
    // ------------------------------------------------------------------ //

    /**
     * @brief Define o código (PK) da história de usuário.
     * @param codigo String no formato: 2 letras maiúsculas + 3 dígitos.
     * @throws std::invalid_argument se o valor for inválido.
     */
    void setCodigo(const std::string& codigo);

    /**
     * @brief Define o título da história de usuário.
     * @param titulo String de até 40 caracteres (letras, dígitos,
     *        vírgula, ponto, espaço), com restrições de pontuação.
     * @throws std::invalid_argument se o valor for inválido.
     */
    void setTitulo(const std::string& titulo);

    /**
     * @brief Define o papel do usuário na história (como...).
     * @param papel Um dos valores: DESENVOLVEDOR, MESTRE SCRUM,
     *        PROPRIETARIO DE PRODUTO.
     * @throws std::invalid_argument se o valor for inválido.
     */
    void setPapel(const std::string& papel);

    /**
     * @brief Define a ação desejada na história (eu quero...).
     * @param acao String de até 40 caracteres com restrições de pontuação.
     * @throws std::invalid_argument se o valor for inválido.
     */
    void setAcao(const std::string& acao);

    /**
     * @brief Define o valor esperado na história (para...).
     * @param valor String de até 40 caracteres com restrições de pontuação.
     * @throws std::invalid_argument se o valor for inválido.
     */
    void setValor(const std::string& valor);

    /**
     * @brief Define a estimativa de esforço da história.
     * @param estimativa Inteiro entre 1 e 365.
     * @throws std::invalid_argument se o valor estiver fora do intervalo.
     */
    void setEstimativa(int estimativa);

    /**
     * @brief Impede conversão implícita de double para int em setEstimativa.
     */
    void setEstimativa(double) = delete;

    /**
     * @brief Define a prioridade da história de usuário.
     * @param prioridade Um dos valores: ALTA, MEDIA, BAIXA.
     * @throws std::invalid_argument se o valor for inválido.
     */
    void setPrioridade(const std::string& prioridade);

    /**
     * @brief Define o estado atual da história de usuário.
     * @param estado Um dos valores: A FAZER, FAZENDO, FEITO.
     * @throws std::invalid_argument se o valor for inválido.
     */
    void setEstado(const std::string& estado);

    // ------------------------------------------------------------------ //
    //  Getters                                                             //
    // ------------------------------------------------------------------ //

    /**
     * @brief Retorna o código da história de usuário.
     * @return String com o código armazenado.
     */
    std::string getCodigo()     const;

    /**
     * @brief Retorna o título da história de usuário.
     * @return String com o título armazenado.
     */
    std::string getTitulo()     const;

    /**
     * @brief Retorna o papel do usuário na história.
     * @return String com o papel armazenado.
     */
    std::string getPapel()      const;

    /**
     * @brief Retorna a ação desejada na história.
     * @return String com a ação armazenada.
     */
    std::string getAcao()       const;

    /**
     * @brief Retorna o valor esperado na história.
     * @return String com o valor armazenado.
     */
    std::string getValor()      const;

    /**
     * @brief Retorna a estimativa de esforço da história.
     * @return Inteiro entre 1 e 365.
     */
    int getEstimativa()         const;

    /**
     * @brief Retorna a prioridade da história de usuário.
     * @return String com a prioridade armazenada.
     */
    std::string getPrioridade() const;

    /**
     * @brief Retorna o estado atual da história de usuário.
     * @return String com o estado armazenado.
     */
    std::string getEstado()     const;
};

#endif // HISTORIA_HPP