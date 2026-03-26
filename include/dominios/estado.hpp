#ifndef ESTADO_HPP_INCLUDED
#define ESTADO_HPP_INCLUDED
#include <string>

class Estado {
public:
    enum Valor {
        A_FAZER,
        FAZENDO,
        FEITO
    };
private:
    Valor valor;
public:
    Estado();
    bool setEstado(std::string& estado);
    std::string getEstado() const;

    Valor getValorInterno() const;
};
#endif // ESTADO_HPP_INCLUDED
