#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==========================================
// STRUCTS
// ==========================================
typedef struct ocorrencia{ //NÓ OCORRÊNCIAS
    int codigo;
    int severidade;
    char descricao[100];
    int status;
    struct ocorrencia *prox;
}Ocorrencia;

typedef struct listaOcorrencias{ //NÓ CABEÇA OCORRÊNCIAS
    Ocorrencia *inicio;
    Ocorrencia *final;
}listaOcorrencias;

typedef struct sensor{ //NÓ SENSOR
    int codigo;
    int tipo;
    int status;
    listaOcorrencias *listaOcorrencias;
    struct sensor *prox;
}Sensor;

typedef struct _listasensores{ //NÓ CABEÇA SENSOR
    Sensor *inicio;
    Sensor *final;
}listaSensores;


//NÓ BAIRRO
typedef struct bairro{ //NÓ
    int codigo;
    char nome[50];
    listaSensores *listaSensores; //vai apontar para uma estrutura S->begin e S->end
    struct bairro *prox;
}Bairro;

//NÓ CABEÇA BAIRRO
typedef struct _listaBairros{
    Bairro *inicio;
    Bairro *final;
}listaBairros;

typedef struct chamado{ //NÓ CHAMADO
 int codigo;
 int prioridade;
 int status;
 Ocorrencia *Ocorrencia;
 struct chamado *prox;
}Chamado;

typedef struct listaChamados{ //NÓ CABEÇA CHAMADO
    Chamado *inicio;
    Chamado *final;
}listaChamados;

typedef struct equipe{ //NÓ EQUIPE
    int codigo;
    char nome[50];
    char especialidade[30];
    int total_atendimentos;
    struct listaChamados *listaChamados;
    struct equipe *prox;
}Equipe;

typedef struct listaEquipes{
    Equipe *inicio;
    Equipe *final;
}listaEquipes;

// ==========================================
// MÁQUINA DE ESTADOS E LEITURA DE ARQUIVOS
// ==========================================
// (Funções de ler txt vão aqui)
void salvarBairros(listaBairros *B);
void carregarBairros(listaBairros *B);

void salvarSensores(listaBairros *B);
void carregarSensores(listaBairros *B);

void salvarOcorrencias(listaBairros *B);
void carregarOcorrencias(listaBairros *B);

void salvarEquipes(listaEquipes *E);
void carregarEquipes(listaEquipes *E);

void salvarChamados(listaChamados *C, listaEquipes *E);
void carregarChamados(listaChamados *C, listaBairros *B, listaEquipes *E);

void gerarRelatorioFinal(listaBairros *B, listaEquipes *E);

// ==========================================
// GERENCIAMENTO DE BAIRROS
// ==========================================
listaBairros *criarListaBairros();
Bairro *criarBairro();
Bairro *buscarBairro (int codigo, listaBairros *B);

void cadastrarBairro (int codigo, char *nome, listaBairros *B);
void listarBairros (listaBairros *B);
void removerBairro (listaBairros *B, int codigo);
// ==========================================
// GERENCIAMENTO DE SENSORES
// ==========================================
listaSensores *criarListaSensor ();
Sensor *criarSensor ();
Sensor *buscarSensor (int codigo, listaSensores *S);

void cadastrarSensor (int codigoSensor, int tipo, int status, int codigoBairro, listaBairros *B);
void alterarStatusSensor (int codigoSensor, int codigoBairro, int novoStatus, listaBairros *B, listaChamados *chamadosPendentes);
void listarSensoresBairro (int codigoBairro, listaBairros *B);
// ==========================================
// REGISTRO DE OCORRENCIAS
// ==========================================
listaOcorrencias *criarListaOcorrencias();
Ocorrencia *criarOcorrencia();
Ocorrencia *buscarOcorrencia(int codigo, listaOcorrencias *O);
Ocorrencia *buscarOcorrenciaGlobal(int codigoOcorrencia, listaBairros *B);

void registrarOcorrencia (int codigo, int severidade, int status, int codigoSensor, int codigoBairro, char *descricao, listaBairros *B, listaChamados *chamadosPendentes);
void listarOcorrencias(listaBairros *B); //não tem parâmetros pq é uma varredura global. listar TODAS as ocorrências

// ==========================================
// GERENCIAMENTO DE EQUIPES E CHAMADOS
// ==========================================
listaEquipes *criarListaEquipes();
Equipe *criarEquipe();
Equipe *buscarEquipe (int codigo, listaEquipes *E);

void cadastrarEquipe (int codigo, char *nome, char *especialidade, listaEquipes *E);
void associarEquipe(int codigoChamado, int codigoEquipe, listaChamados *C, listaEquipes *E);

Chamado *criarChamado(); 
listaChamados *criarListaChamados();
Chamado *buscarChamado(int codigo, listaChamados *C);

void gerarChamado(int codigo, int codigoOcorrencia, int prioridade, int status, listaChamados *C, listaBairros *B);
void finalizarChamado(int codigoChamado, listaEquipes *E);

