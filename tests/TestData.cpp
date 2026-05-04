#include <iostream>
#include "dominios/data.hpp"

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

void testarData() {
    std::cout << "\n===== TESTES DATA =====\n";

    Data d;

    // =========================
    // CASOS VALIDOS
    // =========================
    ASSERT_SUCCESS(d.set("1/01/2000"),  "Dia sem zero, mes com zero, ano minimo");
    ASSERT_SUCCESS(d.set("31/12/2999"), "Ultimo dia do ano, ano maximo");
    ASSERT_SUCCESS(d.set("15/06/2024"), "Data comum no meio do range");
    ASSERT_SUCCESS(d.set("29/02/2000"), "29/02 em ano bissexto (2000)");
    ASSERT_SUCCESS(d.set("29/02/2400"), "29/02 em ano bissexto (2400, divisivel por 400)");
    ASSERT_SUCCESS(d.set("28/02/2001"), "28/02 em ano nao bissexto");
    ASSERT_SUCCESS(d.set("31/01/2024"), "31 dias em janeiro");
    ASSERT_SUCCESS(d.set("31/03/2024"), "31 dias em marco");
    ASSERT_SUCCESS(d.set("30/04/2024"), "30 dias em abril");

    // =========================
    // FORMATO INVALIDO
    // =========================
    ASSERT_THROWS(d.set(""),             "String vazia");
    ASSERT_THROWS(d.set("01-01-2024"),   "Separador errado (hifen)");
    ASSERT_THROWS(d.set("01.01.2024"),   "Separador errado (ponto)");
    ASSERT_THROWS(d.set("01/01"),        "Faltando o ano");
    ASSERT_THROWS(d.set("01/2024"),      "Faltando o dia ou mes");
    ASSERT_THROWS(d.set("/01/2024"),     "Dia vazio");
    ASSERT_THROWS(d.set("01//2024"),     "Mes vazio");
    ASSERT_THROWS(d.set("01/01/"),       "Ano vazio");
    ASSERT_THROWS(d.set("01/01/2024/"),  "Barra em excesso");
    ASSERT_THROWS(d.set("aa/01/2024"),   "Letras no dia");
    ASSERT_THROWS(d.set("01/bb/2024"),   "Letras no mes");
    ASSERT_THROWS(d.set("01/01/abcd"),   "Letras no ano");

    // =========================
    // DIA INVALIDO
    // =========================
    ASSERT_THROWS(d.set("0/01/2024"),  "Dia 0");
    ASSERT_THROWS(d.set("32/01/2024"), "Dia 32 em janeiro");
    ASSERT_THROWS(d.set("31/04/2024"), "Dia 31 em abril (30 dias)");
    ASSERT_THROWS(d.set("31/06/2024"), "Dia 31 em junho (30 dias)");
    ASSERT_THROWS(d.set("31/09/2024"), "Dia 31 em setembro (30 dias)");
    ASSERT_THROWS(d.set("31/11/2024"), "Dia 31 em novembro (30 dias)");
    ASSERT_THROWS(d.set("29/02/2001"), "29/02 em ano nao bissexto (2001)");
    ASSERT_THROWS(d.set("29/02/2100"), "29/02 em centenario nao bissexto (2100)");
    ASSERT_THROWS(d.set("29/02/2200"), "29/02 em centenario nao bissexto (2200)");
    ASSERT_THROWS(d.set("29/02/2300"), "29/02 em centenario nao bissexto (2300)");

    // =========================
    // MES INVALIDO
    // =========================
    ASSERT_THROWS(d.set("01/00/2024"), "Mes 0");
    ASSERT_THROWS(d.set("01/13/2024"), "Mes 13");

    // =========================
    // ANO INVALIDO
    // =========================
    ASSERT_THROWS(d.set("01/01/1999"), "Ano abaixo do minimo (1999)");
    ASSERT_THROWS(d.set("01/01/3000"), "Ano acima do maximo (3000)");
    ASSERT_THROWS(d.set("01/01/0000"), "Ano zero");

    std::cout << "===== FIM TESTES DATA =====\n";
}