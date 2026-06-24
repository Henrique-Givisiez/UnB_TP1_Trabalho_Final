#ifndef APRESENTACAO_HPP_INCLUDED
#define APRESENTACAO_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>

#include "../../include/interfaces/interfaces.hpp"

/**
 * @brief Controladora de apresentação responsável pelas operações de pessoa.
 */
class ControladoraApresentacaoPessoa {
private:
    /**
     * @brief Serviço de pessoa usado pela controladora.
     */
    IPessoaServico* servicoPessoa;

public:
    /**
     * @brief Constrói a controladora sem serviço configurado.
     */
    ControladoraApresentacaoPessoa();

    /**
     * @brief Define o serviço de pessoa usado pela apresentação.
     *
     * @param servicoPessoa Ponteiro para a interface de serviço de pessoa.
     */
    void setServicoPessoa(IPessoaServico* servicoPessoa);

    /**
     * @brief Executa o menu de operações de pessoa.
     */
    void executar();

private:
    /**
     * @brief Conduz o fluxo de criação de pessoa.
     */
    void criarPessoa();

    /**
     * @brief Conduz o fluxo de consulta de pessoa.
     */
    void lerPessoa();

    /**
     * @brief Conduz o fluxo de atualização de pessoa.
     */
    void atualizarPessoa();

    /**
     * @brief Conduz o fluxo de exclusão de pessoa.
     */
    void excluirPessoa();
};

/**
 * @brief Controladora de apresentação responsável pelas operações de projeto.
 */
class ControladoraApresentacaoProjeto {
private:
    /**
     * @brief Serviço de projeto usado pela controladora.
     */
    IProjetoServico* servicoProjeto;

    /**
     * @brief Email do usuário autenticado usado nas operações com controle de acesso.
     */
    std::string emailUsuarioAutenticado;

public:
    /**
     * @brief Constrói a controladora sem serviço configurado.
     */
    ControladoraApresentacaoProjeto();

    /**
     * @brief Define o serviço de projeto usado pela apresentação.
     *
     * @param servicoProjeto Ponteiro para a interface de serviço de projeto.
     */
    void setServicoProjeto(IProjetoServico* servicoProjeto);
    
    /**
     * @brief Define o email do usuário autenticado.
     *
     * @param emailUsuarioAutenticado Email do usuário autenticado no sistema.
     */
    void setEmailUsuarioAutenticado(const std::string& emailUsuarioAutenticado);
    
    /**
     * @brief Executa o menu de operações de projeto.
     */
    void executar();

private:
    /**
     * @brief Conduz o fluxo de criação de projeto.
     */
    void criarProjeto();

    /**
     * @brief Conduz o fluxo de consulta de projeto.
     */
    void lerProjeto();

    /**
     * @brief Conduz o fluxo de atualização de projeto.
     */
    void atualizarProjeto();

    /**
     * @brief Conduz o fluxo de exclusão de projeto.
     */
    void excluirProjeto();

    /**
     * @brief Conduz o fluxo de listagem de projetos associados a uma pessoa.
     */
    void listarProjetosPorPessoa();
};

/**
 * @brief Controladora de apresentação responsável pelas operações de plano de sprint.
 */
class ControladoraApresentacaoPlanoSprint {
private:
    /**
     * @brief Serviço de plano de sprint usado pela controladora.
     */
    IPlanoSprintServico* servicoPlanoSprint;

    /**
     * @brief Email do usuário autenticado usado nas operações com controle de acesso.
     */
    std::string emailUsuarioAutenticado;

public:
    /**
     * @brief Constrói a controladora sem serviço configurado.
     */
    ControladoraApresentacaoPlanoSprint();

    /**
     * @brief Define o serviço de plano de sprint usado pela apresentação.
     *
     * @param servicoPlanoSprint Ponteiro para a interface de serviço de plano de sprint.
     */
    void setServicoPlanoSprint(IPlanoSprintServico* servicoPlanoSprint);

    /**
     * @brief Define o email do usuário autenticado.
     *
     * @param emailUsuarioAutenticado Email do usuário autenticado no sistema.
     */
    void setEmailUsuarioAutenticado(const std::string& emailUsuarioAutenticado);

    /**
     * @brief Executa o menu de operações de plano de sprint.
     */
    void executar();

private:
    /**
     * @brief Conduz o fluxo de criação de plano de sprint.
     */
    void criarPlanoSprint();

    /**
     * @brief Conduz o fluxo de consulta de plano de sprint.
     */
    void lerPlanoSprint();

    /**
     * @brief Conduz o fluxo de atualização de plano de sprint.
     */
    void atualizarPlanoSprint();

    /**
     * @brief Conduz o fluxo de exclusão de plano de sprint.
     */
    void excluirPlanoSprint();

    /**
     * @brief Conduz o fluxo de listagem de planos associados a um projeto.
     */
    void listarPlanosPorProjeto();
};

/**
 * @brief Controladora de apresentação responsável pelas operações de história de usuário.
 */
class ControladoraApresentacaoHistoria {
private:
    /**
     * @brief Serviço de história usado pela controladora.
     */
    IHistoriaServico* servicoHistoria;

    /**
     * @brief Email do usuário autenticado usado nas operações com controle de acesso.
     */
    std::string emailUsuarioAutenticado;

public:
    /**
     * @brief Constrói a controladora sem serviço configurado.
     */
    ControladoraApresentacaoHistoria();

