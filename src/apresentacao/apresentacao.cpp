#include "apresentacao.hpp"

#include <limits>
#include <stdexcept>
#include <vector>

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

    std::cout << "\n========== CRIAR PESSOA ==========\n";

    std::string email = lerLinha("Email: ");
    std::string nome  = lerLinha("Nome: ");
    std::string senha = lerLinha("Senha: ");
    std::string papel = lerLinha("Papel [DESENVOLVEDOR, MESTRE SCRUM, PROPRIETARIO DE PRODUTO]: ");

    try {
        Pessoa pessoa;

        pessoa.setEmail(email);
        pessoa.setNome(nome);
        pessoa.setSenha(senha);
        pessoa.setPapel(papel);

        bool sucesso = servicoPessoa->criar(pessoa);

        if (sucesso) {
            std::cout << "\nPessoa criada com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel criar a pessoa.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao criar pessoa.\n";
    }
}

void ControladoraApresentacaoPessoa::lerPessoa() {
    if (!verificarServico(servicoPessoa)) {
        return;
    }

    std::cout << "\n========== LER PESSOA ==========\n";

    std::string email = lerLinha("Email da pessoa: ");

    try {
        Pessoa pessoa;

        bool sucesso = servicoPessoa->ler(email, &pessoa);

        if (!sucesso) {
            std::cout << "\nPessoa nao encontrada.\n";
            return;
        }

        std::cout << "\nDados da pessoa:\n";
        std::cout << "Email: " << pessoa.getEmail() << "\n";
        std::cout << "Nome : " << pessoa.getNome() << "\n";
        std::cout << "Senha: " << pessoa.getSenha() << "\n";
        std::cout << "Papel: " << pessoa.getPapel() << "\n";

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao ler pessoa.\n";
    }
}

