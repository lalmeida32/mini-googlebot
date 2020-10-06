#ifndef LISTA_H
#define LISTA_H

#define TRUE 1
#define FALSE 0
#define boolean int
#define inicial 0
#define ERRO -32000

#include <TADitem.h>
                       
typedef struct lista_ LISTA;

//cria uma lista na heap
// - Parametros
//    -> void
// - Retorno
//    -> ponteiro do tipo lista, se der erro retorna NULL
LISTA *lista_criar(void);


//diz se a lista esta vazia
// - Parametros
//    -> lista que deseja saber se esta vazia
// - Retorno
//    -> TRUE se a lista estiver vazia e FALSE se a lista nao existir ou se nao estiver vazia
boolean lista_vazia(LISTA *lista);


//diz se a lista esta cheia
// - Parametros
//    -> lista que deseja saber se esta cheia
// - Retorno
//    -> TRUE se a lista estiver cheia e FALSE se a lista nao existir ou se nao estiver cheia
boolean lista_cheia(LISTA *lista);


//diz o tamanho da lista
// - Parametros
//    -> lista que deseja saber o tamanho
// - Retorno
//    -> inteiro que eh o tamanho da lista
int lista_tamanho(LISTA *lista);


//percorre a lista imprimindo todos os itens dela
// - Parametros
//    -> lista que deseja imprimir
// - Retorno
//    -> void
void lista_imprimir(LISTA *lista);


//insere um intem na lista
// - Parametros
//    -> lista que deseja inserir um item
//    -> item que deseja inserir na lista
// - Retorno
//    -> TRUE se inseriu o item e FALSE se a lista nao existir, logo o item n foi inserido
boolean lista_inserir(LISTA *lista, ITEM *i);


//procura um item na lista a partir de sua chave
// - Parametros
//    -> lista que deseja procurar o item
//    -> chave do item
// - Retorno
//    -> se encontrar retorna o item, se nao encontrar retorna NULL
ITEM *lista_busca(LISTA *lista, int chave);


//remove um item na lista a partir de sua chave
// - Parâmetros
//    -> lista que deseja remover o item
//    -> chave do item
// - Retorno
//    -> TRUE se o item for removido e FALSE se a lista nao existir ou se o item nao foi encotrado para ser removido
boolean lista_remover(LISTA *lista, int chave, void (*apagar_conteudo)(void **conteudo));


//apaga a lista da memoria
// - Parâmetros
//    -> endereço da lista que deseja apagar
//    -> Se quiser apagar o conteudo usando uma funcao, passe o endereco dela,
//se ao inves disso quiser usar a funcao free da <stdlib.h>, passe NULL
// - Retorno
//    -> void
void lista_apagar(LISTA **lista, void (*apagar_conteudo)(void **conteudo));

#endif