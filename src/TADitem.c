#include<stdlib.h>
#include<stdio.h>

#include<TADitem.h>

// chave: identificador
// conteudo: ponteiro para o conteúdo do item
struct item_t {
    int chave;
    void *conteudo;
};





// Criar item na memória Heap
ITEM *item_criar(int chave, void *conteudo) {

    // aloca na heap
    ITEM *item = (ITEM *) malloc(sizeof(ITEM));
    if (!item) return NULL;


    // verifica erro nos parâmetros
    boolean error = FALSE;

    error = error || !item_set_chave(item, chave);
    error = error || !item_set_conteudo(item, conteudo);

    if (error) {
        free(item); return NULL;
    }

    // retorno
    return item;
}





// Apagar item da memória Heap e fixar o valor NULL na variável que o armazenava
void item_apagar(ITEM **item, void (*apagar_conteudo) (void **conteudo)) {

    // verifica se o item existe
    if (!(*item)) return;

    // apaga conteúdo
    if ((*item)->conteudo) {

        if (apagar_conteudo) {
            apagar_conteudo(&(*item)->conteudo);
        }

        else {
            free((*item)->conteudo);
            (*item)->conteudo = NULL;
        }
    }

    // apagando item
    free(*item);
    *item = NULL;
}





// Receber a chave de um item
int item_get_chave(ITEM *item, boolean *erro) {

    // caso de erro (item não existe)
    if (!item) {
        if (erro) *erro = TRUE;
        return -1;
    }

    // sem erros
    if (erro) *erro = FALSE;
    return item->chave;
}





// Alterar a chave de um item
boolean item_set_chave(ITEM *item, int chave) {

    // caso de erro (item não existe)
    if (!item) return FALSE;

    // sem erros
    item->chave = chave;
    return TRUE;
}





// Receber o conteúdo de um item
void *item_get_conteudo(ITEM *item, boolean *erro) {

    // caso de erro (item não existe)
    if (!item) {
        if (erro) *erro = TRUE;
        return NULL;
    }

    // sem erros
    if (erro) *erro = FALSE;
    return item->conteudo;
}





// Alterar o conteúdo de um item
boolean item_set_conteudo(ITEM *item, void *conteudo) {

    // caso de erro (item não existe ou conteudo == NULL)
    if (!item || !conteudo) return FALSE;

    // sem erros
    item->conteudo = conteudo;
    return TRUE;
}
