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
/**
 * @brief Verifica se um ano é bissexto.
 *
 * @param ano Ano.
 * @return true se for bissexto; false caso contrário.
 */
bool anoBissexto(int ano) {
    return (ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0);
}

/**
 * @brief Retorna a quantidade de dias antes de determinado mês.
 *
 * @param mes Mês entre 1 e 12.
 * @param ano Ano usado para considerar fevereiro em anos bissextos.
 * @return Quantidade acumulada de dias antes do mês.
 */
int diasAntesDoMes(int mes, int ano) {
    static const int acumuladoNaoBissexto[12] = {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
    };

    int dias = acumuladoNaoBissexto[mes - 1];

    if (mes > 2 && anoBissexto(ano)) {
        dias++;
    }

    return dias;
}

/**
 * @brief Converte data validada no formato DD/MM/AAAA para número absoluto de dias.
 *
 * @param data Data validada pelo domínio Data.
 * @return Quantidade aproximada de dias desde o ano zero.
 */
int converterDataParaDias(const std::string& data) {
    std::size_t primeiraBarra = data.find('/');
    std::size_t segundaBarra = data.find('/', primeiraBarra + 1);

    int dia = std::stoi(data.substr(0, primeiraBarra));
    int mes = std::stoi(data.substr(primeiraBarra + 1,
                                    segundaBarra - primeiraBarra - 1));
    int ano = std::stoi(data.substr(segundaBarra + 1));

    int anosCompletos = ano - 1;

    int dias = anosCompletos * 365;
    dias += anosCompletos / 4;
    dias -= anosCompletos / 100;
    dias += anosCompletos / 400;

    dias += diasAntesDoMes(mes, ano);
    dias += dia;

    return dias;
}

/**
 * @brief Calcula o número de dias entre duas datas.
 *
 * @param dataInicio Data de início.
 * @param dataTermino Data de término.
 * @return Quantidade de dias entre as datas.
 */
int calcularDiasEntreDatas(const std::string& dataInicio,
                           const std::string& dataTermino) {
    return converterDataParaDias(dataTermino) -
           converterDataParaDias(dataInicio);
}

/**
 * @brief Calcula a soma das capacidades dos planos de sprint de um projeto.
 *
 * @param banco Ponteiro para o banco em memória.
 * @param codigoProjeto Código do projeto.
 * @param codigoPlanoIgnorado Código de um plano que deve ser ignorado na soma.
 * @return Soma das capacidades.
 */
int somarCapacidadesPlanosProjeto(BancoDadosMemoria* banco,
                                  const std::string& codigoProjeto,
                                  const std::string& codigoPlanoIgnorado) {
    if (banco == nullptr) {
        return 0;
    }

    int soma = 0;

    std::map<std::string, std::vector<std::string> >::iterator itLista;
    itLista = banco->projetoParaPlanosSprint.find(codigoProjeto);

    if (itLista == banco->projetoParaPlanosSprint.end()) {
        return 0;
    }

    const std::vector<std::string>& codigosPlanos = itLista->second;

    for (std::size_t i = 0; i < codigosPlanos.size(); ++i) {
        if (codigosPlanos[i] == codigoPlanoIgnorado) {
            continue;
        }

        std::map<std::string, PlanoSprint>::iterator itPlano;
        itPlano = banco->planosSprint.find(codigosPlanos[i]);

        if (itPlano != banco->planosSprint.end()) {
            soma += itPlano->second.getCapacidade();
        }
    }

    return soma;
}

/**
 * @brief Obtém o código do projeto associado a um plano de sprint.
 *
 * @param banco Ponteiro para o banco em memória.
 * @param codigoPlanoSprint Código do plano de sprint.
 * @param codigoProjeto Ponteiro para receber o código do projeto.
 * @return true se encontrou associação; false caso contrário.
 */
