#include "apresentacao/apresentacao.hpp"
#include "../include/servico/stubs.hpp"

int main() {
    StubAuthServico stubAuth;
    StubPessoaServico stubPessoa;
    StubProjetoServico stubProjeto;
    StubPlanoSprintServico stubPlanoSprint;
    StubHistoriaServico stubHistoria;

    ControladoraApresentacaoPessoa ctrlPessoa;
    ControladoraApresentacaoProjeto ctrlProjeto;
    ControladoraApresentacaoPlanoSprint ctrlPlanoSprint;
    ControladoraApresentacaoHistoria ctrlHistoria;
    ControladoraApresentacao app;

    ctrlPessoa.setServicoPessoa(&stubPessoa);
    ctrlProjeto.setServicoProjeto(&stubProjeto);
    ctrlPlanoSprint.setServicoPlanoSprint(&stubPlanoSprint);
    ctrlHistoria.setServicoHistoria(&stubHistoria);

    app.setServicoAuth(&stubAuth);
    app.setControladoraPessoa(&ctrlPessoa);
    app.setControladoraProjeto(&ctrlProjeto);
    app.setControladoraPlanoSprint(&ctrlPlanoSprint);
    app.setControladoraHistoria(&ctrlHistoria);

    app.executar();

    return 0;
}