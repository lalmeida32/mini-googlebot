#include <stdio.h>
#include <stdlib.h>
#include <TADavl.h>

typedef struct avl_no AVL_NO;
struct avl_no{
    void *dados;
    AVL_NO *filho_esquerdo;
    AVL_NO *filho_direito;
    int altura;
};

struct avl{
    AVL_NO *raiz;
    int profundidade;
    void (*dados_apagar)(void **);
    int (*dados_comparar)(void *, void *);
    void (*dados_imprimir)(void *);
};



AVL *avl_criar(void){
    AVL *avl = (AVL *) malloc(sizeof(AVL));
    if(avl != NULL){
        avl->raiz = NULL;
        avl->profundidade = -1;
        avl->dados_apagar = NULL;
        avl->dados_comparar = NULL;
        avl->dados_imprimir = NULL;
    }
    return avl;
}


void avl_set_dados_apagar(AVL *avl, void (*dados_apagar)(void **)){
    if(avl != NULL){
        avl->dados_apagar = dados_apagar;
    }
}


void avl_set_dados_comparar(AVL *avl, int (*dados_comparar)(void *, void *)){
    if(avl != NULL){
        avl->dados_comparar = dados_comparar;
    }
}


void avl_set_dados_imprimir(AVL *avl, void (*dados_imprimir)(void *)){
    if(avl != NULL){
        avl->dados_imprimir = dados_imprimir;
    }
}


//funcao auxiliar para a avl_apagar
void avl_apagar_aux(AVL_NO **raiz, void (*dados_apagar)(void **)){
    if (*raiz != NULL){
        avl_apagar_aux(&(*raiz)->filho_esquerdo, dados_apagar);
        avl_apagar_aux(&(*raiz)->filho_direito, dados_apagar);

        if(dados_apagar != NULL)
            dados_apagar(&(*raiz)->dados);
        free(*raiz);
        *raiz = NULL;
    } 
} 

//apaga toda a AVL
void avl_apagar(AVL **arvore){
    avl_apagar_aux(&(*arvore)->raiz, (*arvore)->dados_apagar);

    free(*arvore);
    *arvore = NULL;
} 


AVL_NO *cria_no(void *dados){
    AVL_NO *no = (AVL_NO *) malloc(sizeof(AVL_NO));
    if(no != NULL){
        no->altura = 0;
        no->filho_esquerdo = NULL;
        no->filho_direito = NULL;
        no->dados = dados;
    }
    return no;
}

//recupera a altura de determinado no
int avl_altura_no(AVL_NO *raiz){
    if(raiz == NULL){
        return -1;
    }
    else{
        return raiz->altura;
    }
}


AVL_NO *rotacao_direita(AVL_NO *a){
    AVL_NO *b = a->filho_esquerdo;
    a->filho_esquerdo = b->filho_direito;
    b->filho_direito = a;

    a->altura = max(avl_altura_no(a->filho_esquerdo), avl_altura_no(a->filho_direito)) + 1;
    b->altura = max(avl_altura_no(b->filho_esquerdo), a->altura) + 1;

    return b;
}


AVL_NO *rotacao_esquerda(AVL_NO *a){
    AVL_NO *b = a->filho_direito;
    a->filho_direito = b->filho_esquerdo;
    b->filho_esquerdo = a;

    a->altura = max(avl_altura_no(a->filho_esquerdo), avl_altura_no(a->filho_direito)) + 1;
    b->altura = max(avl_altura_no(b->filho_direito), a->altura) + 1;

    return b;
}


AVL_NO *rotacao_esquerda_direita(AVL_NO *a){
    a->filho_esquerdo = rotacao_esquerda(a->filho_esquerdo);
    return rotacao_direita(a);
}


AVL_NO *rotacao_direita_esquerda(AVL_NO *a){
    a->filho_direito = rotacao_direita(a->filho_direito);
    return rotacao_esquerda(a);
}


AVL_NO *avl_inserir_no(AVL_NO *raiz, void *dados, int (*dados_comparar)(void *, void *)){
    if(raiz == NULL){//se a avl for vazia criamos um no e inserimos
        raiz = cria_no(dados);
    }
    //percorrendo a sub arvore direita
    else if(dados_comparar(dados, raiz->dados) > 0){
        raiz->filho_direito = avl_inserir_no(raiz->filho_direito, dados, dados_comparar);
    }
    //sub arvore esquerda
    else if(dados_comparar(dados, raiz->dados) < 0){
        raiz->filho_esquerdo = avl_inserir_no(raiz->filho_esquerdo, dados, dados_comparar);
    }

    raiz->altura = max(avl_altura_no(raiz->filho_esquerdo), avl_altura_no(raiz->filho_direito)) + 1;
    
    //verificando se precisa fazer alguma rotacao
    if(avl_altura_no(raiz->filho_esquerdo) - avl_altura_no(raiz->filho_direito) == -2)
        if(dados_comparar(dados, raiz->filho_direito->dados) > 0)
            raiz = rotacao_esquerda(raiz);
        else
            raiz = rotacao_direita_esquerda(raiz);
    
    if (avl_altura_no(raiz->filho_esquerdo) - avl_altura_no(raiz->filho_direito) == 2)
        if(dados_comparar(dados, raiz->filho_esquerdo->dados) < 0)
            raiz = rotacao_direita(raiz);
        else
            raiz = rotacao_esquerda_direita(raiz);

    return raiz;
}