bool obterProjetoDoPlano(BancoDadosMemoria* banco,
                         const std::string& codigoPlanoSprint,
                         std::string* codigoProjeto) {
    if (banco == nullptr || codigoProjeto == nullptr) {
        return false;
    }

    std::map<std::string, std::string>::iterator it;
    it = banco->planoSprintParaProjeto.find(codigoPlanoSprint);

    if (it == banco->planoSprintParaProjeto.end()) {
        return false;
    }

    *codigoProjeto = it->second;
    return true;
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

PlanoSprintServico::PlanoSprintServico(BancoDadosMemoria* banco) {
    this->banco = banco;
}

bool PlanoSprintServico::criar(const PlanoSprint& planoSprint,
                               const std::string& codigoProjeto,
                               const std::string& emailUsuarioAutenticado) {
    if (banco == nullptr) {
        return false;
    }

    if (!pessoaPossuiPapel(banco, emailUsuarioAutenticado, "MESTRE SCRUM")) {
        return false;
    }

    if (banco->projetos.find(codigoProjeto) == banco->projetos.end()) {
        return false;
    }

    const std::string codigoPlano = planoSprint.getCodigo();

    if (banco->planosSprint.find(codigoPlano) != banco->planosSprint.end()) {
        return false;
    }

    Projeto projeto = banco->projetos[codigoProjeto];

    int duracaoProjeto = calcularDiasEntreDatas(projeto.getInicio(),
                                                projeto.getTermino());

    int capacidadeAtual = somarCapacidadesPlanosProjeto(banco,
                                                        codigoProjeto,
                                                        "");

    int novaSoma = capacidadeAtual + planoSprint.getCapacidade();

    if (novaSoma > duracaoProjeto) {
        return false;
    }

    banco->planosSprint[codigoPlano] = planoSprint;
    banco->planoSprintParaProjeto[codigoPlano] = codigoProjeto;
    banco->projetoParaPlanosSprint[codigoProjeto].push_back(codigoPlano);

    return true;
}

bool PlanoSprintServico::ler(const std::string& codigo,
                             PlanoSprint* planoSprint) {
    if (banco == nullptr || planoSprint == nullptr) {
        return false;
    }

    std::map<std::string, PlanoSprint>::iterator it;
    it = banco->planosSprint.find(codigo);

    if (it == banco->planosSprint.end()) {
        return false;
    }

    *planoSprint = it->second;
    return true;
}

bool PlanoSprintServico::atualizar(const PlanoSprint& planoSprint,
                                   const std::string& emailUsuarioAutenticado) {
    if (banco == nullptr) {
        return false;
    }

    if (!pessoaPossuiPapel(banco, emailUsuarioAutenticado, "MESTRE SCRUM")) {
        return false;
    }

    const std::string codigoPlano = planoSprint.getCodigo();

    std::map<std::string, PlanoSprint>::iterator itPlano;
    itPlano = banco->planosSprint.find(codigoPlano);

    if (itPlano == banco->planosSprint.end()) {
        return false;
    }

    std::string codigoProjeto;

    if (!obterProjetoDoPlano(banco, codigoPlano, &codigoProjeto)) {
        return false;
    }

    std::map<std::string, Projeto>::iterator itProjeto;
    itProjeto = banco->projetos.find(codigoProjeto);

    if (itProjeto == banco->projetos.end()) {
        return false;
    }

    int duracaoProjeto = calcularDiasEntreDatas(itProjeto->second.getInicio(),
                                                itProjeto->second.getTermino());

    int capacidadeOutrosPlanos = somarCapacidadesPlanosProjeto(banco,
                                                               codigoProjeto,
                                                               codigoPlano);

    int novaSoma = capacidadeOutrosPlanos + planoSprint.getCapacidade();

    if (novaSoma > duracaoProjeto) {
        return false;
    }

    /*
     * A chave primária não muda porque o código usado como chave no map
     * permanece o mesmo.
     */
    itPlano->second = planoSprint;
    return true;
}

bool PlanoSprintServico::excluir(const std::string& codigo,
                                 const std::string& emailUsuarioAutenticado) {
    if (banco == nullptr) {
        return false;
    }

    if (!pessoaPossuiPapel(banco, emailUsuarioAutenticado, "MESTRE SCRUM")) {
        return false;
    }

    std::map<std::string, PlanoSprint>::iterator itPlano;
    itPlano = banco->planosSprint.find(codigo);

    if (itPlano == banco->planosSprint.end()) {
        return false;
    }

    /*
     * Não exclui plano de sprint que possui histórias associadas.
     */
    std::map<std::string, std::string>::iterator itHistoria;

    for (itHistoria = banco->historiaParaPlanoSprint.begin();
         itHistoria != banco->historiaParaPlanoSprint.end();
         ++itHistoria) {
        if (itHistoria->second == codigo) {
            return false;
        }
    }

    std::string codigoProjeto;

    if (!obterProjetoDoPlano(banco, codigo, &codigoProjeto)) {
        return false;
    }

    /*
     * Remove o plano da lista projeto -> planos de sprint.
     */
    std::map<std::string, std::vector<std::string> >::iterator itLista;
    itLista = banco->projetoParaPlanosSprint.find(codigoProjeto);

    if (itLista != banco->projetoParaPlanosSprint.end()) {
        std::vector<std::string>& planos = itLista->second;

        planos.erase(
            std::remove(planos.begin(), planos.end(), codigo),
            planos.end()
        );
    }

    banco->planoSprintParaProjeto.erase(codigo);
    banco->planosSprint.erase(itPlano);

    return true;
}

bool PlanoSprintServico::listarPlanosSprintAssociadosProjeto(const std::string& codigoProjeto,
                                                             std::vector<std::string>* codigosPlanosSprint) {
    if (banco == nullptr || codigosPlanosSprint == nullptr) {
        return false;
    }

    codigosPlanosSprint->clear();

    if (banco->projetos.find(codigoProjeto) == banco->projetos.end()) {
        return false;
    }

    std::map<std::string, std::vector<std::string> >::iterator it;
    it = banco->projetoParaPlanosSprint.find(codigoProjeto);

    if (it == banco->projetoParaPlanosSprint.end()) {
        return true;
    }

    *codigosPlanosSprint = it->second;
    return true;
}

HistoriaServico::HistoriaServico(BancoDadosMemoria* banco) {
    this->banco = banco;
}

bool HistoriaServico::criar(const Historia& historia,
                            const std::string& codigoProjeto,
                            const std::string& emailUsuarioAutenticado) {
    if (banco == nullptr) {
        return false;
    }

    if (!pessoaPossuiPapel(banco, emailUsuarioAutenticado, "PROPRIETARIO DE PRODUTO")) {
        return false;
    }

    if (banco->projetos.find(codigoProjeto) == banco->projetos.end()) {
        return false;
    }

    const std::string codigoHistoria = historia.getCodigo();

    if (banco->historias.find(codigoHistoria) != banco->historias.end()) {
        return false;
    }

    if (historia.getEstado() != "A FAZER") {
        return false;
    }

    banco->historias[codigoHistoria] = historia;

    /*
     * Restrição {OU}: neste momento a história fica associada somente ao projeto.
     */
    banco->historiaParaProjeto[codigoHistoria] = codigoProjeto;
    banco->historiaParaPlanoSprint.erase(codigoHistoria);

    return true;
}

bool HistoriaServico::ler(const std::string& codigo, Historia* historia) {
    if (banco == nullptr || historia == nullptr) {
        return false;
    }

    std::map<std::string, Historia>::iterator it;
    it = banco->historias.find(codigo);

    if (it == banco->historias.end()) {
        return false;
    }

    *historia = it->second;
    return true;
}

bool HistoriaServico::atualizar(const Historia& historia,
                                const std::string& emailUsuarioAutenticado) {
    if (banco == nullptr) {
        return false;
    }

    if (!pessoaPossuiPapel(banco, emailUsuarioAutenticado, "PROPRIETARIO DE PRODUTO")) {
        return false;
    }

    const std::string codigoHistoria = historia.getCodigo();

    std::map<std::string, Historia>::iterator it;
    it = banco->historias.find(codigoHistoria);

    if (it == banco->historias.end()) {
        return false;
    }

    /*
     * O estado é preservado porque existe serviço específico para alterar estado.
     */
    Historia historiaAtualizada = historia;
    historiaAtualizada.setEstado(it->second.getEstado());

    it->second = historiaAtualizada;
    return true;
}

bool HistoriaServico::excluir(const std::string& codigo,
                              const std::string& emailUsuarioAutenticado) {
    if (banco == nullptr) {
        return false;
    }

    if (!pessoaPossuiPapel(banco, emailUsuarioAutenticado, "PROPRIETARIO DE PRODUTO")) {
        return false;
    }

    std::map<std::string, Historia>::iterator it;
    it = banco->historias.find(codigo);

    if (it == banco->historias.end()) {
        return false;
    }

    /*
     * Remove todas as associações para evitar inconsistência.
     */
    banco->historiaParaProjeto.erase(codigo);
    banco->historiaParaPlanoSprint.erase(codigo);
    banco->historiaParaPessoas.erase(codigo);

    banco->historias.erase(it);
    return true;
}

bool HistoriaServico::listarHistoriasAssociadasProjeto(const std::string& codigoProjeto,
                                                       std::vector<std::string>* codigosHistorias) {
    if (banco == nullptr || codigosHistorias == nullptr) {
        return false;
    }

    codigosHistorias->clear();

    if (banco->projetos.find(codigoProjeto) == banco->projetos.end()) {
        return false;
    }

    std::map<std::string, std::string>::iterator it;

    for (it = banco->historiaParaProjeto.begin();
         it != banco->historiaParaProjeto.end();
         ++it) {
        if (it->second == codigoProjeto) {
            codigosHistorias->push_back(it->first);
        }
    }

    return true;
}

bool HistoriaServico::listarHistoriasAssociadasPlanoSprint(const std::string& codigoPlanoSprint,
                                                           std::vector<std::string>* codigosHistorias) {
    if (banco == nullptr || codigosHistorias == nullptr) {
        return false;
    }

    codigosHistorias->clear();

    if (banco->planosSprint.find(codigoPlanoSprint) == banco->planosSprint.end()) {
        return false;
    }

    std::map<std::string, std::string>::iterator it;

    for (it = banco->historiaParaPlanoSprint.begin();
         it != banco->historiaParaPlanoSprint.end();
         ++it) {
        if (it->second == codigoPlanoSprint) {
            codigosHistorias->push_back(it->first);
        }
    }

    return true;
}

bool HistoriaServico::listarHistoriasAssociadasPessoa(const std::string& emailPessoa,
                                                      std::vector<std::string>* codigosHistorias) {
    if (banco == nullptr || codigosHistorias == nullptr) {
        return false;
    }

    codigosHistorias->clear();

    if (banco->pessoas.find(emailPessoa) == banco->pessoas.end()) {
        return false;
    }

    std::map<std::string, std::vector<std::string> >::iterator it;

    for (it = banco->historiaParaPessoas.begin();
         it != banco->historiaParaPessoas.end();
         ++it) {
        const std::vector<std::string>& emails = it->second;

        if (std::find(emails.begin(), emails.end(), emailPessoa) != emails.end()) {
            codigosHistorias->push_back(it->first);
        }
    }

    return true;
}

bool HistoriaServico::associarPessoa(const std::string& codigoHistoria,
                                     const std::string& emailPessoa) {
    return false;
}

bool HistoriaServico::removerAssociacaoPessoa(const std::string& codigoHistoria,
                                              const std::string& emailPessoa) {
    return false;
}

bool HistoriaServico::moverHistoriaParaPlanoSprint(const std::string& codigoHistoria,
                                                   const std::string& codigoProjeto,
                                                   const std::string& codigoPlanoSprint) {
    return false;
}

bool HistoriaServico::alterarEstado(const std::string& codigoHistoria,
                                    const std::string& novoEstado) {
    return false;
}