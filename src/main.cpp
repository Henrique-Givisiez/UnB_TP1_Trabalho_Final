#include <iostream>

#include "../include/servico/servicos.hpp"
#include "../include/servico/stubs.hpp"

#include "apresentacao/apresentacao.hpp"

int main() {
    BancoDadosMemoria banco;

    PessoaServico pessoaServico(&banco);
    AuthServico authServico(&banco);

    StubProjetoServico projetoServico;
    StubPlanoSprintServico planoSprintServico;
    StubHistoriaServico historiaServico;

    /*
     * Conta inicial para permitir a primeira autenticação.
     *
     * O sistema não possui papel ADMIN no domínio Papel.
     * Por isso, usamos PROPRIETARIO DE PRODUTO como conta inicial.
     */
    Pessoa pessoaInicial;

    try {
        pessoaInicial.setEmail("admin@admin.com");
        pessoaInicial.setNome("Admin");
        pessoaInicial.setSenha("A1b2C3");
        pessoaInicial.setPapel("PROPRIETARIO DE PRODUTO");

        pessoaServico.criar(pessoaInicial);
    } catch (const std::invalid_argument& e) {
        std::cout << "Erro ao criar pessoa inicial: " << e.what() << "\n";
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

    controladoraApresentacao.setControladoraPessoa(&controladoraPessoa);
    controladoraApresentacao.setControladoraProjeto(&controladoraProjeto);
    controladoraApresentacao.setControladoraPlanoSprint(&controladoraPlanoSprint);
    controladoraApresentacao.setControladoraHistoria(&controladoraHistoria);

    controladoraApresentacao.executar();

    return 0;
}