#ifndef TEMPO_HPP
#define TEMPO_HPP

#include <string>
#include <stdexcept>

/// @brief Domínio que representa um valor de tempo em dias.
///
/// Formato válido:
/// - Valor inteiro entre 1 e 365 inclusive.
class Tempo {
private:
    int valor;

    void validar(int tempo);

public:
    /// @brief Define o valor do tempo após validação.
    /// @param tempo Inteiro entre 1 e 365.
    /// @throws std::invalid_argument se o valor estiver fora do intervalo permitido.
    void set(int tempo);
    void set(double) = delete; // Impede atribuição de valores decimais

    /// @brief Retorna o valor do tempo.
    /// @return Inteiro com o valor do tempo.
    int get() const;
};


inline int Tempo::get() const {
    return valor;
}

#endif