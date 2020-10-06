#ifndef LISTA_H
#define LISTA_H

#define TRUE 1 /*define valor booleano*/
#define FALSE 0
#define boolean int /*define um tipo booleano*/
#define inicial 0
#define ERRO -32000

#include <item.h>
                       
typedef struct lista_ LISTA;

LISTA *lista_criar(void);
boolean lista_inserir(LISTA *lista, ITEM *i);

void lista_apagar(LISTA **ptr, void (*apagar_conteudo)(void **conteudo));
boolean lista_remover(LISTA *lista, int chave);
ITEM *lista_busca(LISTA *lista, int chave);

int lista_tamanho(LISTA *lista);
boolean lista_vazia(LISTA *lista);
boolean lista_cheia(LISTA *lista);
void lista_imprimir(LISTA *lista);


#endif