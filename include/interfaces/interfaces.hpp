/**
 * @file interfaces.hpp
 * @brief Declaração das interfaces entre as camadas do sistema.
 */
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
    /**
     * @brief Cria uma pessoa no cadastro do sistema.
     *
     * @param pessoa Pessoa que será cadastrada.
     * @return true se a pessoa foi criada; false caso contrário.
     */
    virtual bool criar(const Pessoa& pessoa) = 0;

    /**
     * @brief Lê os dados de uma pessoa cadastrada.
     *
     * @param email Email usado para localizar a pessoa.
     * @param pessoa Ponteiro para receber os dados encontrados.
     * @return true se a pessoa foi encontrada; false caso contrário.
     */
    virtual bool ler(const std::string& email, Pessoa* pessoa) = 0;

    /**
     * @brief Atualiza os dados de uma pessoa cadastrada.
     *
     * @param pessoa Pessoa contendo os dados atualizados.
     * @return true se a pessoa foi atualizada; false caso contrário.
     */
    virtual bool atualizar(const Pessoa& pessoa) = 0;

    /**
     * @brief Exclui uma pessoa cadastrada.
     *
     * @param email Email da pessoa a ser excluída.
     * @return true se a pessoa foi excluída; false caso contrário.
     */
    virtual bool excluir(const std::string& email) = 0;

    /**
     * @brief Destrutor virtual.
     */
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
    /**
     * @brief Cria um plano de sprint associado a um projeto.
     *
     * @param planoSprint Plano de sprint a ser criado.
     * @param codigoProjeto Código do projeto ao qual o plano será associado.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se o plano de sprint foi criado; false caso contrário.
     */
    virtual bool criar(const PlanoSprint& planoSprint,
                       const std::string& codigoProjeto,
                       const std::string& emailUsuarioAutenticado) = 0;

    /**
     * @brief Lê os dados de um plano de sprint.
     *
     * @param codigo Código do plano de sprint.
     * @param planoSprint Ponteiro para receber os dados encontrados.
     * @return true se o plano de sprint foi encontrado; false caso contrário.
     */
    virtual bool ler(const std::string& codigo, PlanoSprint* planoSprint) = 0;

    /**
     * @brief Atualiza os dados de um plano de sprint.
     *
     * @param planoSprint Plano de sprint contendo os dados atualizados.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se o plano de sprint foi atualizado; false caso contrário.
     */
    virtual bool atualizar(const PlanoSprint& planoSprint,
                           const std::string& emailUsuarioAutenticado) = 0;

    /**
     * @brief Exclui um plano de sprint.
     *
     * @param codigo Código do plano de sprint a ser excluído.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se o plano de sprint foi excluído; false caso contrário.
     */
    virtual bool excluir(const std::string& codigo,
                         const std::string& emailUsuarioAutenticado) = 0;

    /**
     * @brief Lista os planos de sprint associados a um projeto.
     *
     * @param codigoProjeto Código do projeto consultado.
     * @param codigosPlanosSprint Ponteiro para receber os códigos dos planos encontrados.
     * @return true se a operação foi realizada; false caso contrário.
     */
    virtual bool listarPlanosSprintAssociadosProjeto(const std::string& codigoProjeto,
                                                     std::vector<std::string>* codigosPlanosSprint) = 0;

    /**
     * @brief Destrutor virtual.
     */
    virtual ~IPlanoSprintServico() {}
};

/**
 * @brief Interface responsável pelos serviços relacionados a histórias de usuário.
 */
class IHistoriaServico {
public:
    /**
     * @brief Cria uma história associada diretamente a um projeto.
     *
     * @param historia História a ser criada.
     * @param codigoProjeto Código do projeto ao qual a história será associada.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se a história foi criada; false caso contrário.
     */
    virtual bool criar(const Historia& historia,
                       const std::string& codigoProjeto,
                       const std::string& emailUsuarioAutenticado) = 0;

