#include "apresentacao.hpp"

#include <limits>
#include <stdexcept>

namespace {

/**
 * @brief Le uma linha de texto do console.
 *
 * @param mensagem Mensagem exibida antes da leitura.
 * @return Texto informado pelo usuario.
 */
std::string lerLinha(const std::string& mensagem) {
    std::string entrada;

    std::cout << mensagem;
    std::getline(std::cin, entrada);

    return entrada;
}

/**
 * @brief Le uma opcao inteira do console.
 *
 * @param mensagem Mensagem exibida antes da leitura.
 * @return Opcao informada pelo usuario.
 */
int lerOpcao(const std::string& mensagem) {
    int opcao;

    std::cout << mensagem;
    std::cin >> opcao;

    if (std::cin.fail()) {
        std::cin.clear();
        opcao = -1;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return opcao;
}

/**
 * @brief Pausa simples para facilitar visualizacao no console.
 */
void pausar() {
    std::cout << "\nPressione ENTER para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * @brief Verifica se um ponteiro de servico foi configurado.
 *
 * @param ponteiro Ponteiro que sera verificado.
 * @return true se o ponteiro foi configurado; false caso contrario.
 */
bool verificarServico(const void* ponteiro) {
    if (ponteiro == nullptr) {
        std::cout << "\nServico nao configurado.\n";
        return false;
    }

    return true;
}

} // namespace

// -----------------------------------------------------------------------------
// ControladoraApresentacaoPessoa
// -----------------------------------------------------------------------------

ControladoraApresentacaoPessoa::ControladoraApresentacaoPessoa() {
    this->servicoPessoa = nullptr;
}

void ControladoraApresentacaoPessoa::setServicoPessoa(IPessoaServico* servicoPessoa) {
    this->servicoPessoa = servicoPessoa;
}

void ControladoraApresentacaoPessoa::executar() {
    int opcao;

    do {
        std::cout << "\n========== MENU PESSOA ==========\n";
        std::cout << "1 - Criar pessoa\n";
        std::cout << "2 - Ler pessoa\n";
        std::cout << "3 - Atualizar pessoa\n";
        std::cout << "4 - Excluir pessoa\n";
        std::cout << "0 - Voltar\n";

        opcao = lerOpcao("Opcao: ");

        switch (opcao) {
            case 1:
                criarPessoa();
                break;

            case 2:
                lerPessoa();
                break;

            case 3:
                atualizarPessoa();
                break;

            case 4:
                excluirPessoa();
                break;

            case 0:
                std::cout << "\nVoltando ao menu principal...\n";
                break;

            default:
                std::cout << "\nOpcao invalida.\n";
                break;
        }

    } while (opcao != 0);
}

void ControladoraApresentacaoPessoa::criarPessoa() {
    if (!verificarServico(servicoPessoa)) {
        return;
    }

    std::cout << "\n[Pessoa] Criar pessoa ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoPessoa::lerPessoa() {
    if (!verificarServico(servicoPessoa)) {
        return;
    }

    std::cout << "\n[Pessoa] Ler pessoa ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoPessoa::atualizarPessoa() {
    if (!verificarServico(servicoPessoa)) {
        return;
    }

    std::cout << "\n[Pessoa] Atualizar pessoa ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoPessoa::excluirPessoa() {
    if (!verificarServico(servicoPessoa)) {
        return;
    }

    std::cout << "\n[Pessoa] Excluir pessoa ainda sera implementado em detalhe.\n";
}

// -----------------------------------------------------------------------------
// ControladoraApresentacaoProjeto
// -----------------------------------------------------------------------------

ControladoraApresentacaoProjeto::ControladoraApresentacaoProjeto() {
    this->servicoProjeto = nullptr;
}

void ControladoraApresentacaoProjeto::setServicoProjeto(IProjetoServico* servicoProjeto) {
    this->servicoProjeto = servicoProjeto;
}

void ControladoraApresentacaoProjeto::executar() {
    int opcao;

    do {
        std::cout << "\n========== MENU PROJETO ==========\n";
        std::cout << "1 - Criar projeto\n";
        std::cout << "2 - Ler projeto\n";
        std::cout << "3 - Atualizar projeto\n";
        std::cout << "4 - Excluir projeto\n";
        std::cout << "5 - Listar projetos por pessoa\n";
        std::cout << "0 - Voltar\n";

        opcao = lerOpcao("Opcao: ");

        switch (opcao) {
            case 1:
                criarProjeto();
                break;

            case 2:
                lerProjeto();
                break;

            case 3:
                atualizarProjeto();
                break;

            case 4:
                excluirProjeto();
                break;

            case 5:
                listarProjetosPorPessoa();
                break;

            case 0:
                std::cout << "\nVoltando ao menu principal...\n";
                break;

            default:
                std::cout << "\nOpcao invalida.\n";
                break;
        }

    } while (opcao != 0);
}

void ControladoraApresentacaoProjeto::criarProjeto() {
    if (!verificarServico(servicoProjeto)) {
        return;
    }

    std::cout << "\n[Projeto] Criar projeto ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoProjeto::lerProjeto() {
    if (!verificarServico(servicoProjeto)) {
        return;
    }

    std::cout << "\n[Projeto] Ler projeto ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoProjeto::atualizarProjeto() {
    if (!verificarServico(servicoProjeto)) {
        return;
    }

    std::cout << "\n[Projeto] Atualizar projeto ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoProjeto::excluirProjeto() {
    if (!verificarServico(servicoProjeto)) {
        return;
    }

    std::cout << "\n[Projeto] Excluir projeto ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoProjeto::listarProjetosPorPessoa() {
    if (!verificarServico(servicoProjeto)) {
        return;
    }

    std::cout << "\n[Projeto] Listar projetos por pessoa ainda sera implementado em detalhe.\n";
}

// -----------------------------------------------------------------------------
// ControladoraApresentacaoPlanoSprint
// -----------------------------------------------------------------------------

ControladoraApresentacaoPlanoSprint::ControladoraApresentacaoPlanoSprint() {
    this->servicoPlanoSprint = nullptr;
}

void ControladoraApresentacaoPlanoSprint::setServicoPlanoSprint(IPlanoSprintServico* servicoPlanoSprint) {
    this->servicoPlanoSprint = servicoPlanoSprint;
}

void ControladoraApresentacaoPlanoSprint::executar() {
    int opcao;

    do {
        std::cout << "\n========== MENU PLANO DE SPRINT ==========\n";
        std::cout << "1 - Criar plano de sprint\n";
        std::cout << "2 - Ler plano de sprint\n";
        std::cout << "3 - Atualizar plano de sprint\n";
        std::cout << "4 - Excluir plano de sprint\n";
        std::cout << "5 - Listar planos por projeto\n";
        std::cout << "0 - Voltar\n";

        opcao = lerOpcao("Opcao: ");

        switch (opcao) {
            case 1:
                criarPlanoSprint();
                break;

            case 2:
                lerPlanoSprint();
                break;

            case 3:
                atualizarPlanoSprint();
                break;

            case 4:
                excluirPlanoSprint();
                break;

            case 5:
                listarPlanosPorProjeto();
                break;

            case 0:
                std::cout << "\nVoltando ao menu principal...\n";
                break;

            default:
                std::cout << "\nOpcao invalida.\n";
                break;
        }

    } while (opcao != 0);
}

void ControladoraApresentacaoPlanoSprint::criarPlanoSprint() {
    if (!verificarServico(servicoPlanoSprint)) {
        return;
    }

    std::cout << "\n[Plano de Sprint] Criar plano de sprint ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoPlanoSprint::lerPlanoSprint() {
    if (!verificarServico(servicoPlanoSprint)) {
        return;
    }

    std::cout << "\n[Plano de Sprint] Ler plano de sprint ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoPlanoSprint::atualizarPlanoSprint() {
    if (!verificarServico(servicoPlanoSprint)) {
        return;
    }

    std::cout << "\n[Plano de Sprint] Atualizar plano de sprint ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoPlanoSprint::excluirPlanoSprint() {
    if (!verificarServico(servicoPlanoSprint)) {
        return;
    }

    std::cout << "\n[Plano de Sprint] Excluir plano de sprint ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoPlanoSprint::listarPlanosPorProjeto() {
    if (!verificarServico(servicoPlanoSprint)) {
        return;
    }

    std::cout << "\n[Plano de Sprint] Listar planos por projeto ainda sera implementado em detalhe.\n";
}

// -----------------------------------------------------------------------------
// ControladoraApresentacaoHistoria
// -----------------------------------------------------------------------------

ControladoraApresentacaoHistoria::ControladoraApresentacaoHistoria() {
    this->servicoHistoria = nullptr;
}

void ControladoraApresentacaoHistoria::setServicoHistoria(IHistoriaServico* servicoHistoria) {
    this->servicoHistoria = servicoHistoria;
}

void ControladoraApresentacaoHistoria::executar() {
    int opcao;

    do {
        std::cout << "\n========== MENU HISTORIA ==========\n";
        std::cout << "1  - Criar historia\n";
        std::cout << "2  - Ler historia\n";
        std::cout << "3  - Atualizar historia\n";
        std::cout << "4  - Excluir historia\n";
        std::cout << "5  - Associar pessoa a historia\n";
        std::cout << "6  - Remover associacao de pessoa\n";
        std::cout << "7  - Listar historias por projeto\n";
        std::cout << "8  - Listar historias por plano de sprint\n";
        std::cout << "9  - Listar historias por pessoa\n";
        std::cout << "10 - Mover historia para plano de sprint\n";
        std::cout << "11 - Alterar estado da historia\n";
        std::cout << "0  - Voltar\n";

        opcao = lerOpcao("Opcao: ");

        switch (opcao) {
            case 1:
                criarHistoria();
                break;

            case 2:
                lerHistoria();
                break;

            case 3:
                atualizarHistoria();
                break;

            case 4:
                excluirHistoria();
                break;

            case 5:
                associarPessoa();
                break;

            case 6:
                removerAssociacaoPessoa();
                break;

            case 7:
                listarHistoriasPorProjeto();
                break;

            case 8:
                listarHistoriasPorPlanoSprint();
                break;

            case 9:
                listarHistoriasPorPessoa();
                break;

            case 10:
                moverHistoriaParaPlanoSprint();
                break;

            case 11:
                alterarEstadoHistoria();
                break;

            case 0:
                std::cout << "\nVoltando ao menu principal...\n";
                break;

            default:
                std::cout << "\nOpcao invalida.\n";
                break;
        }

    } while (opcao != 0);
}

void ControladoraApresentacaoHistoria::criarHistoria() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n[Historia] Criar historia ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoHistoria::lerHistoria() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n[Historia] Ler historia ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoHistoria::atualizarHistoria() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n[Historia] Atualizar historia ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoHistoria::excluirHistoria() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n[Historia] Excluir historia ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoHistoria::associarPessoa() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n[Historia] Associar pessoa ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoHistoria::removerAssociacaoPessoa() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n[Historia] Remover associacao de pessoa ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoHistoria::listarHistoriasPorProjeto() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n[Historia] Listar historias por projeto ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoHistoria::listarHistoriasPorPlanoSprint() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n[Historia] Listar historias por plano de sprint ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoHistoria::listarHistoriasPorPessoa() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n[Historia] Listar historias por pessoa ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoHistoria::moverHistoriaParaPlanoSprint() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n[Historia] Mover historia para plano de sprint ainda sera implementado em detalhe.\n";
}

void ControladoraApresentacaoHistoria::alterarEstadoHistoria() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n[Historia] Alterar estado da historia ainda sera implementado em detalhe.\n";
}

