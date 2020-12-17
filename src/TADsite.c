#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include"TADsite.h"
#include"uteis.h"
struct site_t {
    char nome[50];
    int relevancia;
    char link[100];
    char palavras_chave[10][50];
    int contador_de_palavras_chave;
};




// Retorna o comprimento máximo da propriedade "nome" da estrutura SITE
int site_get_nome_max_length() {
    return sizeof(((SITE *) NULL)->nome);
}

// Retorna o comprimento máximo da propriedade "link" da estrutura SITE
int site_get_link_max_length() {
    return sizeof(((SITE *) NULL)->link);
}

// Retorna o comprimento máximo das palavras-chave da estrutura SITE
int site_get_palavra_chave_max_length() {
    return sizeof(*(((SITE *) NULL)->palavras_chave));
}

// Retorna a quantidade máxima de palavras-chave que a estrutura SITE pode ter
int site_get_palavras_chave_max_count() {
    return sizeof(((SITE *)NULL)->palavras_chave) / site_get_palavra_chave_max_length();
}



// Cria a estrutura site na memória HEAP
SITE *site_criar() {
    SITE *site = (SITE *) malloc(sizeof(SITE));
    if (!site) return NULL;

    // atributos iniciais arbitrários
    site->nome[0] = '\0';
    site->relevancia = -1;
    site->link[0] = '\0';
    site->contador_de_palavras_chave = 0;

    return site;
}

// Desaloca a memória HEAP alocada pelo site
void site_apagar(SITE **site) {

    if (!(*site)) return;

    free(*site);
    *site = NULL;

}

// Altera a propriedade "nome" de uma estrutura SITE
boolean site_set_nome(SITE *site, const char *nome) {
    
    if (!site || !nome) return FALSE;

    set_string(site->nome, nome, site_get_nome_max_length());

    return TRUE;
}

// Altera a propriedade "relevância" de uma estrutura SITE
boolean site_set_relevancia(SITE *site, int relevancia) {

    if (!site || relevancia < 0 || relevancia > 1000) return FALSE;

    site->relevancia = relevancia;
    
    return TRUE;
}

// Altera a propriedade "link" de uma estrutura SITE
boolean site_set_link(SITE *site, const char *link) {

    if (!site || !link) return FALSE;

    set_string(site->link, link, site_get_link_max_length());
    
    return TRUE;
}

// Adiciona uma palavra-chave à uma estrutura SITE, se for possível
boolean site_add_palavra_chave(SITE *site, const char *palavra_chave) {
    
    if (!site || !palavra_chave) return FALSE;
    
    // limite de palavras-chave atingido
    if (site->contador_de_palavras_chave >= site_get_palavras_chave_max_count()) return FALSE;

    // adicionadno palavra-chave
    set_string(site->palavras_chave[site->contador_de_palavras_chave], palavra_chave, site_get_palavra_chave_max_length());
    site->contador_de_palavras_chave++;

    return TRUE;
}



// Retorna a quantidade de palavras-chave que existem em determinada estrutura SITE
int site_get_num_palavras_chave(SITE *site){
    if(site != NULL)
        return (site->contador_de_palavras_chave);
    return (-1);
}


char *site_get_palavra_chave(SITE *site, int index) {
    if (!site || index >= site->contador_de_palavras_chave) return NULL;

    return site->palavras_chave[index];
}

char *site_get_link(SITE *site) {
    if (!site) return NULL;

    return site->link;
}

char *site_get_nome(SITE *site) {
    if (!site) return NULL;

    return site->nome;
}


// Ler e alterar nome de um determinado site
void site_read_nome(SITE *site, FILE *input) {
    char *buffer_string = ler_string(site_get_nome_max_length(), input);
    site_set_nome(site, buffer_string); free(buffer_string);
}

// Ler e alterar relevância de um determinado site
void site_read_relevancia(SITE *site, FILE *input)
{
    site_set_relevancia(site, ler_integer(input));
}

// Ler e alterar link de um determinado site
void site_read_link(SITE *site, FILE *input) {
    char *buffer_string = ler_string(site_get_link_max_length(), input);
    site_set_link(site, buffer_string); free(buffer_string);
}

// Ler e adicionar palavra-chave à determinado site
void site_read_palavra_chave(SITE *site, FILE *input) {
    char *buffer_string = ler_string(site_get_palavra_chave_max_length(), input);
    site_add_palavra_chave(site, buffer_string); free(buffer_string);
}



// Imprime em um arquivo as informações sobre determinado site no formato CSV
void site_imprimir(SITE *site, FILE *output) {
    if (!site) return;
    
    fprintf(output, "%s", site->nome);
    fprintf(output, ",%d", site->relevancia);
    fprintf(output, ",%s", site->link);
    for (int i = 0; i < site->contador_de_palavras_chave; i++) // passsa por todas as palavras-chave
        fprintf(output, ",%s", site->palavras_chave[i]);
}


//compara a relevancia entre dois sites
int site_comparar_relevancia(void *dados1, void *dados2) {
    //fazendo o casting nos dados, transformando eles para sites
    SITE *site1 = (SITE *) dados1;
    SITE *site2 = (SITE *) dados2;

    return site1->relevancia - site2->relevancia;
}

//comapara o link dos sites
int site_comparar_link(void *dados1, void *dados2) {
    //fazendo o casting nos dados, transformando eles para sites
    SITE *site1 = (SITE *) dados1;
    SITE *site2 = (SITE *) dados2;

    return strcmp(site1->link, site2->link);
}

