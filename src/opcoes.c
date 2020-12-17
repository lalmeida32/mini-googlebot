#include<stdlib.h>
#include<stdio.h>

#include"uteis.h"
#include"TADlista.h"
#include"TADsite.h"
#include"TADavl.h"
#include"TADpchave.h"
#include"TADpriorityqueue.h"




// Função para inserir a partir da entrada padrão (stdin) novo site em uma lista de sites
// e avl de palavras-chave
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
    if (!lista_inserir(lista_de_sites, novo_item)) {
        printf("Ocorreu um erro ao inserir este item!\n");
        item_apagar(&novo_item, (void (*) (void **)) &site_apagar);
        return;
    }
    
    printf("Item inserido com sucesso!\n");

    // acrescentando site na avl de palavras chave
    SITE *novo_site = (SITE *) item_get_conteudo(novo_item);
    pchave_insere_site_na_avl(avl_de_palavras_chave, novo_site);

}

// Função que lẽ chave da entrada padrão (stdin) e o remove de uma lista de sites e avl de palavras-chave
void remover_site(LISTA *lista_de_sites, AVL *avl_de_palavras_chave) {
    int chave;

    printf("Chave: "); chave = ler_integer(stdin);

    // Exceção: Chave possui valor inválido
    if (chave < 0 || chave > 9999)
    {
        printf("Não foi possível inserir esse site. (Valor inválido para chave)\n");
        return;
    }

    // Procura por item pra ver se existe
    ITEM *item = lista_busca(lista_de_sites, chave);
    if (!item) {
        printf("Não foi possível encontrar esse item!\n");
        return;
    }

    // Remove o site da avl
    SITE *site = (SITE *) item_get_conteudo(item);
    pchave_remove_site_na_avl(avl_de_palavras_chave, site);

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

        SITE *site = (SITE *) item_get_conteudo(item);

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

                    // Adiciona a palavra-chave à avl
                    pchave_insere_site_na_avl_para_palavra_chave_especifica(avl_de_palavras_chave, site, palavra_chave);
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

        SITE *site = (SITE *) item_get_conteudo(item);

        printf("Relevância: ");

        // Removendo site da avl e o adicionando de volta para garantir que a relevância foi atualizada
        pchave_remove_site_na_avl(avl_de_palavras_chave, site);
        site_read_relevancia(item_get_conteudo(item), stdin);
        pchave_insere_site_na_avl(avl_de_palavras_chave, site);

        return;
    }
    // item não encontrado
    printf("Site nao encontrado\n");

}

// Função que busca por sites relacionados com a palavra-chave digitada
void buscar_por_palavra_chave(LISTA *lista_de_sites, AVL *avl_de_palavras_chave) {
    
    // entrada da palavra-chave
    flush(stdin);
    printf("\nDigite a palavra-chave: ");
    char *palavra_chave = ler_string(site_get_palavra_chave_max_length(), stdin);
    PALAVRA_CHAVE_REF *pchave_ref = pchave_ref_busca_em_avl(avl_de_palavras_chave, palavra_chave);
    free(palavra_chave);

    // Conferindo possíveis erros
    if (!pchave_ref) {
        printf("\nPalavra-chave não possui sites relacionados!\n\n");
        return;
    }

    PQUEUE *sites_relacionados = pchave_get_sites_relacionados(pchave_ref);
    if (!sites_relacionados) {
        printf("\nOcorreu um erro: chave encontrada mas priority queue é inexistente!\n\n");
        return;
    }

    if (pqueue_get_quantidade(sites_relacionados) == 0) {
        printf("\nPalavra-chave não possui sites relacionados!\n\n");
        return;
    }

    // Criando estrutura auxiliar para não perder os dados da PQUEUE de sites_relacionados
    PQUEUE *sites_relacionados_auxiliar = pqueue_criar();
    pqueue_set_dados_comparar(sites_relacionados_auxiliar, &site_comparar_relevancia);

    int site_index = 1;

    // Removendo sites da sites_relacionados e os adicionando na sites_relacionados_auxiliar
    printf("\n");
    while (pqueue_get_quantidade(sites_relacionados)) {

        SITE *site = pqueue_get_topo(sites_relacionados);

        // Antes de remover, exibir o nome e o link do site com maior relevância, já
        // que a pqueue está ordenada assim
        printf("SITE %d\n", site_index);
        printf("Nome: %s\n", site_get_nome(site));
        printf("Link: %s\n", site_get_link(site));
        printf("\n");

        pqueue_inserir(sites_relacionados_auxiliar, site);
        pqueue_remover(sites_relacionados);

        site_index++;
    }
    
    // Alterando referência da pchave_ref para a sites_relacionados_auxiliar
    pchave_set_sites_relacionados(pchave_ref, sites_relacionados_auxiliar);
    pqueue_free(&sites_relacionados);

}

