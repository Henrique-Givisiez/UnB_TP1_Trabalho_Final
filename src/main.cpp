#include <iostream>
#include "dominios/codigo.hpp"
#include "dominios/estado.hpp"
#include "dominios/nome.hpp"
#include "dominios/data.hpp"
#include "dominios/email.hpp"
#include "dominios/senha.hpp"
#include "dominios/tempo.hpp"

void testarCodigo();
void testarEstado();
void testarNome();
void testarData();
void testarEmail();
void testarSenha();
void testarTempo();

int main() {
    testarCodigo();
    testarEstado();
    testarNome();
    testarData();
    testarEmail();
    testarSenha();
    testarTempo();
    return 0;
}
