#ifndef _PRIORITY_QUEUE_H_
    #define _PRIORITY_QUEUE_H_

    #include<stdio.h>
    #include<stdlib.h>

    typedef struct priority_queue_t PQUEUE;


    // Criar uma fila de prioridade na memória Heap
    // - Parâmetros
    //      void
    // - Retorno
    //    -> ponteiro para a fila de prioridade, NULL se der erro
    PQUEUE *pqueue_criar();


    // "setando" o dado para ser apagado da memoria
    // - Parâmetros
    //    -> pqueue: fila de prioridade esoclhida
    //    -> funcao que apaga os dados dentro de cada no da arvore
    // - Retorno
    //      void
    void pqueue_set_dados_apagar(PQUEUE *pqueue, void (*dados_apagar) (void **));


    // "setando" os dados para serem comparados
    // - Parâmetros
    //    -> pqueue: fila de prioridade esoclhida
    //    -> funcao que compara os dados dentro de cada no da arvore
    // - Retorno
    //      void
    void pqueue_set_dados_comparar(PQUEUE *pqueue, int (*dados_comparar) (void *, void *));


    // Libera a fila de prioridade da memória Heap
    // - Parâmetros
    //    -> pqueue: endereco para a fila de prioridade que deseja liberar
    //    -> funcao que apaga os dados dentro de cada no da arvore
    // - Retorno
    //      void
    void pqueue_free(PQUEUE **pqueue);

    
    // Insere um dado na fila de prioridade
    // - Parâmetros
    //    -> pqueue: fila de prioridade na qual deseja fazer a insercao
    //    -> dados: dado que deseja inserir na fila de prioridade
    // - Retorno
    //      void
    void pqueue_inserir(PQUEUE *pqueue, void *dados);


    // Remove dado da fila de prioridade
    // - Parâmetros
    //    -> pqueue: fila de prioridade que deseja remover o dado
    // - Retorno
    //      void
    void pqueue_remover(PQUEUE *pqueue);


    // Recebe o dado do topo da fila de prioridade
    // - Parâmetros
    //    -> pqueue: fila de prioridade que deseja recuperar o topo
    // - Retorno
    //      void
    void *pqueue_get_topo(PQUEUE *pqueue);


    // Recebe a quantidade de dados que tem na fila de prioridade
    // - Parâmetros
    //    -> pqueue: endereco para a fila de prioridade que deseja liberar
    // - Retorno
    //      numero de dados presentes na fila de prioridade
    int pqueue_get_quantidade(PQUEUE *pqueue);

#endif