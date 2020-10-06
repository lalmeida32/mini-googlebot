#include<stdio.h>
#include<stdlib.h>
#include<TADsite.h>

int main(void) {
    printf("%d %d %d %d", site_get_nome_max_length(), site_get_link_max_length(), site_get_palavra_chave_max_length(), site_get_max_count_palavras_chave());

    return 0;
}