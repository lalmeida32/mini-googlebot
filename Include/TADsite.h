#ifndef _SITE_H_
    #define _SITE_H_

    #define TRUE 1
    #define FALSE 0
    #define boolean int

    #include<stdio.h>

    typedef struct site_t SITE;

    SITE *site_criar();
    void site_apagar(SITE **site);

    int site_get_nome_max_length();
    int site_get_link_max_length();
    int site_get_palavra_chave_max_length();
    int site_get_palavras_chave_max_count();

    boolean site_set_nome(SITE *site, const char *nome);
    boolean site_set_relevancia(SITE *site, int relevancia);
    boolean site_set_link(SITE *site, const char *link);
    boolean site_add_palavra_chave(SITE *site, const char *palavra_chave);

    void site_read_nome(SITE *site, FILE *input);
    void site_read_relevancia(SITE *site, FILE *input);
    void site_read_link(SITE *site, FILE *input);
    void site_read_palavra_chave(SITE *site, FILE *input);

#endif
