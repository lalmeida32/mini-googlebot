#include<stdio.h>
#include<stdlib.h>
#include<item.h>
#include<site.h>

typedef struct {
    SITE *site;
} LIVRO;


void livro_apagar(LIVRO **livro) {

    if (!(*livro)) return;

    site_apagar(&(*livro)->site);
    free(*livro);
    *livro = NULL;

}

int main(void) {
    // LIVRO *livro = (LIVRO *) malloc(sizeof(LIVRO));

    // livro->site = site_criar();

    ITEM *item = item_criar(10, site_criar());

    item_apagar(&item, NULL);

    return 0;
}
