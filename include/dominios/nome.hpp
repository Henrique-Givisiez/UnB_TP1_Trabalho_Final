/**
 * @file nome.hpp
 * @brief Declaração do domínio Nome.
 */
#ifndef NOME_HPP_INCLUDED
#define NOME_HPP_INCLUDED
#include <string>

/**
 * @brief Representa um nome textual válido no sistema.
 *
 * Essa classe encapsula a validação e o armazenamento de nomes aceitos pelos
 * campos textuais de identificação do trabalho.
 */
class Nome {
private:
    std::string nome;
    static const int LIMITE = 10;
    void validar(const std::string& nome);

public:
    /**
     * @brief Define o nome armazenado.
     *
     * @param nome Novo nome a ser armazenado.
     * @throws std::invalid_argument Caso o valor informado seja inválido.
     */
    void set(const std::string& nome);

    /**
     * @brief Retorna o nome armazenado.
     *
     * @return Nome atual em formato textual.
     */
    std::string get() const;
};

inline std::string Nome::get() const {
    return nome;
}

#endif // NOME_HPP_INCLUDED
