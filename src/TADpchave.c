#include <stdio.h>
#include <stdlib.h>
#include "TADpchave.h"

struct palavra_chave_ref{
    char palavra_chave[50];
    PQUEUE *sites_relacionados;  
};


PALAVRA_CHAVE_REF *pchave_ref_criar(char *palavra, PQUEUE *sites){
    PALAVRA_CHAVE_REF *pchave = (PALAVRA_CHAVE_REF *) malloc(sizeof(PALAVRA_CHAVE_REF));
    if(pchave != NULL){
        strcpy(pchave->palavra_chave, palavra);
        pchave->sites_relacionados = sites;
    }
    return pchave;
}


int pchave_ref_comparar(void *dados1, void *dados2) {
    PALAVRA_CHAVE_REF *pchave_ref1 = (PALAVRA_CHAVE_REF *) dados1;
    PALAVRA_CHAVE_REF *pchave_ref2 = (PALAVRA_CHAVE_REF *) dados2;

    return strcmp(pchave_ref1->palavra_chave, pchave_ref2->palavra_chave);
}


void pchave_ref_apagar(void **dados){
    if (!dados || !(*dados)) 
        return;

    PALAVRA_CHAVE_REF **pchave_ref = (PALAVRA_CHAVE_REF **) dados;
    pqueue_free(&(*pchave_ref)->sites_relacionados);

    free(*pchave_ref);
    *pchave_ref = NULL;
}


char *pchave_get_palavra_chave(PALAVRA_CHAVE_REF *pchave){
    // caso de erro ( não existe)
    if (pchave == NULL) return NULL;

    // sem erros
    return pchave->palavra_chave;
}

PQUEUE *pchave_get_sites_relacionados(PALAVRA_CHAVE_REF *pchave){
    // caso de erro ( não existe)
    if (pchave == NULL) return NULL;

    return pchave->sites_relacionados;
}

void pchave_set_sites_relacionados(PALAVRA_CHAVE_REF *pchave, PQUEUE *sites_relacionados){
    // caso de erro ( não existe)
    if (pchave == NULL) return;

    pchave->sites_relacionados = sites_relacionados;
}

void pchave_ref_imprimir(void *dados) {
    PALAVRA_CHAVE_REF *pchave = (PALAVRA_CHAVE_REF *) dados;

    printf("%s\n", pchave->palavra_chave);
    site_imprimir(pqueue_get_topo(pchave->sites_relacionados), stdout);
    printf("\n\n");
}

PALAVRA_CHAVE_REF *pchave_ref_busca_em_avl(AVL *avl_de_palavras_chave, char *palavra_chave) {
    if (!avl_de_palavras_chave || !palavra_chave) return NULL;

    PALAVRA_CHAVE_REF *pchave_para_busca = pchave_ref_criar(palavra_chave, NULL);
    PALAVRA_CHAVE_REF *pchave_ref_encontrada = avl_busca(avl_de_palavras_chave, pchave_para_busca);
    pchave_ref_apagar((void **) &pchave_para_busca);

    return pchave_ref_encontrada;

}

void pchave_inserir_site_relacionado_em_avl(AVL *avl_de_palavras_chave, SITE *site) {
    for (int j = 0; j < site_get_num_palavras_chave(site); j++) {
        char *palavra_chave = site_get_palavra_chave(site, j);
        PALAVRA_CHAVE_REF *pchave_ref_encontrada = pchave_ref_busca_em_avl(avl_de_palavras_chave, palavra_chave);

        // encontrou na árvore a palavra-chave buscada
        if (pchave_ref_encontrada)
            
            // insere site na pqueue da palavra chave 
            pqueue_inserir(pchave_get_sites_relacionados(pchave_ref_encontrada), site);
        
        // não encontrou
        else {
            PQUEUE *pqueue_de_sites = pqueue_criar();
            pqueue_set_dados_comparar(pqueue_de_sites, &site_comparar_relevancia);
            pqueue_inserir(pqueue_de_sites, site);
            PALAVRA_CHAVE_REF *pchave_ref = pchave_ref_criar(palavra_chave, pqueue_de_sites);
            avl_inserir(avl_de_palavras_chave, pchave_ref);
        }
        
    }
}