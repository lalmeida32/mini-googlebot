#include <stdlib.h>
#include <stdio.h>
#include <item.h>
#include <lista.h>



typedef struct no_ NO; 

struct no_{
    ITEM *item;
    NO *proximo;
};

struct lista_{ 
    NO *inicio;
    NO *fim;    
    int tamanho;  
};



NO *no_criar(ITEM *item){
   NO *n = (NO *) malloc(sizeof(NO));
      
   if ((n != NULL) && (item != NULL)){
      n->item = item;
      n->proximo = NULL;
      return(n);
   }
   else
       return(NULL);
}


LISTA *lista_criar(void){
          
    LISTA *lista = (LISTA *) malloc(sizeof(LISTA));
    if(lista != NULL) {
        lista->inicio = NULL;
        lista->fim = NULL;
        lista->tamanho = 0;
    }

   return (lista);
}

  
boolean lista_vazia(LISTA *lista){
    if((lista != NULL) && lista->inicio == NULL)
        return(TRUE);
    return(FALSE);
}


boolean lista_cheia(LISTA *lista){
    NO *no = (NO *) malloc(sizeof(NO));
    if (no != NULL){
       free(no);
       no = NULL;
       return (FALSE);
    }
    return(TRUE);
}

int lista_tamanho(LISTA *lista){
    return(lista->tamanho);
}

void lista_imprimir(LISTA *lista){
     int i;
     NO *p;
     if (lista != NULL){
        p = lista->inicio;
        printf("\n");
        while(p != NULL){
            printf("[%d]; ", item_get_chave(p->item, NULL));
            p = p->proximo;
        } 
     }
     return;
}

//Insere um novo no de maneira ordenada na lista.
boolean lista_inserir(LISTA *lista, ITEM *item){

    if((!lista_cheia(lista)) && (lista != NULL)){
        int key = 0;
        NO *pnovo = (NO *) malloc(sizeof (NO));
        NO *aux = NULL;
        NO *p = NULL;
        
        if(lista->inicio == NULL){
            pnovo->item = item;
            lista->inicio = pnovo;
            pnovo->proximo = NULL;
            lista->fim = pnovo;
        }
        else{
            aux = lista->inicio;
            key = item_get_chave(item, NULL);

            if(key < item_get_chave(aux->item, NULL)){//o novo item que esta sendo eh menor que o inicio da lista
                pnovo->item = item;
                lista->inicio = pnovo;
                pnovo->proximo = aux;
            }
            else if(key > item_get_chave(lista->fim->item, NULL)){//item deve ser inserido no fim
                    lista->fim->proximo = pnovo;
                    pnovo->item = item;
                    pnovo -> proximo = NULL;
                    lista->fim = pnovo;
            } 
            else{//percorrendo a lista
                while(key > item_get_chave(aux->item, NULL)){
                    p = aux;
                    aux = aux->proximo;
                }
                pnovo->item = item;
                p->proximo = pnovo;
                pnovo->proximo = aux;
            }
        }
        lista->tamanho++;
        return (TRUE);
    }
    else
        return (FALSE);
}
    


ITEM *lista_busca(LISTA *lista, int chave){
    NO *aux;

    if(lista != NULL){
        aux = lista->inicio;

        while(aux != NULL){
            if(item_get_chave(aux->item, NULL) == chave)
                return (aux->item);
            aux = aux->proximo;
        }
    }
    return NULL;
}

boolean lista_remover(LISTA *lista, int chave){
    NO *aux = NULL;
    NO *p = NULL;

    if(lista != NULL){
        p = lista->inicio;

        while(p != NULL && item_get_chave(p->item, NULL) != chave){
            //vamos percorrer toda a lista
            aux = p;
            p = p->proximo;
        }
        //item encotrada, vamos remove-lo
        if(p != NULL){
            if(p == lista->inicio){
                lista->inicio = p->proximo;
                p->proximo = NULL;
            }
            else{
                aux->proximo = p->proximo;
                p->proximo = NULL;
            }
            if(p == lista->fim){
                lista->fim = aux;
                //p->proximo ja apontava pra NULL pq o ultimo sempre aponta pra NULL
            }
            free(p);
            lista->tamanho--;
            return(TRUE);
        }
        else
            return(FALSE);
    }
}

void lista_apagar(LISTA **ptr){
    NO *aux = NULL;

    if( ((*ptr) != NULL) && (!lista_vazia(*ptr)) ){
        aux = (*ptr)->inicio;

        while((*ptr)->inicio != NULL){
            (*ptr)->inicio = aux->proximo;
            item_apagar(&aux->item);
            aux->proximo = NULL; 
            free(aux);
            aux = NULL;
        }
        free(*ptr);
        (*ptr) = NULL;
    }
}


