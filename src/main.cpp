#include <iostream>
#include <stdexcept>

#include "../include/servico/servicos.hpp"
#include "../include/servico/stubs.hpp"

#include "apresentacao/apresentacao.hpp"

int main() {
    BancoDadosMemoria banco;

    PessoaServico pessoaServico(&banco);
    AuthServico authServico(&banco);
    ProjetoServico projetoServico(&banco);
    PlanoSprintServico planoSprintServico(&banco);
    HistoriaServico historiaServico(&banco);

    /*
     * Dados iniciais para facilitar os testes.
     *
     * Contas criadas:
     *
     * 1) Proprietario de Produto
     *    Email: admin@admin.com
     *    Senha: A1b2C3
     *
     * 2) Mestre Scrum
     *    Email: scrum@tp1.com
     *    Senha: A1b2C3
     *
     * 3) Desenvolvedor
     *    Email: dev@tp1.com
     *    Senha: A1b2C3
     *
     * Projeto criado:
     *    Codigo: PR001
     *
     * Plano de Sprint criado:
     *    Codigo: SP001
     */
    try {
        Pessoa proprietarioProduto;
        proprietarioProduto.setEmail("admin@admin.com");
        proprietarioProduto.setNome("Admin");
        proprietarioProduto.setSenha("A1b2C3");
        proprietarioProduto.setPapel("PROPRIETARIO DE PRODUTO");

        if (!pessoaServico.criar(proprietarioProduto)) {
            std::cout << "Aviso: nao foi possivel criar a pessoa admin.\n";
        }

        Pessoa mestreScrum;
        mestreScrum.setEmail("scrum@scrum.com");
        mestreScrum.setNome("Scrum");
        mestreScrum.setSenha("A1b2C3");
        mestreScrum.setPapel("MESTRE SCRUM");

        if (!pessoaServico.criar(mestreScrum)) {
            std::cout << "Aviso: nao foi possivel criar a pessoa Mestre Scrum.\n";
        }

        Pessoa desenvolvedor;
        desenvolvedor.setEmail("dev@dev.com");
        desenvolvedor.setNome("Dev");
        desenvolvedor.setSenha("A1b2C3");
        desenvolvedor.setPapel("DESENVOLVEDOR");

        if (!pessoaServico.criar(desenvolvedor)) {
            std::cout << "Aviso: nao foi possivel criar a pessoa Desenvolvedor.\n";
        }

        Projeto projetoInicial;
        projetoInicial.setCodigo("PR001");
        projetoInicial.setNome("Projeto A");
        projetoInicial.setInicio("01/01/2026");
        projetoInicial.setTermino("31/01/2026");

        if (!projetoServico.criar(projetoInicial,
                                  "scrum@scrum.com",
                                  "admin@admin.com")) {
            std::cout << "Aviso: nao foi possivel criar o projeto inicial.\n";
        }

        PlanoSprint planoInicial;
        planoInicial.setCodigo("SP001");
        planoInicial.setObjetivo("Sprint inicial");
        planoInicial.setCapacidade(10);

        if (!planoSprintServico.criar(planoInicial,
                                      "PR001",
                                      "scrum@scrum.com")) {
            std::cout << "Aviso: nao foi possivel criar o plano de sprint inicial.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "Erro de validacao ao criar dados iniciais: " << e.what() << "\n";
        return 1;

    } catch (const std::exception& e) {
        std::cout << "Erro ao criar dados iniciais: " << e.what() << "\n";
        return 1;

    } catch (...) {
        std::cout << "Erro desconhecido ao criar dados iniciais.\n";
        return 1;
    }

    ControladoraApresentacaoPessoa controladoraPessoa;
    ControladoraApresentacaoProjeto controladoraProjeto;
    ControladoraApresentacaoPlanoSprint controladoraPlanoSprint;
    ControladoraApresentacaoHistoria controladoraHistoria;

    ControladoraApresentacao controladoraApresentacao;

    controladoraPessoa.setServicoPessoa(&pessoaServico);
    controladoraProjeto.setServicoProjeto(&projetoServico);
    controladoraPlanoSprint.setServicoPlanoSprint(&planoSprintServico);
    controladoraHistoria.setServicoHistoria(&historiaServico);

    controladoraApresentacao.setServicoAuth(&authServico);
    controladoraApresentacao.setServicoPessoa(&pessoaServico);

    controladoraApresentacao.setControladoraPessoa(&controladoraPessoa);
    controladoraApresentacao.setControladoraProjeto(&controladoraProjeto);
    controladoraApresentacao.setControladoraPlanoSprint(&controladoraPlanoSprint);
    controladoraApresentacao.setControladoraHistoria(&controladoraHistoria);

    controladoraApresentacao.executar();

    return 0;
}