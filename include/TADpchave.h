#ifndef _PCHAVE_H_
    #define _PCHAVE_H_

    #include "TADpriorityqueue.h"
    #include "TADavl.h"
    #include <string.h>

    typedef struct palavra_chave_ref PALAVRA_CHAVE_REF;
    
    // Criar a palavra chave na memória Heap
    // - Parâmetros
    //    -> palavra_chave
    //    -> sites_relacioandos: ponteiro para os sites relacioandos  
    // - Retorno
    //    -> ponteiro para estrutura palavra_chave, NULL se der erro
    PALAVRA_CHAVE_REF *pchave_ref_criar(char *palavra_chave, PQUEUE *sites_relacionados);


    // Compara duas palavras chaves
    // - Parâmetros
    //    -> dados1
    //    -> dados2
    // - Retorno
    //    -> retorna 0 se as palavras forem iguais e diferente de 0 se nao forem iguais 
    int pchave_ref_comparar(void *dados1, void *dados2);


    // Apaga a palvra chave da memoria
    // - Parâmetros
    //    -> dados: endereço do dado
    // - Retorno
    //    void
    void pchave_ref_apagar(void **dados);


    // Recupera a palavra chave
    // - Parâmetros
    //    -> pchave: palavra chave de interesse 
    // - Retorno
    //    -> retorna a palavra chave caso o parametro nao seja NULL, se for retorna NULL
    char *pchave_get_palavra_chave(PALAVRA_CHAVE_REF *pchave);

    // Recupera os sites relacioandas a palavra chave
    // - Parâmetros
    //    -> pchave: palavra chave de interesse 
    // - Retorno
    //    -> retorna um ponteiro para a fila de prioridade de sites o parametro nao seja NULL, se for retorna NULL
    PQUEUE *pchave_get_sites_relacionados(PALAVRA_CHAVE_REF *pchave);

    void pchave_ref_imprimir(void *dados);

    PALAVRA_CHAVE_REF *pchave_ref_busca_em_avl(AVL *avl_de_palavras_chave, char *palavra_chave);

    void pchave_inserir_site_relacionado_em_avl(AVL *avl_de_palavras_chave, SITE *site);

#endif