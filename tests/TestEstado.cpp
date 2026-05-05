#include <iostream>
#include "dominios/estado.hpp"

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

void testarEstado() {
    std::cout << "\n===== TESTES ESTADO =====\n";

    Estado e;
    std::string teste;
    // =========================
    // CASOS VALIDOS
    // =========================
    teste = "A FAZER";
    ASSERT_SUCCESS(e.set(teste), "A FAZER deve ser valido");
    teste = "FAZENDO";
    ASSERT_SUCCESS(e.set(teste), "FAZENDO deve ser valido");
    teste = "FEITO";
    ASSERT_SUCCESS(e.set(teste), "FEITO deve ser valido");

    // =========================
    // STRING INVALIDA
    // =========================
    teste = "FAZER";
    ASSERT_THROWS(e.set(teste), "Estado invalido");
    teste = "FAZENDO ";
    ASSERT_THROWS(e.set(teste), "Estado invalido");
    teste = "JA FEITO";
    ASSERT_THROWS(e.set(teste), "Estado invalido");

    // =========================
    // LETRAS MINUSCULAS
    // =========================
    teste = "a fazer";
    ASSERT_THROWS(e.set(teste), "Estado invalido");
    teste = "fazendo";
    ASSERT_THROWS(e.set(teste), "Estado invalido");
    teste = "FEITo";
    ASSERT_THROWS(e.set(teste), "Estado invalido");

    std::cout << "===== FIM TESTES ESTADO =====\n";
}
