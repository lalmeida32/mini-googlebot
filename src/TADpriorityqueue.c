#include<TADpriorityqueue.h>

typedef struct pqueue_no_t PQUEUE_NO;
struct pqueue_no_t {
    void *dados;
    PQUEUE_NO *esquerda;
    PQUEUE_NO *direita;
};

struct priority_queue_t {
    PQUEUE_NO *raiz;
    int quantidade;
    int altura;
    void (*dados_apagar)(void **);
    int (*dados_comparar)(void *, void *);
};

//cria no para que possa ser inserido na fila de prioridade
PQUEUE_NO *pqueue_no_criar(void * dados) {
    PQUEUE_NO *novo_no = (PQUEUE_NO *) malloc(sizeof(PQUEUE_NO));
    if (!novo_no) return NULL;

    novo_no->dados = dados;
    novo_no->esquerda = NULL;
    novo_no->direita = NULL;

    return novo_no;
}


//apaga no fa fila de prioridade
void pqueue_no_free(PQUEUE_NO **no, void (*dados_apagar) (void **)) {
    if (!no || !(*no)) return;

    if (dados_apagar) 
        dados_apagar(&(*no)->dados);
    (*no)->dados = NULL;
    (*no)->esquerda = NULL;
    (*no)->direita = NULL;

    free(*no);
    *no = NULL;
}

//cria tad fila de prioridade (priority queue)
PQUEUE *pqueue_criar() {
    PQUEUE *pqueue = (PQUEUE *) malloc(sizeof(PQUEUE));
    if (!pqueue) return NULL;
    
    pqueue->quantidade = 0;
    pqueue->raiz = NULL;
    pqueue->altura = -1;
    pqueue->dados_apagar = NULL;
    pqueue->dados_comparar = NULL;

    return pqueue;
}

void pqueue_set_dados_apagar(PQUEUE *pqueue, void (*dados_apagar) (void **)) {
    if (!pqueue) return;
    pqueue->dados_apagar = dados_apagar;
}

void pqueue_set_dados_comparar(PQUEUE *pqueue, int (*dados_comparar) (void *, void *)) {
    if (!pqueue) return;
    pqueue->dados_comparar = dados_comparar;
}

//liberando os nos da fila de prioridade (percorre a fila de prioridade usando a estrategia POS ORDEM)
void pqueue_free_nos_pos_ordem(PQUEUE_NO **raiz, void (*dados_apagar) (void **)) {
    if (!raiz || !(*raiz)) return;

    pqueue_free_nos_pos_ordem(&(*raiz)->esquerda, dados_apagar);
    pqueue_free_nos_pos_ordem(&(*raiz)->direita, dados_apagar);
    pqueue_no_free(raiz, dados_apagar);

}

//libera toda a fila de prioridade
void pqueue_free(PQUEUE **pqueue) {
    if (!pqueue || !(*pqueue)) return;

    pqueue_free_nos_pos_ordem(&(*pqueue)->raiz, (*pqueue)->dados_apagar);
    (*pqueue)->dados_apagar = NULL;
    (*pqueue)->dados_comparar = NULL;
    (*pqueue)->quantidade = 0;
    (*pqueue)->altura = -1;

    free(*pqueue);
    *pqueue = NULL;
}

//funcao auxilixar da pqueue_inserir
PQUEUE_NO *pqueue_inserir_recursiva(PQUEUE_NO *no_pai, int no_objetivo, int comprimento, void *dados, int (*dados_comparar) (void *, void *)) {
    
    // Chegou no nó destino
    if (comprimento == 0)
        return pqueue_no_criar(dados);

    const int constante_auxiliar = no_objetivo - (1 << comprimento);

    // Comprimento até o nó objetivo diminui a cada filho da chamada
    const int comprimento_filho = comprimento - 1;

    // Verifica se o próximo filho do percurso até o nó objetivo é o esquerdo ou direito
    const int seleciona_filho = constante_auxiliar >> comprimento_filho;

    // Encontra o índice do nó objetivo para a sub-árvore do nó filho
    const int no_objetivo_filho = (constante_auxiliar) | (1 << comprimento_filho);

    // Chamadas recursivas para encontrar o local do nó para inserir
    PQUEUE_NO *no_filho;
    if (seleciona_filho) {
        no_filho = pqueue_inserir_recursiva(no_pai->direita, no_objetivo_filho, comprimento_filho, dados, dados_comparar);
        no_pai->direita = no_filho;
    }
    else {
        no_filho = pqueue_inserir_recursiva(no_pai->esquerda, no_objetivo_filho, comprimento_filho, dados, dados_comparar);
        no_pai->esquerda = no_filho;
    }

    // Fix-up
    if (dados_comparar(no_filho->dados, no_pai->dados) > 0) {
        void *dados_temporario = no_filho->dados;
        no_filho->dados = no_pai->dados;
        no_pai->dados = dados_temporario;
    }

    return no_pai;
}

