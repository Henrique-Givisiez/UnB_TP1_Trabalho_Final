#include <iostream>
#include "entidades/pessoa.hpp"

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

/**
 * @brief Executa todos os testes da entidade Pessoa.
 *
 * Verifica que setters válidos são aceitos, que getters retornam
 * os valores corretos e que valores inválidos lançam std::invalid_argument.
 */
void testarPessoa() {
    std::cout << "\n===== TESTES PESSOA =====\n";

    Pessoa p;

    // =========================
    // EMAIL
    // =========================
    ASSERT_SUCCESS(p.setEmail("joao@gmail.com"),   "Email valido");
    ASSERT_THROWS( p.setEmail("joao@"),            "Email invalido - dominio vazio");
    ASSERT_THROWS( p.setEmail("@gmail.com"),       "Email invalido - local vazio");
    ASSERT_THROWS( p.setEmail("joaogmail.com"),    "Email invalido - sem arroba");

    // =========================
    // NOME
    // =========================
    ASSERT_SUCCESS(p.setNome("Joao"),              "Nome valido simples");
    ASSERT_SUCCESS(p.setNome("Joao Silva"),        "Nome valido com espaco");
    ASSERT_THROWS( p.setNome(""),                  "Nome vazio");
    ASSERT_THROWS( p.setNome("Joao Silva Jr"),     "Nome excede 10 caracteres");
    ASSERT_THROWS( p.setNome(" Joao"),             "Nome inicia com espaco");
    ASSERT_THROWS( p.setNome("Joao "),             "Nome termina com espaco");

    // =========================
    // SENHA
    // =========================
    ASSERT_SUCCESS(p.setSenha("a1B2c3"),           "Senha valida");
    ASSERT_THROWS( p.setSenha("aabbcc"),           "Senha sem digito e com letras consecutivas");
    ASSERT_THROWS( p.setSenha("123456"),           "Senha sem letras e com digitos consecutivos");
    ASSERT_THROWS( p.setSenha("a1B2c"),            "Senha curta (5 chars)");
    ASSERT_THROWS( p.setSenha("A1B2C3"),           "Senha sem minuscula");

    // =========================
    // PAPEL
    // =========================
    ASSERT_SUCCESS(p.setPapel("DESENVOLVEDOR"),           "Papel DESENVOLVEDOR valido");
    ASSERT_SUCCESS(p.setPapel("MESTRE DE SCRUM"),         "Papel MESTRE DE SCRUM valido");
    ASSERT_SUCCESS(p.setPapel("PROPRIETARIO DE PRODUTO"), "Papel PROPRIETARIO DE PRODUTO valido");
    ASSERT_THROWS( p.setPapel("GERENTE"),                 "Papel invalido");

    // =========================
    // GETTERS — consistencia apos set valido
    // =========================
    p.setEmail("maria@email.com");
    p.setNome("Maria");
    p.setSenha("1a2B3c");
    p.setPapel("DESENVOLVEDOR");

    ASSERT_SUCCESS(
        (p.getEmail() == "maria@email.com" ? (void)0 : throw std::invalid_argument("")),
        "getEmail retorna valor correto"
    );
    ASSERT_SUCCESS(
        (p.getNome() == "Maria" ? (void)0 : throw std::invalid_argument("")),
        "getNome retorna valor correto"
    );
    ASSERT_SUCCESS(
        (p.getSenha() == "1a2B3c" ? (void)0 : throw std::invalid_argument("")),
        "getSenha retorna valor correto"
    );
    ASSERT_SUCCESS(
        (p.getPapel() == "DESENVOLVEDOR" ? (void)0 : throw std::invalid_argument("")),
        "getPapel retorna valor correto"
    );

    std::cout << "===== FIM TESTES PESSOA =====\n";
}