#include <iostream>
#include "dominios/senha.hpp"

#define ASSERT_SUCCESS(comando, msg) \
    try { \
        comando; \
        std::cout << "OK: " << msg << "\n"; \
    } catch (...) { \
        std::cout << "Falhou: " << msg << " (Lancou excecao inesperada)\n"; \
    }

#define ASSERT_THROWS(comando, msg) \
    try { \
        comando; \
        std::cout << "Falhou: " << msg << " (Nao lancou excecao)\n"; \
    } catch (const std::invalid_argument& e) { \
        std::cout << "OK: " << msg << "\n"; \
    } catch (...) { \
        std::cout << "Falhou: " << msg << " (Lancou tipo de excecao errado)\n"; \
    }

void testarSenha() {
    std::cout << "\n===== TESTES SENHA =====\n";

    Senha s;

    // =========================
    // CASOS VALIDOS
    // =========================
    ASSERT_SUCCESS(s.set("a1B2c3"), "Padrao letra-digito alternado valido");
    ASSERT_SUCCESS(s.set("A1b2C3"), "Inicia com maiuscula, alternado valido");
    ASSERT_SUCCESS(s.set("1a2B3c"), "Inicia com digito, alternado valido");
    ASSERT_SUCCESS(s.set("1A2b3C"), "Inicia com digito e maiuscula, alternado valido");

    // =========================
    // TAMANHO INVALIDO
    // =========================
    ASSERT_THROWS(s.set(""),         "String vazia");
    ASSERT_THROWS(s.set("a1B2c"),    "5 caracteres (falta um)");
    ASSERT_THROWS(s.set("a1B2c3d"),  "7 caracteres (um a mais)");

    // =========================
    // CARACTERES INVALIDOS
    // =========================
    ASSERT_THROWS(s.set("a1B2c!"),   "Caractere especial no fim");
    ASSERT_THROWS(s.set("a1B@c3"),   "Arroba no meio");
    ASSERT_THROWS(s.set("a1B2c "),   "Espaco no fim");
    ASSERT_THROWS(s.set("a1B2_3"),   "Underscore");

    // =========================
    // ALTERNANCIA INVALIDA - LETRA SEGUIDA DE LETRA
    // =========================
    ASSERT_THROWS(s.set("ab1C2d"),   "Duas minusculas consecutivas no inicio");
    ASSERT_THROWS(s.set("1aB2Cd"),   "Duas letras consecutivas (maiuscula+minuscula)");
    ASSERT_THROWS(s.set("1a2bCD"),   "Duas maiusculas consecutivas no fim");
    ASSERT_THROWS(s.set("AB1c2d"),   "Duas maiusculas consecutivas no inicio");

    // =========================
    // ALTERNANCIA INVALIDA - DIGITO SEGUIDO DE DIGITO
    // =========================
    ASSERT_THROWS(s.set("12aB3c"),   "Dois digitos consecutivos no inicio");
    ASSERT_THROWS(s.set("a1B23c"),   "Dois digitos consecutivos no meio");
    ASSERT_THROWS(s.set("a1b2C34"),  "Dois digitos no fim (e tamanho 7)");

    // =========================
    // FALTA MINUSCULA
    // =========================
    ASSERT_THROWS(s.set("A1B2C3"),   "Sem nenhuma letra minuscula");
    ASSERT_THROWS(s.set("1A2B3C"),   "Sem minuscula, inicia com digito");

    // =========================
    // FALTA MAIUSCULA
    // =========================
    ASSERT_THROWS(s.set("a1b2c3"),   "Sem nenhuma letra maiuscula");
    ASSERT_THROWS(s.set("1a2b3c"),   "Sem maiuscula, inicia com digito");

    // =========================
    // FALTA DIGITO
    // =========================
    ASSERT_THROWS(s.set("aAbBcC"),   "Sem nenhum digito");

    std::cout << "===== FIM TESTES SENHA =====\n";
}