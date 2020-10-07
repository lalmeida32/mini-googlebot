#include <stdlib.h>
#include <stdio.h>
#include <TADitem.h>
#include <TADlista.h>



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
    if((lista != NULL) && lista->fim != NULL){
        NO *no = (NO *) malloc(sizeof(NO));
        //se conseguirmos criar esse no, entao ainda tem memoria, 
        //logo a lista ainda nao esta cheia
        if (no != NULL){
            free(no);
            no = NULL;
            return (FALSE);
        }
        return(TRUE);
    }
    else
        return(FALSE);
}

int lista_tamanho(LISTA *lista){
    return(lista->tamanho);
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
            key = item_get_chave(item);

            if(key < item_get_chave(aux->item)){//o novo item que esta sendo eh menor que o inicio da lista
                pnovo->item = item;
                lista->inicio = pnovo;
                pnovo->proximo = aux;
            }
            else if(key > item_get_chave(lista->fim->item)){//item deve ser inserido no fim
                    lista->fim->proximo = pnovo;
                    pnovo->item = item;
                    pnovo -> proximo = NULL;
                    lista->fim = pnovo;
            } 
            else{//percorrendo a lista
                while(key > item_get_chave(aux->item)){
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
    

//realiza uma busca na lista a procura de um item
ITEM *lista_busca(LISTA *lista, int chave){
    NO *aux;

    if(lista != NULL){
        aux = lista->inicio;

        while(aux != NULL){
            if(item_get_chave(aux->item) == chave)
                return (aux->item);
            aux = aux->proximo;
        }
    }
    return NULL;
}

boolean lista_remover(LISTA *lista, int chave, void (*apagar_conteudo)(void **conteudo)) {
    NO *aux = NULL;
    NO *p = NULL;

    if(lista != NULL){
        p = lista->inicio;

        while(p != NULL && item_get_chave(p->item) != chave){
            //vamos percorrer toda a lista
            aux = p;
            p = p->proximo;
        }
        //item encotrado, vamos remove-lo
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
                //nesse caso p->proximo ja aponta pra NULL pq o ultimo sempre aponta pra NULL
            }
            item_apagar(&p->item, apagar_conteudo);
            free(p);
            lista->tamanho--;
            return(TRUE);
        }            
    }
    return(FALSE);
}

void lista_apagar(LISTA **lista, void (*apagar_conteudo)(void **))
{
    NO *aux = NULL;

    if( ((*lista) != NULL) && (!lista_vazia(*lista)) ){
        aux = (*lista)->inicio;

        while((*lista)->inicio != NULL){
            (*lista)->inicio = aux->proximo;
            item_apagar(&aux->item, apagar_conteudo);
            aux->proximo = NULL; 
            free(aux);
            aux = (*lista)->inicio;
        }
        free(*lista);
        (*lista) = NULL;
    }
}

void lista_imprimir(LISTA *lista)
{
    NO *p;
    if (lista != NULL)
    {
        p = lista->inicio;
        printf("\n");
        while (p != NULL)
        {
            printf("[%d]; ", item_get_chave(p->item));
            p = p->proximo;
        }
    }
    return;
}

// imprime a chave e o conteudo de cada um dos itens da lista em um arquivo
void lista_imprimir_conteudo(LISTA *lista, FILE *output, void (*imprimir_conteudo)(void *, FILE *), const char *format)
{
    // Exceções
    if (!lista || lista_vazia(lista) || !output || !imprimir_conteudo) return;

    // imprimir cada um dos itens na lista 
    NO *aux = lista->inicio;
    while (aux) {

        // imprime a chave
        // se o formato não for passado, usará "%d"
        if (format) fprintf(output, format, item_get_chave(aux->item));
        else fprintf(output, "%d", item_get_chave(aux->item));

        // imprime o conteúdo e um '\n' caso não seja o último item
        imprimir_conteudo(item_get_conteudo(aux->item), output);
        if (aux->proximo) fprintf(output, "\n");

        // próximo item
        aux = aux->proximo;
    }
}