#include "dominios/texto.hpp"
#include <stdexcept>
#include <string>

// ---------------------------------------------------------------------
// Helpers privados
// ---------------------------------------------------------------------

static bool isTextoChar(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') ||
           c == ',' || c == '.' || c == ' ';
}

void Texto::validar(const std::string& texto) {

    if (texto.empty())
        throw std::invalid_argument("Texto nao pode ser vazio");

    if (texto.size() > 40)
        throw std::invalid_argument("Texto excede 40 caracteres");

    // Primeiro caractere nao pode ser virgula, ponto ou espaco
    char primeiro = texto.front();
    if (primeiro == ',' || primeiro == '.' || primeiro == ' ')
        throw std::invalid_argument("Texto nao pode iniciar com virgula, ponto ou espaco");

    // Ultimo caractere nao pode ser virgula, ponto ou espaco
    char ultimo = texto.back();
    if (ultimo == ',' || ultimo == '.' || ultimo == ' ')
        throw std::invalid_argument("Texto nao pode terminar com virgula, ponto ou espaco");

    for (size_t i = 0; i < texto.size(); i++) {
        char c = texto[i];

        if (!isTextoChar(c))
            throw std::invalid_argument("Caractere invalido no texto");

        // Virgula nao pode ser seguida de virgula ou ponto
        if (c == ',' && (texto[i + 1] == ',' || texto[i + 1] == '.'))
            throw std::invalid_argument("Virgula nao pode ser seguida de virgula ou ponto");

        // Ponto nao pode ser seguido de virgula ou ponto
        if (c == '.' && (texto[i + 1] == ',' || texto[i + 1] == '.'))
            throw std::invalid_argument("Ponto nao pode ser seguido de virgula ou ponto");

        // Espaco deve ser seguido de letra ou digito
        if (c == ' ' && !isalnum(texto[i + 1]))
            throw std::invalid_argument("Espaco deve ser seguido de letra ou digito");
    }
}

// ---------------------------------------------------------------------
// Interface pública
// ---------------------------------------------------------------------

void Texto::set(const std::string& texto) {
    validar(texto);
    valor = texto;
}