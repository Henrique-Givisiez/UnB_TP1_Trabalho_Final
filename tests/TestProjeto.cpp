#include <iostream>
#include "entidades/projeto.hpp"

// ---------- Macros de teste ----------

#define ASSERT_SUCCESS(comando, msg) \
    try { \
        comando; \
        std::cout << "OK: " << msg << "\n"; \
    } catch (const std::invalid_argument& e) { \
        std::cout << "Falhou: " << msg << " (Excecao: " << e.what() << ")\n"; \
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

// ---------- Função de teste ----------

/**
 * @brief Executa todos os testes da entidade Projeto.
 *
 * Verifica que setters válidos são aceitos, que getters retornam
 * os valores corretos e que valores inválidos lançam std::invalid_argument.
 */
void testarProjeto() {
    std::cout << "\n==== TESTES PROJETO ====\n";

    Projeto p;

    // --- setCodigo ---
    ASSERT_SUCCESS(p.setCodigo("AB123"), "setCodigo valor valido");
    ASSERT_THROWS (p.setCodigo(""),      "setCodigo vazio");
    ASSERT_THROWS (p.setCodigo("AB CD"), "setCodigo com espaco");
    ASSERT_THROWS (p.setCodigo("ab123"), "setCodigo minusculo");
    ASSERT_THROWS (p.setCodigo("AB1234"), "setCodigo excede tamanho maximo (5 chars)");

    // --- setNome ---
    ASSERT_SUCCESS(p.setNome("My Project"), "setNome valor valido");
    ASSERT_THROWS(p.setNome("Meu Projeto"), "setNome maximo permitido (10 chars)");
    ASSERT_THROWS (p.setNome(""),            "setNome vazio");

    // --- setInicio ---
    ASSERT_SUCCESS(p.setInicio("01/01/2025"), "setInicio data valida");
    ASSERT_THROWS (p.setInicio("32/01/2025"), "setInicio dia invalido");
    ASSERT_THROWS (p.setInicio("01/13/2025"), "setInicio mes invalido");
    ASSERT_THROWS (p.setInicio(""),         "setInicio vazio");

    // --- setTermino ---
    ASSERT_SUCCESS(p.setTermino("31/12/2025"), "setTermino data valida");
    ASSERT_THROWS (p.setTermino("00/12/2025"), "setTermino dia zero");
    ASSERT_THROWS (p.setTermino(""),         "setTermino vazio");

    // --- Getters após valores válidos ---
    p.setCodigo("XY345");
    p.setNome("Sprint");
    p.setInicio("01/03/2025");
    p.setTermino("30/06/2025");

    ASSERT_SUCCESS(
        { if (p.getCodigo() != "XY345")     throw std::invalid_argument(""); },
        "getCodigo retorna valor correto"
    );
    ASSERT_SUCCESS(
        { if (p.getNome()   != "Sprint") throw std::invalid_argument(""); },
        "getNome retorna valor correto"
    );
    ASSERT_SUCCESS(
        { if (p.getInicio() != "01/03/2025")  throw std::invalid_argument(""); },
        "getInicio retorna valor correto"
    );
    ASSERT_SUCCESS(
        { if (p.getTermino() != "30/06/2025") throw std::invalid_argument(""); },
        "getTermino retorna valor correto"
    );

    std::cout << "==== FIM TESTES PROJETO ====\n";
}