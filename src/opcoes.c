#include<stdlib.h>
#include<stdio.h>
#include<TADlista.h>
#include<TADsite.h>

void inserir_site(LISTA *lista_de_sites) {
    int chave;

    printf("Chave: "); scanf("%d", &chave); flush();

    // Exceção: Já existe um item com essa chave
    ITEM *item_encontrado = lista_busca(lista_de_sites, chave);

    if (item_encontrado) {
        printf("Não foi possível inserir esse site. (Chave já existente)\n");
        return;
    }

    // Exceção: Chave possui valor inválido
    if (chave < 0 || chave > 9999) {
        printf("Não foi possível inserir esse site. (Valor inválido para chave)\n");
        return;
    }

    ITEM *novo_item = item_criar(chave, site_criar());

    printf("Nome: ");
    site_read_nome(item_get_conteudo(novo_item), stdin);
    
    printf("Relevância: ");
    site_read_relevancia(item_get_conteudo(novo_item), stdin);
    
    printf("Link: ");
    site_read_link(item_get_conteudo(novo_item), stdin);

    int contador_de_palavras_chave = 0;

}

void remover_site(LISTA *lista_de_sites) {

}

void inserir_palavra_chave(LISTA *lista_de_sites) {

}

void atualizar_relevancia(LISTA *lista_de_sites) {

}

void chamar_opcao(LISTA *lista_de_sites, int opcao) {
    switch(opcao) {
        case 1:
            inserir_site(lista_de_sites);
            break;
        case 2:
            remover_site(lista_de_sites);
            break;
        case 3:
            inserir_palavra_chave(lista_de_sites);
            break;
        case 4:
            atualizar_relevancia(lista_de_sites);
            break;
        case 5:
            break;
        default:
            printf("Opção inválida!\n");
    }
}