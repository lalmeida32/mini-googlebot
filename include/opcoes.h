#ifndef _OPCOES_H_
    #define _OPCOES_H_

    #include <TADlista.h>

    //funcao que chama a função correta com base no parâmetro opção
    // - Parâmetros
    //    -> lista_de_sites: estrutura a ser manipulada dentro das funções
    //    -> opcao: mapeada a uma função específica 
    // - Retorno
    //       não tem
    void chamar_opcao(LISTA *lista_de_sites, int opcao);

#endif