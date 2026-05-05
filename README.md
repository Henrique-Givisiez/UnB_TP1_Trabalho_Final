# Sistema de Gerenciamento de Projetos Scrum

Trabalho Prático 1 — Técnicas de Programação 1  

---

## Descrição

Sistema de software para suporte a projetos cujos requisitos funcionais são especificados por histórias de usuário, com gestão baseada no framework Scrum. Usuários assumem papéis (Proprietário de Produto, Mestre Scrum ou Desenvolvedor) e interagem com projetos, planos de sprint e histórias de usuário.

---

## Estrutura do Projeto

```
.
├── include/
│   ├── dominios/          # Classes de domínio (validação de dados)
│   │   ├── codigo.hpp
│   │   ├── data.hpp
│   │   ├── email.hpp
│   │   ├── estado.hpp
│   │   ├── nome.hpp
│   │   ├── papel.hpp
│   │   ├── prioridade.hpp
│   │   ├── senha.hpp
│   │   ├── tempo.hpp
│   │   └── texto.hpp
│   ├── entidades/         # Classes entidade (agregam domínios)
│   │   ├── pessoa.hpp
│   │   ├── projeto.hpp
│   │   ├── plano_sprint.hpp
│   │   └── historia.hpp
│   ├── interfaces/        # Interfaces entre camadas (classes abstratas)
│   │   └── interfaces.hpp
│   └── servico/           # Camada de serviço
│       ├── stubs.hpp
│       └── servicos.hpp
│
├── src/
│   ├── dominios/          # Implementações dos domínios
│   ├── entidades/         # Implementações das entidades
│   ├── servico/           # Implementações dos serviços
│   └── apresentacao/      # Camada de apresentação (interface com usuário)
│       ├── apresentacao.hpp
│       └── apresentacao.cpp
│
├── tests/                 # Testes unitários por domínio e entidade
│   ├── TestCodigo.cpp
│   ├── TestData.cpp
│   ├── TestEmail.cpp
│   ├── TestNome.cpp
│   ├── TestSenha.cpp
│   ├── TestTempo.cpp
│   ├── TestTexto.cpp
│   └── TestPessoa.cpp
│
├── docs/
│   ├── arquitetura.pdf    # Diagrama UML da arquitetura
│   └── doxygen/           # Documentação HTML gerada pelo Doxygen
│
├── main.cpp
├── Makefile
├── Doxyfile
└── identificacao.txt
```

---

## Arquitetura

O sistema adota o estilo de arquitetura em camadas:

```
┌─────────────────────┐
│     APRESENTAÇÃO    │  Interface com o usuário + validação de entrada
└────────┬────────────┘
         │ depende de interfaces
┌────────▼────────────┐
│       SERVIÇO       │  Lógica de negócio + armazenamento
└────────┬────────────┘
         │
┌────────▼──────────────────────────────────┐
│  PESSOAS │ PROJETOS │ SPRINTS │ HISTÓRIAS  │  Módulos de dados
└───────────────────────────────────────────┘
```

- A camada de **apresentação** depende apenas de interfaces declaradas como classes abstratas puras.
- A camada de **serviço** implementa essas interfaces e gerencia o armazenamento em memória.
- Os módulos de dados são compostos por classes **domínio** e **entidade**.

---

## Requisitos Funcionais

O sistema provê 25 serviços organizados em torno de 4 entidades:

| Entidade          | Operações                                              |
|-------------------|--------------------------------------------------------|
| Pessoa            | Criar, Ler, Atualizar, Excluir                         |
| Projeto           | Criar, Ler, Atualizar, Excluir                         |
| Plano de Sprint   | Criar, Ler, Atualizar, Excluir                         |
| História de Usuário | Criar, Ler, Atualizar, Excluir, Mover, Alterar Estado |

Além de operações de associação e listagem entre entidades.  
Cada serviço é restrito a papéis específicos (ver especificação do trabalho).

---

## Domínios Implementados

| Domínio    | Tipo do valor | Regra principal                                              |
|------------|---------------|--------------------------------------------------------------|
| Codigo     | `string`      | 2 letras maiúsculas + 3 dígitos (ex: `AB012`)               |
| Data       | `string`      | `DIA/MES/ANO`, com validação de bissexto, ano 2000–2999      |
| Email      | `string`      | `local@dominio`, regras de ponto/hífen, sem maiúsculas       |
| Estado     | `enum`        | `A FAZER`, `FAZENDO`, `FEITO`                                |
| Nome       | `string`      | Até 10 chars, sem espaço no início/fim                       |
| Papel      | `enum`        | `DESENVOLVEDOR`, `MESTRE SCRUM`, `PROPRIETARIO DE PRODUTO`   |
| Prioridade | `enum`        | `BAIXA`, `MEDIA`, `ALTA`                                     |
| Senha      | `string`      | 6 chars, letras e dígitos alternados, mín. 1 de cada tipo    |
| Tempo      | `int`         | Valor entre 1 e 365                                          |
| Texto      | `string`      | Até 40 chars, regras de vírgula, ponto e espaço              |

---

## Como Compilar e Executar

### Pré-requisitos

- `g++` com suporte a C++17
- `make`

### Compilar

```bash
make
```

### Executar

```bash
./programa
```

### Recompilar do zero

```bash
make rebuild
```

### Limpar arquivos gerados

```bash
make clean
```

---

## Como Gerar a Documentação

### Pré-requisito

- [Doxygen](https://www.doxygen.nl/) instalado

### Gerar

```bash
doxygen Doxyfile
```

A documentação HTML será gerada em `docs/doxygen/`. Abra `docs/doxygen/html/index.html` no navegador.

---

## Testes

Os testes unitários ficam em `tests/` e são compilados junto com o projeto pelo Makefile. Cada arquivo de teste expõe uma função `testarX()` que é chamada no `main.cpp`.

Para rodar todos os testes:

```bash
make
./programa
```

---

## Observações

- Acentuação e letra ç não são considerados nas validações (conforme especificação).
- Chaves primárias (ex: email de Pessoa, código de Projeto) não podem ser editadas após cadastro.
- A soma das estimativas das histórias em um plano de sprint não pode exceder sua capacidade.
- A soma das capacidades dos planos de sprint de um projeto não pode exceder o número de dias entre as datas de início e término do projeto.
- Uma história de usuário pertence **ou** a um Projeto **ou** a um Plano de Sprint, nunca aos dois simultaneamente.
