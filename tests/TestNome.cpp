#include <iostream>
#include "dominios/nome.hpp"

// Verifica se a execucao ocorre SEM lancar excecoes (sucesso)
#define ASSERT_SUCCESS(comando, msg) \
    try { \
        comando; \
        std::cout << "OK: " << msg << "\n"; \
    } catch (...) { \
        std::cout << "Falhou: " << msg << " (Lancou excecao inesperada)\n"; \
    }

// Verifica se a execucao LAN�A uma excecao (erro esperado)
#define ASSERT_THROWS(comando, msg) \
    try { \
        comando; \
        std::cout << "Falhou: " << msg << " (Nao lancou excecao)\n"; \
    } catch (const std::invalid_argument& e) { \
        std::cout << "OK: " << msg << "\n"; \
    } catch (...) { \
        std::cout << "Falhou: " << msg << " (Lancou tipo de excecao errado)\n"; \
    }

void testarNome() {
    std::cout << "\n===== TESTES NOME =====\n";

    Nome n;
    std::string teste;
    // =========================
    // CASOS VALIDOS (Nao devem lancar erro)
    // =========================
    ASSERT_SUCCESS(n.set("Henrique"), "Henrique deve ser valido");
    ASSERT_SUCCESS(n.set("Ju Mend"), "Ju Mend deve ser valido");
    ASSERT_SUCCESS(n.set("Joao Paulo"), "Joao Paulo deve ser valido");

    // =========================
    // NOME INVALIDO (Devem lancar invalid_argument)
    // =========================
    ASSERT_THROWS(n.set("Henrique Givisiez"), "Nome maior que 10 caracteres");
    ASSERT_THROWS(n.set("Pedro  Leo"), "Espaco nao seguido de letra");
    ASSERT_THROWS(n.set("Ju\nMend"), "Apenas espaco em branco eh aceito.");
    std::cout << "===== FIM TESTES NOME =====\n";
}
