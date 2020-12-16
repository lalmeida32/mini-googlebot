#include <stdio.h>
#include <stdlib.h>
#include "TADpchave.h"
#include "TADsite.h"


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

void pchave_ref_imprimr(void *dados) {
    PALAVRA_CHAVE_REF *pchave = (PALAVRA_CHAVE_REF *) dados;

    printf("%s\n", pchave->palavra_chave);
    site_imprimir(pqueue_get_topo(pchave->sites_relacionados), stdout);
    printf("\n\n");
}