//insere um no na AVL
boolean avl_inserir(AVL *arvore, void *dados){
    if(arvore->dados_comparar == NULL)
        return FALSE;
    return ((arvore->raiz = avl_inserir_no(arvore->raiz, dados,arvore->dados_comparar)) != NULL);
}

//procura o valor maximo da sub-arvore esquerda e troca com a raiz
void troca_max_esq(AVL_NO *troca, AVL_NO *raiz, AVL_NO *ant){
    if(troca->filho_direito != NULL)
        troca_max_esq(troca->filho_direito, raiz, troca);
        return;
    if(raiz == ant)
        ant->filho_esquerdo = troca->filho_esquerdo;
    else
        ant->filho_direito = troca->filho_esquerdo;

    raiz->dados = troca->dados;
    free(troca);
    troca = NULL;
}


void *avl_busca_aux(AVL_NO *raiz, void *chave, int (*dados_comparar) (void *, void *)) {
    if (!raiz) return NULL;

    if (dados_comparar(chave, raiz->dados) < 0)
        return avl_busca_aux(raiz->filho_esquerdo, chave, dados_comparar);
    if (dados_comparar(chave, raiz->dados) > 0)
        return avl_busca_aux(raiz->filho_direito, chave, dados_comparar);
    return raiz->dados;
}

//busca um elemento na AVL
void *avl_busca(AVL *avl, void *chave) {
    if (!avl || !avl->dados_comparar) return NULL;

    return avl_busca_aux(avl->raiz, chave, avl->dados_comparar);
}


AVL_NO *avl_remover_aux(AVL_NO **raiz, void *chave, void (*dados_apagar)(void **), int (*dados_comparar)(void *, void *)){
    AVL_NO *p;
    if(*raiz == NULL)//arvore vazia
        return NULL;
    else if(dados_comparar(chave, (*raiz)->dados) == 0){
        if((*raiz)->filho_esquerdo == NULL || (*raiz)->filho_direito == NULL){//se o no nao tiver filho ou tiver apenas 1
            p = *raiz;
            if((*raiz)->filho_esquerdo == NULL)
                *raiz = (*raiz)->filho_direito;
            else
                *raiz = (*raiz)->filho_esquerdo;
            if(dados_apagar != NULL)
                dados_apagar(&(p)->dados);
            free(p);
            p = NULL;
        }
        //se o no tiver 2 filhos
        else
            troca_max_esq((*raiz)->filho_esquerdo, (*raiz), (*raiz));
    }//realizando a remocao
    else if(dados_comparar(chave, (*raiz)->dados) < 0)
        (*raiz)->filho_esquerdo = avl_remover_aux(&(*raiz)->filho_esquerdo, chave, dados_apagar, dados_comparar);
    else if(dados_comparar(chave, (*raiz)->dados) > 0)
        (*raiz)->filho_direito = avl_remover_aux(&(*raiz)->filho_direito, chave, dados_apagar, dados_comparar);
    
    if(*raiz != NULL){//realizando as rotacoes se necessario
        (*raiz)->altura = max(avl_altura_no((*raiz)->filho_esquerdo), avl_altura_no((*raiz)->filho_direito)) + 1;

        if(avl_altura_no((*raiz)->filho_esquerdo) - avl_altura_no((*raiz)->filho_direito) == -2){
            if(avl_altura_no((*raiz)->filho_direito->filho_esquerdo) - avl_altura_no((*raiz)->filho_direito->filho_direito) <= 0)
                //rotacao esquerda
                *raiz = rotacao_esquerda(*raiz);
            else
                *raiz = rotacao_direita_esquerda(*raiz);
        }
        if(avl_altura_no((*raiz)->filho_esquerdo) - avl_altura_no((*raiz)->filho_direito) == 2){
            if(avl_altura_no((*raiz)->filho_esquerdo->filho_esquerdo) - avl_altura_no((*raiz)->filho_esquerdo->filho_direito) >= 0)
                *raiz = rotacao_direita(*raiz);
            else
                *raiz = rotacao_esquerda_direita(*raiz);
        }
    }
    return *raiz;

}

//remove um no da AVL, dada uma chave passada pelo usario
boolean avl_remover(AVL *arvore, void *chave){
    if(arvore->dados_comparar == NULL)
        return FALSE;
    return((arvore->raiz = avl_remover_aux(&arvore->raiz, chave, arvore->dados_apagar, arvore->dados_comparar)) != NULL);
}


//percorre a avl em ordem para printar os seus nos
void alv_imprimir_em_ordem(AVL_NO *raiz, void(*dados_imprimir)(void *)){
    if (raiz != NULL){
        alv_imprimir_em_ordem(raiz->filho_esquerdo, dados_imprimir);
        dados_imprimir(raiz->dados);
        alv_imprimir_em_ordem(raiz->filho_direito, dados_imprimir);
    }
}

void avl_print(AVL *arvore){
    if (arvore != NULL && arvore->dados_imprimir != NULL){ 
        alv_imprimir_em_ordem(arvore->raiz, arvore->dados_imprimir);
    }
    return;
}



