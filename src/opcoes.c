#include<stdlib.h>
#include<stdio.h>

#include"uteis.h"
#include"TADlista.h"
#include"TADsite.h"
#include"TADavl.h"
#include"TADpchave.h"
#include"TADpriorityqueue.h"

// Função para inserir a partir da entrada padrão (stdin) novo site em uma lista de sites
void inserir_site(LISTA *lista_de_sites, AVL *avl_de_palavras_chave) {
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

    // novo item pode ser adicionado
    ITEM *novo_item = item_criar(chave, site_criar());


    // leitura das informações sobre o site, conteúdo da estrutura novo_item
    printf("Nome: ");
    site_read_nome(item_get_conteudo(novo_item), stdin);
    
    printf("Relevância: ");
    site_read_relevancia(item_get_conteudo(novo_item), stdin);
    
    printf("Link: ");
    site_read_link(item_get_conteudo(novo_item), stdin);

    int contador_de_palavras_chave = 0;
    int continuar;
    
    // adicionando n palavras chave, até o máximo ser atingido ou até o usuário digitar algo diferente de '0'
    printf("Digite '-1' quando quiser parar de adicionar palavras-chave.\n");
    do {
        char *palavra_chave;
        printf("Chave [%d]: ", contador_de_palavras_chave);
        palavra_chave = ler_string(site_get_palavra_chave_max_length(), stdin);
        continuar = atoi(palavra_chave); 
        if (continuar != -1) {  
            site_add_palavra_chave(item_get_conteudo(novo_item), palavra_chave);
            contador_de_palavras_chave++;
        }

        free(palavra_chave);
    } while (continuar != -1 && contador_de_palavras_chave < site_get_palavras_chave_max_count());

    if (contador_de_palavras_chave == site_get_palavras_chave_max_count())
        printf("Voce ja atingiu o limite de palavras chave para esse site\n");

    // acrescentando o link à lista e verificando se foi mesmo possível adicioná-lo
    if (lista_inserir(lista_de_sites, novo_item)) {
        printf("Item inserido com sucesso!\n");
    }
    else {
        printf("Ocorreu um erro ao inserir este item!\n");
        item_apagar(&novo_item, (void (*) (void **)) &site_apagar);
    }

    SITE *novo_site = (SITE *) item_get_conteudo(novo_item);
    pchave_inserir_site_relacionado_em_avl(avl_de_palavras_chave, novo_site);

}

// Função que lẽ chave da entrada padrão (stdin) e o remove de uma lista de sites
void remover_site(LISTA *lista_de_sites, AVL *avl_de_palavras_chave) {
    int chave;

    printf("Chave: "); chave = ler_integer(stdin);

    // Exceção: Chave possui valor inválido
    if (chave < 0 || chave > 9999)
    {
        printf("Não foi possível inserir esse site. (Valor inválido para chave)\n");
        return;
    }

    // removendo site da lista e verificando se de fato ele foi removido
    if (lista_remover(lista_de_sites, chave, (void (*) (void **)) &site_apagar)) {
        printf("Item removido com sucesso!\n");
    }
    else {
        printf("Não foi possível remover este item!\n");
    }

}

// Função que lê uma chave e n palavras-chave da entrada padrão (stdin) e insere essas
// palavras-chave em determinado site em uma lista de sites
void inserir_palavra_chave(LISTA *lista_de_sites, AVL *avl_de_palavras_chave) {
    int chave, contador_de_palavras_chave, continuar;
    ITEM *item;

    // entrada da chave
    printf("Digite a chave do site que vc deseja inserir uma palavra-chave\n"); chave = ler_integer(stdin);
    
    // buscando pelo item a ter palavra-chave adicionada
    item = lista_busca(lista_de_sites, chave);

    if(item != NULL){
        //obtendo a quantidade de chaves do site
        contador_de_palavras_chave = site_get_num_palavras_chave(item_get_conteudo(item));

        if (contador_de_palavras_chave < site_get_palavras_chave_max_count()) {
            // adicionando n palavras chave, até o máximo ser atingido ou até o usuário digitar algo diferente de '0'
            printf("Digite '-1' quando quiser parar de adicionar palavras-chave.\n");
            do {
                char *palavra_chave;
                printf("Chave [%d]: ", contador_de_palavras_chave);
                palavra_chave = ler_string(site_get_palavra_chave_max_length(), stdin);
                continuar = atoi(palavra_chave); 
                if (continuar != -1) {
                    site_add_palavra_chave(item_get_conteudo(item), palavra_chave);
                    contador_de_palavras_chave++;
                }
                free(palavra_chave);
            } while (continuar != -1 && contador_de_palavras_chave < site_get_palavras_chave_max_count());
            if (contador_de_palavras_chave == site_get_palavras_chave_max_count())
                printf("Voce ja atingiu o limite de palavras chave para esse site\n");
        }
        else
            printf("Voce ja atingiu o limite de palavras chave para esse site\n");
    }
    else
        printf("Site nao encontrado\n");
}

// Função que lê uma chave e um valor inteiro da entrada padrão (stdin)
// e altera a relevância de um site em uma lista de sites
void atualizar_relevancia(LISTA *lista_de_sites, AVL *avl_de_palavras_chave) {
    int chave;
    ITEM *item;

    // entrada da chave
    printf("Digite a chave do site que vc deseja atualizar a relevancia\n"); chave = ler_integer(stdin);
    
    item = lista_busca(lista_de_sites, chave);

    // item encontrado
    if(item != NULL){
        printf("Relevância: ");
        site_read_relevancia(item_get_conteudo(item), stdin);
    }
    // item não encontrado
    else
        printf("Site nao encontrado\n");

}

// Função que chama a função correta com base no parâmetro opção
void chamar_opcao(LISTA *lista_de_sites, AVL *avl_de_palavras_chave, int opcao) {
    switch(opcao) {
        case 1:
            inserir_site(lista_de_sites, avl_de_palavras_chave);
            break;
        case 2:
            remover_site(lista_de_sites, avl_de_palavras_chave);
            break;
        case 3:
            inserir_palavra_chave(lista_de_sites, avl_de_palavras_chave);
            break;
        case 4:
            atualizar_relevancia(lista_de_sites, avl_de_palavras_chave);
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        default:
            printf("Opção inválida!\n");
    }
}