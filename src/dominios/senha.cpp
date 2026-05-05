#include "dominios/senha.hpp"
#include <stdexcept>
#include <string>

void Senha::validar(const std::string& senha) {

    // Deve ter exatamente 6 caracteres
    if (senha.size() != 6)
        throw std::invalid_argument("Senha deve ter exatamente 6 caracteres");

    bool temMinuscula  = false;
    bool temMaiuscula  = false;
    bool temDigito     = false;

    for (size_t i = 0; i < senha.size(); i++) {
        char c = senha[i];

        // Apenas letras e digitos sao permitidos
        if (!isalnum(c))
            throw std::invalid_argument("Senha contem caractere invalido");

        // Letra nao pode ser seguida de letra
        if (isalpha(c) && i + 1 < senha.size() && isalpha(senha[i + 1]))
            throw std::invalid_argument("Letra nao pode ser seguida de letra");

        // Digito nao pode ser seguido de digito
        if (isdigit(c) && i + 1 < senha.size() && isdigit(senha[i + 1]))
            throw std::invalid_argument("Digito nao pode ser seguido de digito");

        if (islower(c)) temMinuscula = true;
        if (isupper(c)) temMaiuscula = true;
        if (isdigit(c)) temDigito    = true;
    }

    if (!temMinuscula)
        throw std::invalid_argument("Senha deve conter pelo menos uma letra minuscula");

    if (!temMaiuscula)
        throw std::invalid_argument("Senha deve conter pelo menos uma letra maiuscula");

    if (!temDigito)
        throw std::invalid_argument("Senha deve conter pelo menos um digito");
}

// ---------------------------------------------------------------------
// Interface pública
// ---------------------------------------------------------------------

void Senha::set(const std::string& senha) {
    validar(senha);
    valor = senha;
}