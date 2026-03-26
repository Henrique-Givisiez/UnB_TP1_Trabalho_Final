#include "dominios/codigo.hpp"
#include <iostream>

using namespace std;

bool Codigo::setCodigo(string codigo) {
    // Verifica se codigo eh valido e define atributo 'codigo' se passar
    if (!validar(codigo)) return false;
    this->codigo = codigo;
    return true;
}

bool Codigo::validar(string codigo) {
    // Garante que codigo seja 5 caracteres apenas
    if (codigo.size() != TAMANHO) return false;

    // 3 primeiras letras maiúsculas
    for (int i = 0; i < 3; i++) {
        if (!isupper(codigo[i])) return false;
    }

    // 2 ultimos digitos
    for (int i = 3; i < TAMANHO; i++) {
       if (!isdigit(codigo[i])) return false;
    }

    return true;
}
