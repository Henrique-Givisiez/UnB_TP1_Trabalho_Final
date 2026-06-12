#include "../../include/servico/servicos.hpp"

#include <algorithm>
#include <string>

namespace {
/**
 * @brief Verifica se uma pessoa cadastrada possui determinado papel.
 *
 * @param banco Ponteiro para o banco em memória.
 * @param email Email da pessoa.
 * @param papelEsperado Papel esperado.
 * @return true se a pessoa existe e possui o papel esperado; false caso contrário.
 */
bool pessoaPossuiPapel(BancoDadosMemoria* banco,
                       const std::string& email,
                       const std::string& papelEsperado) {
    if (banco == nullptr) {
        return false;
    }

    std::map<std::string, Pessoa>::iterator it;
    it = banco->pessoas.find(email);

    if (it == banco->pessoas.end()) {
        return false;
    }

    return it->second.getPapel() == papelEsperado;
}

/**
 * @brief Converte data no formato DD/MM/AAAA ou D/MM/AAAA para inteiro comparável.
 *
 * @param data Data validada pelo domínio Data.
 * @return Valor no formato AAAAMMDD.
 */
int converterDataParaInteiro(const std::string& data) {
    std::size_t primeiraBarra = data.find('/');
    std::size_t segundaBarra = data.find('/', primeiraBarra + 1);

    int dia = std::stoi(data.substr(0, primeiraBarra));
    int mes = std::stoi(data.substr(primeiraBarra + 1,
                                    segundaBarra - primeiraBarra - 1));
    int ano = std::stoi(data.substr(segundaBarra + 1));

    return ano * 10000 + mes * 100 + dia;
}

/**
 * @brief Verifica se a data de início é menor ou igual à data de término.
 *
 * @param dataInicio Data de início.
 * @param dataTermino Data de término.
 * @return true se o intervalo é válido; false caso contrário.
 */
bool intervaloDatasValido(const std::string& dataInicio,
                           const std::string& dataTermino) {
    return converterDataParaInteiro(dataInicio) <=
           converterDataParaInteiro(dataTermino);
}
}

PessoaServico::PessoaServico(BancoDadosMemoria* banco) {
    this->banco = banco;
}

bool PessoaServico::criar(const Pessoa& pessoa) {
    if (banco == nullptr) {
        return false;
    }

    const std::string email = pessoa.getEmail();

    if (banco->pessoas.find(email) != banco->pessoas.end()) {
        return false;
    }

    banco->pessoas[email] = pessoa;
    return true;
}

bool PessoaServico::ler(const std::string& email, Pessoa* pessoa) {
    if (banco == nullptr || pessoa == nullptr) {
        return false;
    }

    std::map<std::string, Pessoa>::iterator it = banco->pessoas.find(email);

    if (it == banco->pessoas.end()) {
        return false;
    }

    *pessoa = it->second;
    return true;
}

bool PessoaServico::atualizar(const Pessoa& pessoa) {
    if (banco == nullptr) {
        return false;
    }

    const std::string email = pessoa.getEmail();

    std::map<std::string, Pessoa>::iterator it = banco->pessoas.find(email);

    if (it == banco->pessoas.end()) {
        return false;
    }

    /*
     * A chave primária não é editada porque o email usado como chave no map
     * permanece o mesmo. A apresentação também não deve oferecer edição da PK.
     */
    it->second = pessoa;
    return true;
}

bool PessoaServico::excluir(const std::string& email) {
    if (banco == nullptr) {
        return false;
    }

    std::map<std::string, Pessoa>::iterator it = banco->pessoas.find(email);

    if (it == banco->pessoas.end()) {
        return false;
    }

    if (possuiAssociacaoImpeditiva(email)) {
        return false;
    }

    banco->pessoas.erase(it);
    return true;
}

bool PessoaServico::possuiAssociacaoImpeditiva(const std::string& email) const {
    if (banco == nullptr) {
        return true;
    }

    /*
     * Impede excluir uma pessoa que esteja associada a algum projeto.
     */
    std::map<std::string, std::vector<std::string> >::const_iterator itProjetos;
    itProjetos = banco->pessoaParaProjetos.find(email);

    if (itProjetos != banco->pessoaParaProjetos.end() &&
        !itProjetos->second.empty()) {
        return true;
    }

    /*
     * Impede excluir uma pessoa que seja Mestre Scrum de algum projeto.
     */
    std::map<std::string, std::string>::const_iterator itMestre;

    for (itMestre = banco->projetoParaMestreScrum.begin();
         itMestre != banco->projetoParaMestreScrum.end();
         ++itMestre) {
        if (itMestre->second == email) {
            return true;
        }
    }

    /*
     * Impede excluir uma pessoa associada a alguma história.
     */
    std::map<std::string, std::vector<std::string> >::const_iterator itHistorias;

    for (itHistorias = banco->historiaParaPessoas.begin();
         itHistorias != banco->historiaParaPessoas.end();
         ++itHistorias) {
        const std::vector<std::string>& emails = itHistorias->second;

        if (std::find(emails.begin(), emails.end(), email) != emails.end()) {
            return true;
        }
    }

    return false;
}

AuthServico::AuthServico(BancoDadosMemoria* banco) {
    this->banco = banco;
}

bool AuthServico::autenticar(const std::string& email,
                             const std::string& senha,
                             Pessoa* pessoaAutenticada) {
    if (banco == nullptr) {
        return false;
    }

    std::map<std::string, Pessoa>::iterator it = banco->pessoas.find(email);

    if (it == banco->pessoas.end()) {
        return false;
    }

    if (it->second.getSenha() != senha) {
        return false;
    }

    *pessoaAutenticada = it->second;
    return true;
}