    /**
     * @brief Lê os dados de uma história.
     *
     * @param codigo Código da história.
     * @param historia Ponteiro para receber os dados encontrados.
     * @return true se a história foi encontrada; false caso contrário.
     */
    virtual bool ler(const std::string& codigo, Historia* historia) = 0;

    /**
     * @brief Atualiza os dados de uma história.
     *
     * @param historia História contendo os dados atualizados.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se a história foi atualizada; false caso contrário.
     */
    virtual bool atualizar(const Historia& historia,
                           const std::string& emailUsuarioAutenticado) = 0;

    /**
     * @brief Exclui uma história.
     *
     * @param codigo Código da história a ser excluída.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se a história foi excluída; false caso contrário.
     */
    virtual bool excluir(const std::string& codigo,
                         const std::string& emailUsuarioAutenticado) = 0;

    /**
     * @brief Associa uma pessoa a uma história.
     *
     * @param codigoHistoria Código da história.
     * @param emailPessoa Email da pessoa a ser associada.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se a associação foi realizada; false caso contrário.
     */
    virtual bool associarPessoa(const std::string& codigoHistoria,
                                const std::string& emailPessoa,
                                const std::string& emailUsuarioAutenticado) = 0;

    /**
     * @brief Remove a associação entre uma pessoa e uma história.
     *
     * @param codigoHistoria Código da história.
     * @param emailPessoa Email da pessoa que será desassociada.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se a associação foi removida; false caso contrário.
     */
    virtual bool removerAssociacaoPessoa(const std::string& codigoHistoria,
                                         const std::string& emailPessoa,
                                         const std::string& emailUsuarioAutenticado) = 0;

    /**
     * @brief Lista histórias associadas diretamente a um projeto.
     *
     * @param codigoProjeto Código do projeto consultado.
     * @param codigosHistorias Ponteiro para receber os códigos das histórias encontradas.
     * @return true se a operação foi realizada; false caso contrário.
     */
    virtual bool listarHistoriasAssociadasProjeto(const std::string& codigoProjeto,
                                                  std::vector<std::string>* codigosHistorias) = 0;

    /**
     * @brief Lista histórias associadas a um plano de sprint.
     *
     * @param codigoPlanoSprint Código do plano de sprint consultado.
     * @param codigosHistorias Ponteiro para receber os códigos das histórias encontradas.
     * @return true se a operação foi realizada; false caso contrário.
     */
    virtual bool listarHistoriasAssociadasPlanoSprint(const std::string& codigoPlanoSprint,
                                                      std::vector<std::string>* codigosHistorias) = 0;

    /**
     * @brief Lista histórias associadas a uma pessoa.
     *
     * @param emailPessoa Email da pessoa consultada.
     * @param codigosHistorias Ponteiro para receber os códigos das histórias encontradas.
     * @return true se a operação foi realizada; false caso contrário.
     */
    virtual bool listarHistoriasAssociadasPessoa(const std::string& emailPessoa,
                                                 std::vector<std::string>* codigosHistorias) = 0;

    /**
     * @brief Move uma história de um projeto para um plano de sprint.
     *
     * @param codigoHistoria Código da história que será movida.
     * @param codigoProjeto Código do projeto de origem.
     * @param codigoPlanoSprint Código do plano de sprint de destino.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se a história foi movida; false caso contrário.
     */
    virtual bool moverHistoriaParaPlanoSprint(const std::string& codigoHistoria,
                                              const std::string& codigoProjeto,
                                              const std::string& codigoPlanoSprint,
                                              const std::string& emailUsuarioAutenticado) = 0;

    /**
     * @brief Altera o estado de uma história.
     *
     * @param codigoHistoria Código da história.
     * @param novoEstado Novo estado da história.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se o estado foi alterado; false caso contrário.
     */
    virtual bool alterarEstado(const std::string& codigoHistoria,
                               const std::string& novoEstado,
                               const std::string& emailUsuarioAutenticado) = 0;

    /**
     * @brief Destrutor virtual.
     */
    virtual ~IHistoriaServico() {}
};

#endif