// ==========================================
// FUNÇÃO PRINCIPAL
// ==========================================
int main()
{
    int opcao; //leitura das opções
    int codBairro = 1000, codSensor = 2000, codOcorrencia = 3000, codChamado = 4000, codEquipe = 5000;
    int codBuscaBairro, codRemoverBairro;
    int tipoSensor, statusSensor, codBairroSensor;
    char nomeBairro[50];
    
    listaBairros *B = criarListaBairros();
    listaSensores *S = criarListaSensor();
    listaOcorrencias *O = criarListaOcorrencias();
    listaEquipes *E = criarListaEquipes();
    listaChamados *C = criarListaChamados();

    carregarBairros(B);
    carregarSensores(B);
    carregarOcorrencias(B);
    carregarEquipes(E);
    carregarChamados(C, B, E);


    
    salvarBairros(B);
    salvarSensores(B);
    salvarOcorrencias(B);
    salvarEquipes(E);
    salvarChamados(C, E);

        do
    {
        printf("==================\nGERENCIAMENTO DE BAIRROS\n==================\n");
        printf("01)Cadastrar bairro\n02)Buscar bairro\n03)Listar bairros cadastrados\n04)Remover bairro\n");
        printf("\n");

        printf("==================\nGERENCIAMENTO DE SENSORES\n==================\n");
        printf("05)Cadastrar sensor\n06)Alterar status de sensor\n07)Buscar sensor\n08)Listar sensor por bairro\n");
        printf("\n");

        printf("==================\nGERENCIAMENTO DE OCORRÊNCIAS\n==================\n");
        printf("09)Registrar ocorrência\n");
        printf("\n");

        printf("==================\nGERENCIAMENTO DE EQUIPES\n==================\n");
        printf("10)Cadastrar equipe\n11)Associar chamado a equipe\n12)Finalizar atendimento\n");
        printf("\n");

        printf("13)Modo simulação\n14)Relatório final\n15)Sair\n");
        printf("\n");

        printf("Opção selecionada: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:
            {
                printf("Informe o nome do bairro a ser cadastrado: ");
                scanf("%s", nomeBairro);

                printf("Código gerado para o bairro: %d\n", codBairro);

                cadastrarBairro(codBairro, nomeBairro, listaGlobalBairros);
                codBairro++;
            }break;
            case 2:
            {
                printf("Informe o código do bairro a ser buscado: ");
                scanf("%d", &codBuscaBairro);

                buscarBairro(codBuscaBairro, listaGlobalBairros);
            }break;
            case 3:
            {
                listarBairros(listaGlobalBairros);
            }break;
            case 4:
            {
                printf("Informe o código do bairro a ser removido: ");
                scanf("%d", &codRemoverBairro);

                removerBairro(listaGlobalBairros, codRemoverBairro);
            }break;
            case 5:
            {
                printf("Informe o tipo do sensor:\n01)Temperatura\n02)Enchente\n03)Fumaca\n04)Transito\n05)Iluminacao_Publica\nTipo do sensor: ");
                scanf("%d", &tipoSensor);

                printf("Informe o status do sensor:\n01)Ativo\n02)Manutenção\n03)Offline\nAtual status do sensor: ");
                scanf("%d", &statusSensor);

                printf("Digite o código do bairro correspondente: ");
                scanf("%d", &codBairroSensor);

                printf("Código gerado para o sensor: %d\n", codSensor);

                cadastrarSensor(codSensor, tipoSensor, statusSensor, codBairroSensor, listaGlobalBairros);
                codSensor++;
            }break;
            case 6:
            {
                int codSensorStatus, codBairroStatus, novoStatus;
                printf("Informe o código do sensor cujo status será alterado: ");
                scanf("%d", &codSensorStatus);

                printf("Informe o código do bairro cujo sensor pertence: ");
                scanf("%d", &codBairroStatus);

                printf("Informe o novo status do sensor: ");
                scanf("%d", &novoStatus);

                alterarStatusSensor(codSensorStatus, codBairroStatus, novoStatus, listaGlobalBairros, chamadosPendentes);
            }break;
            case 7:
            {
                int codBuscaSensor;

                printf("Informe o código do sensor a ser buscado: ");
                scanf("%d", &codBuscaSensor);

                buscaSensor(codBuscaSensor, listaGlobalBairros);
            }break;
            case 8:
            {
                int codBairroListaSensores;
                printf("Informe o código do bairro que tem os sensores: ");
                scanf("%d", &codBairroListaSensores);

                listarSensoresBairros(codBairroListaSensores, listaGlobalBairros);
            }break;
            case 9:
            {
                int codBairroAssociadoOcorrencia, severidadeOcorrencia, codSensorAssociadoOcorrencia;
                printf("Informe a severidade da ocorrência:\n01)Baixa\n02)Média\n03)Alta\n04)Crítica\nSeveridade da ocorrência: ");
                scanf("%d", &severidadeOcorrencia);

                printf("Informe o código do sensor associado: ");
                scanf("%d", &codSensorAssociadoOcorrencia);

                printf("Informe o código do bairro associado: ");
                scanf("%d", &codBairroAssociadoOcorrencia);

                registrarOcorrencia(codOcorrencia, severidadeOcorrencia, 1, codSensorAssociadoOcorrencia, codBairroAssociadoOcorrencia, descricaoOcorrencia, listaGlobalBairros, chamadosPendentes);
                codOcorrencia++;
            }break;
            case 10:
            {
                char nomeEquipe[50], especialidadeEquipe[50];

                printf("Informe o nome da equipe: ");
                scanf("%s", nomeEquipe);

                printf("Informe a especialidade da equipe: ");
                scanf("%s", especialidadeEquipe);

                printf("Equipe registrada com o código: %d\n", codEquipe);

                cadastrarEquipe(codEquipe, nomeEquipe, especialidadeEquipe, listaGlobalEquipes);
                codEquipe++;
            }break;
            case 11:
            {
                int codChamadoAssociar, codEquipeAssociar;

                printf("Informe o código do chamado: ");
                scanf("%d", &codChamadoAssociar);

                printf("Informe o código da equipe: ");
                scanf("%d", &codEquipeAssociar);

                associarEquipe(codChamadoAssociar, codEquipeAssociar, listaGlobalEquipes);

            }break;
            case 12:
            {
                int codChamadoFinalizado;

                printf("Informe o código do chamado: ");
                scanf("%d", codChamadoFinalizado);

                finalizarChamado(codChamadoFinalizado, listaGlobalEquipes);

            }break;
            case 13:
            {

            }break;
            case 14:
            {

            }break;
            case 15:
            {

            }break;
            default:
            {
                printf("Opção inválida! Digite novamente\n");
            }break;
            
        }

    }
    while (opcao != 15);

    return 0;
}

