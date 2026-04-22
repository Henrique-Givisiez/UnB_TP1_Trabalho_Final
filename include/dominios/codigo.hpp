#ifndef CODIGO_HPP_INCLUDED
#define CODIGO_HPP_INCLUDED
#include <string>

using namespace std;

class Codigo {
private:
    string codigo;
    void validar(string);
    static const int TAMANHO = 5;
public:
    void setCodigo(string);
    string getCodigo();
};

inline string Codigo::getCodigo() {
    return codigo;
}

#endif // CODIGO_HPP_INCLUDED
