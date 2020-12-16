#ifndef _SITE_H_
    #define _SITE_H_

    #define TRUE 1
    #define FALSE 0
    #define boolean int

    #include<stdio.h>

    typedef struct site_t SITE;






    // Cria a estrutura site na memória HEAP
    // - Parâmetros
    //    -> não tem
    // - Retorno
    //    -> NULL caso ocorra algum erro
    //    -> ponteiro para estrutura site caso contrário
    SITE *site_criar();

    // Desaloca a memória HEAP alocada pelo site
    // - Parâmetros
    //    -> input: endereço do ponteiro da estrutura SITE a ser apagada
    // - Retorno
    //    -> não tem
    void site_apagar(SITE **site);






    // Retorna o comprimento máximo da propriedade "nome" da estrutura SITE
    int site_get_nome_max_length();

    // Retorna o comprimento máximo da propriedade "link" da estrutura SITE
    int site_get_link_max_length();

    // Retorna o comprimento máximo das palavras-chave da estrutura SITE
    int site_get_palavra_chave_max_length();

    // Retorna a quantidade máxima de palavras-chave que a estrutura SITE pode ter
    int site_get_palavras_chave_max_count();

    // Retorna a quantidade de palavras-chave que existem em determinada estrutura SITE
    int site_get_num_palavras_chave(SITE *site);



    char *site_get_palavra_chave(SITE *site, int index);



    // Altera a propriedade "nome" de uma estrutura SITE
    // - Parâmetros
    //    -> site: ponteiro de estrutura SITE que terá nome alterado
    //    -> nome: novo nome
    // - Retorno
    //    -> TRUE se foi alterada com sucesso; FALSE caso contrário
    boolean site_set_nome(SITE *site, const char *nome);

    // Altera a propriedade "relevância" de uma estrutura SITE
    // - Parâmetros
    //    -> site: ponteiro de estrutura SITE que terá relevância alterada
    //    -> relevancia: novo valor para relevância
    // - Retorno
    //    -> TRUE se foi alterada com sucesso; FALSE caso contrário
    boolean site_set_relevancia(SITE *site, int relevancia);

    // Altera a propriedade "link" de uma estrutura SITE
    // - Parâmetros
    //    -> site: ponteiro de estrutura SITE que terá link alterado
    //    -> link: novo link
    // - Retorno
    //    -> TRUE se foi alterada com sucesso; FALSE caso contrário
    boolean site_set_link(SITE *site, const char *link);

    // Adiciona uma palavra-chave à uma estrutura SITE, se for possível
    // - Parâmetros
    //    -> site: ponteiro de estrutura SITE que terá palavra-chave adicionada
    //    -> palavra-chave: nova palavra-chave a ser adicionada
    // - Retorno
    //    -> TRUE se foi alterada com sucesso; FALSE caso contrário
    boolean site_add_palavra_chave(SITE *site, const char *palavra_chave);





    // Ler e alterar nome de um determinado site
    // - Parâmetros
    //    -> site: ponteiro de estrutura SITE que terá nome alterado
    //    -> input: arquivo de onde será lido o novo nome
    // - Retorno
    //    -> não tem
    void site_read_nome(SITE *site, FILE *input);

    // Ler e alterar relevância de um determinado site
    // - Parâmetros
    //    -> site: ponteiro de estrutura SITE que terá relevância alterada
    //    -> input: arquivo de onde será lido o novo valor para relevância
    // - Retorno
    //    -> não tem
    void site_read_relevancia(SITE *site, FILE *input);

    // Ler e alterar link de um determinado site
    // - Parâmetros
    //    -> site: ponteiro de estrutura SITE que terá link alterado
    //    -> input: arquivo de onde será lido o novo link
    // - Retorno
    //    -> não tem
    void site_read_link(SITE *site, FILE *input);

    // Ler e adicionar palavra-chave à determinado site
    // - Parâmetros
    //    -> site: ponteiro de estrutura SITE que terá palavra-chave adicionada
    //    -> input: arquivo de onde será lido a nova palavra-chave
    // - Retorno
    //    -> não tem
    void site_read_palavra_chave(SITE *site, FILE *input);



    // Imprime em um arquivo as informações sobre determinado site no formato CSV
    // Segue o formato que será impresso:
    //   NomeDoSite,400,https://www.linkdosite.com/,palavrachave1,palavrachave2
    //
    // - Parâmetros
    //    -> site: ponteiro de estrutura SITE que será impressa no arquivo
    //    -> output: arquivo de onde será impresso o site
    // - Retorno
    //    -> não tem
    void site_imprimir(SITE *site, FILE *output);


    int site_comparar_relevancia(void *dados1, void *dados2);


#endif
