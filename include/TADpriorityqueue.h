#ifndef _PRIORITY_QUEUE_H_
    #define _PRIORITY_QUEUE_H_

    #include<stdio.h>
    #include<stdlib.h>

    typedef struct priority_queue_t PQUEUE;

    PQUEUE *pqueue_criar();
    void pqueue_set_dados_apagar(PQUEUE *pqueue, void (*dados_apagar) (void **));
    void pqueue_set_dados_comparar(PQUEUE *pqueue, int (*dados_comparar) (void *, void *));
    void pqueue_free(PQUEUE **pqueue);
    void pqueue_inserir(PQUEUE *pqueue, void *dados);
    void pqueue_remover(PQUEUE *pqueue);
    void *pqueue_get_topo(PQUEUE *pqueue);
    int pqueue_get_quantidade(PQUEUE *pqueue);

#endif