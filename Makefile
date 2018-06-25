#PARA COMPILAR USE :make all
#PARA LIMPAR USE   :make clean


all: compile

compile: worldcup_2018.o
	gcc -g -o worldcup main_wc.c worldcup_2018.o

worldcup_2018.o: worldcup_2018.c
	gcc -g -c worldcup_2018.c

clean:
	rm -rf *o worldcup