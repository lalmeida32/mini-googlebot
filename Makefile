all:
	gcc -c src/TADitem.c -o src/TADitem.o -I./include
	gcc -c src/TADlista.c -o src/TADlista.o -I./include
	gcc -c src/TADsite.c -o src/TADsite.o -I./include
	gcc -c src/opcoes.c -o src/opcoes.o -I./include
	gcc -c src/sites_file.c -o src/sites_file.o -I./include

	ar rcs libTADitem.a src/TADitem.o
	ar rcs libTADlista.a src/TADlista.o
	ar rcs libTADsite.a src/TADsite.o
	ar rcs libopcoes.a src/opcoes.o
	ar rcs libsites_file.a src/sites_file.o

	gcc -o executavel main.c -L. -litem -llista -lsite -I./include

run:
	./executavel

clean:
	-rm *.a
	-rm src/*.o