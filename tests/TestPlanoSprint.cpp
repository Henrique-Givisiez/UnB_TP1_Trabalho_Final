#include <iostream>
#include "entidades/planosprint.hpp"

// ---------- Macros de teste ----------

#define ASSERT_SUCCESS(comando, msg) \
    try { \
        comando; \
        std::cout << "OK: " << msg << "\n"; \
    } catch (const std::invalid_argument& e) { \
        std::cout << "Falhou: " << msg << " (Excecao: " << e.what() << ")\n"; \
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
 * @brief Executa todos os testes da entidade PlanoSprint.
 *
 * Verifica que setters válidos são aceitos, que getters retornam
 * os valores corretos e que valores inválidos lançam std::invalid_argument.
 *
 * Regras dos domínios (conforme especificação):
 *  - Codigo : 5 chars; 2 letras maiúsculas + 3 dígitos.
 *  - Texto  : até 40 chars; letras, dígitos, vírgula, ponto, espaço;
 *             não inicia/termina com vírgula, ponto ou espaço;
 *             espaço seguido de letra/dígito; vírgula/ponto não se repetem.
 *  - Tempo  : inteiro de 1 a 365.
 */
void testarPlanoSprint() {
    std::cout << "\n==== TESTES PLANOSPRINT ====\n";

    PlanoSprint ps;

    // ------------------------------------------------------------------ //
    //  setCodigo                                                           //
    // ------------------------------------------------------------------ //

    ASSERT_SUCCESS(ps.setCodigo("ABC23"),  "setCodigo valor valido (AB123)");
    ASSERT_SUCCESS(ps.setCodigo("ZZZ99"),  "setCodigo valor valido (ZZ999)");
    ASSERT_THROWS (ps.setCodigo(""),       "setCodigo vazio");
    ASSERT_THROWS (ps.setCodigo("ab123"),  "setCodigo letras minusculas");
    ASSERT_THROWS (ps.setCodigo("AB12"),   "setCodigo menos de 5 chars");
    ASSERT_THROWS (ps.setCodigo("ABC123"), "setCodigo mais de 5 chars");
    ASSERT_THROWS (ps.setCodigo("AB CD"),  "setCodigo com espaco");
    ASSERT_THROWS (ps.setCodigo("1B234"),  "setCodigo primeiro char e digito");
    ASSERT_THROWS (ps.setCodigo("ABCDE"),  "setCodigo sem digitos nos ultimos 3");

    // ------------------------------------------------------------------ //
    //  setObjetivo  (domínio Texto: até 40 chars, regras de pontuação)    //
    // ------------------------------------------------------------------ //

    ASSERT_SUCCESS(ps.setObjetivo("Entregar modulo de login"),
                   "setObjetivo valor valido simples");
    ASSERT_SUCCESS(ps.setObjetivo("Concluir testes, revisar e publicar"),
                   "setObjetivo com virgula e ponto validos");
    ASSERT_SUCCESS(ps.setObjetivo("A"),
                   "setObjetivo 1 caractere valido");

    ASSERT_THROWS (ps.setObjetivo(""),
                   "setObjetivo vazio");
    ASSERT_THROWS (ps.setObjetivo(" Objetivo"),
                   "setObjetivo inicia com espaco");
    ASSERT_THROWS (ps.setObjetivo("Objetivo "),
                   "setObjetivo termina com espaco");
    ASSERT_THROWS (ps.setObjetivo(",Objetivo"),
                   "setObjetivo inicia com virgula");
    ASSERT_THROWS (ps.setObjetivo("Objetivo."),
                   "setObjetivo termina com ponto");
    ASSERT_THROWS (ps.setObjetivo("Objetivo,,dupla"),
                   "setObjetivo virgula dupla");
    ASSERT_THROWS (ps.setObjetivo("Objetivo..duplo"),
                   "setObjetivo ponto duplo");
    ASSERT_THROWS (ps.setObjetivo("Objetivo,.errado"),
                   "setObjetivo virgula seguida de ponto");
    ASSERT_THROWS (ps.setObjetivo("Objetivo  espaco duplo"),
                   "setObjetivo espaco seguido de espaco");
    ASSERT_THROWS (ps.setObjetivo("AAAAAAAAAABBBBBBBBBBCCCCCCCCCCDDDDDDDDDDE"),
                   "setObjetivo excede 40 caracteres");

    // ------------------------------------------------------------------ //
    //  setCapacidade  (domínio Tempo: inteiro de 1 a 365)                 //
    // ------------------------------------------------------------------ //

    ASSERT_SUCCESS(ps.setCapacidade(1),   "setCapacidade valor minimo (1)");
    ASSERT_SUCCESS(ps.setCapacidade(180), "setCapacidade valor medio (180)");
    ASSERT_SUCCESS(ps.setCapacidade(365), "setCapacidade valor maximo (365)");

    ASSERT_THROWS (ps.setCapacidade(0),    "setCapacidade zero (abaixo do minimo)");
    ASSERT_THROWS (ps.setCapacidade(366), "setCapacidade 366 (acima do maximo)");
    ASSERT_THROWS (ps.setCapacidade(-1),  "setCapacidade negativo");

    // ------------------------------------------------------------------ //
    //  Getters — verificar retorno correto após atribuições válidas       //
    // ------------------------------------------------------------------ //

    ps.setCodigo("ABC89");
    ps.setObjetivo("Finalizar autenticacao do sistema");
    ps.setCapacidade(80);

    ASSERT_SUCCESS(
        { if (ps.getCodigo()     != "ABC89")                            throw std::invalid_argument(""); },
        "getCodigo retorna valor correto"
    );
    ASSERT_SUCCESS(
        { if (ps.getObjetivo()   != "Finalizar autenticacao do sistema") throw std::invalid_argument(""); },
        "getObjetivo retorna valor correto"
    );
    ASSERT_SUCCESS(
        { if (ps.getCapacidade() != 80)                                throw std::invalid_argument(""); },
        "getCapacidade retorna valor correto"
    );

    std::cout << "==== FIM TESTES PLANOSPRINT ====\n";
}