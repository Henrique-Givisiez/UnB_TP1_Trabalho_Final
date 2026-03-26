#include <iostream>
#include "dominios/codigo.hpp"

#define ASSERT_TRUE(cond, msg) \
    if (!(cond)) std::cout << "Falhou: " << msg << "\n"; \
    else std::cout << "OK: " << msg << "\n";

void testarCodigo() {
    std::cout << "\n===== TESTES CODIGO =====\n";

    Codigo c;

    // =========================
    // CASOS VALIDOS
    // =========================
    ASSERT_TRUE(c.setCodigo("ABC12") == true, "ABC12 deve ser valido");
    ASSERT_TRUE(c.setCodigo("XYZ99") == true, "XYZ99 deve ser valido");
    ASSERT_TRUE(c.setCodigo("QWE00") == true, "QWE00 deve ser valido");

    // =========================
    // TAMANHO INVALIDO
    // =========================
    ASSERT_TRUE(c.setCodigo("AB12") == false, "Menos de 5 caracteres");
    ASSERT_TRUE(c.setCodigo("ABCDE1") == false, "Mais de 5 caracteres");
    ASSERT_TRUE(c.setCodigo("") == false, "String vazia");

    // =========================
    // LETRAS MINUSCULAS
    // =========================
    ASSERT_TRUE(c.setCodigo("abc12") == false, "Letras minusculas nao permitidas");
    ASSERT_TRUE(c.setCodigo("AbC12") == false, "Mistura maiuscula/minuscula");

    // =========================
    // POSICAO ERRADA DE CARACTERES
    // =========================
    ASSERT_TRUE(c.setCodigo("A1C12") == false, "Numero na posicao de letra");
    ASSERT_TRUE(c.setCodigo("AB112") == false, "Numero no lugar de letra");
    ASSERT_TRUE(c.setCodigo("ABC1A") == false, "Letra no lugar de numero");

    // =========================
    // CARACTERES INVALIDOS
    // =========================
    ASSERT_TRUE(c.setCodigo("AB@12") == false, "Caractere especial @");
    ASSERT_TRUE(c.setCodigo("AB#12") == false, "Caractere especial #");
    ASSERT_TRUE(c.setCodigo("AB 12") == false, "Espaço no meio");

    // =========================
    // DIGITOS INVALIDOS
    // =========================
    ASSERT_TRUE(c.setCodigo("ABC1X") == false, "Letra na parte numerica");
    ASSERT_TRUE(c.setCodigo("ABCXY") == false, "Sem numeros no final");

    // =========================
    // EDGE CASES
    // =========================
    ASSERT_TRUE(c.setCodigo("AAA00") == true, "Limite inferior valido");
    ASSERT_TRUE(c.setCodigo("ZZZ99") == true, "Limite superior valido");

    std::cout << "===== FIM TESTES CODIGO =====\n";
}
