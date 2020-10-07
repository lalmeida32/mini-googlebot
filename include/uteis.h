#ifndef _UTEIS_H_
    #define _UTEIS_H_

    #include<stdio.h>

    // Copia string até max_length ser atingido ou até '\0'
    // - Parâmetros
    //    -> destination: string a ser modificada
    //    -> source: string a ser copiada para destination
    //    -> max_length: comprimento máximo aceito
    // - Retorno
    //    -> não tem
    void set_string(char *destination, const char *source, int max_length);

    // Limpa o arquivo até '\n' ou fim de arquivo
    // - Parâmetros
    //    -> input: arquivo que será limpo
    // - Retorno
    //    -> não tem
    void flush(FILE *input);

    // Lê inteiro de um arquivo e limpa até '\n' ou fim de arquivo
    // - Parâmetros
    //    -> input: arquivo de onde o inteiro será lido
    // - Retorno
    //    -> inteiro lido
    int ler_integer(FILE *input);

    // Lê string até '\n', fim de arquivo ou comprimento máximo atingido
    // - Parâmetros
    //    -> length: comprimento máximo
    //    -> input: arquivo de onde a string será lida
    // - Retorno
    //    -> string lida (alocada dinamicamente na memória HEAP)
    char *ler_string(int length, FILE *input);

#endif