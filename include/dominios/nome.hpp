#ifndef NOME_HPP_INCLUDED
#define NOME_HPP_INCLUDED
#include <string>

using namespace std;

class Nome {
private:
    string nome;
    static const int LIMITE = 10;
    void validar(const string&);

public:
    void set(const string&);
    string get() const;
};

inline string Nome::get() const {
    return nome;
}

#endif // NOME_HPP_INCLUDED
