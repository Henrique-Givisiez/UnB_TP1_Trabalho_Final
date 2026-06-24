#ifndef SERVICOS_HPP_INCLUDED
#define SERVICOS_HPP_INCLUDED

#include <map>
#include <string>
#include <vector>

#include "../interfaces/interfaces.hpp"
#include "../entidades/pessoa.hpp"
#include "../entidades/projeto.hpp"
#include "../entidades/planosprint.hpp"
#include "../entidades/historia.hpp"

/**
 * @brief Classe responsável pelo armazenamento em memória dos dados do sistema.
 *
 * Esta classe centraliza os containers usados pelos serviços reais. Todos os
 * serviços devem compartilhar a mesma instância desta classe para garantir
 * consistência entre Pessoas, Projetos, Planos de Sprint e Histórias.
 */
class BancoDadosMemoria {
public:
    /**
     * @brief Pessoas cadastradas, indexadas pelo email.
     */
    std::map<std::string, Pessoa> pessoas;

    /**
     * @brief Projetos cadastrados, indexados pelo código.
     */
    std::map<std::string, Projeto> projetos;

    /**
     * @brief Planos de sprint cadastrados, indexados pelo código.
     */
    std::map<std::string, PlanoSprint> planosSprint;

    /**
     * @brief Histórias cadastradas, indexadas pelo código.
     */
    std::map<std::string, Historia> historias;

    /**
     * @brief Associação entre projeto e email do Mestre Scrum.
     *
     * Chave: código do projeto.
     * Valor: email do Mestre Scrum.
     */
    std::map<std::string, std::string> projetoParaMestreScrum;

    /**
     * @brief Associação entre pessoa e projetos.
     *
     * Chave: email da pessoa.
     * Valor: lista de códigos de projetos associados.
     */
    std::map<std::string, std::vector<std::string> > pessoaParaProjetos;

    /**
     * @brief Associação entre plano de sprint e projeto.
     *
     * Chave: código do plano de sprint.
     * Valor: código do projeto.
     */
    std::map<std::string, std::string> planoSprintParaProjeto;

    /**
     * @brief Associação entre projeto e seus planos de sprint.
     *
     * Chave: código do projeto.
     * Valor: lista de códigos dos planos de sprint.
     */
    std::map<std::string, std::vector<std::string> > projetoParaPlanosSprint;

    /**
     * @brief Associação entre história e projeto.
     *
     * Uma história pode estar associada diretamente a um projeto ou a um plano
     * de sprint, mas nunca aos dois ao mesmo tempo.
     *
     * Chave: código da história.
     * Valor: código do projeto.
     */
    std::map<std::string, std::string> historiaParaProjeto;

    /**
     * @brief Associação entre história e plano de sprint.
     *
     * Chave: código da história.
     * Valor: código do plano de sprint.
     */
    std::map<std::string, std::string> historiaParaPlanoSprint;

    /**
     * @brief Associação entre história e pessoas.
     *
     * Chave: código da história.
     * Valor: lista de emails das pessoas associadas.
     */
    std::map<std::string, std::vector<std::string> > historiaParaPessoas;
};

/**
 * @brief Serviço real responsável pelas operações de Pessoa.
 *
 * Implementa a interface IPessoaServico usando armazenamento em memória.
 */
class PessoaServico : public IPessoaServico {
private:
    /**
     * @brief Banco de dados em memória compartilhado pelos serviços.
     */
    BancoDadosMemoria* banco;

    /**
     * @brief Verifica se uma pessoa possui associações que impedem sua exclusão.
     *
     * @param email Email da pessoa.
     * @return true se houver associação impeditiva; false caso contrário.
     */
    bool possuiAssociacaoImpeditiva(const std::string& email) const;

public:
    /**
     * @brief Construtor.
     *
     * @param banco Ponteiro para o banco de dados em memória compartilhado.
     */
    explicit PessoaServico(BancoDadosMemoria* banco);

    /**
     * @brief Cria uma nova pessoa.
     *
     * @param pessoa Pessoa a ser cadastrada.
     * @return true se a pessoa foi criada; false se o email já existir ou o banco for inválido.
     */
    bool criar(const Pessoa& pessoa) override;

    /**
     * @brief Lê uma pessoa cadastrada.
     *
     * @param email Email da pessoa.
     * @param pessoa Ponteiro para receber os dados encontrados.
     * @return true se encontrou; false caso contrário.
     */
    bool ler(const std::string& email, Pessoa* pessoa) override;

