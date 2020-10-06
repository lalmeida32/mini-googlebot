#include<stdlib.h>
#include<stdio.h>
#include<TADlista.h>
#include<TADsite.h>

void inserir_site(LISTA *lista_de_sites) {
    int chave;

    printf("Chave: "); scanf("%d", &chave);

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
    char *buffer_string;
    int buffer_integer;

    // Adicionando o nome
    printf("Nome: "); buffer_string = ler_string(site_get_nome_max_length(), stdin);
    site_set_nome(item_get_conteudo(novo_item), buffer_string); free(buffer_string);

    // Adicionando a relevância
    printf("Relevância: "); scanf("%d", &buffer_integer);
    site_set_relevancia(item_get_conteudo(novo_item), buffer_integer);

    // Adicionando o link
    printf("Link: "); buffer_string = ler_string(site_get_link_max_length(), stdin);
    site_set_link(item_get_conteudo(novo_item), buffer_string); free(buffer_string);

    // Adicionando as palavras-chave
    int contador_de_palavras_chave = 0;
    printf("Digite as palavras-chave, separando-as por uma quebra de linha\n");
    printf("Para interromper, aperte enter sem ter passado nenhum conteúdo antes\n");
    do {
        printf("Chave [%d]: ", contador_de_palavras_chave + 1);
        buffer_string = ler_string(site_get_palavra_chave_max_length(), stdin);
        site_add_palavra_chave(item_get_conteudo(novo_item), buffer_string);
        free(buffer_string);
        contador_de_palavras_chave++;
    } while(contador_de_palavras_chave < site_get_palavras_chave_max_count());
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