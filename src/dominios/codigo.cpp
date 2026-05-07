#include "dominios/codigo.hpp"
#include <stdexcept>

using namespace std;

void Codigo::set(string codigo) {
    // Verifica se codigo eh valido e define atributo 'codigo' se nao falhar
    validar(codigo);
    this->codigo = codigo;
}

// Verifica se o codigo eh valido. Se for valido, nao retorna nada (segue fluxo normal).
// Se nao for valido, lanca uma excecao que sobe ate o ponto mais 'alto' da chamada
void Codigo::validar(string codigo) {
    // Garante que codigo seja 5 caracteres apenas
    if (codigo.size() != TAMANHO) {
        throw invalid_argument("Codigo deve ter exatamente " + to_string(TAMANHO) + " caracteres.");
    }

    // 2 primeiras letras maiusculas
    for (int i = 0; i < 2; i++) {
        if (!isupper(codigo[i])) {
            throw invalid_argument("Os 2 primeiros caracteres devem ser letras maiusculas.");
        }
    }

    // 2 ultimos digitos
    for (int i = 2; i < TAMANHO; i++) {
       if (!isdigit(codigo[i])) {
           throw invalid_argument("Os 3 ultimos caracteres devem ser digitos.");
       }
    }
}
