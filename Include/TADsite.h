#ifndef _SITE_H_
    #define _SITE_H_

    #define TRUE 1
    #define FALSE 0
    #define boolean int

    typedef struct site_t SITE;

    SITE *site_criar();
    void site_apagar(SITE **site);
    
    boolean site_set_nome(SITE *site, const char *nome);
    boolean site_set_relevancia(SITE *site, int relevancia);
    boolean site_set_link(SITE *site, const char *link);
    boolean site_add_palavra_chave(SITE *site, const char *palavra_chave);


#endif
