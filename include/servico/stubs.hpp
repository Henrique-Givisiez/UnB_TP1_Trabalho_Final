#ifndef STUBS_HPP_INCLUDED
#define STUBS_HPP_INCLUDED

#include "../interfaces/interfaces.hpp"

/**
 * @brief Stub de autenticação.
 */
class StubAuthServico : public IAuthServico {
public:
    bool autenticar(const std::string& email,
                    const std::string& senha,
                    Pessoa* pessoaAutenticada) override;
};

/**
 * @brief Stub de serviços de pessoa.
 */
class StubPessoaServico : public IPessoaServico {
public:
    bool criar(const Pessoa& pessoa) override;

    bool ler(const std::string& email,
             Pessoa* pessoa) override;

    bool atualizar(const Pessoa& pessoa) override;

    bool excluir(const std::string& email) override;
};

/**
 * @brief Stub de serviços de projeto.
 */
class StubProjetoServico : public IProjetoServico {
public:
    bool criar(const Projeto& projeto,
           const std::string& emailMestreScrum,
           const std::string& emailUsuarioAutenticado) override;

    bool ler(const std::string& codigo,
             Projeto* projeto) override;

    bool atualizar(const Projeto& projeto, 
                   const std::string& emailUsuarioAutenticado) override;

    bool excluir(const std::string& codigo, 
                 const std::string& emailUsuarioAutenticado) override;

    bool listarProjetosAssociadosPessoa(
        const std::string& emailPessoa,
        std::vector<std::string>* codigosProjetos) override;
};

/**
 * @brief Stub de serviços de plano de sprint.
 */
class StubPlanoSprintServico : public IPlanoSprintServico {
public:
    bool criar(const PlanoSprint& planoSprint,
           const std::string& codigoProjeto,
           const std::string& emailUsuarioAutenticado) override;


    bool ler(const std::string& codigo,
             PlanoSprint* planoSprint) override;

    bool atualizar(const PlanoSprint& planoSprint,
               const std::string& emailUsuarioAutenticado) override;
    
    bool excluir(const std::string& codigo,
                const std::string& emailUsuarioAutenticado) override;

    bool listarPlanosSprintAssociadosProjeto(
        const std::string& codigoProjeto,
        std::vector<std::string>* codigosPlanos) override;
};

/**
 * @brief Stub de serviços de história de usuário.
 */
class StubHistoriaServico : public IHistoriaServico {
public:
    bool criar(const Historia& historia,
           const std::string& codigoProjeto,
           const std::string& emailUsuarioAutenticado) override;

    bool ler(const std::string& codigo,
             Historia* historia) override;

    bool atualizar(const Historia& historia,
            const std::string& emailUsuarioAutenticado) override;

    bool excluir(const std::string& codigo,
            const std::string& emailUsuarioAutenticado) override;

    bool associarPessoa(const std::string& codigoHistoria,
                        const std::string& emailPessoa) override;

    bool removerAssociacaoPessoa(const std::string& codigoHistoria,
                                 const std::string& emailPessoa) override;

    bool listarHistoriasAssociadasProjeto(
        const std::string& codigoProjeto,
        std::vector<std::string>* codigosHistorias) override;

    bool listarHistoriasAssociadasPlanoSprint(
        const std::string& codigoPlanoSprint,
        std::vector<std::string>* codigosHistorias) override;

    bool listarHistoriasAssociadasPessoa(
        const std::string& emailPessoa,
        std::vector<std::string>* codigosHistorias) override;

    bool moverHistoriaParaPlanoSprint(
        const std::string& codigoHistoria,
        const std::string& codigoProjeto,
        const std::string& codigoPlanoSprint) override;

    bool alterarEstado(const std::string& codigoHistoria,
                       const std::string& novoEstado) override;
};

#endif