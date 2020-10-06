#include<stdlib.h>
#include<stdio.h>

#include<uteis.h>
#include<TADlista.h>
#include<TADsite.h>

void inserir_site(LISTA *lista_de_sites) {
    int chave;

    printf("Chave: "); chave = ler_integer(stdin);

    // Exceção: Chave possui valor inválido
    if (chave < 0 || chave > 9999) {
        printf("Não foi possível inserir esse site. (Valor inválido para chave)\n");
        return;
    }

    // Exceção: Já existe um item com essa chave
    ITEM *item_encontrado = lista_busca(lista_de_sites, chave);

    if (item_encontrado) {
        printf("Não foi possível inserir esse site. (Chave já existente)\n");
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
    int continuar;
    
    printf("Digite '0' quando quiser parar de adicionar palavras-chave.\n");
    do {
        printf("Continuar? (Digite '1') "); continuar = ler_integer(stdin); 
        if (continuar) {
            printf("Chave [%d]: ", contador_de_palavras_chave + 1);
            site_read_palavra_chave(item_get_conteudo(novo_item), stdin);
        }
        contador_de_palavras_chave++;
    } while (continuar && contador_de_palavras_chave < site_get_palavras_chave_max_count());

    if (lista_inserir(lista_de_sites, novo_item)) {
        printf("Item inserido com sucesso!\n");
    }
    else {
        printf("Ocorreu um erro ao inserir este item!\n");
        item_apagar(&novo_item, (void (*) (void **)) &site_apagar);
    }


}

void remover_site(LISTA *lista_de_sites) {
    int chave;

    printf("Chave: ");
    chave = ler_integer(stdin);

    // Exceção: Chave possui valor inválido
    if (chave < 0 || chave > 9999)
    {
        printf("Não foi possível inserir esse site. (Valor inválido para chave)\n");
        return;
    }

    if (lista_remover(lista_de_sites, chave, (void (*) (void **)) &site_apagar)) {
        printf("Item removido com sucesso!\n");
    }
    else {
        printf("Não foi possível remover este item!\n");
    }

}

void inserir_palavra_chave(LISTA *lista_de_sites) {
    int chave, contador_de_palavras_chave, continuar;
    ITEM *item;

    printf("Digite a chave do site que vc deseja inserir uma palavra-chave\n"); chave = ler_integer(stdin);
    
    item = lista_busca(lista_de_sites, chave);

    if(item != NULL){
        //obtendo a quantidade de chaves do site
        contador_de_palavras_chave = site_get_num_palavras_chave(item_get_conteudo(item));

        if(contador_de_palavras_chave < 10){
            printf("Digite '0' quando quiser parar de adicionar palavras-chave.\n");
            do {
                printf("Continuar? (Digite '1') "); continuar = ler_integer(stdin); 
                if (continuar) {
                    printf("Chave [%d]: ", contador_de_palavras_chave + 1);
                    site_read_palavra_chave(item_get_conteudo(item), stdin);
                }
                contador_de_palavras_chave++;
            } while (continuar && contador_de_palavras_chave < site_get_palavras_chave_max_count());
        }
        else
            printf("Voce ja atingiu o limite de palavras chave para esse site\n");
    }
    else
        printf("Site nao encontrado");

}

void atualizar_relevancia(LISTA *lista_de_sites) {
    int chave;
    ITEM *item;

    printf("Digite a chave do site que vc deseja atualizar a relevancia\n"); chave = ler_integer(stdin);
    
    item = lista_busca(lista_de_sites, chave);

    if(item != NULL){
        printf("Relevância: ");
        site_read_relevancia(item_get_conteudo(item), stdin);
    }
    else
        printf("Site nao encontrado");

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