// ==========================================
// GERENCIAMENTO DE BAIRROS
// ==========================================
void salvarBairros(listaBairros *B) {
    if (B == NULL) return;

    FILE *arquivo = fopen("bairros.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }

    Bairro *navegador = B->inicio;
    char nomeTemporario[50];

    while (navegador != NULL) {
        // Copia o nome original para não alterá-lo na memória do programa
        strncpy(nomeTemporario, navegador->nome, sizeof(nomeTemporario) - 1);
        nomeTemporario[sizeof(nomeTemporario) - 1] = '\0';

        // Varre a string trocando espaços por underline
        for (int i = 0; nomeTemporario[i] != '\0'; i++) {
            if (nomeTemporario[i] == ' ') {
                nomeTemporario[i] = '_';
            }
        }

        // Salva no arquivo com o underline. Ex: "1 Jardim_Carvalho"
        fprintf(arquivo, "%d %s\n", navegador->codigo, nomeTemporario);
        navegador = navegador->prox;
    }

    fclose(arquivo);
    printf("Dados persistidos em 'bairros.txt' com sucesso!\n");
}

void carregarBairros(listaBairros *B) {
    FILE *arquivo = fopen("bairros.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo 'bairros.txt' não encontrado. Iniciando lista vazia.\n");
        return;
    }

    char linha[120]; 
    int codigo;
    char nome[50];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Como o nome não tem espaços no arquivo, podemos usar o %s simples no sscanf!
        if (sscanf(linha, "%d %49s", &codigo, nome) == 2) {
            
            // Remove quebras de linha residuais
            nome[strcspn(nome, "\r\n")] = '\0';

            // Varre a string trocando os underlines de volta por espaços
            for (int i = 0; nome[i] != '\0'; i++) {
                if (nome[i] == '_') {
                    nome[i] = ' ';
                }
            }
            
            // Cadastra na memória já com o formato correto: "Vila Nova"
            cadastrarBairro(codigo, nome, B);
        }
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso de 'bairros.txt'.\n");
}

listaBairros *criarListaBairros()
{
    listaBairros *B = (listaBairros *) calloc(1, sizeof(listaBairros));

    return B;
}

Bairro *criarBairro()
{
    Bairro *b = (Bairro *) calloc(1, sizeof(Bairro));

    return b;
}

Bairro *buscarBairro (int codigo, listaBairros *B)
{
    Bairro *navegador = B->inicio;

    while (navegador != NULL && navegador->codigo != codigo)
    {
        navegador = navegador->prox;
    }

    return navegador;  
}

void cadastrarBairro (int codigo, char *nome, listaBairros *B) //equivalente a inserção. inserção no final
{
    //verificar se já não existe um bairro com o código digitado
    Bairro *verificacao = buscarBairro (codigo, B);

    if (verificacao != NULL)
    {
        printf("Bairro já existente!\n");
        return;
    }
    else
    {
        //alocação do espaço + registro das informações
        Bairro *b = criarBairro();
        b->codigo = codigo;
        strncpy(b->nome, nome, sizeof(b->nome) - 1);
        b->nome[sizeof(b->nome) - 1] = '\0';

        // criar a lista de sensores associada a esse bairro no ato do cadastro do bairro
        b->listaSensores = criarListaSensor();

        //ONDE de fato alocar
        if (B->inicio == NULL && B->final == NULL)
        {
            B->inicio = b;
            B->final = b;
        }
        else
        {
            B->final->prox = b;
            B->final = b;
        }
    }

    verificacao = NULL; //limpeza da memória
}

void listarBairros (listaBairros *B)
{
    Bairro *navegador = B->inicio;

    if (B->inicio != NULL && B->final != NULL)
    {
        while (navegador != NULL)
        {
            printf("Nome do bairro: %s\nCódigo cadastrado: %d\n", navegador->nome, navegador->codigo);
            navegador = navegador->prox;
        }
    }
    else
        printf("Não há bairros cadastrados!\n");
    
    navegador = NULL;
}

void removerBairro (listaBairros *B, int codigo)
{
    //percorrem a lista
    Bairro *navegador = B->inicio;
    Bairro *aux = NULL;

    //procuram o bairro a ser removido
    if (B->inicio != NULL && B->final != NULL)
    {
        while (navegador != NULL && navegador->codigo != codigo)
        {
            aux = navegador;
            navegador = navegador->prox;

        }
    }

    //análise do endereço de memória encontrado (para onde o navegador aponta)
    if (navegador == NULL)
    {
        printf("Erro: bairro não encontrado.\n");
        return;
    }
    if (navegador->listaSensores != NULL)
    {
        printf("Erro: não é possível remover bairro com sensores cadastrados.\n");
        return;
    }
    //CASO 01: É o único elemento da lista
    if (B->inicio == B->final)
    {
        B->inicio = NULL;
        B->final = NULL;
    }
    //CASO 02: primeiro elemento da lista
    else if (navegador == B->inicio)
    {
        B->inicio = navegador->prox;
    }
    //CASO 03: ultimo elemento da lista
    else if (navegador == B->final)
    {
        aux->prox = NULL;
        B->final = aux;
    }
    else
    {
        aux->prox = navegador->prox;
    }

    free(navegador);
    navegador = NULL;
    aux = NULL;
}

// ==========================================
// GERENCIAMENTO DE SENSORES
// ==========================================
void salvarSensores(listaBairros *B) {
    if (B == NULL || B->inicio == NULL) return;

    FILE *arquivo = fopen("sensores.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo 'sensores.txt' para escrita!\n");
        return;
    }

    Bairro *bairroNavegador = B->inicio;

    // Percorre cada bairro na memória
    while (bairroNavegador != NULL) {
        // Se o bairro tiver uma lista de sensores válida e não vazia
        if (bairroNavegador->listaSensores != NULL && bairroNavegador->listaSensores->inicio != NULL) {
            Sensor *sensorNavegador = bairroNavegador->listaSensores->inicio;

            // Percorre todos os sensores deste bairro e salva no arquivo
            while (sensorNavegador != NULL) {
                // Formato exigido: codigo tipo status codigo_bairro
                fprintf(arquivo, "%d %d %d %d\n", 
                        sensorNavegador->codigo, 
                        sensorNavegador->tipo, 
                        sensorNavegador->status, 
                        bairroNavegador->codigo);
                
                sensorNavegador = sensorNavegador->prox;
            }
        }
        bairroNavegador = bairroNavegador->prox;
    }

    fclose(arquivo);
    printf("Dados dos sensores persistidos em 'sensores.txt' com sucesso!\n");
}

