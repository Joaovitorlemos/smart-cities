# SmartCity — Sistema Inteligente de Monitoramento Urbano

> Sistema de gerenciamento urbano em C que monitora sensores espalhados pela cidade, detecta ocorrências críticas automaticamente e despacha equipes técnicas para atendimento.

---

## Stack

- **Linguagem:** C (C99)
- **Estruturas de dados:** Listas encadeadas dinâmicas e listas de listas (Bairro → Sensor → Ocorrência)
- **Persistência:** Arquivos `.txt` com leitura e escrita automática
- **Compilação:** GCC via Makefile ou linha de comando

---

## Resultado em destaque

O sistema gerencia uma hierarquia de três níveis de listas encadeadas — **bairros contendo sensores, sensores contendo ocorrências** — totalmente alocada de forma dinâmica, sem nenhum vetor global fixo. Quando um sensor vai offline ou uma ocorrência crítica (severidade 4) é registrada, chamados técnicos são gerados **automaticamente** e despachados para a equipe compatível com a especialidade do sensor. Todo o estado é persistido em arquivos `.txt` e restaurado automaticamente na próxima execução. O sistema suporta ainda um **modo de simulação** que lê comandos de um arquivo de entrada e registra cada operação — com sucesso ou falha — em um log de execução.

---

## Funcionalidades implementadas

- Cadastro, busca, listagem e remoção de bairros com validação de integridade
- Cadastro de sensores vinculados a bairros existentes, com alteração de status
- Registro de ocorrências vinculadas a sensores, com 4 níveis de severidade
- Geração automática de chamados para ocorrências críticas e sensores offline
- Associação de equipes técnicas a chamados compatíveis com sua especialidade
- Finalização de atendimentos com contabilização por equipe
- 6 relatórios urbanos gerados em `relatorio_final.txt`
- Modo de simulação via `simulacao.txt` com log completo em `log_execucao.txt`
- Persistência automática de todos os dados ao encerrar o sistema
- Liberação completa de toda memória alocada dinamicamente

---

## Como rodar localmente

### Pré-requisitos

- GCC instalado (`gcc --version`)
- Sistema operacional Linux, macOS ou Windows com MinGW

### Compilação

```bash
gcc -o smartcity main.c -Wall
```

### Execução

```bash
./smartcity
```

O sistema carrega automaticamente os arquivos de dados na inicialização. Se os arquivos não existirem, o sistema inicia com listas vazias.

### Arquivos de entrada esperados (pasta raiz)

| Arquivo | Conteúdo |
|---|---|
| `bairros.txt` | `codigo nome` |
| `sensores.txt` | `codigo tipo status codigo_bairro` |
| `ocorrencias.txt` | `codigo severidade status codigo_sensor codigo_bairro descricao` |
| `equipes.txt` | `codigo nome especialidade` |
| `chamados.txt` | `codigo codigo_ocorrencia codigo_equipe prioridade status` |
| `simulacao.txt` | Comandos linha a linha (opcional) |

### Exemplo de arquivo de simulação

```
cadastrarBairro 10 Contorno
cadastrarSensor 200 2 1 10
cadastrarEquipe 10 Equipe_Oeste Iluminacao_Publica
registrarOcorrencia 9001 4 1 200 2 Nivel_agua_critico
gerarChamado 8001 9001 4 1
associarEquipe 8001 10
finalizarChamado 8001
relatorioGeral
FIM
```

Para rodar a simulação, selecione a opção **13) Modo simulação** no menu interativo.

---

## Estrutura de dados

```
listaBairros
└── Bairro
    ├── codigo, nome
    └── listaSensores
        └── Sensor
            ├── codigo, tipo, status
            └── listaOcorrencias
                └── Ocorrencia
                    └── codigo, severidade, descricao, status

listaEquipes
└── Equipe
    ├── codigo, nome, especialidade, total_atendimentos
    └── listaChamados
        └── Chamado
            └── codigo, prioridade, status, *Ocorrencia
```

---

## Arquivos de saída

| Arquivo | Conteúdo |
|---|---|
| `relatorio_final.txt` | 6 relatórios: bairros com mais ocorrências, sensores offline, ocorrências críticas abertas, equipe líder em atendimentos, sensores por bairro, ocorrências por severidade |
| `log_execucao.txt` | Histórico completo da simulação com horário lógico, comando executado e resultado (SUCESSO/FALHA) |

---

## Projeto acadêmico

Projeto Final da disciplina **Estrutura de Dados I** — UTFPR Campus Ponta Grossa.  
Desenvolvido em linguagem C com uso obrigatório de alocação dinâmica, listas encadeadas e relacionamentos via ponteiros.