// -----------------------------------------------------------------------------
// ControladoraApresentacao
// -----------------------------------------------------------------------------

ControladoraApresentacao::ControladoraApresentacao() {
    this->servicoAuth = nullptr;

    this->controladoraPessoa = nullptr;
    this->controladoraProjeto = nullptr;
    this->controladoraPlanoSprint = nullptr;
    this->controladoraHistoria = nullptr;
}

void ControladoraApresentacao::setServicoAuth(IAuthServico* servicoAuth) {
    this->servicoAuth = servicoAuth;
}

void ControladoraApresentacao::setControladoraPessoa(ControladoraApresentacaoPessoa* controladoraPessoa) {
    this->controladoraPessoa = controladoraPessoa;
}

void ControladoraApresentacao::setControladoraProjeto(ControladoraApresentacaoProjeto* controladoraProjeto) {
    this->controladoraProjeto = controladoraProjeto;
}

void ControladoraApresentacao::setControladoraPlanoSprint(ControladoraApresentacaoPlanoSprint* controladoraPlanoSprint) {
    this->controladoraPlanoSprint = controladoraPlanoSprint;
}

void ControladoraApresentacao::setControladoraHistoria(ControladoraApresentacaoHistoria* controladoraHistoria) {
    this->controladoraHistoria = controladoraHistoria;
}