void carregarSensores(listaBairros *B) {
    FILE *arquivo = fopen("sensores.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo 'sensores.txt' não encontrado. Iniciando sem sensores mapeados.\n");
        return;
    }

    char linha[120];
    int codigoSensor, tipo, status, codigoBairro;

    // Lê linha por linha do arquivo de sensores
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Tenta extrair os 4 inteiros da linha
        if (sscanf(linha, "%d %d %d %d", &codigoSensor, &tipo, &status, &codigoBairro) == 4) {
            // Usa a sua função de cadastrar para alocar e vincular ao bairro correto
            cadastrarSensor(codigoSensor, tipo, status, codigoBairro, B);
        }
    }

    fclose(arquivo);
    printf("Dados dos sensores carregados com sucesso de 'sensores.txt'.\n");
}

listaSensores *criarListaSensor ()
{
    listaSensores *S = (listaSensores *) calloc(1, sizeof(listaSensores));

    return S;
}

Sensor *criarSensor ()
{
    Sensor *s = (Sensor *) calloc(1, sizeof(Sensor));

    return s;
}

Sensor *buscarSensor (int codigo, listaSensores *S)
{
    //trava de segurança: bairro existe, mas não tem sensores associados a ele
    if (S->inicio == NULL && S->final == NULL)
        return NULL;
    
    Sensor *navegador = S->inicio;

    while (navegador != NULL && navegador->codigo != codigo)
    {
        navegador = navegador->prox;
    }

    return navegador; 
}

void cadastrarSensor (int codigoSensor, int tipo, int status, int codigoBairro, listaBairros *B)
{
    //procura o bairro associado
    Bairro *bairroAssociado = buscarBairro(codigoBairro, B);
    if (bairroAssociado == NULL) 
    {
        printf("ERRO: Bairro %d não existe!\n", codigoBairro);
        return;
    }

    //verificar se já não existe um sensor com o código digitado
    Sensor *verificacao = buscarSensor (codigoSensor, bairroAssociado->listaSensores);
    if (verificacao != NULL)
    {
        printf("ERRO: sensor já existente!\n");
        return;
    }
    else
    {
        //alocação do espaço + registro das informações
        Sensor *s = criarSensor();
        s->codigo = codigoSensor;
        s->tipo = tipo;
        s->status = status;
        s->listaOcorrencias = criarListaOcorrencias();

        //criação do link entre bairros e sensores através da inserção
        //CASO 01: primeiro sensor do bairro
        if (bairroAssociado->listaSensores->inicio == NULL && bairroAssociado->listaSensores->final == NULL)
        {
            bairroAssociado->listaSensores->inicio = s;
            bairroAssociado->listaSensores->final = s;
        }
        else
        {
            bairroAssociado->listaSensores->final->prox = s;
            bairroAssociado->listaSensores->final = s;
        }

    }

    verificacao = NULL;
    bairroAssociado = NULL;
}

void alterarStatusSensor (int codigoSensor, int codigoBairro, int novoStatus, listaBairros *B, listaChamados *chamadosPendentes)
{
    //procurar o sensor dentro da lista associada ao bairro
    Bairro *bairroAssociado = buscarBairro(codigoBairro, B);

    if (bairroAssociado == NULL) 
    {
        printf("ERRO: Bairro %d não existe!\n", codigoBairro);
        return;
    }
    
    Sensor *sensorBuscado = buscarSensor(codigoSensor, bairroAssociado->listaSensores); //retorna o nó
    if (sensorBuscado == NULL)
    {
        printf("ERRO: sensor não cadastrado!\n");
        return;
    }

    sensorBuscado->status = novoStatus;

    if (novoStatus == 3) // Sensor offline
        {
            // 1. criação de ocorrencia para colocar em chamado->ocorrencia = o;
            Ocorrencia *ocorrenciaManutencao = (Ocorrencia *) calloc(1, sizeof(Ocorrencia));
            ocorrenciaManutencao->codigo = codigoSensor * 100; // Gera um código derivado do sensor
            strcpy(ocorrenciaManutencao->descricao, "Manutencao"); // A palavra-chave da equipe!
            ocorrenciaManutencao->status = 1;

            // 2. Criamos um ID automático para o chamado
            static int idChamadoSensor = 9000; 
            
            // 3. Chamamos a sua fábrica normal, sem mexer nela!
            gerarChamado(idChamadoSensor, (codigoSensor * 100), 1, 1, chamadosPendentes, B);
            
            printf("ALERTA: Sensor %d offline! Chamado de Manutenção %d gerado com sucesso.\n", codigoSensor, idChamadoSensor);
            
            idChamadoSensor++;
        }

    bairroAssociado = NULL;
    sensorBuscado = NULL;
}

void listarSensoresBairro (int codigoBairro, listaBairros *B)
{
    Bairro *bairroAssociado = buscarBairro(codigoBairro, B);
    if (bairroAssociado == NULL)
    {
        printf("ERRO: bairro não existe!\n");
        return;
    }

    Sensor *navegador = bairroAssociado->listaSensores->inicio;

    while (navegador != NULL)
    {
        printf("Codigo do sensor: %d\n", navegador->codigo);

        switch (navegador->tipo)
        {
            case 1:
            {
                printf("Tipo do sensor: 1 - temperatura\n");
            }break;
            case 2:
            {
                printf("Tipo do sensor: 2 - enchente\n");
            }break;
            case 3:
            {
                printf("Tipo do sensor: 3 - fumaça\n");
            }break;
            case 4:
            {
                printf("Tipo do sensor: 4 - trânsito\n");
            }break;
            case 5:
            {
                printf("Tipo do sensor: 5 - iluminação pública\n");
            }break;
        }

        switch (navegador->status)
        {
            case 1:
                printf("Status do sensor: ativo\n");
                break;
            case 2:
                printf("Status do sensor: manutenção\n");
                break;
            case 3:
                printf("Status do sensor: offline\n");
                break;
        }

        navegador = navegador->prox;
    }

    navegador = NULL;
    bairroAssociado = NULL;
}

