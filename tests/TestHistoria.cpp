#include <iostream>
#include "entidades/historia.hpp"

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
 * @brief Executa todos os testes da entidade Historia.
 *
 * Verifica que setters válidos são aceitos, que getters retornam
 * os valores corretos e que valores inválidos lançam std::invalid_argument.
 *
 * Regras dos domínios (conforme especificação):
 *  - Codigo    : 5 chars; 2 letras maiúsculas + 3 dígitos.
 *  - Texto     : até 40 chars; letras, dígitos, vírgula, ponto, espaço;
 *                não inicia/termina com vírgula, ponto ou espaço;
 *                espaço seguido de letra/dígito; vírgula/ponto não se repetem.
 *  - Papel     : DESENVOLVEDOR | MESTRE SCRUM | PROPRIETARIO DE PRODUTO.
 *  - Tempo     : int de 1 a 365.
 *  - Prioridade: ALTA | MEDIA | BAIXA.
 *  - Estado    : A FAZER | FAZENDO | FEITO.
 */
void testarHistoria() {
    std::cout << "\n==== TESTES HISTORIA ====\n";

    Historia h;

    // ------------------------------------------------------------------ //
    //  setCodigo                                                           //
    // ------------------------------------------------------------------ //

    ASSERT_SUCCESS(h.setCodigo("AB123"),  "setCodigo valor valido (AB123)");
    ASSERT_SUCCESS(h.setCodigo("ZZ999"),  "setCodigo valor valido (ZZ999)");
    ASSERT_THROWS (h.setCodigo(""),       "setCodigo vazio");
    ASSERT_THROWS (h.setCodigo("ab123"),  "setCodigo letras minusculas");
    ASSERT_THROWS (h.setCodigo("AB12"),   "setCodigo menos de 5 chars");
    ASSERT_THROWS (h.setCodigo("ABC123"), "setCodigo mais de 5 chars");
    ASSERT_THROWS (h.setCodigo("1B234"),  "setCodigo primeiro char e digito");
    ASSERT_THROWS (h.setCodigo("ABCDE"),  "setCodigo sem digitos nos ultimos 2");

    // ------------------------------------------------------------------ //
    //  setTitulo  (domínio Texto)                                         //
    // ------------------------------------------------------------------ //

    ASSERT_SUCCESS(h.setTitulo("Autenticacao de usuarios"),
                   "setTitulo valor valido");
    ASSERT_SUCCESS(h.setTitulo("A"),
                   "setTitulo 1 caractere valido");
    ASSERT_THROWS (h.setTitulo(""),
                   "setTitulo vazio");
    ASSERT_THROWS (h.setTitulo(" Titulo"),
                   "setTitulo inicia com espaco");
    ASSERT_THROWS (h.setTitulo("Titulo "),
                   "setTitulo termina com espaco");
    ASSERT_THROWS (h.setTitulo("Titulo,,dupla"),
                   "setTitulo virgula dupla");
    ASSERT_THROWS (h.setTitulo("Titulo..duplo"),
                   "setTitulo ponto duplo");
    ASSERT_THROWS (h.setTitulo("AAAAAAAAAABBBBBBBBBBCCCCCCCCCCDDDDDDDDDDE"),
                   "setTitulo excede 40 caracteres");

    // ------------------------------------------------------------------ //
    //  setPapel  (domínio Papel)                                          //
    // ------------------------------------------------------------------ //

    ASSERT_SUCCESS(h.setPapel("DESENVOLVEDOR"),        "setPapel DESENVOLVEDOR");
    ASSERT_SUCCESS(h.setPapel("MESTRE SCRUM"),         "setPapel MESTRE SCRUM");
    ASSERT_SUCCESS(h.setPapel("PROPRIETARIO DE PRODUTO"), "setPapel PROPRIETARIO DE PRODUTO");
    ASSERT_THROWS (h.setPapel(""),                     "setPapel vazio");
    ASSERT_THROWS (h.setPapel("GERENTE"),              "setPapel valor invalido");
    ASSERT_THROWS (h.setPapel("desenvolvedor"),        "setPapel minusculo");

    // ------------------------------------------------------------------ //
    //  setAcao  (domínio Texto)                                           //
    // ------------------------------------------------------------------ //

    ASSERT_SUCCESS(h.setAcao("Realizar login com email e senha"),
                   "setAcao valor valido");
    ASSERT_THROWS (h.setAcao(""),
                   "setAcao vazio");
    ASSERT_THROWS (h.setAcao(".Acao invalida"),
                   "setAcao inicia com ponto");
    ASSERT_THROWS (h.setAcao("Acao invalida,"),
                   "setAcao termina com virgula");
    ASSERT_THROWS (h.setAcao("AAAAAAAAAABBBBBBBBBBCCCCCCCCCCDDDDDDDDDDE"),
                   "setAcao excede 40 caracteres");

    // ------------------------------------------------------------------ //
    //  setValor  (domínio Texto)                                          //
    // ------------------------------------------------------------------ //

    ASSERT_SUCCESS(h.setValor("Acessar area restrita do sistema"),
                   "setValor valor valido");
    ASSERT_THROWS (h.setValor(""),
                   "setValor vazio");
    ASSERT_THROWS (h.setValor("Valor invalido "),
                   "setValor termina com espaco");
    ASSERT_THROWS (h.setValor("AAAAAAAAAABBBBBBBBBBCCCCCCCCCCDDDDDDDDDDE"),
                   "setValor excede 40 caracteres");

    // ------------------------------------------------------------------ //
    //  setEstimativa  (domínio Tempo: int de 1 a 365)                     //
    // ------------------------------------------------------------------ //

    ASSERT_SUCCESS(h.setEstimativa(1),   "setEstimativa valor minimo (1)");
    ASSERT_SUCCESS(h.setEstimativa(180), "setEstimativa valor medio (180)");
    ASSERT_SUCCESS(h.setEstimativa(365), "setEstimativa valor maximo (365)");
    ASSERT_THROWS (h.setEstimativa(0),   "setEstimativa zero (abaixo do minimo)");
    ASSERT_THROWS (h.setEstimativa(366), "setEstimativa 366 (acima do maximo)");
    ASSERT_THROWS (h.setEstimativa(-1),  "setEstimativa negativo");

    // ------------------------------------------------------------------ //
    //  setPrioridade  (domínio Prioridade)                                //
    // ------------------------------------------------------------------ //

    ASSERT_SUCCESS(h.setPrioridade("ALTA"),  "setPrioridade ALTA");
    ASSERT_SUCCESS(h.setPrioridade("MEDIA"), "setPrioridade MEDIA");
    ASSERT_SUCCESS(h.setPrioridade("BAIXA"), "setPrioridade BAIXA");
    ASSERT_THROWS (h.setPrioridade(""),      "setPrioridade vazio");
    ASSERT_THROWS (h.setPrioridade("URGENTE"), "setPrioridade valor invalido");  // redundante — ver nota abaixo
    ASSERT_THROWS (h.setPrioridade("alta"),  "setPrioridade minusculo");

    // ------------------------------------------------------------------ //
    //  setEstado  (domínio Estado)                                        //
    // ------------------------------------------------------------------ //

    ASSERT_SUCCESS(h.setEstado("A FAZER"), "setEstado A FAZER");
    ASSERT_SUCCESS(h.setEstado("FAZENDO"), "setEstado FAZENDO");
    ASSERT_SUCCESS(h.setEstado("FEITO"),   "setEstado FEITO");
    ASSERT_THROWS (h.setEstado(""),        "setEstado vazio");
    ASSERT_THROWS (h.setEstado("PAUSADO"), "setEstado valor invalido");
    ASSERT_THROWS (h.setEstado("feito"),   "setEstado minusculo");

    // ------------------------------------------------------------------ //
    //  Getters — verificar retorno correto após atribuições válidas       //
    // ------------------------------------------------------------------ //

    h.setCodigo("HI001");
    h.setTitulo("Login via redes sociais");
    h.setPapel("DESENVOLVEDOR");
    h.setAcao("Realizar login com conta Google");
    h.setValor("Acessar o sistema sem nova senha");
    h.setEstimativa(5);
    h.setPrioridade("ALTA");
    h.setEstado("A FAZER");

    ASSERT_SUCCESS(
        { if (h.getCodigo()     != "HI001")                           throw std::invalid_argument(""); },
        "getCodigo retorna valor correto"
    );
    ASSERT_SUCCESS(
        { if (h.getTitulo()     != "Login via redes sociais")         throw std::invalid_argument(""); },
        "getTitulo retorna valor correto"
    );
    ASSERT_SUCCESS(
        { if (h.getPapel()      != "DESENVOLVEDOR")                   throw std::invalid_argument(""); },
        "getPapel retorna valor correto"
    );
    ASSERT_SUCCESS(
        { if (h.getAcao()       != "Realizar login com conta Google") throw std::invalid_argument(""); },
        "getAcao retorna valor correto"
    );
    ASSERT_SUCCESS(
        { if (h.getValor()      != "Acessar o sistema sem nova senha") throw std::invalid_argument(""); },
        "getValor retorna valor correto"
    );
    ASSERT_SUCCESS(
        { if (h.getEstimativa() != 5)                                 throw std::invalid_argument(""); },
        "getEstimativa retorna valor correto"
    );
    ASSERT_SUCCESS(
        { if (h.getPrioridade() != "ALTA")                            throw std::invalid_argument(""); },
        "getPrioridade retorna valor correto"
    );
    ASSERT_SUCCESS(
        { if (h.getEstado()     != "A FAZER")                         throw std::invalid_argument(""); },
        "getEstado retorna valor correto"
    );

    std::cout << "==== FIM TESTES HISTORIA ====\n";
}