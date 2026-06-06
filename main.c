#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==========================================
// MÁQUINA DE ESTADOS E LEITURA DE ARQUIVOS
// ==========================================
// (Funções de ler txt vão aqui)

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

//NÓ BAIRRO
typedef struct bairro{ //NÓ
    int codigo;
    char nome[50];
    Sensor *listaSensores; //vai apontar para uma estrutura S->begin e S->end
    struct bairro *prox;
}Bairro;

//NÓ CABEÇA BAIRRO
typedef struct _listaBairros{
    Bairro *inicio;
    Bairro *final;
}listaBairros;

typedef struct sensor{ //NÓ SENSOR
    int codigo;
    int tipo;
    int status;
    Ocorrencia *listaOcorrencias;
    struct sensor *prox;
}Sensor;

typedef struct _listasensores{ //NÓ CABEÇA SENSOR
    Sensor *inicio;
    Sensor *final;
}listaSensores;


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
void alterarStatusSensor (int codigoSensor, int codigoBairro, int novoStatus, listaBairros *B);
void listarSensoresBairro (int codigoBairro, listaBairros *B);
// ==========================================
// REGISTRO DE OCORRENCIAS
// ==========================================
listaOcorrencias *criarListaOcorrencias();
Ocorrencia *criarOcorrencia();
Ocorrencia *buscarOcorrencia(int codigo, listaOcorrencias *O);

void registrarOcorrencia (int codigo, int severidade, int status, int codigoSensor, int codigoBairro, char *descricao, listaBairros *B);
void listarOcorrencias(listaBairros *B); //não tem parâmetros pq é uma varredura global. listar TODAS as ocorrências

// ==========================================
// EQUIPES E CHAMADOS
// ==========================================
// (Funções de inserir, buscar e gerenciar equipes)

// ==========================================
// FUNÇÃO PRINCIPAL
// ==========================================
int main()
{
    /*
     listaBairros *B = criarBairro();
     */

    return 0;
}

// ==========================================
// GERENCIAMENTO DE BAIRROS
// ==========================================
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
        strcpy(b->nome, nome); //melhorar? jeito mais eficiente?
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

void alterarStatusSensor (int codigoSensor, int codigoBairro, int novoStatus, listaBairros *B)
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

    bairroAssociado = NULL;
    sensorBuscado = NULL;
    //TRAVAS DE SEGURANÇA + TRATAMENTO DE ERROS 
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

void registrarOcorrencia (int codigo, int severidade, int status, int codigoSensor, int codigoBairro, char *descricao, listaBairros *B)
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