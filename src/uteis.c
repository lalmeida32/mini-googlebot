#include<stdio.h>
#include<stdlib.h>

void flush(FILE *input) {
    char c;
    do {
        c = fgetc(input);
    } while(c != '\n');
}

char *ler_string(int length, FILE *input)
{

    char *string = (char *)malloc(length * sizeof(char));
    int pos = 0;
    char c;

    do
    {
        c = fgetc(input);
        string[pos++] = c;
    } while (c != '\n' && !feof(input) && pos < length);
    string[pos - 1] = '\0';

    while (c != '\n' && !feof(input))
    {
        c = fgetc(input);
    }

    return string;
}