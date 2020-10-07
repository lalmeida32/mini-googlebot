libs=src/TADitem.o src/TADlista.o src/TADsite.o src/opcoes.o src/uteis.o src/sites_file.o

source=src/opcoes.c src/sites_file.c src/TADitem.c src/TADlista.c src/TADsite.c src/uteis.c main.c

all:
	gcc -c src/TADitem.c -o src/TADitem.o -I./include
	gcc -c src/TADlista.c -o src/TADlista.o -I./include
	gcc -c src/TADsite.c -o src/TADsite.o -I./include
	gcc -c src/opcoes.c -o src/opcoes.o -I./include
	gcc -c src/uteis.c -o src/uteis.o -I./include
	gcc -c src/sites_file.c -o src/sites_file.o -I./include


	gcc -o executavel main.c $(libs) -I./include -Wall -Werror -Wextra -std=c99

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