void sugestao_de_sites(LISTA *lista_de_sites, AVL *avl_de_palavras_chave) {

    // a) buscar a palavra fornecida entre as palavras-chave de cada site, selecionando aqueles que a contém

    flush(stdin);
    printf("\nDigite a palavra-chave: ");
    char *palavra_chave = ler_string(site_get_palavra_chave_max_length(), stdin);
    PALAVRA_CHAVE_REF *pchave_ref = pchave_ref_busca_em_avl(avl_de_palavras_chave, palavra_chave);
    free(palavra_chave);

    // Conferindo erros
    if (!pchave_ref) {
        printf("\nPalavra-chave não possui sites relacionados!\n\n");
        return;
    }

    PQUEUE *sites_relacionados = pchave_get_sites_relacionados(pchave_ref);
    if (!sites_relacionados) {
        printf("\nOcorreu um erro: chave encontrada mas priority queue é inexistente!\n\n");
        return;
    }

    if (pqueue_get_quantidade(sites_relacionados) == 0) {
        printf("\nPalavra-chave não possui sites relacionados!\n\n");
        return;
    }


    // Criando estruturas auxiliares
    
    PQUEUE *pqueue_sites_sugestao = pqueue_criar(); // Resposta final
    pqueue_set_dados_comparar(pqueue_sites_sugestao, &site_comparar_relevancia);

    AVL *avl_sites_sugestao = avl_criar(); // Armazenando sites para que não haja repetição
    avl_set_dados_comparar(avl_sites_sugestao, &site_comparar_link);

    PQUEUE *sites_relacionados_auxiliar = pqueue_criar(); // Auxiliar para não perder dados da sites_relacionados original
    pqueue_set_dados_comparar(sites_relacionados_auxiliar, &site_comparar_relevancia);
    
    PQUEUE *sites_relacionados_copy = pqueue_criar(); // Cópia dos dados da sites_relacionados
    pqueue_set_dados_comparar(sites_relacionados_copy, &site_comparar_relevancia);

    // Copiando dados da sites_relacionados para sites_relacionados_copy e pra sites_relacionados_auxiliar
    // À medida que se adiciona sites nessas duas estruturas, são removidos sites da original, já que é uma pqueue
    while (pqueue_get_quantidade(sites_relacionados)) {
        SITE *site_atual = pqueue_get_topo(sites_relacionados);
        pqueue_inserir(sites_relacionados_copy, site_atual);
        pqueue_inserir(sites_relacionados_auxiliar, site_atual);
        pqueue_remover(sites_relacionados);
    }

    // Alterando referência de pchave_ref para sites_relacionados_auxiliar
    pchave_set_sites_relacionados(pchave_ref, sites_relacionados_auxiliar);
    pqueue_free(&sites_relacionados);

    // b) coletar todas as palavras-chave dos sites selecionados no passo “a”

    // Para cada site nos sites relacionados 
    while (pqueue_get_quantidade(sites_relacionados_copy)) {
        SITE *site_atual = pqueue_get_topo(sites_relacionados_copy);

        // Para cada palavra chave nos sites
        for (int i = 0; i < site_get_num_palavras_chave(site_atual); i++) {
            
            // Procura a palavra-chave na AVL
            char *palavra_chave_atual = site_get_palavra_chave(site_atual, i);
            PALAVRA_CHAVE_REF *pchave_ref_atual = pchave_ref_busca_em_avl(avl_de_palavras_chave, palavra_chave_atual);


            // c) buscar os sites que contêm alguma das palavras-chave identificadas no passo “b”

            // Cria uma estrutura auxiliar para não perder dados da PQUEUE original (sites_relacionados_com_chave_atual)
            PQUEUE *sites_relacionados_com_chave_atual = pchave_get_sites_relacionados(pchave_ref_atual);
            PQUEUE *sites_relacionados_com_chave_atual_auxiliar = pqueue_criar();
            pqueue_set_dados_comparar(sites_relacionados_com_chave_atual_auxiliar, &site_comparar_relevancia);

            // Para cada site relacionado com a palavra chave atual
            while (pqueue_get_quantidade(sites_relacionados_com_chave_atual)) {
                SITE *site_relacionado_com_atual = pqueue_get_topo(sites_relacionados_com_chave_atual);
                
                // Se o site já não foi inserido
                if (!avl_busca(avl_sites_sugestao, site_relacionado_com_atual)) {
                    avl_inserir(avl_sites_sugestao, site_relacionado_com_atual);  // Inserir na AVL de sites para verificar se já foi adicionado
                    pqueue_inserir(pqueue_sites_sugestao, site_relacionado_com_atual);  // Inserir na PQUEUE de sites, que será a resposta final 
                }
                
                // À medida que insere dados na auxiliar, remove dados da original
                pqueue_inserir(sites_relacionados_com_chave_atual_auxiliar, site_relacionado_com_atual);
                pqueue_remover(sites_relacionados_com_chave_atual);
            }

            // Altera referência dos sites_relacionados da pchave_ref_atual para auxiliar
            pchave_set_sites_relacionados(pchave_ref_atual, sites_relacionados_com_chave_atual_auxiliar);
            pqueue_free(&sites_relacionados_com_chave_atual);

        }

        // Vai removendo os sites da sites_relacionados_copy, fazendo uma espécie de "iteração"
        pqueue_remover(sites_relacionados_copy);
    }


    // Liberação de memória das estruturas auxiliares que não serão mais usadas

    avl_apagar(&avl_sites_sugestao);
    pqueue_free(&sites_relacionados_copy);


    // d) mostrar o nome e o link dos cinco (5) sites mais relevantes ordenados por relevância (decrescente)

    // Sites são mostrados por relevância já que se trata de uma priority queue
    for (int i = 1; i <= 5 && pqueue_get_quantidade(pqueue_sites_sugestao) > 0; i++) {
        SITE *site_sugerido = pqueue_get_topo(pqueue_sites_sugestao);
        printf("SITE %d\n", i);
        printf("Nome: %s\n", site_get_nome(site_sugerido));
        printf("Link: %s\n", site_get_link(site_sugerido));
        printf("\n");
        pqueue_remover(pqueue_sites_sugestao);
    }

    pqueue_free(&pqueue_sites_sugestao);

}

// Função que chama a função correta com base no parâmetro opção
void chamar_opcao(LISTA *lista_de_sites, AVL *avl_de_palavras_chave, int opcao) {

    void (*funcao_selecionada) (LISTA *, AVL *) = NULL;

    switch(opcao) {
        case 1:
            funcao_selecionada = &inserir_site;
            break;
        case 2:
            funcao_selecionada = &remover_site;
            break;
        case 3:
            funcao_selecionada = &inserir_palavra_chave;
            break;
        case 4:
            funcao_selecionada = &atualizar_relevancia;
            break;
        case 5:
            funcao_selecionada = &buscar_por_palavra_chave;
            break;
        case 6:
            funcao_selecionada = &sugestao_de_sites;
            break;
        case 7:
            break;
        default:
            printf("Opção inválida!\n");
    }

    if (funcao_selecionada)
        funcao_selecionada(lista_de_sites, avl_de_palavras_chave);
}