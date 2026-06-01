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

#endif