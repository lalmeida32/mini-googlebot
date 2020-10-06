#include<stdio.h>
#include<stdlib.h>
#include<opcoes.h>
#include<TADitem.h>
#include<TADsite.h>
#include<TADlista.h>
#include<sites_file.h>

#define FILE_NAME "googlebot.txt"

int main(void) {
    FILE *fp;
    int num_sites, opcao;
    LISTA *lista_de_sites = NULL;

    fp = fopen(FILE_NAME, "r");

    
    num_sites = conta_sites(fp);

    lista_de_sites = recebe_dados(fp, num_sites);
    
    // do {
    //     scanf("%d", &opcao);
    //     chamar_opcao(lista_de_sites, opcao);
    // } while(opcao != 5);

    chamar_opcao(lista_de_sites, 1);
    chamar_opcao(lista_de_sites, 1);
    chamar_opcao(lista_de_sites, 1);
    chamar_opcao(lista_de_sites, 1);

    lista_imprimir(lista_de_sites); printf("\n\n");
    site_imprimir(item_get_conteudo(lista_busca(lista_de_sites, 4)));
    site_imprimir(item_get_conteudo(lista_busca(lista_de_sites, 8)));

    lista_apagar(&lista_de_sites, (void (*)(void **)) & site_apagar);

    fclose(fp);

    return 0;
}