ProjetoServico::ProjetoServico(BancoDadosMemoria* banco) {
    this->banco = banco;
}

bool ProjetoServico::criar(const Projeto& projeto,
                           const std::string& emailMestreScrum,
                           const std::string& emailUsuarioAutenticado) {
    if (banco == nullptr) {
        return false;
    }

    const std::string codigoProjeto = projeto.getCodigo();

    /*
     * Verifica se ja existe projeto com o mesmo codigo.
     */
    if (banco->projetos.find(codigoProjeto) != banco->projetos.end()) {
        return false;
    }
    
    /*
     * Verifica se o usuario autenticado possui papel PROPRIETARIO DE PRODUTO e
     * se o Mestre Scrum informado possui papel MESTRE SCRUM.
     */
    if (!pessoaPossuiPapel(banco, emailUsuarioAutenticado, "PROPRIETARIO DE PRODUTO")) {
        return false;
    }

    if (!pessoaPossuiPapel(banco, emailMestreScrum, "MESTRE SCRUM")) {
        return false;
    }

    /*
     * Verifica se o intervalo de datas e valido (data de inicio <= data de termino).
    */
    if (!intervaloDatasValido(projeto.getInicio(), projeto.getTermino())) {
        return false;
    }

    /*
     * Cadastra projeto e associa Mestre Scrum.
     */
    banco->projetos[codigoProjeto] = projeto;
    banco->projetoParaMestreScrum[codigoProjeto] = emailMestreScrum;

    /*
     * Associa o projeto ao Mestre Scrum e ao Proprietario de Produto criador.
     */
    banco->pessoaParaProjetos[emailMestreScrum].push_back(codigoProjeto);
    banco->pessoaParaProjetos[emailUsuarioAutenticado].push_back(codigoProjeto);

    return true;
}

bool ProjetoServico::ler(const std::string& codigo, Projeto* projeto) {
    if (banco == nullptr || projeto == nullptr) {
        return false;
    }

    std::map<std::string, Projeto>::iterator it;
    it = banco->projetos.find(codigo);

    if (it == banco->projetos.end()) {
        return false;
    }

    *projeto = it->second;
    return true;
}

bool ProjetoServico::atualizar(const Projeto& projeto, const std::string& emailUsuarioAutenticado) {
    if (banco == nullptr) {
        return false;
    }

    if (!pessoaPossuiPapel(banco, emailUsuarioAutenticado, "PROPRIETARIO DE PRODUTO")) {
        return false;
    }
    
    const std::string codigo = projeto.getCodigo();

    std::map<std::string, Projeto>::iterator it;
    it = banco->projetos.find(codigo);

    if (it == banco->projetos.end()) {
        return false;
    }

    /*
     * Verifica se o intervalo de datas e valido (data de inicio <= data de termino).
    */
    if (!intervaloDatasValido(projeto.getInicio(), projeto.getTermino())) {
        return false;
    }
    /*
     * A chave primaria nao muda porque o codigo usado como chave no map
     * permanece o mesmo.
     */
    it->second = projeto;
    return true;
}

bool ProjetoServico::excluir(const std::string& codigo, const std::string& emailUsuarioAutenticado) {
    if (banco == nullptr) {
        return false;
    }

    if (!pessoaPossuiPapel(banco, emailUsuarioAutenticado, "PROPRIETARIO DE PRODUTO")) {
        return false;
    }

    std::map<std::string, Projeto>::iterator it;
    it = banco->projetos.find(codigo);

    if (it == banco->projetos.end()) {
        return false;
    }

    /*
     * Nao exclui projeto que possui planos de sprint associados.
     */
    std::map<std::string, std::vector<std::string> >::iterator itPlanos;
    itPlanos = banco->projetoParaPlanosSprint.find(codigo);

    if (itPlanos != banco->projetoParaPlanosSprint.end() &&
        !itPlanos->second.empty()) {
        return false;
    }

    /*
     * Nao exclui projeto que possui historias associadas diretamente.
     */
    std::map<std::string, std::string>::iterator itHistoria;

    for (itHistoria = banco->historiaParaProjeto.begin();
         itHistoria != banco->historiaParaProjeto.end();
         ++itHistoria) {
        if (itHistoria->second == codigo) {
            return false;
        }
    }

    /*
     * Remove associacao projeto -> Mestre Scrum.
     */
    banco->projetoParaMestreScrum.erase(codigo);

    /*
     * Remove o codigo do projeto das listas pessoa -> projetos.
     */
    std::map<std::string, std::vector<std::string> >::iterator itPessoaProjetos;

    for (itPessoaProjetos = banco->pessoaParaProjetos.begin();
         itPessoaProjetos != banco->pessoaParaProjetos.end();
         ++itPessoaProjetos) {
        std::vector<std::string>& projetosPessoa = itPessoaProjetos->second;

        projetosPessoa.erase(
            std::remove(projetosPessoa.begin(), projetosPessoa.end(), codigo),
            projetosPessoa.end()
        );
    }

    banco->projetos.erase(it);
    return true;
}

bool ProjetoServico::listarProjetosAssociadosPessoa(const std::string& emailPessoa,
                                                    std::vector<std::string>* codigosProjetos) {
    if (banco == nullptr || codigosProjetos == nullptr) {
        return false;
    }

    codigosProjetos->clear();

    if (banco->pessoas.find(emailPessoa) == banco->pessoas.end()) {
        return false;
    }

    std::map<std::string, std::vector<std::string> >::iterator it;
    it = banco->pessoaParaProjetos.find(emailPessoa);

    if (it == banco->pessoaParaProjetos.end()) {
        return true;
    }

    *codigosProjetos = it->second;
    return true;
}