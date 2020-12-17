#ifndef _LIBSITES_FILE_H_
    #define _LIBSITES_FILE_H

    #include <stdio.h>
    #include "TADlista.h"

    // Função que conta o número de sites de um arquivo
    // - Parâmetros
    //    -> arquivo: arquivo googlebot.txt
    // - Retorno
    //    -> inteiro com o numero de sites dento do arquivo
    int conta_sites(FILE *arquivo);

    // Função que recebe os sites e seus dados do googlebot.txt e os insere na lista como item,
    // além de inserir palavra chave na AVL
    // - Parâmetros
    //    -> arquivo: arquivo googlebot.txt
    //    -> num_sites: o numero de sites que eh obtido com a funcao conta_sites
    //    -> lista_de_sites: a lista onde os sites serão inseridos
    //    -> avl_de_palavras_chave: a AVL aonde as palavras chave serão inseridas
    // - Retorno
    //      não tem
    void recebe_dados(FILE *arquivo, int num_sites, LISTA **lista_de_sites, AVL **avl_de_palavras_chave);

    // Função que recebe grava os dados de uma lista de sites em um arquivo
    // - Parâmetros
    //    -> arquivo: o nome do arquivo onde os dados serão gravados
    //    -> lista_de_sites: lista contendo todos os sites no programa
    // - Retorno
    //      TRUE caso os dados tenham sido gravados com sucesso e FALSE caso contrário
    boolean gravar_dados(const char *filename_saida, LISTA *lista_de_sites);

#endif