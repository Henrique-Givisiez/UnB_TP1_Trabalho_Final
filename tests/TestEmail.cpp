#include <iostream>
#include "dominios/email.hpp"

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

void testarEmail() {
    std::cout << "\n===== TESTES EMAIL =====\n";

    Email e;

    // =========================
    // CASOS VALIDOS
    // =========================
    ASSERT_SUCCESS(e.set("joao@gmail.com"),          "Email simples valido");
    ASSERT_SUCCESS(e.set("jo.ao@gmail.com"),         "Ponto no meio da parte local");
    ASSERT_SUCCESS(e.set("jo-ao@gmail.com"),         "Hifen no meio da parte local");
    ASSERT_SUCCESS(e.set("jo3ao@gmail.com"),         "Digito na parte local");
    ASSERT_SUCCESS(e.set("user@localhost"),          "Dominio sem ponto (localhost)");
    ASSERT_SUCCESS(e.set("user@sub.dominio.com"),    "Dominio com multiplas partes");
    ASSERT_SUCCESS(e.set("user@dom-inio.com"),       "Hifen no meio da parte do dominio");
    ASSERT_SUCCESS(e.set("a@b.c"),                   "Email minimo valido");
    ASSERT_SUCCESS(e.set("123@456.com"),             "Parte local so com digitos");

    // =========================
    // FORMATO INVALIDO
    // =========================
    ASSERT_THROWS(e.set(""),                  "String vazia");
    ASSERT_THROWS(e.set("semArroba.com"),     "Sem arroba");
    ASSERT_THROWS(e.set("dois@@arroba.com"),  "Dois arrobas");
    ASSERT_THROWS(e.set("@dominio.com"),      "Parte local vazia");
    ASSERT_THROWS(e.set("user@"),             "Dominio vazio");

    // =========================
    // PARTE LOCAL - INICIO E FIM
    // =========================
    ASSERT_THROWS(e.set(".user@gmail.com"),   "Parte local inicia com ponto");
    ASSERT_THROWS(e.set("-user@gmail.com"),   "Parte local inicia com hifen");
    ASSERT_THROWS(e.set("user.@gmail.com"),   "Parte local termina com ponto");
    ASSERT_THROWS(e.set("user-@gmail.com"),   "Parte local termina com hifen");

    // =========================
    // PARTE LOCAL - CARACTERES INVALIDOS
    // =========================
    ASSERT_THROWS(e.set("us er@gmail.com"),   "Espaco na parte local");
    ASSERT_THROWS(e.set("us@er@gmail.com"),   "Arroba extra na parte local");
    ASSERT_THROWS(e.set("us!er@gmail.com"),   "Exclamacao na parte local");
    ASSERT_THROWS(e.set("Us.er@gmail.com"),   "Letra maiuscula na parte local");
    ASSERT_THROWS(e.set("us_er@gmail.com"),   "Underscore na parte local (nao permitido)");

    // =========================
    // PARTE LOCAL - PONTO/HIFEN CONSECUTIVOS
    // =========================
    ASSERT_THROWS(e.set("us..er@gmail.com"),  "Dois pontos consecutivos na parte local");
    ASSERT_THROWS(e.set("us--er@gmail.com"),  "Dois hifens consecutivos na parte local");
    ASSERT_THROWS(e.set("us.-er@gmail.com"),  "Ponto seguido de hifen na parte local");
    ASSERT_THROWS(e.set("us-.er@gmail.com"),  "Hifen seguido de ponto na parte local");

    // =========================
    // PARTE LOCAL - TAMANHO
    // =========================
    ASSERT_THROWS(e.set(std::string(65, 'a') + "@gmail.com"), "Parte local com 65 caracteres (excede 64)");
    ASSERT_SUCCESS(e.set(std::string(64, 'a') + "@gmail.com"), "Parte local com exatamente 64 caracteres");
    
    // =========================
    // PARTE LOCAL - LETRA MAIUSCULA
    // =========================
    ASSERT_THROWS(e.set("User@gmail.com"),    "Letra maiuscula na parte local");
    
    // =========================
    // DOMINIO - INICIO E FIM DAS PARTES
    // =========================
    ASSERT_THROWS(e.set("user@-gmail.com"),   "Parte do dominio inicia com hifen");
    ASSERT_THROWS(e.set("user@gmail-.com"),   "Parte do dominio termina com hifen");
    ASSERT_THROWS(e.set("user@.gmail.com"),   "Dominio inicia com ponto (parte vazia)");
    ASSERT_THROWS(e.set("user@gmail.com."),   "Dominio termina com ponto (parte vazia)");
    ASSERT_THROWS(e.set("user@gmail..com"),   "Pontos consecutivos no dominio");

    // =========================
    // DOMINIO - CARACTERES INVALIDOS
    // =========================
    ASSERT_THROWS(e.set("user@Gmail.com"),    "Letra maiuscula no dominio");
    ASSERT_THROWS(e.set("user@gm ail.com"),   "Espaco no dominio");
    ASSERT_THROWS(e.set("user@gm!ail.com"),   "Exclamacao no dominio");
    ASSERT_THROWS(e.set("user@gm_ail.com"),   "Underscore no dominio (nao permitido)");


    // =========================
    // DOMINIO - TAMANHO
    // =========================
    // Monta um dominio de 256 caracteres: partes de 'a' separadas por ponto
    // Ex: "aaa...a.com" onde a parte local tem 'a' repetido
    std::string dominioLongo = "";
    // Cada parte tem 63 'a' + ponto, quatro vezes = 256 chars
    for (int i = 0; i < 4; i++)
        dominioLongo += std::string(63, 'a') + ".";
    dominioLongo += "com"; // total > 255
    ASSERT_THROWS(e.set("user@" + dominioLongo), "Dominio com mais de 255 caracteres");

    std::cout << "===== FIM TESTES EMAIL =====\n";
}