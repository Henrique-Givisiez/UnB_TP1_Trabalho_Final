#ifndef CODIGO_HPP_INCLUDED
#define CODIGO_HPP_INCLUDED
#include <string>


class Codigo {
private:
    std::string codigo;
    void validar(std::string);
    static const int TAMANHO = 5;
public:
    void set(std::string);
    std::string get() const;
};

inline std::string Codigo::get() const{
    return codigo;
}

#endif // CODIGO_HPP_INCLUDED
