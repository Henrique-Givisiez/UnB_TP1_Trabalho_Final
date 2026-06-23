#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include <string>
#include <vector>

#include "../entidades/pessoa.hpp"
#include "../entidades/projeto.hpp"
#include "../entidades/planosprint.hpp"
#include "../entidades/historia.hpp"

/**
 * @brief Interface responsável pelos serviços de autenticação.
 */
class IAuthServico {
public:
    /**
     * @brief Autentica uma pessoa no sistema.
     * @param email Email da pessoa.
     * @param senha Senha da pessoa.
     * @param pessoaAutenticada Ponteiro para receber os dados da pessoa autenticada.
     * @return true se a autenticação for realizada com sucesso, false caso contrário.
     */
    virtual bool autenticar(const std::string& email,
                            const std::string& senha,
                            Pessoa* pessoaAutenticada) = 0;

    /**
     * @brief Destrutor virtual.
     */
    virtual ~IAuthServico() {}
};

/**
 * @brief Interface responsável pelos serviços relacionados a pessoas.
 */
class IPessoaServico {
public:
    virtual bool criar(const Pessoa& pessoa) = 0;
    virtual bool ler(const std::string& email, Pessoa* pessoa) = 0;
    virtual bool atualizar(const Pessoa& pessoa) = 0;
    virtual bool excluir(const std::string& email) = 0;

    virtual ~IPessoaServico() {}
};

/**
 * @brief Interface para serviços relacionados a Projeto.
 */
class IProjetoServico {
public:
    /**
     * @brief Cria um projeto.
     *
     * @param projeto Projeto a ser criado.
     * @param emailMestreScrum Email do Mestre Scrum associado ao projeto.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se o projeto foi criado; false caso contrário.
     */
    virtual bool criar(const Projeto& projeto,
                       const std::string& emailMestreScrum,
                       const std::string& emailUsuarioAutenticado) = 0;

    /**
     * @brief Lê um projeto.
     *
     * @param codigo Código do projeto.
     * @param projeto Ponteiro para receber os dados do projeto.
     * @return true se encontrou; false caso contrário.
     */
    virtual bool ler(const std::string& codigo, Projeto* projeto) = 0;

    /**
     * @brief Atualiza um projeto.
     *
     * @param projeto Projeto com os dados atualizados.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se atualizou; false caso contrário.
     */
    virtual bool atualizar(const Projeto& projeto,
                           const std::string& emailUsuarioAutenticado) = 0;

    /**
     * @brief Exclui um projeto.
     *
     * @param codigo Código do projeto.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se excluiu; false caso contrário.
     */
    virtual bool excluir(const std::string& codigo,
                         const std::string& emailUsuarioAutenticado) = 0;

    /**
     * @brief Lista os projetos associados a uma pessoa.
     *
     * @param emailPessoa Email da pessoa.
     * @param codigosProjetos Ponteiro para receber os códigos dos projetos.
     * @return true se a operação foi realizada; false caso contrário.
     */
    virtual bool listarProjetosAssociadosPessoa(const std::string& emailPessoa,
                                                std::vector<std::string>* codigosProjetos) = 0;

    /**
     * @brief Destrutor virtual.
     */
    virtual ~IProjetoServico() {}
};

/**
 * @brief Interface para serviços relacionados a Plano de Sprint.
 */
class IPlanoSprintServico {
public:
    virtual bool criar(const PlanoSprint& planoSprint,
                       const std::string& codigoProjeto,
                       const std::string& emailUsuarioAutenticado) = 0;

    virtual bool ler(const std::string& codigo, PlanoSprint* planoSprint) = 0;

    virtual bool atualizar(const PlanoSprint& planoSprint,
                           const std::string& emailUsuarioAutenticado) = 0;

    virtual bool excluir(const std::string& codigo,
                         const std::string& emailUsuarioAutenticado) = 0;

    virtual bool listarPlanosSprintAssociadosProjeto(const std::string& codigoProjeto,
                                                     std::vector<std::string>* codigosPlanosSprint) = 0;

    virtual ~IPlanoSprintServico() {}
};
/**
 * @brief Interface responsável pelos serviços relacionados a histórias de usuário.
 */
class IHistoriaServico {
public:
    virtual bool criar(const Historia& historia, const std::string& codigoProjeto) = 0;
    virtual bool ler(const std::string& codigo, Historia* historia) = 0;
    virtual bool atualizar(const Historia& historia) = 0;
    virtual bool excluir(const std::string& codigo) = 0;

    virtual bool associarPessoa(const std::string& codigoHistoria,
                                const std::string& emailPessoa) = 0;

    virtual bool removerAssociacaoPessoa(const std::string& codigoHistoria,
                                         const std::string& emailPessoa) = 0;

    virtual bool listarHistoriasAssociadasProjeto(const std::string& codigoProjeto,
                                                  std::vector<std::string>* codigosHistorias) = 0;

    virtual bool listarHistoriasAssociadasPlanoSprint(const std::string& codigoPlanoSprint,
                                                      std::vector<std::string>* codigosHistorias) = 0;

    virtual bool listarHistoriasAssociadasPessoa(const std::string& emailPessoa,
                                                 std::vector<std::string>* codigosHistorias) = 0;

    virtual bool moverHistoriaParaPlanoSprint(const std::string& codigoHistoria,
                                              const std::string& codigoProjeto,
                                              const std::string& codigoPlanoSprint) = 0;

    virtual bool alterarEstado(const std::string& codigoHistoria,
                               const std::string& novoEstado) = 0;

    virtual ~IHistoriaServico() {}
};

#endif