void ControladoraApresentacaoPessoa::atualizarPessoa() {
    if (!verificarServico(servicoPessoa)) {
        return;
    }

    std::cout << "\n========== ATUALIZAR PESSOA ==========\n";

    std::string email = lerLinha("Email da pessoa que sera atualizada: ");

    try {
        Pessoa pessoaAtual;

        bool encontrada = servicoPessoa->ler(email, &pessoaAtual);

        if (!encontrada) {
            std::cout << "\nPessoa nao encontrada.\n";
            return;
        }

        std::cout << "\nDados atuais:\n";
        std::cout << "Email: " << pessoaAtual.getEmail() << "\n";
        std::cout << "Nome : " << pessoaAtual.getNome() << "\n";
        std::cout << "Senha: " << pessoaAtual.getSenha() << "\n";
        std::cout << "Papel: " << pessoaAtual.getPapel() << "\n";

        std::cout << "\nInforme os novos dados.\n";
        std::cout << "Observacao: o email nao sera alterado, pois e chave primaria.\n";

        std::string novoNome  = lerLinha("Novo nome: ");
        std::string novaSenha = lerLinha("Nova senha: ");
        std::string novoPapel = lerLinha("Novo papel [DESENVOLVEDOR, MESTRE SCRUM, PROPRIETARIO DE PRODUTO]: ");

        Pessoa pessoaAtualizada;

        pessoaAtualizada.setEmail(email);
        pessoaAtualizada.setNome(novoNome);
        pessoaAtualizada.setSenha(novaSenha);
        pessoaAtualizada.setPapel(novoPapel);

        bool sucesso = servicoPessoa->atualizar(pessoaAtualizada);

        if (sucesso) {
            std::cout << "\nPessoa atualizada com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel atualizar a pessoa.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao atualizar pessoa.\n";
    }
}

void ControladoraApresentacaoPessoa::excluirPessoa() {
    if (!verificarServico(servicoPessoa)) {
        return;
    }

    std::cout << "\n========== EXCLUIR PESSOA ==========\n";

    std::string email = lerLinha("Email da pessoa que sera excluida: ");

    try {
        Pessoa pessoa;

        bool encontrada = servicoPessoa->ler(email, &pessoa);

        if (!encontrada) {
            std::cout << "\nPessoa nao encontrada.\n";
            return;
        }

        std::cout << "\nPessoa encontrada:\n";
        std::cout << "Email: " << pessoa.getEmail() << "\n";
        std::cout << "Nome : " << pessoa.getNome() << "\n";
        std::cout << "Papel: " << pessoa.getPapel() << "\n";

        std::string confirmacao = lerLinha("\nConfirmar exclusao? [S/N]: ");

        if (confirmacao != "S" && confirmacao != "s") {
            std::cout << "\nExclusao cancelada.\n";
            return;
        }

        bool sucesso = servicoPessoa->excluir(email);

        if (sucesso) {
            std::cout << "\nPessoa excluida com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel excluir a pessoa.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao excluir pessoa.\n";
    }
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

    std::cout << "\n========== CRIAR PROJETO ==========\n";

    std::string codigo = lerLinha("Codigo do projeto: ");
    std::string nome = lerLinha("Nome do projeto: ");
    std::string inicio = lerLinha("Data de inicio [DD/MM/AAAA]: ");
    std::string termino = lerLinha("Data de termino [DD/MM/AAAA]: ");
    std::string emailMestreScrum = lerLinha("Email do Mestre Scrum associado: ");

    try {
        Projeto projeto;

        projeto.setCodigo(codigo);
        projeto.setNome(nome);
        projeto.setInicio(inicio);
        projeto.setTermino(termino);

        bool sucesso = servicoProjeto->criar(projeto, emailMestreScrum);

        if (sucesso) {
            std::cout << "\nProjeto criado com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel criar o projeto.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao criar projeto.\n";
    }
}

void ControladoraApresentacaoProjeto::lerProjeto() {
    if (!verificarServico(servicoProjeto)) {
        return;
    }

    std::cout << "\n========== LER PROJETO ==========\n";

    std::string codigo = lerLinha("Codigo do projeto: ");

    try {
        Projeto projeto;

        bool sucesso = servicoProjeto->ler(codigo, &projeto);

        if (!sucesso) {
            std::cout << "\nProjeto nao encontrado.\n";
            return;
        }

        std::cout << "\nDados do projeto:\n";
        std::cout << "Codigo : " << projeto.getCodigo() << "\n";
        std::cout << "Nome   : " << projeto.getNome() << "\n";
        std::cout << "Inicio : " << projeto.getInicio() << "\n";
        std::cout << "Termino: " << projeto.getTermino() << "\n";

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao ler projeto.\n";
    }
}

void ControladoraApresentacaoProjeto::atualizarProjeto() {
    if (!verificarServico(servicoProjeto)) {
        return;
    }

    std::cout << "\n========== ATUALIZAR PROJETO ==========\n";

    std::string codigo = lerLinha("Codigo do projeto que sera atualizado: ");

    try {
        Projeto projetoAtual;

        bool encontrado = servicoProjeto->ler(codigo, &projetoAtual);

        if (!encontrado) {
            std::cout << "\nProjeto nao encontrado.\n";
            return;
        }

        std::cout << "\nDados atuais:\n";
        std::cout << "Codigo : " << projetoAtual.getCodigo() << "\n";
        std::cout << "Nome   : " << projetoAtual.getNome() << "\n";
        std::cout << "Inicio : " << projetoAtual.getInicio() << "\n";
        std::cout << "Termino: " << projetoAtual.getTermino() << "\n";

        std::cout << "\nInforme os novos dados.\n";
        std::cout << "Observacao: o codigo nao sera alterado, pois e chave primaria.\n";

        std::string novoNome = lerLinha("Novo nome: ");
        std::string novoInicio = lerLinha("Nova data de inicio [DD/MM/AAAA]: ");
        std::string novoTermino = lerLinha("Nova data de termino [DD/MM/AAAA]: ");

        Projeto projetoAtualizado;

        projetoAtualizado.setCodigo(codigo);
        projetoAtualizado.setNome(novoNome);
        projetoAtualizado.setInicio(novoInicio);
        projetoAtualizado.setTermino(novoTermino);

        bool sucesso = servicoProjeto->atualizar(projetoAtualizado);

        if (sucesso) {
            std::cout << "\nProjeto atualizado com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel atualizar o projeto.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao atualizar projeto.\n";
    }
}

void ControladoraApresentacaoProjeto::excluirProjeto() {
    if (!verificarServico(servicoProjeto)) {
        return;
    }

    std::cout << "\n========== EXCLUIR PROJETO ==========\n";

    std::string codigo = lerLinha("Codigo do projeto que sera excluido: ");

    try {
        Projeto projeto;

        bool encontrado = servicoProjeto->ler(codigo, &projeto);

        if (!encontrado) {
            std::cout << "\nProjeto nao encontrado.\n";
            return;
        }

        std::cout << "\nProjeto encontrado:\n";
        std::cout << "Codigo : " << projeto.getCodigo() << "\n";
        std::cout << "Nome   : " << projeto.getNome() << "\n";
        std::cout << "Inicio : " << projeto.getInicio() << "\n";
        std::cout << "Termino: " << projeto.getTermino() << "\n";

        std::string confirmacao = lerLinha("\nConfirmar exclusao? [S/N]: ");

        if (confirmacao != "S" && confirmacao != "s") {
            std::cout << "\nExclusao cancelada.\n";
            return;
        }

        bool sucesso = servicoProjeto->excluir(codigo);

        if (sucesso) {
            std::cout << "\nProjeto excluido com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel excluir o projeto.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao excluir projeto.\n";
    }
}

void ControladoraApresentacaoProjeto::listarProjetosPorPessoa() {
    if (!verificarServico(servicoProjeto)) {
        return;
    }

    std::cout << "\n========== LISTAR PROJETOS POR PESSOA ==========\n";

    std::string emailPessoa = lerLinha("Email da pessoa: ");

    try {
        std::vector<std::string> codigosProjetos;

        bool sucesso = servicoProjeto->listarProjetosAssociadosPessoa(
            emailPessoa,
            &codigosProjetos
        );

        if (!sucesso) {
            std::cout << "\nNao foi possivel listar os projetos associados a pessoa.\n";
            return;
        }

        if (codigosProjetos.empty()) {
            std::cout << "\nNenhum projeto associado a esta pessoa.\n";
            return;
        }

        std::cout << "\nProjetos associados:\n";

        for (std::size_t i = 0; i < codigosProjetos.size(); ++i) {
            std::cout << "- " << codigosProjetos[i] << "\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao listar projetos por pessoa.\n";
    }
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

    std::cout << "\n========== CRIAR PLANO DE SPRINT ==========\n";

    std::string codigo = lerLinha("Codigo do plano de sprint: ");
    std::string objetivo = lerLinha("Objetivo: ");
    std::string capacidade = lerLinha("Capacidade [1 a 365]: ");
    std::string codigoProjeto = lerLinha("Codigo do projeto associado: ");

    try {
        PlanoSprint planoSprint;

        planoSprint.setCodigo(codigo);
        planoSprint.setObjetivo(objetivo);
        planoSprint.setCapacidade(std::stoi(capacidade));

        bool sucesso = servicoPlanoSprint->criar(planoSprint, codigoProjeto);

        if (sucesso) {
            std::cout << "\nPlano de sprint criado com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel criar o plano de sprint.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao criar plano de sprint.\n";
    }
}

void ControladoraApresentacaoPlanoSprint::lerPlanoSprint() {
    if (!verificarServico(servicoPlanoSprint)) {
        return;
    }

    std::cout << "\n========== LER PLANO DE SPRINT ==========\n";

    std::string codigo = lerLinha("Codigo do plano de sprint: ");

    try {
        PlanoSprint planoSprint;

        bool sucesso = servicoPlanoSprint->ler(codigo, &planoSprint);

        if (!sucesso) {
            std::cout << "\nPlano de sprint nao encontrado.\n";
            return;
        }

        std::cout << "\nDados do plano de sprint:\n";
        std::cout << "Codigo    : " << planoSprint.getCodigo() << "\n";
        std::cout << "Objetivo  : " << planoSprint.getObjetivo() << "\n";
        std::cout << "Capacidade: " << planoSprint.getCapacidade() << "\n";

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao ler plano de sprint.\n";
    }
}

void ControladoraApresentacaoPlanoSprint::atualizarPlanoSprint() {
    if (!verificarServico(servicoPlanoSprint)) {
        return;
    }

    std::cout << "\n========== ATUALIZAR PLANO DE SPRINT ==========\n";

    std::string codigo = lerLinha("Codigo do plano de sprint que sera atualizado: ");

    try {
        PlanoSprint planoAtual;

        bool encontrado = servicoPlanoSprint->ler(codigo, &planoAtual);

        if (!encontrado) {
            std::cout << "\nPlano de sprint nao encontrado.\n";
            return;
        }

        std::cout << "\nDados atuais:\n";
        std::cout << "Codigo    : " << planoAtual.getCodigo() << "\n";
        std::cout << "Objetivo  : " << planoAtual.getObjetivo() << "\n";
        std::cout << "Capacidade: " << planoAtual.getCapacidade() << "\n";

        std::cout << "\nInforme os novos dados.\n";
        std::cout << "Observacao: o codigo nao sera alterado, pois e chave primaria.\n";

        std::string novoObjetivo = lerLinha("Novo objetivo: ");
        std::string novaCapacidade = lerLinha("Nova capacidade [1 a 365]: ");

        PlanoSprint planoAtualizado;

        planoAtualizado.setCodigo(codigo);
        planoAtualizado.setObjetivo(novoObjetivo);
        planoAtualizado.setCapacidade(std::stoi(novaCapacidade));

        bool sucesso = servicoPlanoSprint->atualizar(planoAtualizado);

        if (sucesso) {
            std::cout << "\nPlano de sprint atualizado com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel atualizar o plano de sprint.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao atualizar plano de sprint.\n";
    }
}

void ControladoraApresentacaoPlanoSprint::excluirPlanoSprint() {
    if (!verificarServico(servicoPlanoSprint)) {
        return;
    }

    std::cout << "\n========== EXCLUIR PLANO DE SPRINT ==========\n";

    std::string codigo = lerLinha("Codigo do plano de sprint que sera excluido: ");

    try {
        PlanoSprint planoSprint;

        bool encontrado = servicoPlanoSprint->ler(codigo, &planoSprint);

        if (!encontrado) {
            std::cout << "\nPlano de sprint nao encontrado.\n";
            return;
        }

        std::cout << "\nPlano de sprint encontrado:\n";
        std::cout << "Codigo    : " << planoSprint.getCodigo() << "\n";
        std::cout << "Objetivo  : " << planoSprint.getObjetivo() << "\n";
        std::cout << "Capacidade: " << planoSprint.getCapacidade() << "\n";

        std::string confirmacao = lerLinha("\nConfirmar exclusao? [S/N]: ");

        if (confirmacao != "S" && confirmacao != "s") {
            std::cout << "\nExclusao cancelada.\n";
            return;
        }

        bool sucesso = servicoPlanoSprint->excluir(codigo);

        if (sucesso) {
            std::cout << "\nPlano de sprint excluido com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel excluir o plano de sprint.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao excluir plano de sprint.\n";
    }
}

void ControladoraApresentacaoPlanoSprint::listarPlanosPorProjeto() {
    if (!verificarServico(servicoPlanoSprint)) {
        return;
    }

    std::cout << "\n========== LISTAR PLANOS POR PROJETO ==========\n";

    std::string codigoProjeto = lerLinha("Codigo do projeto: ");

    try {
        std::vector<std::string> codigosPlanos;

        bool sucesso = servicoPlanoSprint->listarPlanosSprintAssociadosProjeto(
            codigoProjeto,
            &codigosPlanos
        );

        if (!sucesso) {
            std::cout << "\nNao foi possivel listar os planos associados ao projeto.\n";
            return;
        }

        if (codigosPlanos.empty()) {
            std::cout << "\nNenhum plano de sprint associado a este projeto.\n";
            return;
        }

        std::cout << "\nPlanos de sprint associados:\n";

        for (std::size_t i = 0; i < codigosPlanos.size(); ++i) {
            std::cout << "- " << codigosPlanos[i] << "\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao listar planos por projeto.\n";
    }
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

    std::cout << "\n========== CRIAR HISTORIA ==========\n";

    std::string codigo = lerLinha("Codigo da historia: ");
    std::string titulo = lerLinha("Titulo: ");
    std::string papel = lerLinha("Papel [DESENVOLVEDOR, MESTRE SCRUM, PROPRIETARIO DE PRODUTO]: ");
    std::string acao = lerLinha("Acao [eu quero...]: ");
    std::string valor = lerLinha("Valor [para...]: ");
    std::string estimativaTexto = lerLinha("Estimativa [1 a 365]: ");
    std::string prioridade = lerLinha("Prioridade [ALTA, MEDIA, BAIXA]: ");
    std::string codigoProjeto = lerLinha("Codigo do projeto associado: ");

    try {
        int estimativa = std::stoi(estimativaTexto);

        Historia historia;

        historia.setCodigo(codigo);
        historia.setTitulo(titulo);
        historia.setPapel(papel);
        historia.setAcao(acao);
        historia.setValor(valor);
        historia.setEstimativa(estimativa);
        historia.setPrioridade(prioridade);

        /*
         * Regra do trabalho:
         * Ao criar historia, o estado inicial deve ser A FAZER.
         * Portanto, a apresentacao ja envia esse estado inicial.
         */
        historia.setEstado("A FAZER");

        bool sucesso = servicoHistoria->criar(historia, codigoProjeto);

        if (sucesso) {
            std::cout << "\nHistoria criada com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel criar a historia.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::out_of_range& e) {
        std::cout << "\nErro de validacao: estimativa fora do intervalo aceito.\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao criar historia.\n";
    }
}

void ControladoraApresentacaoHistoria::lerHistoria() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n========== LER HISTORIA ==========\n";

    std::string codigo = lerLinha("Codigo da historia: ");

    try {
        Historia historia;

        bool sucesso = servicoHistoria->ler(codigo, &historia);

        if (!sucesso) {
            std::cout << "\nHistoria nao encontrada.\n";
            return;
        }

        std::cout << "\nDados da historia:\n";
        std::cout << "Codigo    : " << historia.getCodigo() << "\n";
        std::cout << "Titulo    : " << historia.getTitulo() << "\n";
        std::cout << "Papel     : " << historia.getPapel() << "\n";
        std::cout << "Acao      : " << historia.getAcao() << "\n";
        std::cout << "Valor     : " << historia.getValor() << "\n";
        std::cout << "Estimativa: " << historia.getEstimativa() << "\n";
        std::cout << "Prioridade: " << historia.getPrioridade() << "\n";
        std::cout << "Estado    : " << historia.getEstado() << "\n";

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao ler historia.\n";
    }
}

void ControladoraApresentacaoHistoria::atualizarHistoria() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n========== ATUALIZAR HISTORIA ==========\n";

    std::string codigo = lerLinha("Codigo da historia que sera atualizada: ");

    try {
        Historia historiaAtual;

        bool encontrada = servicoHistoria->ler(codigo, &historiaAtual);

        if (!encontrada) {
            std::cout << "\nHistoria nao encontrada.\n";
            return;
        }

        std::cout << "\nDados atuais:\n";
        std::cout << "Codigo    : " << historiaAtual.getCodigo() << "\n";
        std::cout << "Titulo    : " << historiaAtual.getTitulo() << "\n";
        std::cout << "Papel     : " << historiaAtual.getPapel() << "\n";
        std::cout << "Acao      : " << historiaAtual.getAcao() << "\n";
        std::cout << "Valor     : " << historiaAtual.getValor() << "\n";
        std::cout << "Estimativa: " << historiaAtual.getEstimativa() << "\n";
        std::cout << "Prioridade: " << historiaAtual.getPrioridade() << "\n";
        std::cout << "Estado    : " << historiaAtual.getEstado() << "\n";

        std::cout << "\nInforme os novos dados.\n";
        std::cout << "Observacao: o codigo nao sera alterado, pois e chave primaria.\n";

        std::string novoTitulo = lerLinha("Novo titulo: ");
        std::string novoPapel = lerLinha("Novo papel [DESENVOLVEDOR, MESTRE SCRUM, PROPRIETARIO DE PRODUTO]: ");
        std::string novaAcao = lerLinha("Nova acao [eu quero...]: ");
        std::string novoValor = lerLinha("Novo valor [para...]: ");
        std::string novaEstimativaTexto = lerLinha("Nova estimativa [1 a 365]: ");
        std::string novaPrioridade = lerLinha("Nova prioridade [ALTA, MEDIA, BAIXA]: ");

        int novaEstimativa = std::stoi(novaEstimativaTexto);

        Historia historiaAtualizada;

        historiaAtualizada.setCodigo(codigo);
        historiaAtualizada.setTitulo(novoTitulo);
        historiaAtualizada.setPapel(novoPapel);
        historiaAtualizada.setAcao(novaAcao);
        historiaAtualizada.setValor(novoValor);
        historiaAtualizada.setEstimativa(novaEstimativa);
        historiaAtualizada.setPrioridade(novaPrioridade);

        /*
         * O estado nao e alterado aqui.
         * Para isso existe uma funcionalidade especifica: alterarEstadoHistoria().
         */
        historiaAtualizada.setEstado(historiaAtual.getEstado());

        bool sucesso = servicoHistoria->atualizar(historiaAtualizada);

        if (sucesso) {
            std::cout << "\nHistoria atualizada com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel atualizar a historia.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::out_of_range& e) {
        std::cout << "\nErro de validacao: estimativa fora do intervalo aceito.\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao atualizar historia.\n";
    }
}

void ControladoraApresentacaoHistoria::excluirHistoria() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n========== EXCLUIR HISTORIA ==========\n";

    std::string codigo = lerLinha("Codigo da historia que sera excluida: ");

    try {
        Historia historia;

        bool encontrada = servicoHistoria->ler(codigo, &historia);

        if (!encontrada) {
            std::cout << "\nHistoria nao encontrada.\n";
            return;
        }

        std::cout << "\nHistoria encontrada:\n";
        std::cout << "Codigo    : " << historia.getCodigo() << "\n";
        std::cout << "Titulo    : " << historia.getTitulo() << "\n";
        std::cout << "Papel     : " << historia.getPapel() << "\n";
        std::cout << "Estimativa: " << historia.getEstimativa() << "\n";
        std::cout << "Prioridade: " << historia.getPrioridade() << "\n";
        std::cout << "Estado    : " << historia.getEstado() << "\n";

        std::string confirmacao = lerLinha("\nConfirmar exclusao? [S/N]: ");

        if (confirmacao != "S" && confirmacao != "s") {
            std::cout << "\nExclusao cancelada.\n";
            return;
        }

        bool sucesso = servicoHistoria->excluir(codigo);

        if (sucesso) {
            std::cout << "\nHistoria excluida com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel excluir a historia.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao excluir historia.\n";
    }
}

void ControladoraApresentacaoHistoria::associarPessoa() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n========== ASSOCIAR PESSOA A HISTORIA ==========\n";

    std::string codigoHistoria = lerLinha("Codigo da historia: ");
    std::string emailPessoa = lerLinha("Email da pessoa: ");

    try {
        bool sucesso = servicoHistoria->associarPessoa(codigoHistoria, emailPessoa);

        if (sucesso) {
            std::cout << "\nPessoa associada a historia com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel associar a pessoa a historia.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao associar pessoa.\n";
    }
}

void ControladoraApresentacaoHistoria::removerAssociacaoPessoa() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n========== REMOVER ASSOCIACAO DE PESSOA ==========\n";

    std::string codigoHistoria = lerLinha("Codigo da historia: ");
    std::string emailPessoa = lerLinha("Email da pessoa: ");

    try {
        bool sucesso = servicoHistoria->removerAssociacaoPessoa(codigoHistoria, emailPessoa);

        if (sucesso) {
            std::cout << "\nAssociacao removida com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel remover a associacao.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao remover associacao.\n";
    }
}

void ControladoraApresentacaoHistoria::listarHistoriasPorProjeto() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n========== LISTAR HISTORIAS POR PROJETO ==========\n";

    std::string codigoProjeto = lerLinha("Codigo do projeto: ");

    try {
        std::vector<std::string> codigosHistorias;

        bool sucesso = servicoHistoria->listarHistoriasAssociadasProjeto(
            codigoProjeto,
            &codigosHistorias
        );

        if (!sucesso) {
            std::cout << "\nNao foi possivel listar as historias associadas ao projeto.\n";
            return;
        }

        if (codigosHistorias.empty()) {
            std::cout << "\nNenhuma historia associada a este projeto.\n";
            return;
        }

        std::cout << "\nHistorias associadas ao projeto:\n";

        for (std::size_t i = 0; i < codigosHistorias.size(); ++i) {
            std::cout << "- " << codigosHistorias[i] << "\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao listar historias por projeto.\n";
    }
}

void ControladoraApresentacaoHistoria::listarHistoriasPorPlanoSprint() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n========== LISTAR HISTORIAS POR PLANO DE SPRINT ==========\n";

    std::string codigoPlanoSprint = lerLinha("Codigo do plano de sprint: ");

    try {
        std::vector<std::string> codigosHistorias;

        bool sucesso = servicoHistoria->listarHistoriasAssociadasPlanoSprint(
            codigoPlanoSprint,
            &codigosHistorias
        );

        if (!sucesso) {
            std::cout << "\nNao foi possivel listar as historias associadas ao plano de sprint.\n";
            return;
        }

        if (codigosHistorias.empty()) {
            std::cout << "\nNenhuma historia associada a este plano de sprint.\n";
            return;
        }

        std::cout << "\nHistorias associadas ao plano de sprint:\n";

        for (std::size_t i = 0; i < codigosHistorias.size(); ++i) {
            std::cout << "- " << codigosHistorias[i] << "\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao listar historias por plano de sprint.\n";
    }
}

void ControladoraApresentacaoHistoria::listarHistoriasPorPessoa() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n========== LISTAR HISTORIAS POR PESSOA ==========\n";

    std::string emailPessoa = lerLinha("Email da pessoa: ");

    try {
        std::vector<std::string> codigosHistorias;

        bool sucesso = servicoHistoria->listarHistoriasAssociadasPessoa(
            emailPessoa,
            &codigosHistorias
        );

        if (!sucesso) {
            std::cout << "\nNao foi possivel listar as historias associadas a pessoa.\n";
            return;
        }

        if (codigosHistorias.empty()) {
            std::cout << "\nNenhuma historia associada a esta pessoa.\n";
            return;
        }

        std::cout << "\nHistorias associadas a pessoa:\n";

        for (std::size_t i = 0; i < codigosHistorias.size(); ++i) {
            std::cout << "- " << codigosHistorias[i] << "\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao listar historias por pessoa.\n";
    }
}

void ControladoraApresentacaoHistoria::moverHistoriaParaPlanoSprint() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n========== MOVER HISTORIA PARA PLANO DE SPRINT ==========\n";

    std::string codigoHistoria = lerLinha("Codigo da historia: ");
    std::string codigoProjeto = lerLinha("Codigo do projeto de origem: ");
    std::string codigoPlanoSprint = lerLinha("Codigo do plano de sprint de destino: ");

    try {
        bool sucesso = servicoHistoria->moverHistoriaParaPlanoSprint(
            codigoHistoria,
            codigoProjeto,
            codigoPlanoSprint
        );

        if (sucesso) {
            std::cout << "\nHistoria movida para o plano de sprint com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel mover a historia para o plano de sprint.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao mover historia.\n";
    }
}

void ControladoraApresentacaoHistoria::alterarEstadoHistoria() {
    if (!verificarServico(servicoHistoria)) {
        return;
    }

    std::cout << "\n========== ALTERAR ESTADO DA HISTORIA ==========\n";

    std::string codigoHistoria = lerLinha("Codigo da historia: ");
    std::string novoEstado = lerLinha("Novo estado [A FAZER, FAZENDO, FEITO]: ");

    try {
        bool sucesso = servicoHistoria->alterarEstado(codigoHistoria, novoEstado);

        if (sucesso) {
            std::cout << "\nEstado da historia alterado com sucesso.\n";
        } else {
            std::cout << "\nNao foi possivel alterar o estado da historia.\n";
        }

    } catch (const std::invalid_argument& e) {
        std::cout << "\nErro de validacao: " << e.what() << "\n";

    } catch (const std::exception& e) {
        std::cout << "\nErro: " << e.what() << "\n";

    } catch (...) {
        std::cout << "\nErro desconhecido ao alterar estado da historia.\n";
    }
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