#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <stdexcept>

/// @brief Domínio que representa uma data no formato DIA/MES/ANO.
///
/// Formato válido: DIA/MES/ANO
/// - DIA: 1 a 31
/// - MES: 01, 02, ..., 12
/// - ANO: 2000 a 2999
/// Data deve ser válida considerando anos bissextos.
class Data {
private:
    std::string valor;

    void validar(const std::string& data);
    bool bissexto(int ano) const;
    int diasNoMes(int mes, int ano) const;

public:
    /// @brief Define o valor da data após validação.
    /// @param data String no formato DIA/MES/ANO.
    /// @throws std::invalid_argument se o formato ou valor for inválido.
    void set(const std::string& data);

    /// @brief Retorna o valor da data.
    /// @return String no formato DIA/MES/ANO.
    std::string get() const { return valor; }
};

#endif