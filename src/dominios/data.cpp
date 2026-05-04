#include "dominios/data.hpp"
#include <stdexcept>
#include <string>

// ---------------------------------------------------------------------
// Helpers privados
// ---------------------------------------------------------------------

bool Data::bissexto(int ano) const {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int Data::diasNoMes(int mes, int ano) const {
    switch (mes) {
        case 1: case 3: case 5: case 7:
        case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return bissexto(ano) ? 29 : 28;
        default:
            return 0;
    }
}

void Data::validar(const std::string& data) {
    // Formato esperado: DIA/MES/ANO
    // Exemplos válidos: 1/01/2000, 29/02/2000, 31/12/2999

    // Encontra as barras
    size_t primeiraB = data.find('/');
    size_t segundaB  = data.find('/', primeiraB + 1);

    // Deve haver exatamente duas barras
    if (primeiraB == std::string::npos || segundaB == std::string::npos)
        throw std::invalid_argument("Formato invalido: use DIA/MES/ANO");

    if (data.find('/', segundaB + 1) != std::string::npos)
        throw std::invalid_argument("Formato invalido: barras em excesso");

    std::string parteDia = data.substr(0, primeiraB);
    std::string parteMes = data.substr(primeiraB + 1, segundaB - primeiraB - 1);
    std::string parteAno = data.substr(segundaB + 1);

    // Cada parte deve ser não-vazia e conter só dígitos
    for (const std::string& parte : {parteDia, parteMes, parteAno}) {
        if (parte.empty())
            throw std::invalid_argument("Formato invalido: parte vazia");
        for (char c : parte)
            if (c < '0' || c > '9')
                throw std::invalid_argument("Formato invalido: caractere nao numerico");
    }

    int dia = std::stoi(parteDia);
    int mes = std::stoi(parteMes);
    int ano = std::stoi(parteAno);

    // Valida mês
    if (mes < 1 || mes > 12)
        throw std::invalid_argument("Mes invalido: deve ser entre 01 e 12");

    // Valida ano
    if (ano < 2000 || ano > 2999)
        throw std::invalid_argument("Ano invalido: deve ser entre 2000 e 2999");

    // Valida dia considerando o mês e ano
    if (dia < 1 || dia > diasNoMes(mes, ano))
        throw std::invalid_argument("Dia invalido para o mes e ano informados");
}

// ---------------------------------------------------------------------
// Interface pública
// ---------------------------------------------------------------------

void Data::set(const std::string& data) {
    validar(data);
    valor = data;
}