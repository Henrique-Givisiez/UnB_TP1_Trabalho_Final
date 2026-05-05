#include <iostream>
#include "dominios/texto.hpp"

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

void testarTexto() {
    std::cout << "\n===== TESTES TEXTO =====\n";

    Texto t;

    // =========================
    // CASOS VALIDOS
    // =========================
    ASSERT_SUCCESS(t.set("Hello"),                    "Palavra simples");
    ASSERT_SUCCESS(t.set("Hello World"),              "Duas palavras com espaco");
    ASSERT_SUCCESS(t.set("Hello, World"),             "Virgula seguida de espaco e letra");
    ASSERT_SUCCESS(t.set("versao 1.0"),               "Ponto no meio");
    ASSERT_SUCCESS(t.set("item1, item2, item3"),      "Multiplas virgulas validas");
    ASSERT_SUCCESS(t.set("Dr. Smith"),                "Ponto seguido de espaco e letra");
    ASSERT_SUCCESS(t.set("abc123"),                   "Letras e digitos misturados");
    ASSERT_SUCCESS(t.set("a"),                        "Texto de um caractere");
    ASSERT_SUCCESS(t.set(std::string(40, 'a')),       "Exatamente 40 caracteres");

    // =========================
    // TAMANHO INVALIDO
    // =========================
    ASSERT_THROWS(t.set(""),                          "String vazia");
    ASSERT_THROWS(t.set(std::string(41, 'a')),        "41 caracteres (excede limite)");

    // =========================
    // PRIMEIRO E ULTIMO CARACTERE
    // =========================
    ASSERT_THROWS(t.set(" Hello"),                    "Inicia com espaco");
    ASSERT_THROWS(t.set(",Hello"),                    "Inicia com virgula");
    ASSERT_THROWS(t.set(".Hello"),                    "Inicia com ponto");
    ASSERT_THROWS(t.set("Hello "),                    "Termina com espaco");
    ASSERT_THROWS(t.set("Hello,"),                    "Termina com virgula");
    ASSERT_THROWS(t.set("Hello."),                    "Termina com ponto");

    // =========================
    // VIRGULA - SEQUENCIAS INVALIDAS
    // =========================
    ASSERT_THROWS(t.set("Hello,,World"),              "Duas virgulas consecutivas");
    ASSERT_THROWS(t.set("Hello,.World"),              "Virgula seguida de ponto");

    // =========================
    // PONTO - SEQUENCIAS INVALIDAS
    // =========================
    ASSERT_THROWS(t.set("Hello..World"),              "Dois pontos consecutivos");
    ASSERT_THROWS(t.set("Hello.,World"),              "Ponto seguido de virgula");

    // =========================
    // ESPACO - SEQUENCIAS INVALIDAS
    // =========================
    ASSERT_THROWS(t.set("Hello  World"),              "Dois espacos consecutivos");
    ASSERT_THROWS(t.set("Hello ,World"),              "Espaco seguido de virgula");
    ASSERT_THROWS(t.set("Hello .World"),              "Espaco seguido de ponto");

    // =========================
    // CARACTERES INVALIDOS
    // =========================
    ASSERT_THROWS(t.set("Hello!"),                    "Exclamacao");
    ASSERT_THROWS(t.set("Hello@World"),               "Arroba");
    ASSERT_THROWS(t.set("Hello#World"),               "Cerquilha");
    ASSERT_THROWS(t.set("Hello-World"),               "Hifen (nao permitido em Texto)");
    ASSERT_THROWS(t.set("Hello_World"),               "Underscore");

    std::cout << "===== FIM TESTES TEXTO =====\n";
}