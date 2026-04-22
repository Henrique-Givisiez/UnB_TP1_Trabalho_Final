#include <iostream>
#include "dominios/nome.hpp"

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

void testarNome() {
    std::cout << "\n===== TESTES NOME =====\n";

    Nome n;
    std::string teste;
    // =========================
    // CASOS VALIDOS (Não devem lançar erro)
    // =========================
    teste = "Henrique";
    ASSERT_SUCCESS(n.setNome(teste), "Henrique deve ser valido");
    teste = "Ju Mend";
    ASSERT_SUCCESS(n.setNome(teste), "Ju Mend deve ser valido");
    teste = "Joao Paulo";
    ASSERT_SUCCESS(n.setNome(teste), "Joao Paulo deve ser valido");

    // =========================
    // NOME INVALIDO (Devem lançar invalid_argument)
    // =========================
    teste = "Henrique Givisiez";
    ASSERT_THROWS(n.setNome(teste), "Nome maior que 10 caracteres");
    teste = "Pedro  Leo";
    ASSERT_THROWS(n.setNome(teste), "Espaco nao seguido de letra");
    teste = "Ju\nMend";
    ASSERT_THROWS(n.setNome(teste), "Apenas espaco em branco eh aceito.");
    teste = "Júlia";
    ASSERT_THROWS(n.setNome(teste), "Acentos nao sao permitidos");
    std::cout << "===== FIM TESTES NOME =====\n";
}
