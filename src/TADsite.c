#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include<TADsite.h>
#include<uteis.h>

struct site_t {
    char nome[50];
    int relevancia;
    char link[100];
    char palavras_chave[10][50];
    int contador_de_palavras_chave;
};



void site_set_string(char *destination, const char *source, int max_length) {
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

    site_set_string(site->link, link, site_get_link_max_length());
    
    return TRUE;
}

boolean site_add_palavra_chave(SITE *site, const char *palavra_chave) {
    
    if (!site || !palavra_chave) return FALSE;
    
    if (site->contador_de_palavras_chave >= site_get_palavras_chave_max_count()) return FALSE;

    site_set_string(site->palavras_chave[site->contador_de_palavras_chave], palavra_chave, site_get_palavra_chave_max_length());
    site->contador_de_palavras_chave++;

    return TRUE;
}


int site_get_num_palavras_chave(SITE *site){
    if(site != NULL)
        return (site->contador_de_palavras_chave);
    return (-1);
}


void site_read_nome(SITE *site, FILE *input) {
    char *buffer_string = ler_string(site_get_nome_max_length(), input);
    site_set_nome(site, buffer_string); free(buffer_string);
}

void site_read_relevancia(SITE *site, FILE *input)
{
    site_set_relevancia(site, ler_integer(input));
}

void site_read_link(SITE *site, FILE *input) {
    char *buffer_string = ler_string(site_get_link_max_length(), input);
    site_set_link(site, buffer_string); free(buffer_string);
}

void site_read_palavra_chave(SITE *site, FILE *input) {
    char *buffer_string = ler_string(site_get_palavra_chave_max_length(), input);
    site_add_palavra_chave(site, buffer_string); free(buffer_string);
}

void site_imprimir(SITE *site, FILE *output) {
    fprintf(output, ",%s", site->nome);
    fprintf(output, ",%d", site->relevancia);
    fprintf(output, ",%s", site->link);
    for (int i = 0; i < site->contador_de_palavras_chave; i++)
        fprintf(output, ",%s", site->palavras_chave[i]);
    fprintf(output, "\n");
}