all:
	gcc -c src/item.c -o src/item.o -I./includes
	gcc -c src/lista.c -o src/lista.o -I./includes
	gcc -c src/site.c -o src/site.o -I./includes

	ar rcs libitem.a src/item.o
	ar rcs liblista.a src/lista.o
	ar rcs libsite.a src/site.o
	gcc -o executavel main.c -L. -litem -llista -lsite -I./includes

run:
	./executavel
