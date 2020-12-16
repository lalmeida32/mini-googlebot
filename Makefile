objs=obj/TADitem.o obj/TADlista.o obj/TADsite.o obj/opcoes.o obj/uteis.o obj/sites_file.o obj/TADpriorityqueue.o obj/TADavl.o obj/TADpchave.o

all:
	gcc -c src/TADitem.c -o obj/TADitem.o -I./include
	gcc -c src/TADlista.c -o obj/TADlista.o -I./include
	gcc -c src/TADsite.c -o obj/TADsite.o -I./include
	gcc -c src/TADpriorityqueue.c -o obj/TADpriorityqueue.o -I./include
	gcc -c src/TADavl.c -o obj/TADavl.o -I./include
	gcc -c src/opcoes.c -o obj/opcoes.o -I./include
	gcc -c src/uteis.c -o obj/uteis.o -I./include
	gcc -c src/sites_file.c -o obj/sites_file.o -I./include
	gcc -c src/TADpchave.c -o obj/TADpchave.o -I./include



	gcc -o executavel main.c $(objs) -I./include -Wall -Werror -Wextra -std=c99

run:
	./executavel

clean:
	rm -f obj/*.o
	rm -f ./executavel
	rm -f googlebot_out.txt
	rm -f *.zip

zip:
	zip -r mini-googlebot.zip src/*.c include/*.h ./googlebot.txt ./Makefile ./main.c ./README.md ./obj