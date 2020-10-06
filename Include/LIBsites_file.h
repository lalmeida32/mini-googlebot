#ifndef _LIBSITES_FILE_H_
    #define _LIBSITES_FILE_H

    #include <stdio.h>
    #include <TADlista.h>

    
    // - Parâmetros
    //    -> arquivo: arquivo googlebot.txt
    // - Retorno
    //    -> inteiro com o numero de sites dento do arquivo
    int conta_sites(FILE *arquivo);

    //funcao recebe o googlebot.txt e 
    // - Parâmetros
    //    -> arquivo: arquivo googlebot.txt
    //    -> num_sites: o numero de sites que eh obtido com a funcao conta_sites
    // - Retorno
    //      funcao retorna a lista com todos os sites
    LISTA *recebe_dados(FILE *arquivo, int num_sites);

#endif