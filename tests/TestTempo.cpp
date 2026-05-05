#include <iostream>
#include "dominios/tempo.hpp"

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

void testarTempo() {
    std::cout << "\n===== TESTES TEMPO =====\n";

    Tempo t;

    // =========================
    // CASOS VALIDOS
    // =========================
    ASSERT_SUCCESS(t.set(1),   "Limite inferior (1)");
    ASSERT_SUCCESS(t.set(365), "Limite superior (365)");
    ASSERT_SUCCESS(t.set(180), "Valor no meio do intervalo (180)");

    // =========================
    // LIMITES INVALIDOS
    // =========================
    ASSERT_THROWS(t.set(0),    "Zero (abaixo do minimo)");
    ASSERT_THROWS(t.set(366),  "366 (acima do maximo)");
    ASSERT_THROWS(t.set(-1),   "Negativo (-1)");
    ASSERT_THROWS(t.set(-365), "Negativo grande (-365)");
    ASSERT_THROWS(t.set(1000), "Valor muito alto (1000)");

    std::cout << "===== FIM TESTES TEMPO =====\n";
}