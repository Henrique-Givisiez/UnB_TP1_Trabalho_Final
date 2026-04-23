#ifndef ESTADO_HPP_INCLUDED
#define ESTADO_HPP_INCLUDED
#include <string>

using namespace std;

class Estado {
public:
    enum EstadoEnum {
        A_FAZER,
        FAZENDO,
        FEITO
    };
private:
    EstadoEnum estado;
public:
    Estado();
    void setEstado(string& novoEstado);
    string getEstado() const;

    EstadoEnum getEstadoInterno() const;
};
#endif // ESTADO_HPP_INCLUDED
