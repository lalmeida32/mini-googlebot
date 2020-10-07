#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TADitem.h>
#include <TADlista.h>
#include <TADsite.h>
#include <sites_file.h>


char *readline(FILE *stream) {
    char *string = (char *) malloc(700);
    int pos = 0;
    do{
        string[pos] = (char) fgetc(stream);
    }while(string[pos] != '\n' && !feof(stream) && ++pos);

    string[pos] = '\0';

    return string;
}

int conta_sites(FILE *arquivo){
    int num_sites = 1;

    while(!feof(arquivo)){
        char c = fgetc(arquivo);
        //se n for de fato o fim do arquvo e encontrar um \n contamos um site
        if(!feof(arquivo) && c == '\n')
            num_sites++;
    }
    return num_sites;
}


//funcao que separa os dados e os atribui para o item
ITEM *separa_dados(char *dados){
    ITEM *item;
    char *token;
    int aux, i = 1;
    //sabemos quais sao as informacoes de um site e a ordem: Chave, Nome, Relevancia, link, Palavras-chave
    //obtendo a chave
    token = strtok(dados, ",");
    aux = atoi(token);
    item = item_criar(aux, site_criar());

    //obtendo os outros dados
    while( token != NULL ){
        token = strtok(NULL, ",");
        if(i == 1)
            site_set_nome(item_get_conteudo(item), token);
        else if(i == 2){
            aux = atoi(token);
            site_set_relevancia(item_get_conteudo(item), aux);
        }
        else if(i == 3)
            site_set_link(item_get_conteudo(item), token);
        else
            site_add_palavra_chave(item_get_conteudo(item), token);
        i++;
   }
   return item;
}


//funcao que recebe os dados do googlebot.txt e os insere na lista
LISTA *recebe_dados(FILE *arquivo, int num_sites){
    char *dados_site;
    int i = 0;
    ITEM *item;
    LISTA *lista = lista_criar();

    //posicionando o cursor no inicio do arquivo
    fseek(arquivo, 0, SEEK_SET);

    //lendo os dados do arquivo
    while(i < num_sites){            
        dados_site = readline(arquivo);
        item = separa_dados(dados_site);
        lista_inserir(lista, item);
        i++;
        free(dados_site);
    }
    return lista;
}  


boolean gravar_dados(const char* filename_saida, LISTA *lista_de_sites) {
    
    FILE *arquivo_de_saida = fopen(filename_saida, "w");
    if (!arquivo_de_saida) return FALSE;

    ITEM **vetor = lista_converter_para_vetor(lista_de_sites);
    if (!vetor) {
        fclose(arquivo_de_saida);
        return FALSE;
    }

    for (int i = 0; i < lista_tamanho(lista_de_sites); i++) {
        fprintf(arquivo_de_saida, "%04d,", item_get_chave(vetor[i]));
        site_imprimir(item_get_conteudo(vetor[i]), arquivo_de_saida);
    }


    fclose(arquivo_de_saida);
    free(vetor);
    return TRUE;
}
