# Mini Googlebot

Projeto 1 da disciplina Algoritmos e Estruturas de Dados I - Prof. Rudinei Goularte

## Integrantes

Eduardo Vinícius Barbosa Rossi - 10716887

Lucas Ferreira de Almeida - 11262063

## Compilador utilizado

Neste trabalho utilizamos o compilador GCC no Linux.

## Instruções de uso do programa

- Primeiramente, tenha o compilador GCC instalado em seu computador.

- Execute o comando "make" no terminal de sua preferência para compilar o programa e gerar um executável.

- Execute o comando "make run" para executar o programa, após compilar.

  - Na tela inicial do programa aparecerá um menu com os comandos disponíveis para uso. Há um número que antecede cada um dos comandos; ao digitar este número e pressionar enter, o comando relativo àquele número será executado.

- Execute o comando "make clean" para limpar os arquivos gerados pela compilação do programa e pelo comando "make zip".

- Execute o comando "make zip" para criar um arquivo .zip contendo os diretórios e arquivos necessários para a compilação do programa.

## Justificativas

Para organizar os sites do arquivo "googlebot.txt", decidimos utilizar a estrutura de dados **lista**. Era necessário inserir e remover elementos em qualquer posição, por isso não foi conveniente implementar a estrutura **pilha**, visto que a pilha apenas permite acesso a um elemento de uma das extremidades.

Decidimos implementar a lista como **simplesmente encadeada** principalmente por não sabermos a quantidade de elementos que seriam inseridos. Além disso, para inserir (ou remover) um elemento no meio da lista, não há a necessidade de mover os elementos posteriores.

Implementamos a inserção de modo que a lista fique sempre **ordenada** pois, como é dito no enunciado, os sites devem ser ordenados pela chave.

Foi utilizada a **busca sequencial otimizada** pois não é possível realizar a **busca binária** em listas simplesmente encadeadas.

## Comentários adicionais

Tivemos que alterar o TAD item para que seja possível inserir um conteúdo (além da chave).

Como consequência, verificou-se a necessidade de adicionar uma função ao TAD lista para imprimir as chaves junto com o conteúdo de cada um dos itens.

Cada vez que o programa é executado, um arquivo "googlebot_out.txt" é gerado de acordo com as operações que foram executadas.
