#include<stdio.h>
#include<stdlib.h>
#include<opcoes.h>
#include<TADitem.h>
#include<TADsite.h>
#include<TADlista.h>
#include<sites_file.h>

#define INPUT_FILE_NAME "googlebot.txt"
#define OUTPUT_FILE_NAME "googlebot_out.txt"

int main(void) {
    FILE *fp;
    int num_sites, opcao;
    LISTA *lista_de_sites = NULL;

    fp = fopen(INPUT_FILE_NAME, "r");
    num_sites = conta_sites(fp);
    lista_de_sites = recebe_dados(fp, num_sites);
    fclose(fp);

    printf("Bem-vindo ao mini-googlebot!\n\n");
    do {
        printf("*** Menu ***\n");
        printf("1 - Inserir Site\n");
        printf("2 - Remover Site\n");
        printf("3 - Inserir Palavra-chave\n");
        printf("4 - Atualizar Relevância\n");
        printf("5 - Sair\n");

        scanf("%d", &opcao);
        chamar_opcao(lista_de_sites, opcao);
    } while(opcao != 5);

    printf("Aguarde enquanto os dados estão sendo gravados no arquivo de saída\n");
    if (gravar_dados(OUTPUT_FILE_NAME, lista_de_sites))
        printf("Dados gravados com sucesso!\n");
    else
        printf("Falha ao gravar dados...\n");



    lista_apagar(&lista_de_sites, (void (*)(void **)) & site_apagar);

    return 0;
}
