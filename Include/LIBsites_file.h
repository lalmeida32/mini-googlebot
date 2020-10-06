#ifndef _LIBSITES_FILE_H_
    #define _LIBSITES_FILE_H

    #include <stdio.h>
    #include <TADlista.h>

    //funcao vai receber o arquivo googlebot.txt e contar quantos sites tem no arquivo
    int conta_sites(FILE *arquivo);

    //funcao recebe o googlebot.txt e o numero de sites que eh obtido com a funcao conta_sites
    //funcao retorna a lista com todos os sites
    LISTA *recebe_dados(FILE *arquivo, int num_sites);

#endif