    /**
     * @brief Atualiza uma pessoa cadastrada.
     *
     * A chave primária email não é alterada. A atualização ocorre apenas se já
     * existir uma pessoa cadastrada com o mesmo email informado no objeto.
     *
     * @param pessoa Pessoa com os novos dados.
     * @return true se atualizou; false caso contrário.
     */
    bool atualizar(const Pessoa& pessoa) override;

    /**
     * @brief Exclui uma pessoa cadastrada.
     *
     * A exclusão só é realizada se não houver associações que possam gerar
     * inconsistência no sistema.
     *
     * @param email Email da pessoa.
     * @return true se excluiu; false caso contrário.
     */
    bool excluir(const std::string& email) override;
};

/**
 * @brief Serviço real responsável pela autenticação de usuários.
 *
 * Implementa a interface IAuthServico usando as pessoas cadastradas no banco
 * de dados em memória.
 */
class AuthServico : public IAuthServico {
private:
    /**
     * @brief Banco de dados em memória compartilhado pelos serviços.
     */
    BancoDadosMemoria* banco;

public:
    /**
     * @brief Construtor.
     *
     * @param banco Ponteiro para o banco de dados em memória compartilhado.
     */
    explicit AuthServico(BancoDadosMemoria* banco);

    /**
     * @brief Autentica uma pessoa pelo email e senha.
     *
     * @param email Email informado.
     * @param senha Senha informada.
     * @param pessoaAutenticada Ponteiro que receberá a pessoa autenticada.
     * @return true se autenticação teve sucesso; false caso contrário.
     */
    bool autenticar(const std::string& email,
                    const std::string& senha,
                    Pessoa* pessoaAutenticada) override;
};

/**
 * @brief Serviço real responsável pelas operações de Projeto.
 *
 * Implementa a interface IProjetoServico usando armazenamento em memória
 * e aplicando regras de negócio relacionadas a projetos.
 */
class ProjetoServico : public IProjetoServico {
private:
    /**
     * @brief Banco de dados em memória compartilhado pelos serviços.
     */
    BancoDadosMemoria* banco;

public:
    /**
     * @brief Construtor.
     *
     * @param banco Ponteiro para o banco de dados em memória compartilhado.
     */
    explicit ProjetoServico(BancoDadosMemoria* banco);

    /**
     * @brief Cria um projeto.
     *
     * Apenas usuários com papel PROPRIETARIO DE PRODUTO podem criar projetos.
     * O Mestre Scrum informado deve existir e possuir papel MESTRE SCRUM.
     *
     * @param projeto Projeto a ser criado.
     * @param emailMestreScrum Email do Mestre Scrum associado ao projeto.
     * @param emailUsuarioAutenticado Email do usuário autenticado que solicitou a criação.
     * @return true se criou; false caso contrário.
     */
    bool criar(const Projeto& projeto,
               const std::string& emailMestreScrum,
               const std::string& emailUsuarioAutenticado) override;

    /**
     * @brief Lê um projeto cadastrado.
     *
     * @param codigo Código do projeto.
     * @param projeto Ponteiro para receber os dados encontrados.
     * @return true se encontrou; false caso contrário.
     */
    bool ler(const std::string& codigo, Projeto* projeto) override;

    /**
     * @brief Atualiza um projeto cadastrado.
     *
     * Apenas usuários com papel PROPRIETARIO DE PRODUTO podem atualizar
     * projetos. O intervalo de datas deve permanecer válido.
     *
     * @param projeto Projeto com os novos dados.
     * @param emailUsuarioAutenticado Email do usuário autenticado que solicitou a atualização.
     * @return true se atualizou; false caso contrário.
     */
    bool atualizar(const Projeto& projeto, const std::string& emailUsuarioAutenticado) override;

    /**
     * @brief Exclui um projeto cadastrado.
     *
     * Apenas usuários com papel PROPRIETARIO DE PRODUTO podem excluir
     * projetos. A exclusão não ocorre se houver planos de sprint ou histórias
     * associadas.
     *
     * @param codigo Código do projeto.
     * @param emailUsuarioAutenticado Email do usuário autenticado que solicitou a exclusão.
     * @return true se excluiu; false caso contrário.
     */
    bool excluir(const std::string& codigo, const std::string& emailUsuarioAutenticado) override;

