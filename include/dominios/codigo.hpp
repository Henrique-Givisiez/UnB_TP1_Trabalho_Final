#ifndef CODIGO_HPP_INCLUDED
#define CODIGO_HPP_INCLUDED
#include <string>

using namespace std;

class Codigo {
private:
    string codigo;
    bool validar(string);
    static const int TAMANHO = 5;
public:
    bool setCodigo(string);
    string getCodigo();
};

inline string Codigo::getCodigo() {
    return codigo;
}

#endif // CODIGO_HPP_INCLUDED
