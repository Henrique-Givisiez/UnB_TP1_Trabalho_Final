#include "dominios/nome.hpp"
#include <stdexcept>

using namespace std;

void Nome::validar(string& nome) {
    if (nome.size() > LIMITE ) {
        throw invalid_argument("O nome deve ter no maximo " + to_string(LIMITE) + " caracteres.");
    }

    char primeiro_char = nome[0];
    char ultimo_char = nome[nome.size()- 1];

    if (isspace(primeiro_char) || (isspace(ultimo_char))) {
        throw invalid_argument("Espaco na primeira ou na ultima posicao nao eh permitido.");
    }

    for (unsigned int i = 0; i < nome.size(); i++) {
        char c = nome[i];

        if (!isalpha(c) && c != 32) {
            throw invalid_argument("Caracter invalido.");
        } else {
            if (c == 32 && !isalpha(nome[i+1])) {
                throw invalid_argument("Nome invalido, espacos devem ser seguidos de letra.");
            }
        }
    }
}

void Nome::setNome(string& nome) {
    validar(nome);
    this->NOME = nome;
}
