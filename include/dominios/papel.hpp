#ifndef PAPEL_HPP_INCLUDED
#define PAPEL_HPP_INCLUDED
#include <string>

using namespace std;

class Papel {
public:
    enum PapelEnum {
        DESENVOLVEDOR,
        MESTRE_SCRUM,
        PROPRIETARIO_PROD
    };
private:
    PapelEnum papel;
public:
    void setPapel(string& novoPapel);
    string getPapel() const;

    PapelEnum getPapelInterno() const;
};

#endif // PAPEL_HPP_INCLUDED
