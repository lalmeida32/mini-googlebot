#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include<site.h>

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

    const size_t max_length = sizeof(site->nome);
    site_set_string(site->nome, nome, max_length);

    return TRUE;
}

boolean site_set_relevancia(SITE *site, int relevancia) {

    if (!site || relevancia < 0 || relevancia > 1000) return FALSE;

    site->relevancia = relevancia;
    
    return TRUE;
}

boolean site_set_link(SITE *site, const char *link) {

    if (!site || !link) return FALSE;

    const size_t max_length = sizeof(site->link);
    site_set_string(site->link, link, max_length);
    
    return TRUE;
}

boolean site_add_palavra_chave(SITE *site, const char *palavra_chave) {
    
    if (!site || !palavra_chave) return FALSE;
    
    const size_t max_length = sizeof(*(site->palavras_chave));
    const size_t max_palavras_chave = sizeof(site->palavras_chave) / max_length;
    if (site->contador_de_palavras_chave >= max_palavras_chave) return FALSE;

    site_set_string(site->palavras_chave[site->contador_de_palavras_chave], palavra_chave, max_length);
    site->contador_de_palavras_chave++;

    return TRUE;
}