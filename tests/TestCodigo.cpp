#include <iostream>
#include "dominios/codigo.hpp"

// Verifica se a execucao ocorre SEM lancar excecoes (sucesso)
#define ASSERT_SUCCESS(comando, msg) \
    try { \
        comando; \
        std::cout << "OK: " << msg << "\n"; \
    } catch (...) { \
        std::cout << "Falhou: " << msg << " (Lancou excecao inesperada)\n"; \
    }

// Verifica se a execucao LANCA uma excecao (erro esperado)
#define ASSERT_THROWS(comando, msg) \
    try { \
        comando; \
        std::cout << "Falhou: " << msg << " (Nao lancou excecao)\n"; \
    } catch (const std::invalid_argument& e) { \
        std::cout << "OK: " << msg << "\n"; \
    } catch (...) { \
        std::cout << "Falhou: " << msg << " (Lancou tipo de excecao errado)\n"; \
    }

void testarCodigo() {
    std::cout << "\n===== TESTES CODIGO =====\n";

    Codigo c;

    // =========================
    // CASOS VALIDOS (Nao devem lancar erro)
    // =========================
    ASSERT_SUCCESS(c.set("AB123"), "AB123 deve ser valido");
    ASSERT_SUCCESS(c.set("XYZ99"), "XY999 deve ser valido");
    ASSERT_SUCCESS(c.set("QW000"), "QW000 deve ser valido");

    // =========================
    // TAMANHO INVALIDO (Devem lancar invalid_argument)
    // =========================
    ASSERT_THROWS(c.set("AB12"), "Menos de 5 caracteres");
    ASSERT_THROWS(c.set("AB1234"), "Mais de 5 caracteres");
    ASSERT_THROWS(c.set(""), "String vazia");

    // =========================
    // LETRAS MINUSCULAS
    // =========================
    ASSERT_THROWS(c.set("ab123"), "Letras minusculas nao permitidas");
    ASSERT_THROWS(c.set("Ab123"), "Mistura maiuscula/minuscula");
    ASSERT_THROWS(c.set("aB123"), "Mistura maiuscula/minuscula");

    // =========================
    // POSICAO ERRADA DE CARACTERES
    // =========================
    ASSERT_THROWS(c.set("A1123"), "Numero na posicao de letra");
    ASSERT_THROWS(c.set("AB12A"), "Letra no lugar de numero");

    // =========================
    // CARACTERES INVALIDOS
    // =========================
    ASSERT_THROWS(c.set("AB@12"), "Caractere especial @");
    ASSERT_THROWS(c.set("AB 12"), "Espaco no meio");

    // =========================
    // EDGE CASES (Validos)
    // =========================
    ASSERT_SUCCESS(c.set("AA000"), "Limite inferior valido");
    ASSERT_SUCCESS(c.set("ZZ999"), "Limite superior valido");

    std::cout << "===== FIM TESTES CODIGO =====\n";
}