// ==========================================
// REGISTRO DE OCORRENCIAS
// ==========================================
void salvarOcorrencias(listaBairros *B) {
    if (B == NULL || B->inicio == NULL) return;

    FILE *arquivo = fopen("ocorrencias.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo 'ocorrencias.txt' para escrita!\n");
        return;
    }

    Bairro *bNav = B->inicio;
    while (bNav != NULL) {
        if (bNav->listaSensores != NULL) {
            Sensor *sNav = bNav->listaSensores->inicio;
            while (sNav != NULL) {
                if (sNav->listaOcorrencias != NULL) {
                    Ocorrencia *oNav = sNav->listaOcorrencias->inicio;
                    while (oNav != NULL) {
                        // Criar cópia da descrição para trocar espaços por underline
                        char descTemp[100];
                        strncpy(descTemp, oNav->descricao, 99);
                        descTemp[99] = '\0';

                        for (int i = 0; descTemp[i] != '\0'; i++) {
                            if (descTemp[i] == ' ' || descTemp[i] == '\n' || descTemp[i] == '\r') 
                                descTemp[i] = '_';
                        }

                        // Formato: codigo severidade status codigo_sensor codigo_bairro descricao
                        fprintf(arquivo, "%d %d %d %d %d %s\n", 
                                oNav->codigo, oNav->severidade, oNav->status, 
                                sNav->codigo, bNav->codigo, descTemp);
                        
                        oNav = oNav->prox;
                    }
                }
                sNav = sNav->prox;
            }
        }
        bNav = bNav->prox;
    }

    fclose(arquivo);
    printf("Dados das ocorrências persistidos com sucesso!\n");
}

void carregarOcorrencias(listaBairros *B) {
    FILE *arquivo = fopen("ocorrencias.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo 'ocorrencias.txt' não encontrado.\n");
        return;
    }

    int cod, sev, stat, codS, codB;
    char desc[100];

    // Formato esperado: %d %d %d %d %d %s
    while (fscanf(arquivo, "%d %d %d %d %d %s", &cod, &sev, &stat, &codS, &codB, desc) == 6) {
        // Voltar underlines para espaços
        for (int i = 0; desc[i] != '\0'; i++) {
            if (desc[i] == '_') desc[i] = ' ';
        }

        // Registra na memória vinculando aos IDs de sensor e bairro lidos
        registrarOcorrencia(cod, sev, stat, codS, codB, desc, B, NULL);
    }

    fclose(arquivo);
    printf("Dados das ocorrências carregados com sucesso!\n");
}

listaOcorrencias *criarListaOcorrencias() //usado na hora de cadastrar o sensor
{  
    listaOcorrencias *O = (listaOcorrencias *) calloc(1, sizeof(listaOcorrencias));

    return O;

}

Ocorrencia *criarOcorrencia()
{
    Ocorrencia *o = (Ocorrencia *) calloc(1, sizeof(Ocorrencia));

    return o;
}

Ocorrencia *buscarOcorrencia(int codigo, listaOcorrencias *O)
{
    //trava de segurança: sensor existe, mas não tem ocorrẽncias associadas a ele
    if (O == NULL || O->inicio == NULL && O->final == NULL)
        return NULL;

    Ocorrencia *navegador = O->inicio;

    while (navegador != NULL && navegador->codigo != codigo)
    {
        navegador = navegador->prox;
    }

    return navegador; 
}

Ocorrencia *buscarOcorrenciaGlobal(int codigoOcorrencia, listaBairros *B) {
    if (B == NULL || B->inicio == NULL) return NULL;

    Bairro *bNav = B->inicio;
    while (bNav != NULL) {
        if (bNav->listaSensores != NULL) {
            Sensor *sNav = bNav->listaSensores->inicio;
            while (sNav != NULL) {
                if (sNav->listaOcorrencias != NULL) {
                    // Aqui usamos a sua função original, pois temos a lista de ocorrências do sensor
                    Ocorrencia *oEncontrada = buscarOcorrencia(codigoOcorrencia, sNav->listaOcorrencias);
                    if (oEncontrada != NULL) {
                        return oEncontrada; // Encontrou! Retorna o ponteiro dela
                    }
                }
                sNav = sNav->prox;
            }
        }
        bNav = bNav->prox;
    }
    return NULL; // Se percorrer tudo e não achar nada
}

void registrarOcorrencia (int codigo, int severidade, int status, int codigoSensor, int codigoBairro, char *descricao, listaBairros *B, listaChamados *chamadosPendentes)
{
    //procura bairro associado
    Bairro *bairroAssociado = buscarBairro(codigoBairro, B);
    if (bairroAssociado == NULL) 
    {
        printf("ERRO: Bairro %d não existe!\n", codigoBairro);
        return;
    }

    //procura sensor associado
    Sensor *sensorAssociado = buscarSensor(codigoSensor, bairroAssociado->listaSensores);
    if (sensorAssociado == NULL)
    {
        printf("ERRO: Sensor %d não existe!\n", codigoSensor);
        return;
    }

    //verifica se já não existe uma ocorrência com o código digitado
    Ocorrencia *verificacao = buscarOcorrencia (codigo, sensorAssociado->listaOcorrencias);
    if (verificacao != NULL)
    {
        printf("Erro: ocorrência já existente!\n");
        return;
    }
    else
    {
        //alocação do espaço + registro das informações
        Ocorrencia *o = criarOcorrencia();
        o->codigo = codigo;
        o->severidade = severidade;
        o->status = status;
        strcpy(o->descricao, descricao); //melhorar -> maior eficiencia

        //INSERÇÃO NO FINAL -> CASO 01: primeira ocorrência do sensor
        if (sensorAssociado->listaOcorrencias->inicio == NULL && sensorAssociado->listaOcorrencias->final == NULL)
        {
            sensorAssociado->listaOcorrencias->inicio = o;
            sensorAssociado->listaOcorrencias->final = o;
        }
        else
        {
            sensorAssociado->listaOcorrencias->final->prox = o;
            sensorAssociado->listaOcorrencias->final = o;
        }
    }

    // GERAÇÃO AUTOMÁTICA DO CHAMADO
   if (severidade == 4)
{
    static int idChamadoAutomatico = 1000; 
    printf("ALERTA: Ocorrência grave registrada!\n");
    gerarChamado(idChamadoAutomatico, codigo, 4, 1, chamadosPendentes, B);
    idChamadoAutomatico++;
}

    bairroAssociado = NULL;
    sensorAssociado = NULL;
    verificacao = NULL;
}

