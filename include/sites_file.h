#ifndef _LIBSITES_FILE_H_
    #define _LIBSITES_FILE_H

    #include <stdio.h>
    #include "TADlista.h"

    
    // - Parâmetros
    //    -> arquivo: arquivo googlebot.txt
    // - Retorno
    //    -> inteiro com o numero de sites dento do arquivo
    int conta_sites(FILE *arquivo);

    //funcao que recebe os sites e seus dados do googlebot.txt e os insere na lista como item
    // - Parâmetros
    //    -> arquivo: arquivo googlebot.txt
    //    -> num_sites: o numero de sites que eh obtido com a funcao conta_sites
    // - Retorno
    //      funcao retorna a lista com todos os sites
    LISTA *recebe_dados(FILE *arquivo, int num_sites);

    //funcao que recebe grava os dados de uma lista de sites em um arquivo
    // - Parâmetros
    //    -> arquivo: o nome do arquivo onde os dados serão gravados
    //    -> lista_de_sites: lista contendo todos os sites no programa
    // - Retorno
    //      TRUE caso os dados tenham sido gravados com sucesso e FALSE caso contrário
    boolean gravar_dados(const char *filename_saida, LISTA *lista_de_sites);

#endif