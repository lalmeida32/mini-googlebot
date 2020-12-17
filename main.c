#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<opcoes.h>
#include<TADitem.h>
#include<TADsite.h>
#include<TADlista.h>
#include<TADavl.h>
#include<TADpriorityqueue.h>
#include<TADpchave.h>
#include<sites_file.h>

// Nome dos arquivos de entrada e de saída
#define INPUT_FILE_NAME "googlebot.txt"
#define OUTPUT_FILE_NAME "googlebot_out.txt"

// Laço principal
int main(void) {
    FILE *fp;
    int num_sites, opcao;
    LISTA *lista_de_sites = NULL;
    AVL *avl_de_palavras_chave = NULL;

    // abrir lista de sites a partir de arquivo
    fp = fopen(INPUT_FILE_NAME, "r");
    num_sites = conta_sites(fp);
    recebe_dados(fp, num_sites, &lista_de_sites, &avl_de_palavras_chave);
    fclose(fp);

    avl_print(avl_de_palavras_chave);

    // laço para as opções
    printf("Bem-vindo ao mini-googlebot!\n");
    do {
        printf("\n*** Menu ***\n");
        printf("1 - Inserir Site\n");
        printf("2 - Remover Site\n");
        printf("3 - Inserir Palavra-chave\n");
        printf("4 - Atualizar Relevância\n");
        printf("5 - Buscar por Palavra-chave\n");
        printf("6 - Sugestão de Sites\n");
        printf("7 - Sair\n\n");

        scanf("%d", &opcao);
        chamar_opcao(lista_de_sites, avl_de_palavras_chave, opcao);
    } while(opcao != 7);

    avl_print(avl_de_palavras_chave);

    // nova lista de sites modificadas salva no arquivo de saída
    printf("Aguarde enquanto os dados estão sendo gravados no arquivo de saída\n");
    if (gravar_dados(OUTPUT_FILE_NAME, lista_de_sites))
        printf("Dados gravados com sucesso!\n");
    else
        printf("Falha ao gravar dados...\n");

    // liberação de memória
    avl_apagar(&avl_de_palavras_chave);
    lista_apagar(&lista_de_sites, (void (*)(void **)) &site_apagar);

    return 0;
}
