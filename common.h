/******************************************************************************
 ** ISCTE-IUL: Trabalho prático 3 de Sistemas Operativos
 **
 ** Aluno: Nº: XXXXXX  Nome: Este Módulo não precisa ser entregue
 ** Nome do Módulo: common.h
 ** Descrição/Explicação do Módulo:
 **     Definição das estruturas de dados comuns aos módulos servidor e cliente
 **
 ******************************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__

#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/shm.h>

#define MIN_PROCESSAMENTO        1  // Tempo mínimo de processamento do Cliente
#define MAX_PROCESSAMENTO        7  // Tempo máximo de processamento do Cliente
#define MAX_ESPERA               5  // Tempo máximo de espera por parte do Cliente
#define MAX_USERS               20  // Número máximo de utilizadores
#define MAX_PRODUCTS            30  // Número máximo de produtos

#define SEM_MUTEX_INITIAL_VALUE  1  // Valor inicial por omissão nos semáforos do tipo MUTEX
#define SEM_USERS                0  // Índice do semáforo de acesso à lista de utilizadores no grupo de semáforos
#define SEM_PRODUCTS             1  // Índice do semáforo de acesso à lista de produtos no grupo de semáforos
#define SEM_NR_SRV_DEDICADOS     2  // Índice do semáforo de controlo do nº de servidores dedicados no grupo de semáforos

#define MSGTYPE_LOGIN            1  // Valor convencionado para a msgType (mailbox) de Login do Servidor
#define FIM_LISTA_PRODUTOS      -2  // Valor convencionado para indicar no campo idProduto que a lista de produtos terminou
#define PRODUTO_COMPRADO        -3  // Valor convencionado para indicar no campo idProduto que o produto foi comprado
#define PRODUTO_NAO_COMPRADO    -4  // Valor convencionado para indicar no campo idProduto que o produto NÃO foi comprado
#define USER_NOT_FOUND          -1  // Valor convencionado para indicar que o utilizador não existe ou não foi encontrado
#define PRODUCT_NOT_FOUND       -1  // Valor convencionado para indicar que o produto não existe ou não foi encontrado
#define PROCESSO_FILHO           0  // Valor com que a variável resultado de fork fica no caso de estarmos no processo Filho

#define RET_ERROR               -1  // Valor convencionado para retornar erro nas várias funções que retornam um inteiro representando Sucesso
#define RET_SUCCESS              0  // Valor convencionado para retornar sucesso nas várias funções que retornam um inteiro representando Sucesso

typedef struct {
    int nif;                        // Número de contribuinte do utilizador
    char senha[20];                 // Senha do utilizador
    char nome[52];                  // Nome do utilizador
    int saldo;                      // Saldo do utilizador
    int pidCliente;                 // PID do processo Cliente
    int pidServidorDedicado;        // PID do processo Servidor Dedicado
} Login;

typedef struct {
    int idProduto;                  // Identificador único do produto
    char nomeProduto[40];           // Nome do Produto
    char categoria[40];             // Categoria do Produto
    int preco;                      // Preço do Produto
    int stock;                      // Stock do Produto
} Produto;

typedef struct {
    long msgType;                   // Tipo da Mensagem
    struct {
        Login infoLogin;            // Informação sobre o Login
        Produto infoProduto;        // Informação sobre um Produto
    } msgData;                      // Dados da Mensagem
} MsgContent;

typedef struct {                    // Estrutura de dados a ser guardada em Memória Partilhada
    Login listUsers[MAX_USERS];
    Produto listProducts[MAX_PRODUCTS];
} DadosServidor;

#define FILE_DATABASE_USERS  "bd_utilizadores.dat"  // Ficheiro de acesso direto que armazena a lista de utilizadores
#define FILE_DATABASE_PRODUCTS  "bd_produtos.dat"   // Ficheiro de acesso direto que armazena a lista de produtos

/**
 *  KEY to be used on all Linux IPC get operations
 */
#define IPC_KEY 0x0a98450     // Suggestion: Replace with your student number

#endif