    /**
     * @brief Lista os projetos associados a uma pessoa.
     *
     * @param emailPessoa Email da pessoa.
     * @param codigosProjetos Ponteiro para receber os códigos dos projetos.
     * @return true se a operação foi realizada; false caso contrário.
     */
    bool listarProjetosAssociadosPessoa(const std::string& emailPessoa,
                                        std::vector<std::string>* codigosProjetos) override;
};

/**
 * @brief Serviço real responsável pelas operações de Plano de Sprint.
 *
 * Implementa a interface IPlanoSprintServico usando armazenamento em memória
 * e aplicando regras de negócio relacionadas aos planos de sprint.
 */
class PlanoSprintServico : public IPlanoSprintServico {
private:
    /**
     * @brief Banco de dados em memória compartilhado pelos serviços.
     */
    BancoDadosMemoria* banco;

public:
    /**
     * @brief Construtor.
     *
     * @param banco Ponteiro para o banco de dados em memória compartilhado.
     */
    explicit PlanoSprintServico(BancoDadosMemoria* banco);

    /**
     * @brief Cria um plano de sprint associado a um projeto.
     *
     * Apenas usuários com papel MESTRE SCRUM podem criar planos de sprint.
     * A soma das capacidades dos planos de sprint não pode exceder a duração
     * do projeto.
     *
     * @param planoSprint Plano de sprint a ser criado.
     * @param codigoProjeto Código do projeto associado.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se criou; false caso contrário.
     */
    bool criar(const PlanoSprint& planoSprint,
               const std::string& codigoProjeto,
               const std::string& emailUsuarioAutenticado) override;

    /**
     * @brief Lê um plano de sprint cadastrado.
     *
     * @param codigo Código do plano de sprint.
     * @param planoSprint Ponteiro para receber os dados encontrados.
     * @return true se encontrou; false caso contrário.
     */
    bool ler(const std::string& codigo, PlanoSprint* planoSprint) override;

    /**
     * @brief Atualiza um plano de sprint cadastrado.
     *
     * Apenas usuários com papel MESTRE SCRUM podem atualizar planos de sprint.
     *
     * @param planoSprint Plano de sprint atualizado.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se atualizou; false caso contrário.
     */
    bool atualizar(const PlanoSprint& planoSprint,
                   const std::string& emailUsuarioAutenticado) override;

    /**
     * @brief Exclui um plano de sprint cadastrado.
     *
     * A exclusão só ocorre se não houver histórias associadas ao plano.
     *
     * @param codigo Código do plano de sprint.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se excluiu; false caso contrário.
     */
    bool excluir(const std::string& codigo,
                 const std::string& emailUsuarioAutenticado) override;

    /**
     * @brief Lista planos de sprint associados a um projeto.
     *
     * @param codigoProjeto Código do projeto.
     * @param codigosPlanosSprint Ponteiro para receber os códigos dos planos.
     * @return true se a operação foi realizada; false caso contrário.
     */
    bool listarPlanosSprintAssociadosProjeto(const std::string& codigoProjeto,
                                             std::vector<std::string>* codigosPlanosSprint) override;
};

/**
 * @brief Serviço real responsável pelas operações de História de Usuário.
 *
 * Implementa a interface IHistoriaServico usando armazenamento em memória
 * e aplicando regras de negócio relacionadas às histórias.
 */
class HistoriaServico : public IHistoriaServico {
private:
    /**
     * @brief Banco de dados em memória compartilhado pelos serviços.
     */
    BancoDadosMemoria* banco;

public:
    /**
     * @brief Construtor.
     *
     * @param banco Ponteiro para o banco de dados em memória compartilhado.
     */
    explicit HistoriaServico(BancoDadosMemoria* banco);

    /**
     * @brief Cria uma história associada diretamente a um projeto.
     *
     * Apenas usuários com papel PROPRIETARIO DE PRODUTO podem criar histórias.
     * A história deve iniciar com estado A FAZER.
     *
     * @param historia História a ser criada.
     * @param codigoProjeto Código do projeto associado.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se criou; false caso contrário.
     */
    bool criar(const Historia& historia,
               const std::string& codigoProjeto,
               const std::string& emailUsuarioAutenticado) override;

    /**
     * @brief Lê uma história cadastrada.
     *
     * @param codigo Código da história.
     * @param historia Ponteiro para receber os dados encontrados.
     * @return true se encontrou; false caso contrário.
     */
    bool ler(const std::string& codigo, Historia* historia) override;

