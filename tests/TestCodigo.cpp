#include <iostream>
#include "dominios/codigo.hpp"

// Verifica se a execu��o ocorre SEM lan�ar exce��es (sucesso)
#define ASSERT_SUCCESS(comando, msg) \
    try { \
        comando; \
        std::cout << "OK: " << msg << "\n"; \
    } catch (...) { \
        std::cout << "Falhou: " << msg << " (Lan�ou exce��o inesperada)\n"; \
    }

// Verifica se a execu��o LAN�A uma exce��o (erro esperado)
#define ASSERT_THROWS(comando, msg) \
    try { \
        comando; \
        std::cout << "Falhou: " << msg << " (N�o lan�ou exce��o)\n"; \
    } catch (const std::invalid_argument& e) { \
        std::cout << "OK: " << msg << "\n"; \
    } catch (...) { \
        std::cout << "Falhou: " << msg << " (Lan�ou tipo de exce��o errado)\n"; \
    }

void testarCodigo() {
    std::cout << "\n===== TESTES CODIGO =====\n";

    Codigo c;

    // =========================
    // CASOS VALIDOS (N�o devem lan�ar erro)
    // =========================
    ASSERT_SUCCESS(c.set("ABC12"), "ABC12 deve ser valido");
    ASSERT_SUCCESS(c.set("XYZ99"), "XYZ99 deve ser valido");
    ASSERT_SUCCESS(c.set("QWE00"), "QWE00 deve ser valido");

    // =========================
    // TAMANHO INVALIDO (Devem lan�ar invalid_argument)
    // =========================
    ASSERT_THROWS(c.set("AB12"), "Menos de 5 caracteres");
    ASSERT_THROWS(c.set("ABCDE1"), "Mais de 5 caracteres");
    ASSERT_THROWS(c.set(""), "String vazia");

    // =========================
    // LETRAS MINUSCULAS
    // =========================
    ASSERT_THROWS(c.set("abc12"), "Letras minusculas nao permitidas");
    ASSERT_THROWS(c.set("AbC12"), "Mistura maiuscula/minuscula");

    // =========================
    // POSICAO ERRADA DE CARACTERES
    // =========================
    ASSERT_THROWS(c.set("A1C12"), "Numero na posicao de letra");
    ASSERT_THROWS(c.set("ABC1A"), "Letra no lugar de numero");

    // =========================
    // CARACTERES INVALIDOS
    // =========================
    ASSERT_THROWS(c.set("AB@12"), "Caractere especial @");
    ASSERT_THROWS(c.set("AB 12"), "Espa�o no meio");

    // =========================
    // EDGE CASES (V�lidos)
    // =========================
    ASSERT_SUCCESS(c.set("AAA00"), "Limite inferior valido");
    ASSERT_SUCCESS(c.set("ZZZ99"), "Limite superior valido");

    std::cout << "===== FIM TESTES CODIGO =====\n";
}
