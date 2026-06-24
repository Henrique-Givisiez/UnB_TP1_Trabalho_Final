#ifndef ESTADO_HPP_INCLUDED
#define ESTADO_HPP_INCLUDED
#include <string>

/**
 * @brief Representa um estado válido de história de usuário no sistema.
 *
 * Essa classe encapsula o armazenamento do estado de uma história de usuário,
 * aceitando apenas os valores definidos pelas regras do domínio do trabalho.
 */
class Estado {
public:
    /**
     * @brief Valores internos aceitos para o estado da história de usuário.
     */
    enum EstadoEnum {
        A_FAZER, /**< História ainda não iniciada. */
        FAZENDO, /**< História em desenvolvimento. */
        FEITO    /**< História concluída. */
    };
private:
    EstadoEnum estado;
public:
    /**
     * @brief Inicializa o estado com o valor padrão.
     *
     * O valor inicial do domínio é A FAZER.
     */
    Estado();

    /**
     * @brief Define o estado da história de usuário.
     *
     * @param novoEstado Novo estado a ser armazenado.
     * @throws std::invalid_argument Caso o valor informado seja inválido.
     */
    void set(const std::string& novoEstado);

    /**
     * @brief Retorna o estado armazenado.
     *
     * @return Estado atual em formato textual.
     */
    std::string get() const;

    /**
     * @brief Retorna o valor interno do estado.
     *
     * @return Valor atual do estado na enumeração EstadoEnum.
     */
    EstadoEnum getEstadoInterno() const;
};
#endif // ESTADO_HPP_INCLUDED
