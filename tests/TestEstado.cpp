#include <iostream>
#include "dominios/estado.hpp"

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

void testarEstado() {
    std::cout << "\n===== TESTES ESTADO =====\n";

    Estado e;
    std::string teste;
    // =========================
    // CASOS VALIDOS
    // =========================
    teste = "A FAZER";
    ASSERT_SUCCESS(e.setEstado(teste), "A FAZER deve ser valido");
    teste = "FAZENDO";
    ASSERT_SUCCESS(e.setEstado(teste), "FAZENDO deve ser valido");
    teste = "FEITO";
    ASSERT_SUCCESS(e.setEstado(teste), "FEITO deve ser valido");

    // =========================
    // STRING INVALIDA
    // =========================
    teste = "FAZER";
    ASSERT_THROWS(e.setEstado(teste), "Estado invalido");
    teste = "FAZENDO ";
    ASSERT_THROWS(e.setEstado(teste), "Estado invalido");
    teste = "JA FEITO";
    ASSERT_THROWS(e.setEstado(teste), "Estado invalido");

    // =========================
    // LETRAS MINUSCULAS
    // =========================
    teste = "a fazer";
    ASSERT_THROWS(e.setEstado(teste), "Estado invalido");
    teste = "fazendo";
    ASSERT_THROWS(e.setEstado(teste), "Estado invalido");
    teste = "FEITo";
    ASSERT_THROWS(e.setEstado(teste), "Estado invalido");

    std::cout << "===== FIM TESTES ESTADO =====\n";
}