void ControladoraApresentacao::executar() {
    std::cout << "=====================================\n";
    std::cout << "    GERENCIADOR SCRUM - TP1\n";
    std::cout << "=====================================\n";

    if (!autenticar()) {
        std::cout << "\nNao foi possivel autenticar o usuario.\n";
        return;
    }

    mostrarMenuPrincipal();
}

bool ControladoraApresentacao::autenticar() {
    if (!verificarServico(servicoAuth)) {
        return false;
    }

    std::cout << "\n========== AUTENTICACAO ==========\n";

    std::string email = lerLinha("Email: ");
    std::string senha = lerLinha("Senha: ");

    try {
        bool sucesso = servicoAuth->autenticar(email, senha, &pessoaAutenticada);

        if (sucesso) {
            std::cout << "\nUsuario autenticado com sucesso.\n";
            return true;
        }

        std::cout << "\nEmail ou senha invalidos.\n";
        return false;

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";
        return false;

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";
        return false;

    } catch (...) {
        std::cout << "\nErro desconhecido durante autenticacao.\n";
        return false;
    }
}

void ControladoraApresentacao::mostrarMenuPrincipal() {
    int opcao;

    do {
        std::cout << "\n========== MENU PRINCIPAL ==========\n";
        std::cout << "Usuario: " << pessoaAutenticada.getEmail() << "\n";
        std::cout << "Papel: " << pessoaAutenticada.getPapel() << "\n\n";

        std::cout << "1 - Pessoas\n";
        std::cout << "2 - Projetos\n";
        std::cout << "3 - Planos de Sprint\n";
        std::cout << "4 - Historias de Usuario\n";
        std::cout << "0 - Sair\n";

        opcao = lerOpcao("Opcao: ");

        switch (opcao) {
            case 1:
                if (controladoraPessoa != nullptr) {
                    controladoraPessoa->executar();
                } else {
                    std::cout << "\nControladora de pessoa nao configurada.\n";
                }
                break;

            case 2:
                if (controladoraProjeto != nullptr) {
                    controladoraProjeto->executar();
                } else {
                    std::cout << "\nControladora de projeto nao configurada.\n";
                }
                break;

            case 3:
                if (controladoraPlanoSprint != nullptr) {
                    controladoraPlanoSprint->executar();
                } else {
                    std::cout << "\nControladora de plano de sprint nao configurada.\n";
                }
                break;

            case 4:
                if (controladoraHistoria != nullptr) {
                    controladoraHistoria->executar();
                } else {
                    std::cout << "\nControladora de historia nao configurada.\n";
                }
                break;

            case 0:
                std::cout << "\nEncerrando sistema...\n";
                break;

            default:
                std::cout << "\nOpcao invalida.\n";
                break;
        }

    } while (opcao != 0);
}