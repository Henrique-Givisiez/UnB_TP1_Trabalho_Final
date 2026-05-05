#include "dominios/email.hpp"
#include <stdexcept>
#include <string>

// ---------------------------------------------------------------------
// Helpers privados
// ---------------------------------------------------------------------

static bool isLocalChar(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') ||
           c == '.' || c == '-';
}

static bool isDominioChar(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') ||
           c == '-' || c == '.';
}

static bool isAlphanumeric(char c) {
    return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

void Email::validarParteLocal(const std::string& local) {
    if (local.empty())
        throw std::invalid_argument("Parte local vazia");

    if (local.size() > 64)
        throw std::invalid_argument("Parte local excede 64 caracteres");

    // Nao pode iniciar com ponto ou hifen
    if (local.front() == '.' || local.front() == '-')
        throw std::invalid_argument("Parte local nao pode iniciar com ponto ou hifen");

    // Nao pode terminar com ponto ou hifen
    if (local.back() == '.' || local.back() == '-')
        throw std::invalid_argument("Parte local nao pode terminar com ponto ou hifen");

    for (size_t i = 0; i < local.size(); i++) {
        char c = local[i];

        if (!isLocalChar(c))
            throw std::invalid_argument("Caractere invalido na parte local");

        // Ponto ou hifen deve ser seguido por letra ou digito
        if ((c == '.' || c == '-') && !isAlphanumeric(local[i + 1]))
            throw std::invalid_argument("Ponto ou hifen deve ser seguido por letra ou digito na parte local");
    }
}

void Email::validarDominio(const std::string& dominio) {
    if (dominio.empty())
        throw std::invalid_argument("Dominio vazio");

    if (dominio.size() > 255)
        throw std::invalid_argument("Dominio excede 255 caracteres");

    // Verifica caracteres validos no dominio
    for (size_t i = 0; i < dominio.size(); i++) {
        char c = dominio[i];

        if (!isDominioChar(c))
            throw std::invalid_argument("Caractere invalido no dominio");
    }

    // Quebra o dominio em partes pelo ponto e valida cada uma
    size_t inicio = 0;
    while (true) {
        size_t fim = dominio.find('.', inicio);
        std::string parte = dominio.substr(inicio, fim - inicio);

        if (parte.empty())
            throw std::invalid_argument("Parte do dominio vazia (pontos consecutivos ou ponto no inicio/fim)");

        if (parte.front() == '-')
            throw std::invalid_argument("Parte do dominio nao pode iniciar com hifen");

        if (parte.back() == '-')
            throw std::invalid_argument("Parte do dominio nao pode terminar com hifen");

        if (fim == std::string::npos) break;
        inicio = fim + 1;
    }
}

void Email::validar(const std::string& email) {
    size_t arroba = email.find('@');

    if (arroba == std::string::npos)
        throw std::invalid_argument("Email deve conter @");

    // Deve haver exatamente um @
    if (email.find('@', arroba + 1) != std::string::npos)
        throw std::invalid_argument("Email nao pode conter mais de um @");

    std::string local   = email.substr(0, arroba);
    std::string dominio = email.substr(arroba + 1);

    validarParteLocal(local);
    validarDominio(dominio);
}

// ---------------------------------------------------------------------
// Interface pública
// ---------------------------------------------------------------------

void Email::set(const std::string& email) {
    validar(email);
    valor = email;
}