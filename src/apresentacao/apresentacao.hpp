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
    IPessoaServico* servicoPessoa;

public:
    ControladoraApresentacaoPessoa();

    void setServicoPessoa(IPessoaServico* servicoPessoa);

    void executar();

private:
    void criarPessoa();
    void lerPessoa();
    void atualizarPessoa();
    void excluirPessoa();
};

/**
 * @brief Controladora de apresentação responsável pelas operações de projeto.
 */
class ControladoraApresentacaoProjeto {
private:
    IProjetoServico* servicoProjeto;
    std::string emailUsuarioAutenticado;

public:
    ControladoraApresentacaoProjeto();

    void setServicoProjeto(IProjetoServico* servicoProjeto);
    
    /**
     * @brief Define o email do usuário autenticado.
     *
     * @param emailUsuarioAutenticado Email do usuário autenticado no sistema.
     */
    void setEmailUsuarioAutenticado(const std::string& emailUsuarioAutenticado);
    
    void executar();

private:
    void criarProjeto();
    void lerProjeto();
    void atualizarProjeto();
    void excluirProjeto();
    void listarProjetosPorPessoa();
};

/**
 * @brief Controladora de apresentação responsável pelas operações de plano de sprint.
 */
class ControladoraApresentacaoPlanoSprint {
private:
    IPlanoSprintServico* servicoPlanoSprint;
    std::string emailUsuarioAutenticado;

public:
    ControladoraApresentacaoPlanoSprint();

    void setServicoPlanoSprint(IPlanoSprintServico* servicoPlanoSprint);

    /**
     * @brief Define o email do usuário autenticado.
     *
     * @param emailUsuarioAutenticado Email do usuário autenticado no sistema.
     */
    void setEmailUsuarioAutenticado(const std::string& emailUsuarioAutenticado);

    void executar();

private:
    void criarPlanoSprint();
    void lerPlanoSprint();
    void atualizarPlanoSprint();
    void excluirPlanoSprint();
    void listarPlanosPorProjeto();
};

/**
 * @brief Controladora de apresentação responsável pelas operações de história de usuário.
 */
class ControladoraApresentacaoHistoria {
private:
    IHistoriaServico* servicoHistoria;

public:
    ControladoraApresentacaoHistoria();

    void setServicoHistoria(IHistoriaServico* servicoHistoria);

    void executar();

private:
    void criarHistoria();
    void lerHistoria();
    void atualizarHistoria();
    void excluirHistoria();

    void associarPessoa();
    void removerAssociacaoPessoa();

    void listarHistoriasPorProjeto();
    void listarHistoriasPorPlanoSprint();
    void listarHistoriasPorPessoa();

    void moverHistoriaParaPlanoSprint();
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
    IAuthServico* servicoAuth;
    IPessoaServico* servicoPessoa;

    ControladoraApresentacaoPessoa* controladoraPessoa;
    ControladoraApresentacaoProjeto* controladoraProjeto;
    ControladoraApresentacaoPlanoSprint* controladoraPlanoSprint;
    ControladoraApresentacaoHistoria* controladoraHistoria;

    Pessoa pessoaAutenticada;

public:
    ControladoraApresentacao();

    void setServicoAuth(IAuthServico* servicoAuth);

    void setServicoPessoa(IPessoaServico* servicoPessoa);

    void setControladoraPessoa(ControladoraApresentacaoPessoa* controladoraPessoa);
    void setControladoraProjeto(ControladoraApresentacaoProjeto* controladoraProjeto);
    void setControladoraPlanoSprint(ControladoraApresentacaoPlanoSprint* controladoraPlanoSprint);
    void setControladoraHistoria(ControladoraApresentacaoHistoria* controladoraHistoria);

    void executar();

private:
    bool autenticar();
    void mostrarMenuPrincipal();

    void atualizarPessoaAutenticada();
};

#endif