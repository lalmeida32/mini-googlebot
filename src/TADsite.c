#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include<TADsite.h>

struct site_t {
    char nome[50];
    int relevancia;
    char link[100];
    char palavras_chave[10][50];
    int contador_de_palavras_chave;
};



void site_set_string(char *destination, const char *source, size_t max_length) {
    strncpy(destination, source, max_length);
    destination[max_length - 1] = '\0';
}


int site_get_nome_max_length() {
    return sizeof(((SITE *) NULL)->nome);
}

int site_get_link_max_length() {
    return sizeof(((SITE *) NULL)->link);
}

int site_get_palavra_chave_max_length() {
    return sizeof(*(((SITE *) NULL)->palavras_chave));
}

int site_get_palavras_chave_max_count() {
    return sizeof(((SITE *)NULL)->palavras_chave) / site_get_palavra_chave_max_length();
}

SITE *site_criar() {
    SITE *site = (SITE *) malloc(sizeof(SITE));
    if (!site) return NULL;

    site->nome[0] = '\0';
    site->relevancia = -1;
    site->link[0] = '\0';
    site->contador_de_palavras_chave = 0;

    return site;
}

void site_apagar(SITE **site) {

    if (!(*site)) return;

    free(*site);
    *site = NULL;

}

boolean site_set_nome(SITE *site, const char *nome) {
    
    if (!site || !nome) return FALSE;

    site_set_string(site->nome, nome, site_get_nome_max_length());

    return TRUE;
}

boolean site_set_relevancia(SITE *site, int relevancia) {

    if (!site || relevancia < 0 || relevancia > 1000) return FALSE;

    site->relevancia = relevancia;
    
    return TRUE;
}

boolean site_set_link(SITE *site, const char *link) {

    if (!site || !link) return FALSE;

    site_set_string(site->link, link, site_get_link_max_length);
    
    return TRUE;
}

boolean site_add_palavra_chave(SITE *site, const char *palavra_chave) {
    
    if (!site || !palavra_chave) return FALSE;
    
    if (site->contador_de_palavras_chave >= site_get_palavras_chave_max_count) return FALSE;

    site_set_string(site->palavras_chave[site->contador_de_palavras_chave], palavra_chave, site_get_palavra_chave_max_length);
    site->contador_de_palavras_chave++;

    return TRUE;
}