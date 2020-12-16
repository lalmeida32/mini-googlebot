#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<opcoes.h>
#include<TADitem.h>
#include<TADsite.h>
#include<TADlista.h>
#include<TADavl.h>
#include<TADpriorityqueue.h>
#include<sites_file.h>

// Nome dos arquivos de entrada e de saída
#define INPUT_FILE_NAME "googlebot.txt"
#define OUTPUT_FILE_NAME "googlebot_out.txt"

typedef struct {
    char *palavra_chave;
    PQUEUE *sites_relacionados;  
} PALAVRA_CHAVE_REF;

int palavras_chave_ref_comparar(void *dados1, void *dados2) {
    PALAVRA_CHAVE_REF *pchave_ref1 = (PALAVRA_CHAVE_REF *) dados1;
    PALAVRA_CHAVE_REF *pchave_ref2 = (PALAVRA_CHAVE_REF *) dados2;

    return strcmp(pchave_ref1->palavra_chave, pchave_ref2->palavra_chave);
}

void palavra_chave_ref_apagar(void **dados) {
    if (!dados || !(*dados)) return;

    free(*dados);
    *dados = NULL;
}

// Laço principal
int main(void) {
    FILE *fp;
    int num_sites, opcao;
    LISTA *lista_de_sites = NULL;

    // abrir lista de sites a partir de arquivo
    fp = fopen(INPUT_FILE_NAME, "r");
    num_sites = conta_sites(fp);
    lista_de_sites = recebe_dados(fp, num_sites);
    fclose(fp);

    AVL *avl_de_palavras_chave = avl_criar();
    avl_set_dados_comparar(avl_de_palavras_chave, &palavras_chave_ref_comparar);
    avl_set_dados_apagar(avl_de_palavras_chave, &palavra_chave_ref_apagar);

    // laço para as opções
    printf("Bem-vindo ao mini-googlebot!\n");
    do {
        printf("\n*** Menu ***\n");
        printf("1 - Inserir Site\n");
        printf("2 - Remover Site\n");
        printf("3 - Inserir Palavra-chave\n");
        printf("4 - Atualizar Relevância\n");
        printf("5 - Sair\n\n");

        scanf("%d", &opcao);
        chamar_opcao(lista_de_sites, opcao);
    } while(opcao != 5);


    // nova lista de sites modificadas salva no arquivo de saída
    printf("Aguarde enquanto os dados estão sendo gravados no arquivo de saída\n");
    if (gravar_dados(OUTPUT_FILE_NAME, lista_de_sites))
        printf("Dados gravados com sucesso!\n");
    else
        printf("Falha ao gravar dados...\n");

    // liberação de memória
    avl_apagar(&avl_de_palavras_chave);
    lista_apagar(&lista_de_sites, (void (*)(void **)) & site_apagar);

    return 0;
}
