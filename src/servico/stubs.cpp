#include "../../include/servico/stubs.hpp"

using std::string;
using std::vector;

/* ========================================================= */
/* ================== STUB AUTH SERVICO ==================== */
/* ========================================================= */

bool StubAuthServico::autenticar(const string& email,
                                 const string& senha,
                                 Pessoa* pessoaAutenticada) {

    if(email.empty() || senha.empty() || pessoaAutenticada == nullptr) {
        return false;
    }

    pessoaAutenticada->setEmail(email);
    pessoaAutenticada->setNome("Usuario");
    pessoaAutenticada->setSenha(senha);
    pessoaAutenticada->setPapel("DESENVOLVEDOR");

    return true;
}

/* ========================================================= */
/* ================= STUB PESSOA SERVICO =================== */
/* ========================================================= */

bool StubPessoaServico::criar(const Pessoa& pessoa) {
    return true;
}

bool StubPessoaServico::ler(const string& email,
                            Pessoa* pessoa) {

    if(email.empty() || pessoa == nullptr) {
        return false;
    }

    pessoa->setEmail(email);
    pessoa->setNome("Pessoa");
    pessoa->setSenha("A1b2C3");
    pessoa->setPapel("DESENVOLVEDOR");

    return true;
}

bool StubPessoaServico::atualizar(const Pessoa& pessoa) {
    return true;
}

bool StubPessoaServico::excluir(const string& email) {
    return !email.empty();
}

/* ========================================================= */
/* ================ STUB PROJETO SERVICO =================== */
/* ========================================================= */

bool StubProjetoServico::criar(const Projeto& projeto,
                               const std::string& emailMestreScrum,
                               const std::string& emailUsuarioAutenticado) {

    return true;
}

bool StubProjetoServico::ler(const string& codigo,
                             Projeto* projeto) {

    if(codigo.empty() || projeto == nullptr) {
        return false;
    }

    projeto->setCodigo(codigo);
    projeto->setNome("Projeto");
    projeto->setInicio("01/01/2026");
    projeto->setTermino("10/01/2026");

    return true;
}

bool StubProjetoServico::atualizar(const Projeto& projeto,
                                  const string& emailUsuarioAutenticado) {
    return true;
}

bool StubProjetoServico::excluir(const string& codigo,
                                 const string& emailUsuarioAutenticado) {
    return true;
}

bool StubProjetoServico::listarProjetosAssociadosPessoa(
    const string& emailPessoa,
    vector<string>* codigosProjetos) {

    if(emailPessoa.empty() || codigosProjetos == nullptr) {
        return false;
    }

    codigosProjetos->push_back("PR001");
    codigosProjetos->push_back("PR002");

    return true;
}

/* ========================================================= */
/* ============== STUB PLANO SPRINT SERVICO ================ */
/* ========================================================= */

bool StubPlanoSprintServico::criar(const PlanoSprint& planoSprint,
                                   const string& codigoProjeto,
                                   const std::string& emailUsuarioAutenticado) {
    return true;
}

bool StubPlanoSprintServico::ler(const string& codigo,
                                 PlanoSprint* planoSprint) {

    if(codigo.empty() || planoSprint == nullptr) {
        return false;
    }

    planoSprint->setCodigo(codigo);
    planoSprint->setObjetivo("Objetivo do sprint");
    planoSprint->setCapacidade(10);

    return true;
}

bool StubPlanoSprintServico::atualizar(const PlanoSprint& planoSprint,
                                      const std::string& emailUsuarioAutenticado) {
    return true;
}

bool StubPlanoSprintServico::excluir(const std::string& codigo,
                                    const std::string& emailUsuarioAutenticado) {
    return true;
}

bool StubPlanoSprintServico::listarPlanosSprintAssociadosProjeto(
    const string& codigoProjeto,
    vector<string>* codigosPlanos) {

    if(codigoProjeto.empty() || codigosPlanos == nullptr) {
        return false;
    }

    codigosPlanos->push_back("PS001");
    codigosPlanos->push_back("PS002");

    return true;
}

/* ========================================================= */
/* ================ STUB HISTORIA SERVICO ================== */
/* ========================================================= */

bool StubHistoriaServico::criar(const Historia& historia,
                         const std::string& codigoProjeto,
                         const std::string& emailUsuarioAutenticado) {
    return true;
}

bool StubHistoriaServico::ler(const string& codigo,
                              Historia* historia) {

    if(codigo.empty() || historia == nullptr) {
        return false;
    }

    historia->setCodigo(codigo);
    historia->setTitulo("Titulo da historia");
    historia->setAcao("Acao desejada");
    historia->setValor("Valor esperado");
    historia->setPapel("DESENVOLVEDOR");
    historia->setPrioridade("ALTA");
    historia->setEstado("A FAZER");
    historia->setEstimativa(5);

    return true;
}

bool StubHistoriaServico::atualizar(const Historia& historia,
                                   const std::string& emailUsuarioAutenticado) {
    return true;
}

bool StubHistoriaServico::excluir(const std::string& codigo,
                                 const std::string& emailUsuarioAutenticado) {
    return true;
}

bool StubHistoriaServico::associarPessoa(
    const string& codigoHistoria,
    const string& emailPessoa) {

    return (!codigoHistoria.empty() &&
            !emailPessoa.empty());
}

bool StubHistoriaServico::removerAssociacaoPessoa(
    const string& codigoHistoria,
    const string& emailPessoa) {

    return (!codigoHistoria.empty() &&
            !emailPessoa.empty());
}

bool StubHistoriaServico::listarHistoriasAssociadasProjeto(
    const string& codigoProjeto,
    vector<string>* codigosHistorias) {

    if(codigoProjeto.empty() || codigosHistorias == nullptr) {
        return false;
    }

    codigosHistorias->push_back("HT001");
    codigosHistorias->push_back("HT002");

    return true;
}

bool StubHistoriaServico::listarHistoriasAssociadasPlanoSprint(
    const string& codigoPlanoSprint,
    vector<string>* codigosHistorias) {

    if(codigoPlanoSprint.empty() || codigosHistorias == nullptr) {
        return false;
    }

    codigosHistorias->push_back("HT003");
    codigosHistorias->push_back("HT004");

    return true;
}

bool StubHistoriaServico::listarHistoriasAssociadasPessoa(
    const string& emailPessoa,
    vector<string>* codigosHistorias) {

    if(emailPessoa.empty() || codigosHistorias == nullptr) {
        return false;
    }

    codigosHistorias->push_back("HT005");
    codigosHistorias->push_back("HT006");

    return true;
}

bool StubHistoriaServico::moverHistoriaParaPlanoSprint(
    const string& codigoHistoria,
    const string& codigoProjeto,
    const string& codigoPlanoSprint) {

    return (!codigoHistoria.empty() &&
            !codigoProjeto.empty() &&
            !codigoPlanoSprint.empty());
}

bool StubHistoriaServico::alterarEstado(
    const string& codigoHistoria,
    const string& novoEstado) {

    return (!codigoHistoria.empty() &&
            !novoEstado.empty());
}