void listarOcorrencias(listaBairros *B) //é um loop triplo -> pode melhorar?
{
    //a "trava de seguraça" seria verificar se algum desses ponteiros são nulos
    
    //trava principal: a cidade tem bairros?
    if (B == NULL || B->inicio == NULL)
    {
        printf("ERRO: nenhum bairro cadastrado!\n");
        return;
    }
    Bairro *navegador1 = B->inicio; //aponta para o primeiro nó da masterlist de bairros

    while (navegador1 != NULL) //enquanto não chega no final da masterlist de bairros. vai apontar para os nós
    {
        //trava de segurança do bairro: esse barro em específico tem sensores associados a ele?
        if (navegador1->listaSensores != NULL && navegador1->listaSensores->inicio != NULL) //
        {
            Sensor *navegador2 = navegador1->listaSensores->inicio;

            while (navegador2 != NULL) //percorre os nós da lista de sensores associada ao bairro atual (para onde o navegador1 está apontando)
            {
                //trava de segurança do sensor: esse sensor em específico tem ocorrências associadas a ele?
                if (navegador2->listaOcorrencias != NULL && navegador2->listaOcorrencias->inicio != NULL)
                {
                    Ocorrencia *navegador3 = navegador2->listaOcorrencias->inicio;
                    while (navegador3 != NULL) //percorre os nós da lista de ocorrências associada ao sensor atual (para onde o navegador2 está apontando)
                    {
                        printf("--- Bairro: %s | Sensor: %d ---\n", navegador1->nome, navegador2->codigo);
                        printf("Codigo da ocorrência: %d\n", navegador3->codigo);
                        switch (navegador3->severidade)
                        {
                            case 1:
                                printf("Severidade: 1 - baixa\n");
                                break;
                            case 2:
                                printf("Severidade: 2 - média\n");
                                break;
                            case 3:
                                printf("Severidade: 3 - alta\n");
                                break;
                            case 4:
                                printf("Severidade: 4 - crítica\n");
                                break;
                        }
                        printf("Descrição: %s", navegador3->descricao);
                        switch (navegador3->status)
                        {
                            case 1:
                                printf("Status: 1 - aberta\n");
                                break;
                            case 2:
                                printf("Status: 2 - em andamento\n");
                                break;
                            case 3:
                                printf("Status: 3 - finalizada\n");
                                break;
                        }
                        printf("\n");
                        navegador3 = navegador3->prox;
                    }
                }

                navegador2 = navegador2->prox;
            }
            
        }

        navegador1 = navegador1->prox;
    }
}

// ==========================================
// GERENCIAMENTO DE EQUIPES E CHAMADOS
// ==========================================
void salvarEquipes(listaEquipes *E) {
    if (E == NULL || E->inicio == NULL) return;

    FILE *arquivo = fopen("equipes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo 'equipes.txt' para escrita!\n");
        return;
    }

    Equipe *navegador = E->inicio;
    while (navegador != NULL) {
        char nomeTemp[50], especTemp[30];
        
        // Copia e troca espaços por underline no nome
        strncpy(nomeTemp, navegador->nome, sizeof(nomeTemp) - 1);
        nomeTemp[sizeof(nomeTemp) - 1] = '\0';
        for (int i = 0; nomeTemp[i] != '\0'; i++) {
            if (nomeTemp[i] == ' ') nomeTemp[i] = '_';
        }

        // Copia e troca espaços por underline na especialidade
        strncpy(especTemp, navegador->especialidade, sizeof(especTemp) - 1);
        especTemp[sizeof(especTemp) - 1] = '\0';
        for (int i = 0; especTemp[i] != '\0'; i++) {
            if (especTemp[i] == ' ') especTemp[i] = '_';
        }

        // Formato: codigo nome especialidade
        fprintf(arquivo, "%d %s %s\n", navegador->codigo, nomeTemp, especTemp);
        navegador = navegador->prox;
    }

    fclose(arquivo);
    printf("Dados das equipes persistidos em 'equipes.txt' com sucesso!\n");
}

void carregarEquipes(listaEquipes *E) {
    FILE *arquivo = fopen("equipes.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo 'equipes.txt' não encontrado.\n");
        return;
    }

    int codigo;
    char nome[50], especialidade[30];

    // Lê os dados formatados (sem espaços)
    while (fscanf(arquivo, "%d %s %s", &codigo, nome, especialidade) == 3) {
        // Restaura espaços no nome
        for (int i = 0; nome[i] != '\0'; i++) {
            if (nome[i] == '_') nome[i] = ' ';
        }
        // Restaura espaços na especialidade
        for (int i = 0; especialidade[i] != '\0'; i++) {
            if (especialidade[i] == '_') especialidade[i] = ' ';
        }
        
        cadastrarEquipe(codigo, nome, especialidade, E);
    }

    fclose(arquivo);
    printf("Dados das equipes carregados com sucesso!\n");
}

listaEquipes *criarListaEquipes()
{
    listaEquipes *E = (listaEquipes *) calloc(1, sizeof(listaEquipes));

    return E;
}
Equipe *criarEquipe()
{
    Equipe *e = (Equipe *) calloc(1, sizeof(Equipe));

    return e;
}

Equipe *buscarEquipe (int codigo, listaEquipes *E)
{
    //verificar se nenhuma equipe foi inicializada OU se a lista de equipes está vazia
    if (E == NULL || E->inicio == NULL && E->final == NULL)
        return NULL;

    Equipe *navegador = E->inicio;

    while (navegador != NULL && navegador->codigo != codigo)
        navegador = navegador->prox;

    return navegador;
}

