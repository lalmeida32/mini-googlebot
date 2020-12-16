#ifndef AVL_H
    #define AVL_H

    #include "item.h"
    #define boolean int
    #define TRUE 1
    #define FALSE 0
    #define max(a, b) ((a > b) ? a : b)
    typedef struct avl AVL;

    AVL *avl_criar(void);
    void avl_apagar(AVL **arvore);
    boolean avl_inserir(AVL *arvore, void *dados);
    boolean avl_remover(AVL *arvore, void *chave);
    void avl_print(AVL *arvore);
    void avl_set_dados_apagar(AVL *avl, void (*dados_apagar)(void **));
    void avl_set_dados_comparar(AVL *avl, int (*dados_comparar)(void *, void *));
    void avl_set_dados_imprimir(AVL *avl, void (*dados_imprimir)(void *));


#endif