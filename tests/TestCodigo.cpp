#include <iostream>
#include "dominios/codigo.hpp"

// Verifica se a execução ocorre SEM lançar exceções (sucesso)
#define ASSERT_SUCCESS(comando, msg) \
    try { \
        comando; \
        std::cout << "OK: " << msg << "\n"; \
    } catch (...) { \
        std::cout << "Falhou: " << msg << " (Lançou exceção inesperada)\n"; \
    }

// Verifica se a execução LANÇA uma exceção (erro esperado)
#define ASSERT_THROWS(comando, msg) \
    try { \
        comando; \
        std::cout << "Falhou: " << msg << " (Não lançou exceção)\n"; \
    } catch (const std::invalid_argument& e) { \
        std::cout << "OK: " << msg << "\n"; \
    } catch (...) { \
        std::cout << "Falhou: " << msg << " (Lançou tipo de exceção errado)\n"; \
    }

void testarCodigo() {
    std::cout << "\n===== TESTES CODIGO =====\n";

    Codigo c;

    // =========================
    // CASOS VALIDOS (Não devem lançar erro)
    // =========================
    ASSERT_SUCCESS(c.setCodigo("ABC12"), "ABC12 deve ser valido");
    ASSERT_SUCCESS(c.setCodigo("XYZ99"), "XYZ99 deve ser valido");
    ASSERT_SUCCESS(c.setCodigo("QWE00"), "QWE00 deve ser valido");

    // =========================
    // TAMANHO INVALIDO (Devem lançar invalid_argument)
    // =========================
    ASSERT_THROWS(c.setCodigo("AB12"), "Menos de 5 caracteres");
    ASSERT_THROWS(c.setCodigo("ABCDE1"), "Mais de 5 caracteres");
    ASSERT_THROWS(c.setCodigo(""), "String vazia");

    // =========================
    // LETRAS MINUSCULAS
    // =========================
    ASSERT_THROWS(c.setCodigo("abc12"), "Letras minusculas nao permitidas");
    ASSERT_THROWS(c.setCodigo("AbC12"), "Mistura maiuscula/minuscula");

    // =========================
    // POSICAO ERRADA DE CARACTERES
    // =========================
    ASSERT_THROWS(c.setCodigo("A1C12"), "Numero na posicao de letra");
    ASSERT_THROWS(c.setCodigo("ABC1A"), "Letra no lugar de numero");

    // =========================
    // CARACTERES INVALIDOS
    // =========================
    ASSERT_THROWS(c.setCodigo("AB@12"), "Caractere especial @");
    ASSERT_THROWS(c.setCodigo("AB 12"), "Espaço no meio");

    // =========================
    // EDGE CASES (Válidos)
    // =========================
    ASSERT_SUCCESS(c.setCodigo("AAA00"), "Limite inferior valido");
    ASSERT_SUCCESS(c.setCodigo("ZZZ99"), "Limite superior valido");

    std::cout << "===== FIM TESTES CODIGO =====\n";
}