void cadastrarEquipe (int codigo, char *nome, char *especialidade, listaEquipes *E)
{
    //verificar se já não existe um bairro com o código digitado
    Equipe *verificacao = buscarEquipe (codigo, E);

     if (verificacao != NULL)
    {
        printf("Equipe já existente!\n");
        return;
    }
    else
    {
        //alocação do espaço + registro das informações
        Equipe *e = criarEquipe();
        e->codigo = codigo;
        strcpy(e->nome, nome); //melhorar? jeito mais eficiente?
        strcpy(e->especialidade, especialidade); //melhorar? jeito mais eficiente?
        //e->listaChamados = criarListaChamados();

        //ONDE de fato alocar
        if (E->inicio == NULL && E->final == NULL) //caso 1: primeira equipe a ser alocada
        {
            E->inicio = e;
            E->final = e;
        }
        else
        {
            E->final->prox = e;
            E->final = e;
        }
    }

    verificacao = NULL; //limpeza da memória
}

Chamado *criarChamado()
{
    Chamado *c = (Chamado *) calloc(1, sizeof(Chamado));

    return c;
}

listaChamados *criarListaChamados()
{
    listaChamados *C = (listaChamados *) calloc(1, sizeof(listaChamados));

    return C;
}
Chamado *buscarChamado(int codigo, listaChamados *C)
{
    //trava de segurança
    if (C == NULL || C->inicio == NULL && C->final == NULL)
        return NULL;

    Chamado *navegador = C->inicio;
    while (navegador != NULL && navegador->codigo != codigo)
        navegador = navegador->prox;

    return navegador;
}

void gerarChamado(int codigo, int codigoOcorrencia, int prioridade, int status, listaChamados *C, listaBairros *B)
{
    // transformação do ID em ponteiro
    Ocorrencia *ocorrenciaEncontrada = buscarOcorrenciaGlobal(codigoOcorrencia, B);
    
    if (ocorrenciaEncontrada == NULL) {
        printf("ERRO: Ocorrencia %d não existe na cidade! Chamado não gerado.\n", codigoOcorrencia);
        return;
    }

    //trava de segurança: chamado já existente
    Chamado *verificacao = buscarChamado(codigo, C);
    if (verificacao != NULL) {
        printf("ERRO: já existe um chamado com o código %d!\n", verificacao->codigo);
        return;
    }

    // 3. Alocação e Preenchimento
    Chamado *c = criarChamado();
    c->codigo = codigo;
    c->prioridade = prioridade;
    c->status = status;
    c->Ocorrencia = ocorrenciaEncontrada;

    // 4. inserção na fila global
    if (C->inicio == NULL && C->final == NULL) {
        C->inicio = c;
        C->final = c;
    } else {
        C->final->prox = c;
        C->final = c;
    }
}

void associarEquipe(int codigoChamado, int codigoEquipe, listaChamados *C, listaEquipes *E)
{
    //passo 01) achar a equipe
    //regra do edital: associar equipe com o chamado compatível com a especialidade
    Equipe *equipeAssociada = buscarEquipe (codigoEquipe, E);
    //verificação: equipe não encontrada
    if (equipeAssociada == NULL)
    {
        printf("ERRO: equipe %d não existe!\n", codigoEquipe);
        return;
    }
    //verificação: compatibilidade entre a equipe e o chamado

    //passo 02: buscar o chamado na lista de chamados pendentes
    //trava de segurança: não existe nenhum chamado pendente
    if (C == NULL || C->inicio == NULL && C->final == NULL)
    {
        printf("ERRO: não há nenhum chamado pendente!\n");
        return;
    }

    Chamado *navegador = C->inicio;
    Chamado *anterior = NULL;

    //navegação até achar o chamado com o código correspondente
    while (navegador != NULL && navegador->codigo != codigoChamado)
    {
        anterior = navegador;
        navegador = navegador->prox;
    }
    if (navegador == NULL)
    {
        printf("ERRO: chamado com o código %d não encontrado!\n", codigoChamado);
        return;
    }

    //passo 03: colocar o chamado na lista de chamados da equipe
    //trava de segurança: verificar compatibilidade entre chamado e ocorrência
    if (strcmp(equipeAssociada->especialidade, navegador->Ocorrencia->descricao) != 0) 
    {
        printf("ERRO: Incompatibilidade. A equipe %s (Especialidade: %s) não atende a ocorrência: %s\n", 
            equipeAssociada->nome, equipeAssociada->especialidade, navegador->Ocorrencia->descricao);
        return;
    }

    //passo 04: atualização do status do chamado e da ocorrência
    navegador->status = 2;
    navegador->Ocorrencia->status = 2;

    //passo 05: isolamento e remoção da lista global de chamados (antigo passo 6)
    Chamado *proximoDaFila = navegador->prox; // Salva o resto da fila global
    navegador->prox = NULL; // Quebra a ponte. O nó agora está isolado.

    if (anterior == NULL)
    {
        //caso 01) o chamado era o primeiro da lista de chamados pendentes
        C->inicio = proximoDaFila;
        if (C->inicio == NULL)
        {
            C->final = NULL;
        }
    }
    else
    {
        anterior->prox = proximoDaFila;
        if (proximoDaFila == NULL)
        {
            C->final = anterior;
        }
    }

    //passo 06: colocar o chamado ISOLADO na lista de chamados de equipe
    if (equipeAssociada->listaChamados->inicio == NULL && equipeAssociada->listaChamados->final == NULL)
    {
        equipeAssociada->listaChamados->inicio = navegador;
        equipeAssociada->listaChamados->final = navegador;
    }
    else
    {
      equipeAssociada->listaChamados->final->prox = navegador;
      equipeAssociada->listaChamados->final = navegador;  
    }

}

