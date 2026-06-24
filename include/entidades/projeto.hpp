/**
 * @file projeto.hpp
 * @brief Declaração da entidade Projeto.
 */
#ifndef PROJETO_HPP
#define PROJETO_HPP

#include "dominios/codigo.hpp"
#include "dominios/nome.hpp"
#include "dominios/data.hpp"

/**
 * @class Projeto
 * @brief Representa um projeto no sistema Scrum.
 *
 * Um projeto possui um código único (PK), nome, data de início e data de término.
 * Cada atributo é armazenado como instância do domínio correspondente,
 * delegando toda validação ao domínio.
 */
class Projeto {
private:
    Codigo codigo;   ///< Código único do projeto (PK).
    Nome   nome;     ///< Nome do projeto.
    Data   inicio;   ///< Data de início do projeto.
    Data   termino;  ///< Data de término do projeto.

public:
    /**
     * @brief Define o código do projeto.
     * @param codigo String com o código a ser validado e armazenado.
     * @throws std::invalid_argument se o código for inválido.
     */
    void setCodigo(const std::string& codigo);

    /**
     * @brief Define o nome do projeto.
     * @param nome String com o nome a ser validado e armazenado.
     * @throws std::invalid_argument se o nome for inválido.
     */
    void setNome(const std::string& nome);

    /**
     * @brief Define a data de início do projeto.
     * @param inicio String com a data de início (formato DD-MM-AA).
     * @throws std::invalid_argument se a data for inválida.
     */
    void setInicio(const std::string& inicio);

    /**
     * @brief Define a data de término do projeto.
     * @param termino String com a data de término (formato DD-MM-AA).
     * @throws std::invalid_argument se a data for inválida.
     */
    void setTermino(const std::string& termino);

    /**
     * @brief Retorna o código do projeto.
     * @return String com o código armazenado.
     */
    std::string getCodigo() const;

    /**
     * @brief Retorna o nome do projeto.
     * @return String com o nome armazenado.
     */
    std::string getNome() const;

    /**
     * @brief Retorna a data de início do projeto.
     * @return String com a data de início armazenada.
     */
    std::string getInicio() const;

    /**
     * @brief Retorna a data de término do projeto.
     * @return String com a data de término armazenada.
     */
    std::string getTermino() const;
};

#endif // PROJETO_HPP