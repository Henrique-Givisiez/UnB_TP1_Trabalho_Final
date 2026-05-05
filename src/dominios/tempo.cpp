#include "dominios/tempo.hpp"
#include <stdexcept>

// ---------------------------------------------------------------------
// Helper privado
// ---------------------------------------------------------------------

void Tempo::validar(int tempo) {
    if (tempo < 1 || tempo > 365)
        throw std::invalid_argument("Tempo invalido: deve ser entre 1 e 365");
}

// ---------------------------------------------------------------------
// Interface pública
// ---------------------------------------------------------------------

void Tempo::set(int tempo) {
    validar(tempo);
    valor = tempo;
}