    /**
     * @brief Define o serviço de história usado pela apresentação.
     *
     * @param servicoHistoria Ponteiro para a interface de serviço de história.
     */
    void setServicoHistoria(IHistoriaServico* servicoHistoria);

    /**
     * @brief Define o email do usuário autenticado.
     *
     * @param emailUsuarioAutenticado Email do usuário autenticado no sistema.
     */
    void setEmailUsuarioAutenticado(const std::string& emailUsuarioAutenticado);

    /**
     * @brief Executa o menu de operações de história.
     */
    void executar();

private:
    /**
     * @brief Conduz o fluxo de criação de história.
     */
    void criarHistoria();

    /**
     * @brief Conduz o fluxo de consulta de história.
     */
    void lerHistoria();

    /**
     * @brief Conduz o fluxo de atualização de história.
     */
    void atualizarHistoria();

    /**
     * @brief Conduz o fluxo de exclusão de história.
     */
    void excluirHistoria();

    /**
     * @brief Conduz o fluxo de associação de pessoa a história.
     */
    void associarPessoa();

    /**
     * @brief Conduz o fluxo de remoção da associação entre pessoa e história.
     */
    void removerAssociacaoPessoa();

    /**
     * @brief Conduz o fluxo de listagem de histórias associadas a um projeto.
     */
    void listarHistoriasPorProjeto();

    /**
     * @brief Conduz o fluxo de listagem de histórias associadas a um plano de sprint.
     */
    void listarHistoriasPorPlanoSprint();

    /**
     * @brief Conduz o fluxo de listagem de histórias associadas a uma pessoa.
     */
    void listarHistoriasPorPessoa();

    /**
     * @brief Conduz o fluxo de movimentação de história para plano de sprint.
     */
    void moverHistoriaParaPlanoSprint();

    /**
     * @brief Conduz o fluxo de alteração de estado de história.
     */
    void alterarEstadoHistoria();
};

/**
 * @brief Controladora principal da camada de apresentação.
 *
 * Responsável pelo menu inicial, autenticação e direcionamento
 * para as demais controladoras da camada de apresentação.
 */
class ControladoraApresentacao {
private:
    /**
     * @brief Serviço de autenticação usado pela controladora principal.
     */
    IAuthServico* servicoAuth;

    /**
     * @brief Serviço de pessoa usado para recarregar a pessoa autenticada.
     */
    IPessoaServico* servicoPessoa;

    /**
     * @brief Controladora de apresentação de pessoa.
     */
    ControladoraApresentacaoPessoa* controladoraPessoa;

    /**
     * @brief Controladora de apresentação de projeto.
     */
    ControladoraApresentacaoProjeto* controladoraProjeto;

    /**
     * @brief Controladora de apresentação de plano de sprint.
     */
    ControladoraApresentacaoPlanoSprint* controladoraPlanoSprint;

    /**
     * @brief Controladora de apresentação de história.
     */
    ControladoraApresentacaoHistoria* controladoraHistoria;

    /**
     * @brief Pessoa autenticada na sessão atual.
     */
    Pessoa pessoaAutenticada;

public:
    /**
     * @brief Constrói a controladora principal sem serviços ou controladoras configurados.
     */
    ControladoraApresentacao();

    /**
     * @brief Define o serviço de autenticação.
     *
     * @param servicoAuth Ponteiro para a interface de serviço de autenticação.
     */
    void setServicoAuth(IAuthServico* servicoAuth);

    /**
     * @brief Define o serviço de pessoa.
     *
     * @param servicoPessoa Ponteiro para a interface de serviço de pessoa.
     */
    void setServicoPessoa(IPessoaServico* servicoPessoa);

    /**
     * @brief Define a controladora de apresentação de pessoa.
     *
     * @param controladoraPessoa Ponteiro para a controladora de pessoa.
     */
    void setControladoraPessoa(ControladoraApresentacaoPessoa* controladoraPessoa);

    /**
     * @brief Define a controladora de apresentação de projeto.
     *
     * @param controladoraProjeto Ponteiro para a controladora de projeto.
     */
    void setControladoraProjeto(ControladoraApresentacaoProjeto* controladoraProjeto);

    /**
     * @brief Define a controladora de apresentação de plano de sprint.
     *
     * @param controladoraPlanoSprint Ponteiro para a controladora de plano de sprint.
     */
    void setControladoraPlanoSprint(ControladoraApresentacaoPlanoSprint* controladoraPlanoSprint);

    /**
     * @brief Define a controladora de apresentação de história.
     *
     * @param controladoraHistoria Ponteiro para a controladora de história.
     */
    void setControladoraHistoria(ControladoraApresentacaoHistoria* controladoraHistoria);

    /**
     * @brief Executa o fluxo principal da aplicação.
     */
    void executar();

private:
    /**
     * @brief Conduz o fluxo de autenticação do usuário.
     *
     * @return true se o usuário foi autenticado; false caso contrário.
     */
    bool autenticar();

    /**
     * @brief Exibe o menu principal e direciona para as demais controladoras.
     *
     * @return true se o usuário escolheu sair do sistema; false em caso de logout.
     */
    bool mostrarMenuPrincipal();

    /**
     * @brief Recarrega os dados da pessoa autenticada a partir do serviço.
     *
     * @return true se a pessoa autenticada ainda existe; false caso contrário.
     */
    bool atualizarPessoaAutenticada();
};

#endif