    /**
     * @brief Atualiza uma história cadastrada.
     *
     * Apenas usuários com papel PROPRIETARIO DE PRODUTO podem atualizar
     * histórias. O estado atual é preservado e deve ser alterado pela operação
     * específica de alteração de estado. Se a história estiver em um plano de
     * sprint, a nova estimativa não pode exceder a capacidade do plano.
     *
     * @param historia História com os novos dados.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se atualizou; false caso contrário.
     */
    bool atualizar(const Historia& historia,
                   const std::string& emailUsuarioAutenticado) override;

    /**
     * @brief Exclui uma história cadastrada.
     *
     * Apenas usuários com papel PROPRIETARIO DE PRODUTO podem excluir
     * histórias. As associações da história são removidas junto com o cadastro.
     *
     * @param codigo Código da história.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se excluiu; false caso contrário.
     */
    bool excluir(const std::string& codigo,
                 const std::string& emailUsuarioAutenticado) override;

    /**
     * @brief Associa uma pessoa a uma história.
     *
     * Apenas usuários com papel MESTRE SCRUM podem realizar a associação.
     *
     * @param codigoHistoria Código da história.
     * @param emailPessoa Email da pessoa a ser associada.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se associou; false caso contrário.
     */
    bool associarPessoa(const std::string& codigoHistoria,
                        const std::string& emailPessoa,
                        const std::string& emailUsuarioAutenticado) override;

    /**
     * @brief Remove a associação entre uma pessoa e uma história.
     *
     * Apenas usuários com papel MESTRE SCRUM podem remover a associação.
     *
     * @param codigoHistoria Código da história.
     * @param emailPessoa Email da pessoa que será desassociada.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se removeu a associação; false caso contrário.
     */
    bool removerAssociacaoPessoa(const std::string& codigoHistoria,
                                 const std::string& emailPessoa,
                                 const std::string& emailUsuarioAutenticado) override;

    /**
     * @brief Lista histórias associadas diretamente a um projeto.
     *
     * @param codigoProjeto Código do projeto.
     * @param codigosHistorias Ponteiro para receber os códigos das histórias.
     * @return true se a operação foi realizada; false caso contrário.
     */
    bool listarHistoriasAssociadasProjeto(const std::string& codigoProjeto,
                                          std::vector<std::string>* codigosHistorias) override;

    /**
     * @brief Lista histórias associadas a um plano de sprint.
     *
     * @param codigoPlanoSprint Código do plano de sprint.
     * @param codigosHistorias Ponteiro para receber os códigos das histórias.
     * @return true se a operação foi realizada; false caso contrário.
     */
    bool listarHistoriasAssociadasPlanoSprint(const std::string& codigoPlanoSprint,
                                              std::vector<std::string>* codigosHistorias) override;

    /**
     * @brief Lista histórias associadas a uma pessoa.
     *
     * @param emailPessoa Email da pessoa.
     * @param codigosHistorias Ponteiro para receber os códigos das histórias.
     * @return true se a operação foi realizada; false caso contrário.
     */
    bool listarHistoriasAssociadasPessoa(const std::string& emailPessoa,
                                         std::vector<std::string>* codigosHistorias) override;

    /**
     * @brief Move uma história de um projeto para um plano de sprint.
     *
     * Apenas usuários com papel MESTRE SCRUM podem mover histórias. A história
     * deve estar associada diretamente ao projeto informado, o plano deve
     * pertencer ao mesmo projeto e a capacidade do plano não pode ser excedida.
     *
     * @param codigoHistoria Código da história.
     * @param codigoProjeto Código do projeto de origem.
     * @param codigoPlanoSprint Código do plano de sprint de destino.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se moveu; false caso contrário.
     */
    bool moverHistoriaParaPlanoSprint(const std::string& codigoHistoria,
                                      const std::string& codigoProjeto,
                                      const std::string& codigoPlanoSprint,
                                      const std::string& emailUsuarioAutenticado) override;

    /**
     * @brief Altera o estado de uma história.
     *
     * Apenas usuários com papel PROPRIETARIO DE PRODUTO ou MESTRE SCRUM podem
     * alterar o estado da história.
     *
     * @param codigoHistoria Código da história.
     * @param novoEstado Novo estado da história.
     * @param emailUsuarioAutenticado Email do usuário autenticado.
     * @return true se alterou o estado; false caso contrário.
     */
    bool alterarEstado(const std::string& codigoHistoria,
                       const std::string& novoEstado,
                       const std::string& emailUsuarioAutenticado) override;
};

#endif
