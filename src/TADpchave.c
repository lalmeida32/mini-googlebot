#include <stdio.h>
#include <stdlib.h>
#include "TADpchave.h"

struct palavra_chave_ref{
    char palavra_chave[50];
    PQUEUE *sites_relacionados;  
};


//cria o tad pchave
PALAVRA_CHAVE_REF *pchave_ref_criar(char *palavra, PQUEUE *sites){
    PALAVRA_CHAVE_REF *pchave = (PALAVRA_CHAVE_REF *) malloc(sizeof(PALAVRA_CHAVE_REF));
    if(pchave != NULL){
        strcpy(pchave->palavra_chave, palavra);
        pchave->sites_relacionados = sites;
    }
    return pchave;
}

//compara duas palavras chaves
int pchave_ref_comparar(void *dados1, void *dados2) {
    //fazendo um casting para poder comparar as palavras chaves
    PALAVRA_CHAVE_REF *pchave_ref1 = (PALAVRA_CHAVE_REF *) dados1;
    PALAVRA_CHAVE_REF *pchave_ref2 = (PALAVRA_CHAVE_REF *) dados2;

    return strcmp(pchave_ref1->palavra_chave, pchave_ref2->palavra_chave);
}


//apaga o tad pchave
void pchave_ref_apagar(void **dados){
    if (!dados || !(*dados)) 
        return;

    PALAVRA_CHAVE_REF **pchave_ref = (PALAVRA_CHAVE_REF **) dados;
    pqueue_free(&(*pchave_ref)->sites_relacionados);

    free(*pchave_ref);
    *pchave_ref = NULL;
}


char *pchave_get_palavra_chave(PALAVRA_CHAVE_REF *pchave){
    //se nao existir
    if (pchave == NULL) return NULL;

    // sem erros
    return pchave->palavra_chave;
}

PQUEUE *pchave_get_sites_relacionados(PALAVRA_CHAVE_REF *pchave){
    // caso de erro ( não existe)
    if (pchave == NULL) return NULL;

    return pchave->sites_relacionados;
}

void pchave_set_sites_relacionados(PALAVRA_CHAVE_REF *pchave, PQUEUE *sites_relacionados) {
    // caso de erro ( não existe)
    if (pchave == NULL) return;

    pchave->sites_relacionados = sites_relacionados;
}

//imprime a palavra-chave e o site relacionado a ela com maior relevancia
void pchave_ref_imprimir(void *dados) {
    PALAVRA_CHAVE_REF *pchave = (PALAVRA_CHAVE_REF *) dados;

    printf("%s\n", pchave->palavra_chave);
    site_imprimir(pqueue_get_topo(pchave->sites_relacionados), stdout);
    printf("\n\n");
}


//busca na avl de palavras chave a procura de uma determinada palavra chave
PALAVRA_CHAVE_REF *pchave_ref_busca_em_avl(AVL *avl_de_palavras_chave, char *palavra_chave) {
    if (!avl_de_palavras_chave || !palavra_chave) return NULL;

    PALAVRA_CHAVE_REF *pchave_para_busca = pchave_ref_criar(palavra_chave, NULL);
    PALAVRA_CHAVE_REF *pchave_ref_encontrada = avl_busca(avl_de_palavras_chave, pchave_para_busca);
    pchave_ref_apagar((void **) &pchave_para_busca);

    return pchave_ref_encontrada;

}

// Busca por uma palavra chave de um site na avl e o adiciona na pqueue de sites relacionados
void pchave_insere_site_na_avl_para_palavra_chave_especifica(AVL *avl_de_palavras_chave, SITE *site, char *palavra_chave) {
    PALAVRA_CHAVE_REF *pchave_ref_encontrada = pchave_ref_busca_em_avl(avl_de_palavras_chave, palavra_chave);

    // não encontrou
    if (!pchave_ref_encontrada) {
        PQUEUE *pqueue_de_sites = pqueue_criar();
        pqueue_set_dados_comparar(pqueue_de_sites, &site_comparar_relevancia);
        pqueue_inserir(pqueue_de_sites, site);
        PALAVRA_CHAVE_REF *pchave_ref = pchave_ref_criar(palavra_chave, pqueue_de_sites);
        avl_inserir(avl_de_palavras_chave, pchave_ref);
        return;
    }
    
    // encontrou na árvore a palavra-chave buscada
    // insere site na pqueue da palavra chave 
    pqueue_inserir(pchave_get_sites_relacionados(pchave_ref_encontrada), site);
}

// Busca pelas palavras chaves de um site na avl e adiciona o site na pqueue de sites relacionados
void pchave_insere_site_na_avl(AVL *avl_de_palavras_chave, SITE *site) {
    for (int j = 0; j < site_get_num_palavras_chave(site); j++) {
        char *palavra_chave = site_get_palavra_chave(site, j);

        pchave_insere_site_na_avl_para_palavra_chave_especifica(avl_de_palavras_chave, site, palavra_chave);
    }
}

//remove site da fila de prioridade de sites de uma palavra-chave especifica(buscada na avl_de_palavras_chave)
void pchave_remove_site_na_avl_para_palavra_chave_especifica(AVL *avl_de_palavras_chave, SITE *site, char *palavra_chave) {
    
    PALAVRA_CHAVE_REF *pchave_ref_encontrada = pchave_ref_busca_em_avl(avl_de_palavras_chave, palavra_chave);

    // não encontrou
    if (!pchave_ref_encontrada) return;

    PQUEUE *pqueue_atual = pchave_get_sites_relacionados(pchave_ref_encontrada);
    PQUEUE *auxiliar = pqueue_criar();
    pqueue_set_dados_comparar(auxiliar, &site_comparar_relevancia);

    while (pqueue_get_quantidade(pqueue_atual)) {
        SITE *site_atual = pqueue_get_topo(pqueue_atual);
        if (site_atual != site)
            pqueue_inserir(auxiliar, site_atual);
        pqueue_remover(pqueue_atual);
    }
    pchave_set_sites_relacionados(pchave_ref_encontrada, auxiliar);

    pqueue_free(&pqueue_atual);

}


//Elimina todas as "ligaçoes" do site (passado como parameto) com as palavras chave da avl_de_palavras_chave
void pchave_remove_site_na_avl(AVL *avl_de_palavras_chave, SITE *site) {

    for (int i = 0; i < site_get_num_palavras_chave(site); i++) {
        char *palavra_chave = site_get_palavra_chave(site, i);

        pchave_remove_site_na_avl_para_palavra_chave_especifica(avl_de_palavras_chave, site, palavra_chave);
    }
}