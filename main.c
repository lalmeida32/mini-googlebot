#include<stdio.h>
#include<stdlib.h>
#include<TADitem.h>
#include<TADsite.h>
#include<TADlista.h>

#define FILE_NAME "googlebot.txt"

int main(void) {

    LISTA *lista_de_sites = lista_criar();
    ler_arquivo_de_sites(FILE_NAME, lista_de_sites);

    
    int opcao;

    do {
        scanf("%d", &opcao);
        chamar_opcao(lista_de_sites, opcao);
    } while(opcao != 5);


    escrever_arquivo_de_sites(FILE_NAME, lista_de_sites);
    lista_apagar(&lista_de_sites, (void (*) (void **)) &site_apagar);

    return 0;
}
