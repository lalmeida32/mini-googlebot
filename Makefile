libs=-L. -lTADitem -lTADlista -lTADsite -lopcoes -luteis -lsites_file

source=src/opcoes.c src/sites_file.c src/TADitem.c src/TADlista.c src/TADsite.c src/uteis.c main.c

all:
	gcc -c src/TADitem.c -o src/TADitem.o -I./include
	gcc -c src/TADlista.c -o src/TADlista.o -I./include
	gcc -c src/TADsite.c -o src/TADsite.o -I./include
	gcc -c src/opcoes.c -o src/opcoes.o -I./include
	gcc -c src/uteis.c -o src/uteis.o -I./include
	gcc -c src/sites_file.c -o src/sites_file.o -I./include

	ar rcs libTADitem.a src/TADitem.o
	ar rcs libTADlista.a src/TADlista.o
	ar rcs libTADsite.a src/TADsite.o
	ar rcs libopcoes.a src/opcoes.o
	ar rcs libuteis.a src/uteis.o
	ar rcs libsites_file.a src/sites_file.o

	gcc -o executavel main.c $(libs) -I./include

run:
	./executavel

clean:
	rm *.a
	rm src/*.o
	rm ./teste
	rm ./debugfile
	rm ./executavel

debug:
	gcc $(source) -I./include -o debugfile -Wall -Wextra -std=c99