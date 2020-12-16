#ifndef _ITEM_H_
    #define _ITEM_H_

    #define TRUE 1
    #define FALSE 0
    #define boolean int

    typedef struct item_t ITEM;




    // Criar item na memória Heap
    // - Parâmetros
    //    -> chave: identificador do item
    //    -> conteudo: ponteiro para o conteúdo do item
    // - Retorno
    //    -> ponteiro para estrutura item, NULL se der erro
    ITEM *item_criar(int chave, void *conteudo);



    // Apagar item da memória Heap e fixar o valor NULL na variável que o armazenava
    // - Parâmetros
    //    -> item: endereço da estrutura item a ser apagada
    //    -> apagar_conteudo: ponteiro para função que apaga conteúdo do item
    // - Retorno
    //    void
    void item_apagar(ITEM **item, void (*apagar_conteudo) (void **conteudo));




    // Receber a chave de um item
    // - Parâmetros
    //    -> item
    // - Retorno
    //    -> chave do item (em caso de erro, retorna -1)
    int item_get_chave(ITEM *item);




    // Receber a chave de um item
    // - Parâmetros
    //    -> item
    //    -> erro: se diferente de nulo, retorna (por referência) se houve erro ou não
    // - Retorno
    //    -> chave do item (em caso de erro, retorna -1)
    int item_get_chave_erro(ITEM *item, boolean *erro);




    // Alterar a chave de um item
    // - Parâmetros
    //    -> item: item a ter a chave alterada
    //    -> chave: nova chave
    // - Retorno
    //    -> se a chave foi alterada com sucesso
    boolean item_set_chave(ITEM *item, int chave);




    // Receber o conteúdo de um item
    // - Parâmetros
    //    -> item
    // - Retorno
    //    -> conteúdo do item (em caso de erro, retorna NULL)
    void *item_get_conteudo(ITEM *item);





    // Receber o conteúdo de um item
    // - Parâmetros
    //    -> item
    //    -> erro: se diferente de nulo, retorna (por referência) se houve erro ou não
    // - Retorno
    //    -> conteúdo do item (em caso de erro, retorna NULL)
    void *item_get_conteudo_erro(ITEM *item, boolean *erro);





    // Alterar o conteúdo de um item
    // - Parâmetros
    //    -> item: item a ter o conteúdo alterado
    //    -> conteudo: novo conteúdo, se for diferente de NULL
    // - Retorno
    //    -> se o conteúdo do item foi alterado com sucesso
    boolean item_set_conteudo(ITEM *item, void *conteudo);




#endif
