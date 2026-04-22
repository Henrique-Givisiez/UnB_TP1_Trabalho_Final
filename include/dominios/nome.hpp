#ifndef NOME_HPP_INCLUDED
#define NOME_HPP_INCLUDED
#include <string>

using namespace std;

class Nome {
private:
    string NOME;
    static const int LIMITE = 10;
    void validar(string&);

public:
    void setNome(string&);
    string getNome() const;
};

inline string Nome::getNome() const {
    return NOME;
}

#endif // NOME_HPP_INCLUDED
