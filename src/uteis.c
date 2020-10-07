#include<stdio.h>
#include<stdlib.h>

// Limpa o arquivo até '\n' ou fim de arquivo
void flush(FILE *input) {
    char c;
    do {
        c = fgetc(input);
    } while(c != '\n' && !feof(input));
}

// Lê inteiro de um arquivo e limpa até '\n' ou fim de arquivo
int ler_integer(FILE *input) {
    int integer;

    fscanf(input, "%d", &integer);
    flush(input);

    return integer;
}

// Lê string até '\n', fim de arquivo ou comprimento máximo atingido
char *ler_string(int length, FILE *input)
{
    // alocação de memória para string
    char *string = (char *)malloc(length * sizeof(char));
    int pos = 0;
    char c;

    // ler até '\n', fim de arquivo ou o comprimento máximo ser atingido
    do
    {
        c = fgetc(input);
        string[pos++] = c;
    } while (c != '\n' && !feof(input) && pos < length);
    string[pos - 1] = '\0';

    // limpando arquivo até '\n' ou fim de arquivo
    // PS: função flush não funciona nesse caso, pois há necessidade de uma verificação
    // inicial antes de entrar no loop
    while (c != '\n' && !feof(input))
    {
        c = fgetc(input);
    }

    return string;
}