void finalizarChamado(int codigoChamado, listaEquipes *E) 
{
    // trava de segurança: nenhuma equipe cadastrada
    if (E == NULL || E->inicio == NULL) {
        printf("ERRO: Nenhuma equipe cadastrada!\n");
        return;
    }

    Equipe *navegadorEquipe = E->inicio;

    // passo 01) procurar o chamado correto através da lista de equipes
    while (navegadorEquipe != NULL) 
    {
        // trava de segurança: verifica se a equipe tem uma lista de chamados e se a lista de chamados possui chamados cadastrados
        if (navegadorEquipe->listaChamados != NULL && navegadorEquipe->listaChamados->inicio != NULL) 
        {
            Chamado *navegadorChamado = navegadorEquipe->listaChamados->inicio;
            Chamado *anterior = NULL; // mantém o link da lista quando remove o chamado

            // passo 1.1) procurar o chamado informado
            while (navegadorChamado != NULL && navegadorChamado->codigo != codigoChamado) 
            {
                anterior = navegadorChamado;
                navegadorChamado = navegadorChamado->prox;
            }

            // 1.2) chamado encontrado
            if (navegadorChamado != NULL) 
            {
                navegadorEquipe->total_atendimentos++; // Incrementa os atendimentos da equipe
                navegadorChamado->Ocorrencia->status = 3; // ocorrência resolvida
                
                // 1.3) REMOÇÃO DO CHAMADO DA LISTA DE CHAMADOS DA EQUIPE
                if (anterior == NULL) {
                    // primeiro da lista
                    navegadorEquipe->listaChamados->inicio = navegadorChamado->prox;
                    if (navegadorEquipe->listaChamados->inicio == NULL) {
                        navegadorEquipe->listaChamados->final = NULL;
                    }
                } else {
                    // o chamado estava no meio ou no final da lista
                    anterior->prox = navegadorChamado->prox;
                    if (navegadorChamado->prox == NULL) {
                        navegadorEquipe->listaChamados->final = anterior; // era o último
                    }
                }

                // deleta o chamado da memória
                free(navegadorChamado); // Destrói a prancheta para liberar memória
                
                printf("Sucesso: Chamado %d finalizado pela equipe %s!\n", codigoChamado, navegadorEquipe->nome);
                return;
            }
        }
        navegadorEquipe = navegadorEquipe->prox;
    }

    // trava de segurança
    printf("ERRO: Chamado %d não está associado a nenhuma equipe!\n", codigoChamado);
}


void salvarChamados(listaChamados *C, listaEquipes *E) {
    if (C == NULL || C->inicio == NULL) return;

    FILE *arquivo = fopen("chamados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo 'chamados.txt' para escrita!\n");
        return;
    }

    Chamado *cNav = C->inicio;
    while (cNav != NULL) {
        int codigo_equipe = 0;

        // Descobrir qual equipe possui esse chamado associado (caso sua lógica vincule equipe->chamado)
        // Se a associação for direta, use o código correspondente. Caso contrário, salvamos 0 ou o ID correto.
        if (E != NULL) {
            Equipe *eNav = E->inicio;
            while (eNav != NULL) {
                // Se no seu sistema a equipe aponta para o chamado ou vice-versa, faça a checagem aqui.
                // Como na struct Equipe o campo 'listaChamados' está comentado, adapte se necessário:
                eNav = eNav->prox;
            }
        }

        int codOcorrencia = (cNav->Ocorrencia != NULL) ? cNav->Ocorrencia->codigo : 0;

        // Formato: codigo codigo_ocorrencia codigo_equipe prioridade status
        fprintf(arquivo, "%d %d %d %d %d\n", 
                cNav->codigo, 
                codOcorrencia, 
                codigo_equipe, // Ajuste para salvar o ID real se houver vínculo mapeado
                cNav->prioridade, 
                cNav->status);

        cNav = cNav->prox;
    }

    fclose(arquivo);
    printf("Dados dos chamados persistidos em 'chamados.txt' com sucesso!\n");
}

void carregarChamados(listaChamados *C, listaBairros *B, listaEquipes *E) {
    FILE *arquivo = fopen("chamados.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo 'chamados.txt' não encontrado.\n");
        return;
    }

    int codigo, codOcorrencia, codEquipe, prioridade, status;

    // Formato: %d %d %d %d %d
    while (fscanf(arquivo, "%d %d %d %d %d", &codigo, &codOcorrencia, &codEquipe, &prioridade, &status) == 5) {
        
        // 1. Buscar o nó da ocorrência correspondente de forma global na memória
        Ocorrencia *ocorrenciaEncontrada = NULL;
        if (B != NULL && B->inicio != NULL) {
            Bairro *bNav = B->inicio;
            while (bNav != NULL && ocorrenciaEncontrada == NULL) {
                if (bNav->listaSensores != NULL) {
                    Sensor *sNav = bNav->listaSensores->inicio;
                    while (sNav != NULL && ocorrenciaEncontrada == NULL) {
                        if (sNav->listaOcorrencias != NULL) {
                            ocorrenciaEncontrada = buscarOcorrencia(codOcorrencia, sNav->listaOcorrencias);
                        }
                        sNav = sNav->prox;
                    }
                }
                bNav = bNav->prox;
            }
        }

        // 2. Alocar o Chamado e restaurar os dados na lista
        Chamado *novoChamado = (Chamado *) calloc(1, sizeof(Chamado));
        if (novoChamado != NULL) {
            novoChamado->codigo = codigo;
            novoChamado->prioridade = prioridade;
            novoChamado->status = status;
            novoChamado->Ocorrencia = ocorrenciaEncontrada; // Vincula ao nó real da memória

            // Inserção na lista cabeça de chamados
            if (C->inicio == NULL && C->final == NULL) {
                C->inicio = novoChamado;
                C->final = novoChamado;
            } else {
                C->final->prox = novoChamado;
                C->final = novoChamado;
            }

            // 3. Se houver código de equipe associado (> 0), refaz o vínculo
            if (codEquipe > 0 && E != NULL) {
                // Aqui você pode chamar a sua função: associarEquipe(codigo, codEquipe);
            }
        }
    }

    fclose(arquivo);
    printf("Dados dos chamados carregados com sucesso de 'chamados.txt'.\n");
}
