#include<stdio.h>
#include<stdlib.h>
#include<TADitem.h>
#include<TADsite.h>
#include<TADlista.h>
#include<sites_file.h>

#define FILE_NAME "googlebot.txt"

int main(void) {
    FILE *fp;
    int num_sites, opcao;
    LISTA *lista_de_sites;

    fp = fopen(FILE_NAME, "r");
    num_sites = conta_sites(fp);

    lista_de_sites = recebe_dados(fp, num_sites);


    // do {
    //     scanf("%d", &opcao);
    //     chamar_opcao(lista_de_sites, opcao);
    // } while(opcao != 5);

    lista_apagar(&lista_de_sites, (void (*) (void **)) &site_apagar);

    return 0;
}
