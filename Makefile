libs=src/TADitem.o src/TADlista.o src/TADsite.o src/opcoes.o src/uteis.o src/sites_file.o

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
	rm -f src/*.o
	rm -f ./executavel
	rm -f googlebot_out.txt
