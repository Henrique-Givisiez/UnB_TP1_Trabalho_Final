#ifndef PRIORIDADE_HPP_INCLUDED
#define PRIORIDADE_HPP_INCLUDED
#include <string>

using namespace std;

class Prioridade {
public:
    enum PrioridadeEnum {
        BAIXA,
        MEDIA,
        ALTA
    };
private:
    PrioridadeEnum prioridade;
public:
    Prioridade();
    void set(string& novaProridade);
    string get() const;

    PrioridadeEnum getPrioridadeInterno() const;
};


#endif // PRIORIDADE_HPP_INCLUDED
