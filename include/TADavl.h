#ifndef AVL_H
    #define AVL_H

    #define boolean int
    #define TRUE 1
    #define FALSE 0
    #define max(a, b) ((a > b) ? a : b)
    typedef struct avl AVL;



    // Criar avl na memória Heap
    // - Parâmetros
    //    -> não tem
    // - Retorno
    //    -> ponteiro para estrutura AVL, NULL se der erro
    AVL *avl_criar(void);

    // Apaga a AVL da memória Heap
    // - Parâmetros
    //    -> endereço da estrutura item a ser apagada
    // - Retorno
    //    void
    void avl_apagar(AVL **arvore);



    // Insere um dado na AVL
    // - Parâmetros
    //    -> arvore: AVL no qual deseja fazer a insercao
    //    -> dados: dado no qual deseja armazenar na AVL
    // - Retorno
    //    TRUE em caso de sucesso e FALSE caso nao consiga inserir
    boolean avl_inserir(AVL *arvore, void *dados);

    // Remove um dado na AVL
    // - Parâmetros
    //    -> arvore: AVL no qual deseja fazer a remocao
    //    -> chave: algum dado que identifique o no que deseja inserir
    // - Retorno
    //    TRUE em caso de sucesso e FALSE caso nao consiga remover
    boolean avl_remover(AVL *arvore, void *chave);

    // Realiza uma busca na AVL a procura de uma chave
    // - Parâmetros
    //    -> arvore: AVL no qual deseja realizar a busca
    //    -> chave: identificador de um dado de um no da arvore
    // - Retorno
    //      retorna um void * apontando para o dado buscado caso a busca seja bem sucedida, se não retona NULL
    void *avl_busca(AVL *avl, void *chave);



    // "setando" a função que apaga dados da memória
    // - Parâmetros
    //    -> arvore: AVL no qual deseja apagar o dado
    //    -> funcao que apaga os dados dentro de cada no da arvore
    // - Retorno
    //      void
    void avl_set_dados_apagar(AVL *avl, void (*dados_apagar)(void **));

    // "setando" a função que compara dados
    // - Parâmetros
    //    -> arvore: AVL no qual deseja comaparar os dados
    //    -> funcao que compara os dados dos nos da arvore
    // - Retorno
    //      void
    void avl_set_dados_comparar(AVL *avl, int (*dados_comparar)(void *, void *));

    // "setando" a função que imprime os dados
    // - Parâmetros
    //    -> arvore: AVL no qual deseja imprimir os dados
    //    -> funcao que imprime os dados dentro de cada no da arvore
    // - Retorno
    //      void
    void avl_set_dados_imprimir(AVL *avl, void (*dados_imprimir)(void *));



    // Printa a AVL a percorrendo no modo EM ORDEM. Cada elemento abaixo do outro (nenhuma representacao utilizada)
    // - Parâmetros
    //    -> arvore: AVL no qual deseja printar
    // - Retorno
    //      void
    void avl_print(AVL *arvore);



#endif