// Insere nó na max heap que é utilizada para a priority queue
void pqueue_inserir(PQUEUE *pqueue, void *dados) {
    if (!pqueue || !pqueue->dados_comparar) return;

    // Nó objetivo está no índice "quantidade + 1" pois, estamos considerando os índices começando em "1"
    const int no_objetivo = pqueue->quantidade + 1;
    // Captura altura da árvore com a inserção do novo nó
    const int comprimento_ate_no_objetivo = pqueue->altura + !(no_objetivo & pqueue->quantidade);

    // Insere o novo nó
    pqueue->raiz = pqueue_inserir_recursiva(pqueue->raiz, no_objetivo, comprimento_ate_no_objetivo, dados, pqueue->dados_comparar);

    // Atualiza a quantidade e a altura da pqueue
    pqueue->quantidade = no_objetivo;
    pqueue->altura = comprimento_ate_no_objetivo;
}

// Função auxiliar da pqueue_remover
PQUEUE_NO *pqueue_remover_recursiva(PQUEUE_NO *no_pai, int no_objetivo, int comprimento, PQUEUE_NO *raiz, void (*dados_apagar) (void **)) {

    // Chegou no nó destino
    if (comprimento == 0) {
        // Troca com nó raiz e remove
        raiz->dados = no_pai->dados;
        pqueue_no_free(&no_pai, dados_apagar);
        return NULL;
    }

    const int constante_auxiliar = no_objetivo - (1 << comprimento);

    // Comprimento até o nó objetivo diminui a cada filho da chamada
    const int comprimento_filho = comprimento - 1;

    // Verifica se o próximo filho do percurso até o nó objetivo é o esquerdo ou direito
    const int seleciona_filho = constante_auxiliar >> comprimento_filho;

    // Encontra o índice do nó objetivo para a sub-árvore do nó filho
    const int no_objetivo_filho = (constante_auxiliar) | (1 << comprimento_filho);


    // Chamadas recursivas para encontrar o nó_objetivo
    PQUEUE_NO *no_filho;
    if (seleciona_filho) {
        no_filho = pqueue_remover_recursiva(no_pai->direita, no_objetivo_filho, comprimento_filho, raiz, dados_apagar);
        no_pai->direita = no_filho;
    }
    else {
        no_filho = pqueue_remover_recursiva(no_pai->esquerda, no_objetivo_filho, comprimento_filho, raiz, dados_apagar);
        no_pai->esquerda = no_filho;    
    }

    return no_pai;
}

//restaura a ordem da heap
void pqueue_fix_down(PQUEUE_NO *no_pai, int (*dados_comparar) (void *, void *)) {
    PQUEUE_NO *troca = no_pai;
    PQUEUE_NO *esquerda = no_pai->esquerda;
    PQUEUE_NO *direita = no_pai->direita;
    
    if (esquerda && dados_comparar(troca->dados, esquerda->dados) < 0)
        troca = esquerda;
    if (direita && dados_comparar(troca->dados, direita->dados) < 0)
        troca = direita;
    
    // Se tiver algum filho maior que o pai e maior que o outro filho,
    // troca os dados de pai e filho e chama recursivamente pro próximo filho
    if (troca != no_pai) {
        void *dados_temporario = troca->dados;
        troca->dados = no_pai->dados;
        no_pai->dados = dados_temporario;
        pqueue_fix_down(troca, dados_comparar);
    }
}

//remove o no (do topo) fila de prioridade
void pqueue_remover(PQUEUE *pqueue) {

    if (!pqueue || pqueue->quantidade == 0 || !pqueue->dados_comparar) return;

    // Nó objetivo é o último pois será o nó a ter os dados trocados com a raiz e a ser removido
    const int no_objetivo = pqueue->quantidade;
    const int comprimento_ate_no_objetivo = pqueue->altura;

    // Troca os dados do último nó com os do nó raiz e remove último nó
    pqueue->raiz = pqueue_remover_recursiva(pqueue->raiz, no_objetivo, comprimento_ate_no_objetivo, pqueue->raiz, pqueue->dados_apagar);

    // Cálculo para quantidade e altura serem atualizadas
    pqueue->quantidade = no_objetivo - 1;
    pqueue->altura = comprimento_ate_no_objetivo - !(no_objetivo & pqueue->quantidade);

    if (pqueue->quantidade == 0) return;
    
    //restaurando a ordem da heap (max heap)
    pqueue_fix_down(pqueue->raiz, pqueue->dados_comparar);

}



void *pqueue_get_topo(PQUEUE *pqueue) {
    if (!pqueue || !pqueue->raiz) return NULL;
    return pqueue->raiz->dados;
}

int pqueue_get_quantidade(PQUEUE *pqueue) {
    if (!pqueue) return -1;
    return pqueue->quantidade; //retorna a quantidade de nos que possuem na pqueue
}
