#ifndef ESTADO_HPP_INCLUDED
#define ESTADO_HPP_INCLUDED
#include <string>

using namespace std;

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
    void setEstado(string& estado);
    string getEstado() const;

    Valor getValorInterno() const;
};
#endif // ESTADO_HPP_INCLUDED
