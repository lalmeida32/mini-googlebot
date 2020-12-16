#ifndef _PCHAVE_H_
    #define _PCHAVE_H_

    #include "TADpriorityqueue.h"
    #include <string.h>

    typedef struct palavra_chave_ref PALAVRA_CHAVE_REF;
    
    PALAVRA_CHAVE_REF *pchave_ref_criar(char *palavra_chave, PQUEUE *sites_relacionados);
    int pchave_ref_comparar(void *dados1, void *dados2);
    void pchave_ref_apagar(void **dados);
    char *pchave_get_palavra_chave(PALAVRA_CHAVE_REF *pchave);
    PQUEUE *pchave_get_sites_relacionado(PALAVRA_CHAVE_REF *pchave);



#endif